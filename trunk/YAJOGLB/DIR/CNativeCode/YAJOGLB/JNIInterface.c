/*
  Helper routines for calling JNI functions.
 
  Copyright 2001, Robert Allan Zeh (razeh@yahoo.com)
  7346 Lake Street #3W
  River Forest, IL 60305
 
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA

*/

/*
 * JNIInterface.c
 *
 * $Id: JNIInterface.c,v 1.6 2001/07/06 23:40:05 razeh Exp $
 *
 * This module handles convience routines for dealing with the Java
 * Native Interface.
 *
 */


#include "cygnusFixes.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"


typedef enum _checkArrayResults { isInstanceOf, isNotInstanceOf, error }
 checkArrayResults;

 struct javaArrayAccessDescription { 
	char *className;            /* The java class name. */
	char *errorDescription;     /* The error to print if we can't find the class name. */
	void *(JNICALL *accessor)();
	};

 struct javaArrayReleaseDescription {
	 char *className;          /* The java class name. */
	 char *errorDescription;   /* The error to print out if we have trouble with class name. */
	 void (JNICALL *releaser)();
 };


/* Lookup the static integer field in class and store the return value
   in fieldValue.  If there is a problem getting the value fieldValue
   is not changed and 1 is returned.  Otherwise 0 is returned, and the
   field value is stored in *fieldValue.  */
int lookupStaticIntField(JNIEnv *env, jclass class,
						 const char *fieldName, jint *fieldValue)
{
  jfieldID field;
  int returnCode = 0;

  field = (*env)->GetStaticFieldID(env, class, fieldName, "I");
  if (0 == field) {
	  handleError(env, OPENGL_NATIVE_EXCEPTION, "Unable to get static field ID.");
      returnCode = 1;
  } else {
	  if (NULL != fieldValue) {
		  *fieldValue = (*env)->GetStaticIntField(env, class, field);
	  } else {
		  handleError(env, OPENGL_NATIVE_EXCEPTION, "lookupStaticIntField was passed a null field value.");
		  returnCode = 1;
	  }
  }

  return returnCode;
}



/* Lookup a integer field in object and store the return value in
   fieldValue.	If there is a problem getting the value fieldValue is
   not changed, an exception is thrown and 1 is returned. Otherwise 0 
   is returned, and the fieldValue is stored in *fieldValue. */
int lookupIntField(JNIEnv *env, jobject object,
		   const char *fieldName, jint *fieldValue)
{
  jfieldID field;
  jclass   objectClass;
  int      returnCode = 0;

  objectClass = (*env)->GetObjectClass(env, object);

  field = (*env)->GetFieldID(env, objectClass, fieldName, "I");
  if (field == 0) {
    handleError(env, OPENGL_NATIVE_EXCEPTION,
		"Unable to get field ID");
    returnCode = 1;
  } else {
    *fieldValue = (*env)->GetIntField(env, object, field);
  }

  return returnCode;
}



/* This performs the same functions as lookupStaticIntField, but
   returns the integer field instead of placing it in a variable.  If
   there is a problem with the field lookup an exception is thrown inside of
   lookupStaticIntField(). */
int staticIntField(JNIEnv *env, jclass class,
		   const char *fieldName)
{
  jint fieldValue = -1;

  lookupStaticIntField(env, class, fieldName, &fieldValue);

  return fieldValue;
}



static jclass 
getFullyQualifiedClass(JNIEnv *env,
		       const char *className,     /* The class to lookup. */
		       const char *exceptionName, /* The exception to throw. */
		       const char *errorString)   /* The error to print. */
{
  jclass class;

  class = (*env)->FindClass(env, className);
  if (class == 0) {
	  handleError(env, exceptionName, errorString);
	  return NULL;
  }
  return class;
}



/* This returns the class name handed to it. */
jclass getClass(JNIEnv *env,
		const char *className,     /* The class to lookup. */
		const char *errorString)   /* The error to print. */
{
  return getFullyQualifiedClass(env, className, OPENGL_NATIVE_EXCEPTION,
				errorString);
}


/* This returns a methodID for the given class, method name and method 
   signature.  It will return NULL after calling handleError() if
   something went wrong, and the methodID if things worked out properly. */
jmethodID getStaticMethodID(JNIEnv *env, jclass class,
							const char *methodName,
							const char *methodSignature,
							const char *errorMessage)
{
	jmethodID methodID = NULL;

	methodID = (*env)->GetStaticMethodID(env, class, methodName, methodSignature);
	if (NULL == methodID) {
		handleError(env, OPENGL_NATIVE_EXCEPTION, errorMessage);
	}

	return methodID;
}


/* This returns a methodID for the given class, method name and method
   signature.  It will return NULL after calling handleError() if
   something went wrong, and the methodID if things work out properly.  */
jmethodID getMethodID(JNIEnv *env, jclass class,
		      const char *methodName,
		      const char *methodSignature,
		      const char *errorMessage)
{
  jmethodID methodID = NULL;

  methodID = (*env)->GetMethodID(env, class, 
				 methodName, methodSignature);
  if (NULL == methodID) {
    handleError(env, OPENGL_NATIVE_EXCEPTION, errorMessage);
    methodID = NULL;
  }
  return methodID;
}



/* After looking up object's class, call getMethodID with the supplied 
   arguments. */
jmethodID getMethodIDForObject(JNIEnv* env, jobject object,
			  const char *methodName,
			  const char *methodSignature,
			  const char *errorMessage)
{
	jclass objectClass = (*env)->GetObjectClass(env, object);
	return getMethodID(env, objectClass, methodName, methodSignature, errorMessage);
}


static checkArrayResults _checkArray(JNIEnv *env, jobject jarray, const char *className)
/*  This checks to see if the supplied object is of the given class name. 
    We return one of three possible values: isInstanceOf, isNotInstanceOf, and error. */
{
	jclass arrayClass = NULL;

	arrayClass = (*env)->FindClass(env, className);
	if (NULL == arrayClass) {
		return error;
	} else {
		if ((*env)->IsInstanceOf(env, jarray, arrayClass)) {
			return isInstanceOf;
		}
	}
	return isNotInstanceOf;
}



/* This releases the java array that has been converted into a carray.  We return
0 if everything work ok, 1 if we had a problem finding an array class, and 2
if the object passed in wasn't an instance of anything we knew about.*/
int releaseArrayElements(JNIEnv *env, jobject jarray, void *carray, int mode) 
{
	struct javaArrayReleaseDescription arrayTypes[] =
	{
		{"[B", "Unable to find byte array class ([B)",
			((*env)->ReleaseByteArrayElements)},
		{"[C", "Unable to find character array class ([C)",
		(*env)->ReleaseCharArrayElements},
		{"[I", "Unable to find int array class ([I)",
		(*env)->ReleaseIntArrayElements},
		{"[F", "Unable to find float array class ([F)",
		(*env)->ReleaseFloatArrayElements},
		{"[S", "Unable to find short array class ([S)",
		(*env)->ReleaseShortArrayElements},
		{"[D", "Unable to find double array class ([D)",
		(*env)->ReleaseDoubleArrayElements},
		{"[L", "Unable to find long array class ([L)",
		(*env)->ReleaseLongArrayElements},
		{"[Z", "Unable to find boolean array class ([Z)",
		(*env)->ReleaseBooleanArrayElements},
	}; 

	int i;
	for(i = 0; i < sizeof(arrayTypes) / sizeof(arrayTypes[0]); i++) {
		struct javaArrayReleaseDescription arrayDescription;
		checkArrayResults arrayResult;

		arrayDescription = arrayTypes[i];
		arrayResult = _checkArray(env, jarray, arrayTypes[i].className);
		if (arrayResult == error) {
			handleError(env, OPENGL_NATIVE_EXCEPTION,
				arrayTypes[i].errorDescription);
			return 1;
		}
		if (arrayResult == isInstanceOf) {
			void (JNICALL *arrayReleaser)() = arrayTypes[i].releaser;
			(*arrayReleaser)(env, jarray, carray, mode);
			return 0;
		}
	}
	
    /* We were unable to find the array type. */

	handleError(env, OPENGL_NATIVE_EXCEPTION,
				"Unable to find array class for supplied object");
	return 2;
}


/* This expects array to point to a Java primitive array, which it unpacks.
   We return an arrayElements structure that contains a void pointer to the
   unpacked array, and a description of the element type in the array.

   If there is a problem unpacking the array we call handleError and
   return an arrayElements structure that contains NULL pointers for the
   array elements and the array type.
 */
arrayElements getArrayElements(JNIEnv *env, jobject jarray, jboolean *isCopy)

{
	arrayElements result = { NULL, NULL };

	struct javaArrayAccessDescription arrayTypes[] = 
	{
		{"[B", "Unable to find byte array class ([B)",
		(void*)	(*env)->GetByteArrayElements},
		{"[C", "Unable to find character array class ([C)",
		(void *) (*env)->GetCharArrayElements},
		{"[I", "Unable to find int array class ([I)",
		(void *) (*env)->GetIntArrayElements},
		{"[F", "Unable to find float array class ([F)",
		(void *) (*env)->GetFloatArrayElements},
		{"[S", "Unable to find short array class ([S)",
		(void *) (*env)->GetShortArrayElements},
		{"[D", "Unable to find double array class ([D)",
		(void *) (*env)->GetDoubleArrayElements},
		{"[L", "Unable to find long array class ([L)",
		(void *) (*env)->GetLongArrayElements},
		{"[Z", "Unable to find boolean array class ([Z)",
		(void *) (*env)->GetBooleanArrayElements},
	}; 
	
	int i;

	for(i = 0; i < sizeof(arrayTypes) / sizeof(arrayTypes[0]); i++) {
		struct javaArrayAccessDescription arrayDescription;
		checkArrayResults arrayResult;

		arrayDescription = arrayTypes[i];
		arrayResult = _checkArray(env, jarray, arrayTypes[i].className);
		if (arrayResult == error) {
			handleError(env, OPENGL_NATIVE_EXCEPTION,
				arrayTypes[i].errorDescription);
			return result;
		}
		if (arrayResult == isInstanceOf) {
			void *array = NULL;
			void *(JNICALL *arrayAccessor)() = arrayTypes[i].accessor;
			array = (*arrayAccessor)(env, jarray, isCopy);
			if (NULL == array) {
				handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
					"Unable to map an array.");
			}
			result.arrayElements = array;
			result.elementType   = arrayTypes[i].className;
			return result;
		}
	}
	
    /* We were unable to find the array type. */

	handleError(env, OPENGL_NATIVE_EXCEPTION,
				"Unable to find array class for supplied object.");
	return result;
}

/*
 * JNIInterface.c
 *
 * $Id: JNIInterface.c,v 1.2 1997/11/16 02:53:15 razeh Exp $
 *
 * This module handles convience routines for dealing with the Java
 * Native Interface.
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */


#include "cygnusFixes.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"


/* Lookup the static integer field in class and store the return value
   in fieldValue.  If there is a problem getting the value fieldValue
   is not changed and 1 is returned.  Otherwise 0 is returned, and the
   field value is stored in *fieldValue.  */
int lookupStaticIntField(JNIEnv *env, jclass class,
			 const char *fieldName, int *fieldValue)

{
  jfieldID field;
  int returnCode = 0;

  field = (*env)->GetStaticFieldID(env, class, fieldName, "I");
  if (field == 0) {
    handleError(env, "OpenGL/OpenGLNativeException",
		"Unable to get static field ID");
    returnCode = 1;
  } else {
    *fieldValue =
      (*env)->GetStaticIntField(env, class, field);
  }

  return returnCode;
}



/* Lookup a integer field in object and store the return value in
   fieldValue.  If there is a problem getting the value fieldValue is
   not changed and 1 is returned. Otherwise 0 is returned, and the
   fieldValue is stored in *fieldValue. */
int lookupIntField(JNIEnv *env, jobject object,
		   const char *fieldName, int *fieldValue)
{
  jfieldID field;
  jclass   objectClass;
  int      returnCode = 0;

  objectClass = (*env)->GetObjectClass(env, object);

  field = (*env)->GetFieldID(env, objectClass, fieldName, "I");
  if (field == 0) {
    handleError(env, "OpenGL/OpenGLNativeException",
		"Unable to get field ID");
    returnCode = 1;
  } else {
    *fieldValue = (*env)->GetIntField(env, objectClass, field);
  }

  return returnCode;
}



/* This performs the same functions as lookupStaticIntField, but
   returns the integer field instead of placing it in a variable.  If
   there is a problem with the field lookup abort() is called. */
int staticIntField(JNIEnv *env, jclass class,
		   const char *fieldName)
{
  int fieldValue = -1;

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
  return getFullyQualifiedClass(env, className, "OpenGL/OpenGLNativeException",
				errorString);
}



/* This returns a methodID for the given class, method name and method
   signature.  It will return NULL after calling handleError() if
   something went wrong, and the methodID if things work out properly.  */
jmethodID getMethodID(JNIEnv *env, jclass class,
		      const char *methodName,
		      const char *methodSignature,
		      const char *errorMessage)
{
  jmethodID methodID;

  methodID = (*env)->GetMethodID(env, class, 
				 methodName, methodSignature);
  if (methodID == 0) {
    handleError(env, "OpenGL/OpenGLNativeException", errorMessage);
    methodID = NULL;
  }
  return methodID;
}

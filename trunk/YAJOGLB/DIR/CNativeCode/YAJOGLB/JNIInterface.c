/*
 * JNIInterface.c
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
  jfieldID field; int returnCode = 0;

  field = (*env)->GetStaticFieldID(env, class, fieldName, "I");
  if (field == 0) {
    handleError(env, "OpenGL/OpenGLNativeException",
		"Unable to get field ID");
    returnCode = 1;
  }
  
  *fieldValue =
    (*env)->GetStaticIntField(env, class, field);
  
  return returnCode;
}



/* This performs the same functions as lookupStaticIntField, but
   returns the integer field instead of placing it in a variable.  If
   there is a problem with the field lookup abort() is called. */
int staticIntField(JNIEnv *env, jclass class,
		   const char *fieldName)
{
  int fieldValue;

  if (lookupStaticIntField(env, class, fieldName, &fieldValue) != 0)
    abort();

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




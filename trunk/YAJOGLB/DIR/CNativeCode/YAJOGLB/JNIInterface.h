/*
 * JNIInterface.h 
 *
 * $Id: JNIInterface.h,v 1.2 1997/11/16 02:53:15 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */


#include <jni.h>

int lookupStaticIntField(JNIEnv *env, jclass class, 
			 const char *fieldName, int *fieldValue);

int lookupIntField(JNIEnv *env,  jobject object,
		   const char *fieldName, int *fieldValue);

int staticIntField(JNIEnv *env, jclass class, const char *fieldName);

jclass getClass(JNIEnv *env,
		const char *className,      /* The class to lookup. */
		const char *errorString);   /* The error to print. */

jmethodID getMethodID(JNIEnv *env, jclass class,
		      const char *methodName,
		      const char *methodSignature,
		      const char *errorMessage);

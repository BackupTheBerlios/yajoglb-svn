/*
 * JNIInterface.h 
 *
 * $Id: JNIInterface.h,v 1.4 1998/11/04 00:27:40 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */


#include <jni.h>

int lookupStaticIntField(JNIEnv *env, jclass class, 
			 const char *fieldName, jint *fieldValue);

int lookupIntField(JNIEnv *env,  jobject object,
		   const char *fieldName, jint *fieldValue);

int staticIntField(JNIEnv *env, jclass class, const char *fieldName);

jclass getClass(JNIEnv *env,
		const char *className,      /* The class to lookup. */
		const char *errorString);   /* The error to print. */

jmethodID getMethodID(JNIEnv *env, jclass class,
		      const char *methodName,
		      const char *methodSignature,
		      const char *errorMessage);


typedef struct _arrayElements {
	void *arrayElements;
    char *elementType;
} arrayElements;

arrayElements getArrayElements(JNIEnv *env, jobject array, jboolean *isCopy);
int releaseArrayElements(JNIEnv *env, jobject jarray, void *carray, int mode); 

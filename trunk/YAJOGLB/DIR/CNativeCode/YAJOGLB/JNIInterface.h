/*
 * JNIInterface.h 
 *
 * $Id: JNIInterface.h,v 1.7 2001/07/06 23:41:00 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@yahoo.com)
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

jmethodID getStaticMethodID(JNIEnv *env, jclass class,
							const char *methodName,
							const char *methodSignature,
							const char *errorMessage);

jmethodID getMethodID(JNIEnv *env, jclass class,
					  const char *methodName,
					  const char *methodSignature,
		              const char *errorMessage);

jmethodID getMethodIDForObject(JNIEnv* env, jobject object,
							   const char *methodName,
							   const char *methodSignature,
							   const char *errorMessage);

typedef struct _arrayElements {
	void *arrayElements;
    char *elementType;
} arrayElements;

arrayElements getArrayElements(JNIEnv *env, jobject array, jboolean *isCopy);
int releaseArrayElements(JNIEnv *env, jobject jarray, void *carray, int mode); 


/* If _LP64 is good enough for the JNI headers, it is good enough for us. */
#if __WORDSIZE == 64
#define TO_POINTER(x) ((void*) x)
#else
#define TO_POINTER(x) ((void*) (int)x)
#endif

#define FROM_POINTER(x) ((jlong) (int)x)

#ifndef CALLBACK
#define CALLBACK
#endif

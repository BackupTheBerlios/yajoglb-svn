/*
 * ErrorHandling.c
 *
 * This code handles invoking the handleEvent method for our widget
 * with a newly created OpenGLEvent object.
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com) 
 */

#include "cygnusFixes.h"
#include <stdlib.h>
#include "ErrorHandling.h"

#define BUFFERLENGTH 32

/* This is the method that gets called when something goes wrong with
   our interface to the java virtual machine. */
void handleError(JNIEnv *env, 
                 const char *exceptionClass, 
				 const char *errorMessage)
{
  jthrowable exc;
  jclass     newExceptionClass;

  exc = (*env)->ExceptionOccurred(env);
  if (exc) {
    (*env)->ExceptionDescribe(env);
    (*env)->ExceptionClear(env);
  }
  
  newExceptionClass = (*env)->FindClass(env, exceptionClass);
  if (newExceptionClass == 0) {
    const char *fatalErrorMessage = errorMessage;
    (*env)->FatalError(env, fatalErrorMessage);
  }
  if ((*env)->ThrowNew(env, newExceptionClass, errorMessage) < 0) {
    (*env)->FatalError(env, "Unable to throw exception");
  }
}



/* This should be called when we run out of memory. */
void handleOutOfMemoryError(JNIEnv *env, const char *errorMessage)
{
	handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION, errorMessage);
}



void logMessage(JNIEnv *env, const char *string)
{
  fprintf(stderr, string);
}


/* Call this function when you have an error that can not be
   reported via the JVM.  This can happen if you are unable to
   get an environment pointer for some reason. */
void fatalUnreportableError(const char *errorString)
{
  fprintf(stderr, errorString);
  abort();
}



void logHex(JNIEnv *env, unsigned int h)
{
  char outputBuffer[BUFFERLENGTH+1];
  int i;

  for(i = 0; i < BUFFERLENGTH+1; i++)
    outputBuffer[i] ='\0';

  for(i = 0; i < BUFFERLENGTH; i++) {
    char thisDigit =(((0xF << (i*4)) & h) >> (i*4)) + '0';
    if (thisDigit > '9')
      thisDigit = (((0xF << (i*4)) & h) >> (i*4)) + ('a' - ':') + '0';
    outputBuffer[BUFFERLENGTH-1-i] = thisDigit;
  }
  logMessage(env, outputBuffer);
}

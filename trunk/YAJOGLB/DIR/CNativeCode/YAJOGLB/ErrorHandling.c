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
#include "ErrorHandling.h"

#define BUFFERLENGTH 32

/* This is the method that gets called when something goes wrong with
   our interface to the java virtual machine. */
void handleError(JNIEnv *env, 
		 const char *exceptionClass, const char *errorMessage)
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



void log(JNIEnv *env, const char *string)
{
  jclass   system, printStream;
  jfieldID outID;
  jobject  out;
  jmethodID printChar;
  const char *stringPointer = string;

  system = (*env)->FindClass(env, "java/lang/System");
  if (system == NULL) {
    handleError(env, "OpenGL/OpenGLNativeException", "Unable to get java/lang/System");
    return;
  }

  outID = (*env)->GetStaticFieldID(env, system, "out", "Ljava/io/PrintStream;");
  if (outID == NULL) {
    handleError(env, "OpenGL/OpenGLNativeException", "Unable to get out field ID");
    return;
  }

  out = (*env)->GetStaticObjectField(env, system, outID);
  if (out == NULL) {
    handleError(env, "OpenGL/OpenGLNativeException", "Unable to get out field");
    return;
  }

  printStream = (*env)->GetObjectClass(env, out);
  if (printStream == NULL) {
    handleError(env, "OpenGL/OpenGLNativeException", "Unable to out class");
    return;
  }
    
  printChar = (*env)->GetMethodID(env, printStream, "print", "(C)V");
  if (printChar == NULL) {
    handleError(env, "OpenGL/OpenGLNativeException", "Unable to get print methodID");
    return;
  }

  if (stringPointer == NULL) {
    handleError(env, "OpenGL/OpenGLNativeException", "Passed a NULL log string");
    return;
  }

  while(*stringPointer != '\0') {
    (*env)->CallVoidMethod(env, out, printChar, *stringPointer);
    stringPointer++;
  }
}



void logHex(JNIEnv *env, int h)
{
  char outputBuffer[BUFFERLENGTH];
  int i;

  for(i = 0; i < BUFFERLENGTH; i++)
    outputBuffer[i] ='\0';

  for(i = 0; i < 8; i++) {
    outputBuffer[7-i] =(((0xF << (i*4)) & h) >> (i*4))+ '0';
    if (outputBuffer[7-i] > '9')
      outputBuffer[7-i] = (((0xF << (i*4)) & h) >> (i*4)) + ('a' - ':') + '0';
  }
  log(env, outputBuffer);
}

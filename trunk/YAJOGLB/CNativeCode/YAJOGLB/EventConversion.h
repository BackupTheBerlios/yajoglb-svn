#include <jni.h>

/* This converts the windows idea of a key code into Java's idea of a
   key code. */
int win32CharacterToJava(JNIEnv *env, jclass class,
			 int character);
long GetModifiers(JNIEnv *env, jclass class,
		  unsigned int nFlags);


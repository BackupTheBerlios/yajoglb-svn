#include <jni.h>

/* These handle creating and passing the proper event off to the given
   OpenGLWidget. */
int handOffWindowActivated(JNIEnv *env, jobject widget);
int handOffWindowExposed(JNIEnv *env, jobject widget);
int handOffWindowResized(JNIEnv *env, jobject widget, 
			 int width, int height);
int handOffKeyPressed(JNIEnv *env, jobject widget,
		      int keyCode);
int handOffKeyReleased(JNIEnv *env, jobject widget,
		       int keyCode);
int handOffMouseMove(JNIEnv *env, jobject widget,
		     int x, int y);
int handOffMouseDown(JNIEnv *env, jobject widget,
		     int x, int y);
int handOffMouseUp(JNIEnv *env, jobject widget,
		   int x, int y);

#include <windows.h>
#include "cygnusFixes.h"
#include <jni.h>


HDC getDCForWidget(JNIEnv *env, jobject widget);
HGLRC getGLRCForWidget(JNIEnv *env, jobject widget);
void setGLRCForWidget(JNIEnv *env, jobject widget, HGLRC hGLRC);
void setDCForWidget(JNIEnv *env, jobject widget, HDC hDC);

JNIEnv *environmentForWindow(HWND hWnd);
jobject widgetForWindow(HWND hWnd);
HWND windowForWidget(JNIEnv *env, jobject widget);
void setWidgetForWindow(HWND hWnd, JNIEnv *environment, jobject widget);
void setEnvironmentForWindow(HWND hWnd, JNIEnv *environment, jobject widget);

void setupDCLocks();

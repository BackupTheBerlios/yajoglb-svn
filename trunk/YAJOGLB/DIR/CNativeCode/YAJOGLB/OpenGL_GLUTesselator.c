/*
 * OpenGL_OpenGLTesselator.c
 *
 * $Id: OpenGL_GLUTesselator.c,v 1.2 1998/12/23 00:38:55 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements some of the native methods that are needed to support tesselators.
 */

#include <windows.h>
#include <GL/glu.h>

#include "cygnusFixes.h"
#include "memory.h"
#include "ErrorHandling.h"
#include "JNIInterface.h"
#include "OpenGL_GLUTesselator.h"

/* This structure holds the parameters we need to invoke the proper
   tesselator method for callbacks. */
typedef struct GLUTesselatorAndJNIParametersStruct {
  JNIEnv *environment; /* The environment to supply. */
  jobject jtesselator;  /* The tesselator to call. */
  jobject vertexOrPolygonData;  /* Attached Vertex or polygon data. */
  GLUtesselator *tesselator;
} GLUTesselatorAndJNIParameters;

/* This establish our callback environment.*/
static void establishCallback(JNIEnv* env, jobject jtesselator, jobject data,
							  GLUTesselatorAndJNIParameters *parameters)
{
	parameters->jtesselator = jtesselator;
	parameters->environment = env;
	parameters->vertexOrPolygonData = data;
	printf("jtesselator = %p, parameters = %p\n", jtesselator, parameters);
}

/* These implement the callbacks.  We expect the "polygon data" to be
    a JNI calling parameter. */

/* The error callback. */
static void CALLBACK errorData(GLenum errorNumber, void *polygonData)
{
	printf("error %d\n", errorNumber);
}


/* The begin callback. */
 static void CALLBACK beginData(GLenum type, void *polygonData)
{
	if (NULL != polygonData) {
		jobject   jtesselator = ((GLUTesselatorAndJNIParameters*)polygonData)->jtesselator;
		JNIEnv*   env         = ((GLUTesselatorAndJNIParameters*)polygonData)->environment;
		jmethodID methodID    = NULL;

		methodID = getMethodIDForObject(env, jtesselator, "begin", "(I)V", "Unable to locate the begin method."); 
		if (NULL != methodID) {
			(*env)->CallObjectMethod(env, jtesselator, methodID, type);
		}  
	} else {
		fatalUnreportableError("Unable to aquire an JNI environment pointer in beginData.");  
	}
}

/* The end callback. */
static void CALLBACK endData(void *polygonData)
{
	if (NULL != polygonData) {
		jobject   jtesselator = ((GLUTesselatorAndJNIParameters*)polygonData)->jtesselator;
		JNIEnv*   env         = ((GLUTesselatorAndJNIParameters*)polygonData)->environment;
		jmethodID methodID    = NULL;

		printf("endData = %p\n", polygonData);
		methodID = getMethodIDForObject(env, jtesselator, "end", "()V", "Unable to locate the end method."); 
		if (NULL != methodID) {
			(*env)->CallObjectMethod(env, jtesselator, methodID);
		}
	} else {
		fatalUnreportableError("Unable to aquire an JNI environment pointer in endData.");  
	}
}

static void CALLBACK vertexData(GLdouble *location, void *polygonData) 
{
	if ((NULL != polygonData) && (NULL != location)) {
		jobject   jtesselator = ((GLUTesselatorAndJNIParameters*)polygonData)->jtesselator;
		JNIEnv*   env         = ((GLUTesselatorAndJNIParameters*)polygonData)->environment;
		jobject   vertexData  = ((GLUTesselatorAndJNIParameters*)polygonData)->vertexOrPolygonData;
		jmethodID methodID    = NULL;

		printf("vertex = %p\n", polygonData);
		methodID = getMethodIDForObject(env, jtesselator, "vertex", "(DDDLjava/lang/Object;)V", "Unable to locate the vertex method.");
		if (NULL != methodID) {
			(*env)->CallVoidMethod(env, jtesselator, methodID, location[0], location[1], location[2], vertexData);
		}
	} else {
		fatalUnreportableError("Unable to aquire an JNI environment pointer in vertexData.");  
	}
}



static void CALLBACK combineData(GLdouble coords[3], void *vertex_data[4],
                                 GLfloat weight[4], void **outData,
                                 void *polygon_data)
{
	printf("combineData\n");
}

/* The actual native methods are implemented here. */

/* Returns a new tesselator. */
JNIEXPORT jint JNICALL Java_OpenGL_GLUTesselator_gluNewTess
  (JNIEnv *env, jobject obj)
{
	GLUtesselator                 *newTesselator                 = NULL;
	GLUTesselatorAndJNIParameters *newTesselatorAndJNIParameters = NULL;

	newTesselator = gluNewTess();
	if (NULL != newTesselator) {
	    gluTessCallback(newTesselator, GLU_TESS_ERROR_DATA, errorData);
		gluTessCallback(newTesselator, GLU_TESS_BEGIN_DATA, beginData);
		gluTessCallback(newTesselator, GLU_TESS_END_DATA, endData);
		gluTessCallback(newTesselator, GLU_TESS_VERTEX_DATA, vertexData);
		newTesselatorAndJNIParameters = privateMalloc(sizeof(GLUTesselatorAndJNIParameters));
		newTesselatorAndJNIParameters->tesselator = newTesselator;
	}

	return (int) newTesselatorAndJNIParameters;
}

/*  Deletes a tesselator.  */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_gluDeleteTess
  (JNIEnv *env, jobject obj, jint tess)
{
	GLUTesselatorAndJNIParameters *tesselatorAndJNIParameters = NULL;

	tesselatorAndJNIParameters = (GLUTesselatorAndJNIParameters*)tess;
	gluDeleteTess(tesselatorAndJNIParameters->tesselator);
	privateFree(tesselatorAndJNIParameters);
}

JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_beginContour
  (JNIEnv *env, jobject obj, jint tess)
{
	GLUTesselatorAndJNIParameters *tesselatorAndJNIParameters = NULL;

	tesselatorAndJNIParameters = (GLUTesselatorAndJNIParameters*)tess;
	establishCallback(env, obj, NULL, tesselatorAndJNIParameters);
	gluTessBeginContour(((GLUTesselatorAndJNIParameters*) tess)->tesselator);
}

JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_beginPolygon
  (JNIEnv *env, jobject obj, jint tess, jobject data)
{
	GLUTesselatorAndJNIParameters *tesselatorAndJNIParameters = NULL;

	tesselatorAndJNIParameters = (GLUTesselatorAndJNIParameters*)tess;
	establishCallback(env, obj, data, tesselatorAndJNIParameters);
	gluTessBeginPolygon(tesselatorAndJNIParameters->tesselator, tesselatorAndJNIParameters);
}

JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_endContour
  (JNIEnv *env, jobject obj, jint tess)
{
	GLUTesselatorAndJNIParameters *tesselatorAndJNIParameters = NULL;

	tesselatorAndJNIParameters = (GLUTesselatorAndJNIParameters*)tess;
	printf("Start of EndCountour = %p\n", tesselatorAndJNIParameters);
	establishCallback(env, obj, NULL, tesselatorAndJNIParameters);
	gluTessEndContour(tesselatorAndJNIParameters->tesselator);
	printf("End of EndCountour\n");
}

JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_endPolygon
  (JNIEnv *env, jobject obj, jint tess)
{
	GLUTesselatorAndJNIParameters *tesselatorAndJNIParameters = NULL;

	tesselatorAndJNIParameters = (GLUTesselatorAndJNIParameters*)tess;
	printf("EndPolygon = %p\n", tesselatorAndJNIParameters );
	establishCallback(env, obj, NULL, tesselatorAndJNIParameters);
	gluTessEndPolygon(tesselatorAndJNIParameters->tesselator);
	printf("End of EndPolygon\n");
}

JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_normal
  (JNIEnv *env, jobject obj, jint tess, 
   jdouble valueX, jdouble valueY, jdouble valueZ)
{
	GLUTesselatorAndJNIParameters *tesselatorAndJNIParameters = NULL;

	tesselatorAndJNIParameters = (GLUTesselatorAndJNIParameters*)tess;
	establishCallback(env, obj, NULL, tesselatorAndJNIParameters);
	gluTessNormal(tesselatorAndJNIParameters->tesselator, valueX, valueY, valueZ); 
}

/* Not done yet */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_vertex
  (JNIEnv *env, jobject obj, jint tess, jdoubleArray jlocation, jobject vertexData)
{
	GLUTesselatorAndJNIParameters *tesselatorAndJNIParameters = NULL;
	GLdouble *location = NULL;

	location = (*env)->GetDoubleArrayElements(env, jlocation, 0);
	if (NULL == location) {
		handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
		  "Unable to map the location verticies.");
		return;
	}
	tesselatorAndJNIParameters = (GLUTesselatorAndJNIParameters*)tess;
	tesselatorAndJNIParameters->jtesselator = obj;
	tesselatorAndJNIParameters->environment = env;
	tesselatorAndJNIParameters->vertexOrPolygonData = vertexData;
	gluTessVertex(tesselatorAndJNIParameters->tesselator, location, 
		      tesselatorAndJNIParameters);
	//(*env)->ReleaseDoubleArrayElements(env, jlocation, location, JNI_ABORT);
}


JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_setProperty
  (JNIEnv *env, jobject obj, jint tess, jint which, jdouble data)
{
	GLUTesselatorAndJNIParameters *tesselatorAndJNIParameters = NULL;

	tesselatorAndJNIParameters = (GLUTesselatorAndJNIParameters*)tess;
	establishCallback(env, obj, NULL, tesselatorAndJNIParameters);
	gluTessProperty(tesselatorAndJNIParameters->tesselator, which, data);
}


JNIEXPORT jdouble JNICALL Java_OpenGL_GLUTesselator_property
  (JNIEnv *env, jobject obj, jint tess, jint property)
{
	GLdouble dataOut;
	GLUTesselatorAndJNIParameters *tesselatorAndJNIParameters = NULL;

	tesselatorAndJNIParameters = (GLUTesselatorAndJNIParameters*)tess;
	establishCallback(env, obj, NULL, tesselatorAndJNIParameters);

	gluGetTessProperty(tesselatorAndJNIParameters->tesselator, property, &dataOut);

	return dataOut;
}








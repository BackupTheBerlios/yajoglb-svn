/*
 * OpenGL_OpenGLTesselator.c
 *
 * $Id: OpenGL_GLUTesselator.c,v 1.4 1999/01/26 23:55:44 razeh Exp $
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@balr.com)
 *
 * This implements some of the native methods that are needed to support tesselators.
 * The primary problem with tesselators is the callbacks, which should call our
 * own Java methods.  So, we setup some functions to get the tesselator that the
 * current thread is using.
 *
 * Future work includes reusing polygon containers.  Right now they can be allocated,
 * deallocated and then allocated and deallocated all over again.
 */

#include <windows.h>
#include <GL/glu.h>

#include "cygnusFixes.h"
#include "memory.h"
#include "CallbackObject.h"
#include "ErrorHandling.h"
#include "EnvDictionary.h"
#include "JNIInterface.h"
#include "OpenGL_GLUTesselator.h"



////////////////////////////////////////////////////////////////////////
// Container structures and functions.
////////////////////////////////////////////////////////////////////////



/* These three structures are used for holding the tesselator,
   polygon data and vertex data. */
typedef struct polygonDataContainerStruct {
	jobject polygonData;
} polygonDataContainer;

typedef struct vertexDataContainerStruct {
	jobject vertexData;            // The data that our caller is passing in.
	GLdouble vertexLocation[3];    // The copy of the vertex location passed to OpenGL.
	struct vertexDataContainerStruct *nextVertexData;
} vertexDataContainer;

typedef struct tesselatorContainerStruct {
	GLUtesselator *tesselator; 
	vertexDataContainer  *vertexDataList;       // The tesselator's list of verticies.
	polygonDataContainer *polygonDataContainer; // The tesselator's polygon data.
} tesselatorContainer;



/* Cleanup all of the vertex data in tess container. */
static void cleanupVertexDataList(JNIEnv *env, tesselatorContainer  *tessContainer)
{
	vertexDataContainer *vertexContainer = NULL;

	// Go through our entire list of vertex data containers and release
	// all of the global references and then delete the containers themselve.
	vertexContainer = tessContainer->vertexDataList;
	while(NULL != vertexContainer) {
		vertexDataContainer *nextContainer = vertexContainer->nextVertexData;
		(*env)->DeleteGlobalRef(env, vertexContainer->vertexData);
		privateFree(vertexContainer);
		vertexContainer = nextContainer;
	}
	tessContainer->vertexDataList = NULL;
}


/* Cleanup the polygon data container attached to the tesselator container. */
static void cleanupPolygonDataContainer(JNIEnv *env, tesselatorContainer* tessContainer)
{
	if (NULL != tessContainer->polygonDataContainer) {
		(*env)->DeleteGlobalRef(env, tessContainer->polygonDataContainer->polygonData);
		privateFree(tessContainer->polygonDataContainer);
		tessContainer->polygonDataContainer = NULL;
	}
}



/* Allocate and return a new tesselator container.
   If we run out of memory while doing the allocate call handleOutOfMemoryError and 
   return NULL. */
static tesselatorContainer *newTesselatorContainer(JNIEnv *env)
{
	tesselatorContainer *newContainer = NULL;

	newContainer = privateMalloc(sizeof(*newContainer));
	if (NULL != newContainer) {
		newContainer->vertexDataList = NULL;
		newContainer->polygonDataContainer = NULL;
	} else {
		handleOutOfMemoryError(env, "Ran out of memory while creating a tesselator container.");
	}
	return newContainer;
}



/* Allocate and return a new polygon data container holding our polygonData argument.
   If we run out of memory while doing the allocate call handleOutOfMemoryError and 
   return NULL.  If there is already a polygon container present something is very
   wrong with the order that we are being called and we return NULL without calling
   any error functions, assuming that the tesselator will detect the error.  */
static polygonDataContainer *newPolygonDataContainer(JNIEnv *env, 
													 tesselatorContainer *tessContainer,
													 jobject polygonData)
{
	polygonDataContainer *newContainer = NULL;

	// Make sure there is no container already present.
	if (NULL == tessContainer->polygonDataContainer) {
		newContainer = privateMalloc(sizeof(*newContainer));
		if (NULL != newContainer) {
			newContainer->polygonData = (*env)->NewGlobalRef(env, polygonData);
		tessContainer->polygonDataContainer = newContainer;
		} else {
			handleOutOfMemoryError(env, "Ran out of memory while creating a polygon container.");
		}
	} else {
		newContainer = tessContainer->polygonDataContainer;
		(*env)->DeleteGlobalRef(env, newContainer->polygonData);
		newContainer->polygonData = (*env)->NewGlobalRef(env, polygonData);
	}

	return newContainer;
}



/* Allocate and return a new vertex data container holding our vertexData argument.
   If we run out of memory while doing the allocate call handleOutOfMemoryError and
   return NULL.  */
static vertexDataContainer *newVertexDataContainer(JNIEnv *env, 
												   tesselatorContainer *tessContainer,
												   jobject vertexData,
												   GLdouble *vertexLocation)
{
	vertexDataContainer *newContainer = NULL;

	newContainer = (vertexDataContainer*)privateMalloc(sizeof(*newContainer));
	if (NULL != newContainer) {
		newContainer->nextVertexData = tessContainer->vertexDataList;
		tessContainer->vertexDataList = newContainer;
		newContainer->vertexData = (*env)->NewGlobalRef(env, vertexData);
		// Store the vertexLocation someplace safe until
		// endPolygon is called.
		if (NULL != vertexLocation) {
			newContainer->vertexLocation[0] = vertexLocation[0];
			newContainer->vertexLocation[1] = vertexLocation[1];
			newContainer->vertexLocation[2] = vertexLocation[2];
		}
	} else {
		handleOutOfMemoryError(env, "Ran out of memory while creating a vertex container.");
	}
	return newContainer;
}



////////////////////////////////////////////////////////////////////////
// Environment mapping.
////////////////////////////////////////////////////////////////////////



/* This returns the current tesselator that callbacks should use. */
static jobject getActiveTesselator(JNIEnv *env)
{
	jclass      tesselatorClass         = NULL;
	jobject     activeTesselator        = NULL;
	int         error                   = 0;

	// Get the tesselator class
	if (!error) {
		tesselatorClass = getClass(env, "OpenGL/GLUTesselator", 
			"Unable to get the OpenGL/GLUTesselator class.");
		error = (NULL == tesselatorClass);
	}

	activeTesselator = getActiveCallbackObjectForClass(env, tesselatorClass);
	
	return activeTesselator;
}



/* Gets the active tesselator container by getting the active tesselator and
   then getting the heap pointer from it. */
tesselatorContainer *getActiveTesselatorContainer(JNIEnv *env)
{
	tesselatorContainer *activeTesselator = NULL;
	jobject              jtesselator      = getActiveTesselator(env);
	jmethodID            methodID         = NULL;

	if (NULL != jtesselator) {
		methodID = getMethodIDForObject(env, jtesselator, "heapPointer", "()I",
			"Unable to locate the heapPointer method."); 
		if (NULL != methodID) {
			activeTesselator = (tesselatorContainer*) 
				(*env)->CallIntMethod(env, jtesselator, methodID);
		}
	}

	return activeTesselator;
}



////////////////////////////////////////////////////////////////////////
// Our callbacks
////////////////////////////////////////////////////////////////////////



/* The error callback. */
static void CALLBACK errorData(GLenum errorNumber, polygonDataContainer *polygonDataContainer)
{
	// Our caller will not halt if we hit an exception, and we do not 
	// want to do anything if an exception has been thrown.
    JNIEnv* env = environmentPointerForCurrentThread();

	if (NULL != polygonDataContainer &&
		(NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject   jtesselator = getActiveTesselator(env);
		jobject   polygonData = polygonDataContainer->polygonData;
	    jmethodID methodID    = NULL;

		methodID = getMethodIDForObject(env, jtesselator, "error", "(ILjava/lang/Object;)V", "Unable to locate the error method."); 
	     if (NULL != methodID) {
			 (*env)->CallVoidMethod(env, jtesselator, methodID, errorNumber, polygonData);
		}
	}
}



/* The begin callback. */
 static void CALLBACK beginData(GLenum type, polygonDataContainer *polygonDataContainer)
{
	// Our caller will not halt if we hit an exception, and we do not 
	// want to do anything if an exception has been thrown.
    JNIEnv* env = environmentPointerForCurrentThread();

	if (NULL != polygonDataContainer &&
		(NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject   jtesselator = getActiveTesselator(env);
		jobject   polygonData = polygonDataContainer->polygonData;
	    jmethodID methodID    = NULL;

	    methodID = getMethodIDForObject(env, jtesselator, "begin", "(ILjava/lang/Object;)V", "Unable to locate the begin method."); 
	    if (NULL != methodID) {
			(*env)->CallObjectMethod(env, jtesselator, methodID, type, polygonData);
		}
	}
}



/* The end callback. */
static void CALLBACK endData(polygonDataContainer *polygonDataContainer)
{
	// Our caller will not halt if we hit an exception, and we do not 
	// want to do anything if an exception has been thrown.
    JNIEnv* env = environmentPointerForCurrentThread();

	if (NULL != polygonDataContainer &&
		(NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject   jtesselator = getActiveTesselator(env);
		jobject   polygonData = polygonDataContainer->polygonData;
		jmethodID methodID    = NULL;

		methodID = getMethodIDForObject(env, jtesselator, "end", "(Ljava/lang/Object;)V", "Unable to locate the end method."); 
		if (NULL != methodID) {
			(*env)->CallObjectMethod(env, jtesselator, methodID, polygonData);
		}
	}
}



/* The vertex callback */
static void CALLBACK vertexData(vertexDataContainer  *vertexDataContainer,
								polygonDataContainer *polygonDataContainer) 
{
	// Our caller will not halt if we hit an exception, and we do not 
	// want to do anything if an exception has been thrown.
    JNIEnv* env = environmentPointerForCurrentThread();

	if ((NULL != vertexDataContainer) && (NULL != polygonDataContainer) &&
		(NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject   jtesselator = getActiveTesselator(env);
		jobject   polygonData = polygonDataContainer->polygonData;
		jobject   vertexData  = vertexDataContainer->vertexData;
		jmethodID methodID    = NULL;

		methodID = getMethodIDForObject(env, jtesselator, "vertex", "(Ljava/lang/Object;Ljava/lang/Object;)V",
			"Unable to locate the vertex method.");
		if (NULL != methodID) {
			(*env)->CallVoidMethod(env, jtesselator, methodID, vertexData, polygonData);
		}
	} 
}



static void CALLBACK combineData(GLdouble coords[3], vertexDataContainer *vertexData[4],
                                 GLfloat weight[4],  vertexDataContainer **outData,
                                 polygonDataContainer *polygonDataContainer)
{
	// Our caller will not halt if we hit an exception, and we do not 
	// want to do anything if an exception has been thrown.
    JNIEnv* env = environmentPointerForCurrentThread();

	if (NULL != polygonDataContainer &&
		(NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject              jtesselator   = getActiveTesselator(env);
		JNIEnv              *env           = environmentPointerForCurrentThread();
		jobject              polygonData   = polygonDataContainer->polygonData;
		tesselatorContainer *tessContainer = getActiveTesselatorContainer(env);
		jmethodID            methodID      = NULL;
		jobject              vertexData0   = NULL;
		jobject              vertexData1   = NULL;
		jobject              vertexData2   = NULL;
		jobject              vertexData3   = NULL;
		jobject              combinedData  = NULL;

		methodID = getMethodIDForObject(env, jtesselator, "combine", 
			"(DDDLjava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;Ljava/lang/Object;FFFFLjava/lang/Object;)Ljava/lang/Object;",
			"Unable to locate the vertex method.");
	
		// We are not always given 4 verticies, so we need to figure
		// out which ones are NULL pointers here.
		if (NULL != vertexData[0]) {
			vertexData0 = vertexData[0]->vertexData;
		}

		if (NULL != vertexData[1]) {
			vertexData1 = vertexData[1]->vertexData;
		}

		if (NULL != vertexData[2]) {
			vertexData2 = vertexData[2]->vertexData;
		}

		if (NULL != vertexData[3]) {
			vertexData3 = vertexData[3]->vertexData;
		}

		// Invoke the native method.
		if (NULL != methodID) {
			combinedData = (*env)->CallObjectMethod(env, jtesselator, methodID,
				coords[0], coords[1], coords[2],
				vertexData0, vertexData1, vertexData2, vertexData3,
				weight[0], weight[1], weight[2], weight[3],
				polygonDataContainer->polygonData);

			// Create a new vertex container for combinedData iff
			// our Java method did not return null.
			if (combinedData != NULL) {
				vertexDataContainer *newContainer = NULL;

				newContainer = newVertexDataContainer(env, tessContainer, combinedData, NULL);
				if (NULL != newContainer) {
					*outData = newContainer;
				}
			}
		}
	}
}


/* Implements the edge flag callback. */
static void CALLBACK edgeFlagData(GLboolean flag, polygonDataContainer *polygonDataContainer)
{
	// Our caller will not halt if we hit an exception, and we do not 
	// want to do anything if an exception has been thrown.
    JNIEnv* env = environmentPointerForCurrentThread();

	if (NULL != polygonDataContainer &&
		(NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
		jobject   jtesselator = getActiveTesselator(env);
		jobject   polygonData = polygonDataContainer->polygonData;
		jmethodID methodID    = NULL;

		methodID = getMethodIDForObject(env, jtesselator, "edgeFlag", "(ZLjava/lang/Object;)V",
			"Unable to locate the edgeFlag method.");
		if (NULL != methodID) {
			(*env)->CallVoidMethod(env, jtesselator, methodID, flag, polygonData);
		}
	}
}


////////////////////////////////////////////////////////////////////////
// The actual native methods for the GLUTesselator class.
////////////////////////////////////////////////////////////////////////



/* Returns a new tesselator. */
JNIEXPORT jint JNICALL Java_OpenGL_GLUTesselator_gluNewTess
  (JNIEnv *env, jobject obj)
{
	GLUtesselator       *newTesselator          = NULL;
	tesselatorContainer *newTessContainer       = NULL;

	newTesselator = gluNewTess();
	if (NULL != newTesselator) {
	    gluTessCallback(newTesselator, GLU_TESS_ERROR_DATA, errorData);
		gluTessCallback(newTesselator, GLU_TESS_BEGIN_DATA, beginData);
		gluTessCallback(newTesselator, GLU_TESS_END_DATA, endData);
		gluTessCallback(newTesselator, GLU_TESS_VERTEX_DATA, vertexData);
		gluTessCallback(newTesselator, GLU_TESS_COMBINE_DATA, combineData);
		// We do not add in the edge flag callback, because it modifies the 
		// behaviour of the tesselator and we allow the user to control that.
		newTessContainer = newTesselatorContainer(env);
		if (NULL != newTessContainer) {
			newTessContainer->tesselator = newTesselator;
		}
	}

	return (int) newTessContainer;
}



/*  Deletes a tesselator.  */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_gluDeleteTess
  (JNIEnv *env, jobject obj, jint tess)
{
	tesselatorContainer *container = (tesselatorContainer*)tess;

	cleanupVertexDataList(env, container);
	cleanupPolygonDataContainer(env, container);
	gluDeleteTess(container->tesselator);
	privateFree(container);
}



/* Marks the begining of a contour. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_beginContour
  (JNIEnv *env, jobject obj, jint tess)
{
	tesselatorContainer *container = (tesselatorContainer*)tess;
	
	gluTessBeginContour(container->tesselator);
}



/* Marks the begining of a polygon. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_beginPolygon
  (JNIEnv *env, jobject obj, jint tess, jobject polygonData)
{
	tesselatorContainer  *container            = (tesselatorContainer*)tess;
	polygonDataContainer *polygonDataContainer = NULL;
	
	polygonDataContainer = newPolygonDataContainer(env, container, polygonData);
	if (NULL != polygonDataContainer) {
		gluTessBeginPolygon(container->tesselator, polygonDataContainer);
	}
}



/* Marks the end of a contour. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_endContour
  (JNIEnv *env, jobject obj, jint tess)
{
	tesselatorContainer *container = (tesselatorContainer*)tess;

	gluTessEndContour(container->tesselator);
}



/* Marks the end of a polygon. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_endPolygon
  (JNIEnv *env, jobject obj, jint tess)
{
	tesselatorContainer *container = (tesselatorContainer*)tess;

	gluTessEndPolygon(container->tesselator);
	cleanupVertexDataList(env, container);
	cleanupPolygonDataContainer(env, container);
}



/* Describes the normal for the current polygon. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_normal
  (JNIEnv *env, jobject obj, jint tess, 
   jdouble valueX, jdouble valueY, jdouble valueZ)
{
	tesselatorContainer *container = (tesselatorContainer*)tess;

	gluTessNormal(container->tesselator, valueX, valueY, valueZ); 
}



/* Used to mark a vertex point. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_contourVertex
  (JNIEnv *env, jobject obj, jint tess, jdoubleArray jlocation, jobject vertexData)
{
	tesselatorContainer *tessContainer       = (tesselatorContainer*)tess;
	vertexDataContainer *vertexDataContainer = NULL;
	GLdouble            *location            = NULL;

	// Map our Java location array into a C heap array.
	location = (*env)->GetDoubleArrayElements(env, jlocation, 0);
	if (NULL == location) {
		handleError(env, OPENGL_NATIVE_MEMORY_EXHAUSTED_EXCEPTION,
		  "Unable to map the location verticies.");
		return;
	}

	// Create a vertex container for our vertex data.
	vertexDataContainer = newVertexDataContainer(env, tessContainer, vertexData,
		location);
	// Use the vertex location that has been copied into the vertex container
	// so that it will stick around for the tesselator calls made out of 
	// gluTessEndPolygon().
	if (NULL != vertexDataContainer) {
		gluTessVertex(tessContainer->tesselator, vertexDataContainer->vertexLocation, 
			          vertexDataContainer);
	}

    (*env)->ReleaseDoubleArrayElements(env, jlocation, location, JNI_ABORT);
}



/* Sets a tesselator property. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_setProperty
  (JNIEnv *env, jobject obj, jint tess, jint which, jdouble data)
{
	tesselatorContainer *container = (tesselatorContainer*)tess;

	gluTessProperty(container->tesselator, which, data);
}



/* Gets a tesselator property. */
JNIEXPORT jdouble JNICALL Java_OpenGL_GLUTesselator_property
  (JNIEnv *env, jobject obj, jint tess, jint property)
{
	GLdouble             dataOut   = 0.0;
	tesselatorContainer *container = (tesselatorContainer*)tess;

	gluGetTessProperty(container->tesselator, property, &dataOut);

	return dataOut;
}



/* Enables the edge flag callback. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_enableEdgeFlag
  (JNIEnv *env, jobject obj, jint tess)
{
	tesselatorContainer *container = (tesselatorContainer*)tess;

	gluTessCallback(container->tesselator, GLU_TESS_EDGE_FLAG_DATA, edgeFlagData);
}



/* Disables the edge flag callback. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_disableEdgeFlag
  (JNIEnv *env, jobject obj, jint tess)
{
	tesselatorContainer *container = (tesselatorContainer*)tess;

	gluTessCallback(container->tesselator, GLU_TESS_EDGE_FLAG_DATA, NULL);
}









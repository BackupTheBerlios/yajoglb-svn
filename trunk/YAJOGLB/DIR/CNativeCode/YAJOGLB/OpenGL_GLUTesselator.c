/*
  Provides references to items on the C memory heap.
 
  Copyright 2001, Robert Allan Zeh (razeh@yahoo.com)
  7346 Lake Street #3W
  River Forest, IL 60305
 
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA

*/

/*
 * OpenGL_OpenGLTesselator.c
 *
 * $Id: OpenGL_GLUTesselator.c,v 1.9 2002/04/14 18:26:46 razeh Exp $
 *
 * This implements some of the native methods that are needed to
 * support tesselators.  The primary problem with tesselators is the
 * callbacks, which should call our own Java methods.  So, we setup
 * some functions to get the tesselator that the current thread is
 * using.
 *
 * Future work includes reusing polygon containers.  Right now they
 * can be allocated, deallocated and then allocated and deallocated
 * all over again.  
 */

#include "SystemIncludes.h"
#include <GL/glu.h>

#include "cygnusFixes.h"
#include "Memory.h"
#include "CallbackObject.h"
#include "ErrorHandling.h"
#include "EnvDictionary.h"
#include "JNIInterface.h"
#include "OpenGL_GLUTesselator.h"


#define DEBUG 1

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

#ifdef DEBUG
  printf("cleanupVertexDataList\n");
  fflush(stdout);
#endif

  // Go through our entire list of vertex data containers and
  // release all of the global references and then delete the
  // containers themselve.
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
static void cleanupPolygonDataContainer(JNIEnv *env, 
					tesselatorContainer* tessContainer)
{
#ifdef DEBUG
  printf("cleanupPolygonDataContainer\n");
#endif
  if (NULL != tessContainer->polygonDataContainer) {
    (*env)->DeleteGlobalRef(env, tessContainer->polygonDataContainer->polygonData);
    privateFree(tessContainer->polygonDataContainer);
    tessContainer->polygonDataContainer = NULL;
  }
}



/* Allocate and return a new tesselator container.  If we run out of
   memory while doing the allocate call handleOutOfMemoryError and
   return NULL. */
static tesselatorContainer *newTesselatorContainer(JNIEnv *env)
{
  tesselatorContainer *newContainer = NULL;

  newContainer = (tesselatorContainer*) privateMalloc(sizeof(*newContainer));
  if (NULL != newContainer) {
    newContainer->vertexDataList = NULL;
    newContainer->polygonDataContainer = NULL;
  } else {
    handleOutOfMemoryError(env, "Ran out of memory while creating a tesselator container.");
  }
  return newContainer;
}



/* Allocate and return a new polygon data container holding our
   polygonData argument.  If we run out of memory while doing the
   allocate call handleOutOfMemoryError and return NULL.  If there is
   already a polygon container present something is very wrong with
   the order that we are being called and we return NULL without
   calling any error functions, assuming that the tesselator will
   detect the error.  */
static polygonDataContainer *newPolygonDataContainer(JNIEnv *env, 
						     tesselatorContainer *tessContainer,
						     jobject polygonData)
{
  polygonDataContainer *newContainer = NULL;

  // Make sure there is no container already present.
  if (NULL == tessContainer->polygonDataContainer) {
    newContainer = (polygonDataContainer*) privateMalloc(sizeof(*newContainer));
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



/* Allocate and return a new vertex data container holding our
   vertexData argument.  If we run out of memory while doing the
   allocate call handleOutOfMemoryError and return NULL.  */
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



/* Gets the active tesselator container by getting the active
   tesselator and then getting the heap pointer from it. */
tesselatorContainer *getActiveTesselatorContainer(JNIEnv *env)
{
  tesselatorContainer *activeTesselator = NULL;
  jobject              jtesselator      = getActiveTesselator(env);
  jmethodID            methodID         = NULL;

  if (NULL != jtesselator) {
    methodID = getMethodIDForObject(env, jtesselator, "getHeapPointer", "()J",
				    "Unable to locate the getHeapPointer method."); 
    if (NULL != methodID) {
      activeTesselator = (tesselatorContainer*) 
	TO_POINTER((*env)->CallLongMethod(env, jtesselator, methodID));
    }
  }

  (*env)->DeleteLocalRef(env, jtesselator); jtesselator = 0;
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
    (*env)->DeleteLocalRef(env, jtesselator); jtesselator = 0;
  }
}



/* The begin callback. */
static void CALLBACK beginData(GLenum type, polygonDataContainer *polygonDataContainer)
{
  // Our caller will not halt if we hit an exception, and we do not 
  // want to do anything if an exception has been thrown.
  JNIEnv* env = environmentPointerForCurrentThread();
  (*env)->PushLocalFrame(env, 16);
	
  if (NULL != polygonDataContainer &&
      (NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
    jobject   jtesselator = getActiveTesselator(env);
    jobject   polygonData = polygonDataContainer->polygonData;
    jmethodID methodID    = NULL;

    methodID = getMethodIDForObject(env, jtesselator, "begin", "(ILjava/lang/Object;)V", "Unable to locate the begin method."); 
    if (NULL != methodID) {
      (*env)->CallVoidMethod(env, jtesselator, methodID, type, polygonData);
    }
    (*env)->DeleteLocalRef(env, jtesselator); jtesselator = 0;
  }
  (*env)->PopLocalFrame(env, NULL);
}



/* The end callback. */
static void CALLBACK endData(polygonDataContainer *polygonDataContainer)
{
  // Our caller will not halt if we hit an exception, and we do not 
  // want to do anything if an exception has been thrown.
  JNIEnv* env = environmentPointerForCurrentThread();
  (*env)->PushLocalFrame(env, 16);

  if (NULL != polygonDataContainer &&
      (NULL != env) && (NULL == (*env)->ExceptionOccurred(env))) {
    jobject   jtesselator = getActiveTesselator(env);
    jobject   polygonData = polygonDataContainer->polygonData;
    jmethodID methodID    = NULL;

    methodID = getMethodIDForObject(env, jtesselator, "end", "(Ljava/lang/Object;)V", "Unable to locate the end method."); 
    if (NULL != methodID) {
      (*env)->CallVoidMethod(env, jtesselator, methodID, polygonData);
    }
    (*env)->DeleteLocalRef(env, jtesselator); jtesselator = 0;
  }
  (*env)->PopLocalFrame(env, NULL);
}



/* The vertex callback */
static void CALLBACK vertexData(vertexDataContainer  *vertexDataContainer,
				polygonDataContainer *polygonDataContainer) 
{
  // Our caller will not halt if we hit an exception, and we do not 
  // want to do anything if an exception has been thrown.
  JNIEnv* env = environmentPointerForCurrentThread();
	
  (*env)->PushLocalFrame(env, 16);
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
    (*env)->DeleteLocalRef(env, jtesselator); jtesselator = 0;
  } 
  (*env)->PopLocalFrame(env, NULL);
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
      (*env)->DeleteLocalRef(env, jtesselator);  jtesselator = 0; 
    }
  }
}


/* Implements the edge flag callback. */
static void CALLBACK edgeFlagData(GLboolean flag, polygonDataContainer *polygonDataContainer)
{
  // Our caller will not halt if we hit an exception, and we do not 
  // want to do anything if an exception has been thrown.
  JNIEnv* env = environmentPointerForCurrentThread();
  (*env)->PushLocalFrame(env, 16);
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
    (*env)->DeleteLocalRef(env, jtesselator); jtesselator = 0;
  }
  (*env)->PopLocalFrame(env, NULL);
}


////////////////////////////////////////////////////////////////////////
// The actual native methods for the GLUTesselator class.
////////////////////////////////////////////////////////////////////////



/* Returns a new tesselator. */
JNIEXPORT jlong JNICALL Java_OpenGL_GLUTesselator_newTess
(JNIEnv *env, jobject obj)
{
  GLUtesselator       *newTesselator          = NULL;
  tesselatorContainer *newTessContainer       = NULL;

  newTesselator = gluNewTess();
  if (NULL != newTesselator) {
#ifdef GLU_VERSION_1_2
    gluTessCallback(newTesselator, GLU_TESS_ERROR_DATA, errorData);
    gluTessCallback(newTesselator, GLU_TESS_BEGIN_DATA, beginData);
    gluTessCallback(newTesselator, GLU_TESS_END_DATA, endData);
    gluTessCallback(newTesselator, GLU_TESS_VERTEX_DATA, vertexData);
    gluTessCallback(newTesselator, GLU_TESS_COMBINE_DATA, combineData);
    /* We do not add in the edge flag callback, because it
       modifies the behaviour of the tesselator and we allow
       the user to control that. */
#endif
    newTessContainer = newTesselatorContainer(env);
    if (NULL != newTessContainer) {
      newTessContainer->tesselator = newTesselator; }
  }

#ifdef DEBUG
  printf("newTess %p\n", newTessContainer);
#endif
  return FROM_POINTER(newTessContainer);
}



/*  Deletes a tesselator.  */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_deleteTess
(JNIEnv *env, jobject obj, jlong tess)
{
  tesselatorContainer *container = (tesselatorContainer*)(TO_POINTER(tess));

#ifdef DEBUG
  printf("deleteTess %p\n", container);
#endif

  cleanupVertexDataList(env, container);
  cleanupPolygonDataContainer(env, container);
  gluDeleteTess(container->tesselator);
  privateFree(container);
}



/* Marks the begining of a contour. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_beginContour
(JNIEnv *env, jobject obj, jlong tess)
{
#ifdef GLU_VERSION_1_2
  tesselatorContainer *container = (tesselatorContainer*)(TO_POINTER(tess));
#ifdef DEBUG
  printf("beginContour %d %p %p\n", 
	 (int)tess, container, container->tesselator);
#endif
  gluTessBeginContour(container->tesselator);
  printf("end of beginContour\n");
#else
  handleError(env, OPENGL_UNSUPPORTED_METHOD_EXCEPTION,
	      "beginContour is not supported by the native OpenGL implementation, which has a tesselator version prior to 1.2");
#endif
}



/* Marks the begining of a polygon. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_beginPolygon
(JNIEnv *env, jobject obj, jlong tess, jobject polygonData)
{
#ifdef GLU_VERSION_1_2
  tesselatorContainer  *container            = (tesselatorContainer*)(TO_POINTER(tess));
  polygonDataContainer *polygonDataContainer = NULL;
	
#ifdef DEBUG
  printf("beginPolygon %d %p %p\n", (int)tess, container, container->tesselator);
#endif
  //polygonDataContainer = newPolygonDataContainer(env, container, polygonData);
  if (NULL != polygonDataContainer) {
    //gluTessBeginPolygon(container->tesselator, polygonDataContainer);
  }
  printf("!beginPolygon %I64d %p %p\n", tess, container, container->tesselator);
#else
  handleError(env, OPENGL_UNSUPPORTED_METHOD_EXCEPTION,
	      "beginPolygon is not supported by the native OpenGL implementation, which has a tesselator version prior to 1.2");
#endif
}



/* Marks the end of a contour. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_endContour
(JNIEnv *env, jobject obj, jlong tess)
{
#ifdef GLU_VERSION_1_2
  tesselatorContainer *container = (tesselatorContainer*)(TO_POINTER(tess));
#ifdef DEBUG
  printf("endContour\n");
#endif

  gluTessEndContour(container->tesselator);
#else
  handleError(env, OPENGL_UNSUPPORTED_METHOD_EXCEPTION,
	      "endContour is not supported by the native OpenGL implementation, which has a tesselator version prior to 1.2");
#endif
}



/* Marks the end of a polygon. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_endPolygon
(JNIEnv *env, jobject obj, jlong tess)
{
#ifdef GLU_VERSION_1_2
  tesselatorContainer *container = (tesselatorContainer*)(TO_POINTER(tess));

#ifdef DEBUG
  printf("gluTessEndPolygon %d\n", (int)tess);
  fflush(stdout);
#endif
  //gluTessEndPolygon(container->tesselator);
  //cleanupVertexDataList(env, container);
  //cleanupPolygonDataContainer(env, container);
#else
  handleError(env, OPENGL_UNSUPPORTED_METHOD_EXCEPTION,
	      "endPolygon is not supported by the native OpenGL implementation, which has a tesselator version prior to 1.2");
#endif
}



/* Describes the normal for the current polygon. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_normal
(JNIEnv *env, jobject obj, jlong tess, 
 jdouble valueX, jdouble valueY, jdouble valueZ)
{
#ifdef GLU_VERSION_1_2
  tesselatorContainer *container = (tesselatorContainer*)(TO_POINTER(tess));
#ifdef DEBUG
  printf("normal\n");
#endif

  gluTessNormal(container->tesselator, valueX, valueY, valueZ); 
#else
  handleError(env, OPENGL_UNSUPPORTED_METHOD_EXCEPTION,
	      "normal is not supported by the native OpenGL implementation, which has a tesselator version prior to 1.2");
#endif
}



/* Used to mark a vertex point. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_contourVertex
(JNIEnv *env, jobject obj, jlong tess, jdoubleArray jlocation, jobject vertexData)
{
  tesselatorContainer *tessContainer       = (tesselatorContainer*)(TO_POINTER(tess));
  vertexDataContainer *vertexDataContainer = NULL;
  GLdouble            *location            = NULL;

#ifdef DEBUG
  //printf("contourVertex\n");
#endif

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
  // Use the vertex location that has been copied into the
  // vertex container so that it will stick around for the
  // tesselator calls made out of gluTessEndPolygon().
  if (NULL != vertexDataContainer) {
    gluTessVertex(tessContainer->tesselator, vertexDataContainer->vertexLocation, 
		  vertexDataContainer);
  }

  (*env)->ReleaseDoubleArrayElements(env, jlocation, location, JNI_ABORT);
}



/* Sets a tesselator property. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_setProperty
(JNIEnv *env, jobject obj, jlong tess, jint which, jdouble data)
{
#ifdef GLU_VERSION_1_2
  tesselatorContainer *container = (tesselatorContainer*)(TO_POINTER(tess));
#ifdef DEBUG
  printf("setProperty\n");
#endif

  gluTessProperty(container->tesselator, which, data);
#else
  handleError(env, OPENGL_UNSUPPORTED_METHOD_EXCEPTION,
	      "setProperty is not supported by the native OpenGL implementation, which has a tesselator version prior to 1.2");
#endif
}



/* Gets a tesselator property. */
JNIEXPORT jdouble JNICALL Java_OpenGL_GLUTesselator_property
(JNIEnv *env, jobject obj, jlong tess, jint property)
{
  GLdouble             dataOut   = 0.0;
#ifdef GLU_VERSION_1_2
  tesselatorContainer *container = (tesselatorContainer*)(TO_POINTER(tess));
#ifdef DEBUG
  printf("property\n");
#endif

  gluGetTessProperty(container->tesselator, property, &dataOut);

#else
  handleError(env, OPENGL_UNSUPPORTED_METHOD_EXCEPTION,
	      "getProperty is not supported by the native OpenGL implementation, which has a tesselator version prior to 1.2");
#endif
  return dataOut;
}



/* Enables the edge flag callback. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_enableEdgeFlag
(JNIEnv *env, jobject obj, jlong tess)
{
#ifdef GLU_VERSION_1_2
  tesselatorContainer *container = (tesselatorContainer*)(TO_POINTER(tess));
#ifdef DEBUG
  printf("enableEdgeFlag\n");
#endif

  gluTessCallback(container->tesselator, GLU_TESS_EDGE_FLAG_DATA, edgeFlagData);
#endif
}



/* Disables the edge flag callback. */
JNIEXPORT void JNICALL Java_OpenGL_GLUTesselator_disableEdgeFlag
(JNIEnv *env, jobject obj, jlong tess)
{
#ifdef GLU_VERSION_1_2
  tesselatorContainer *container = (tesselatorContainer*)(TO_POINTER(tess));
#ifdef DEBUG
  printf("disableEdgeFlag %d\n", (int)tess);
#endif
  gluTessCallback(container->tesselator, GLU_TESS_EDGE_FLAG_DATA, NULL);
#ifdef DEBUG
  printf("!disableEdgeFlag\n");
#endif
#endif
}

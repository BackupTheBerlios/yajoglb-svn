/*
 * OpenGL_OpenGLVertexPointer.c
 * 
 * $Id$
 *
 * Copyright 1998
 * Robert Allan Zeh (razeh@yahoo.com)
 */

/* This files implements the native interface for the OpenGLVertexPointer
 * class.  All of the normal OpenGL vertex pointer functions are grouped
 * under the OpenGLVertexPointer class so that we can properly deal with
 * persistent arrays, something we can't easily do with the JNI.
 */

/* With the Cygnus tools you need to include the GL stuff first. */
#include <windows.h>
#include <GL/gl.h>

#include "cygnusFixes.h"
#include "JNIInterface.h"
#include "ErrorHandling.h"
#include "OpenGL_OpenGLVertexPointer.h"

struct javaToGLMap {
	const  char *className; /* The Java class name. */
	GLenum glType;          /* The corresponding OpenGL type. */
};



/* This returns the GLenum type appropriate for the elements of javaArrayType. */
static GLenum _glTypeForJavaType(const char *javaArrayType)
{
	struct javaToGLMap arrayTypes[] =
	{ 
		{ "[S", GL_SHORT },
		{ "[I", GL_INT },
		{ "[F", GL_FLOAT },
		{ "[D", GL_DOUBLE },
		{ "[B", GL_BYTE },
		{ "[Z", GL_BYTE }
	};

	int i;
	for(i = 0; i < sizeof(arrayTypes) / sizeof(arrayTypes[0]); i++) {
		if (0 == strcmp(arrayTypes[i].className, javaArrayType))
			return arrayTypes[i].glType;
	}
	return 0;
}

/* This calls the appropriate vertex pointer based on the given capability. */
static void _setVertexPointer(GLint size,
							  GLenum type,
			                  GLsizei stride,
			                  const GLvoid *pointer,
							  GLenum capability)
{
	switch(capability) {
	case GL_VERTEX_ARRAY:
		glVertexPointer(size, type, stride, pointer);
		break;
	case GL_NORMAL_ARRAY:
		glNormalPointer(type, stride, pointer);
		break;
	case GL_COLOR_ARRAY:
		glColorPointer(size, type, stride, pointer);
		break;
	case GL_INDEX_ARRAY:
		glIndexPointer(type, stride, pointer);
		break;
	case GL_TEXTURE_COORD_ARRAY:
		glTexCoordPointer(size, type, stride, pointer);
		break;
	case GL_EDGE_FLAG_ARRAY:
		glEdgeFlagPointer(stride, pointer);
	}
}



JNIEXPORT void JNICALL Java_OpenGL_OpenGLVertexPointer_drawArrays
  (JNIEnv *env, jobject vertexPointerObject,
    jint mode, jint first, jint count, 
	jobject jvertexPointer, jint vertexPointerSize, jint vertexPointerStride, 
	jobject jnormalPointer, jint normalPointerStride,
	jobject jcolorPointer, jint colorPointerSize, jint colorPointerStride,
	jobject jindexPointer, jint indexPointerStride,
	jobject jtexCoordPointer, jint texCoordPointerSize, jint texCoordPointerStride,
	jbooleanArray jedgeFlagPointer, jint edgeFlagPointerStride)
{
	struct vertexArrayDescription {
       arrayElements nativeArray; /* The native portion of the vertex array. */
	   jobject       jarray;      /* The java side of the array. */
       GLenum        capability;  /* The OpenGL array label. */
	   GLint         size;        /* The size parameter for this capability. */
	   GLsizei       stride;      /* The stride for this vertex array. */
	};
	
	struct vertexArrayDescription vertexArray[6];

    const int vertexArrayCount = sizeof(vertexArray)/sizeof(vertexArray[0]);
	int i;

	/* Fill in our vertex array with the correct parameter information. */
	vertexArray[0].jarray     = jvertexPointer;
	vertexArray[0].capability = GL_VERTEX_ARRAY;
	vertexArray[0].size       = vertexPointerSize;
	vertexArray[0].stride     = vertexPointerStride;
	
	vertexArray[1].jarray     = jnormalPointer;
 	vertexArray[1].capability = GL_NORMAL_ARRAY;
	vertexArray[1].stride     = normalPointerStride;
   
	vertexArray[2].jarray     = jcolorPointer;
	vertexArray[2].capability = GL_COLOR_ARRAY;
	vertexArray[2].size       = colorPointerSize;
	vertexArray[2].stride     = colorPointerStride;

	vertexArray[3].jarray     = jindexPointer;
	vertexArray[3].capability = GL_INDEX_ARRAY;
	vertexArray[3].stride     = indexPointerStride;

	vertexArray[4].jarray     = jtexCoordPointer;
	vertexArray[4].capability = GL_TEXTURE_COORD_ARRAY;
	vertexArray[4].size       = texCoordPointerSize;
	vertexArray[4].stride     = texCoordPointerStride;

	vertexArray[5].jarray     = jedgeFlagPointer;
	vertexArray[5].capability = GL_EDGE_FLAG_ARRAY;
	vertexArray[5].stride     = edgeFlagPointerStride;

	/* Setup each of our arrays, skipping over the null ones. */
	for(i = 0; i < vertexArrayCount; i++) {
		jboolean isCopy;
		if (0 != vertexArray[i].jarray) {
			vertexArray[i].nativeArray =
				getArrayElements(env, vertexArray[i].jarray, &isCopy);
			if (NULL == vertexArray[i].nativeArray.arrayElements) {
				/* Something went wrong --- release our allocated arrays and return. */
				int j;
				for(j = i - 1 ; j >= 0; j--) {
					releaseArrayElements(env, vertexArray[j].jarray,
						vertexArray[j].nativeArray.arrayElements, JNI_ABORT);
				}
				return;
			}
			glEnableClientState(vertexArray[i].capability);
			_setVertexPointer(vertexArray[i].size,
				_glTypeForJavaType(vertexArray[i].nativeArray.elementType),
				vertexArray[i].stride,
				vertexArray[i].nativeArray.arrayElements,
				vertexArray[i].capability);
		} else {
			glDisableClientState(vertexArray[i].capability);
		}
	}

	/* Actually draw the arrays! */
	glDrawArrays(mode, first, count);


	/* Clean everything up. */
	for(i = 0; i < vertexArrayCount; i++) {
		if (0 != vertexArray[i].jarray) {
			glDisableClientState(vertexArray[i].capability);
			if (0 != releaseArrayElements(env, vertexArray[i].jarray,
				vertexArray[i].nativeArray.arrayElements, JNI_ABORT))
				return;
		}
	}
}


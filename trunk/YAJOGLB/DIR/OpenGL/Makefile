# Some Cygnus tools stuff

include ../Makefile.common
include ../Makefile.config

# Some rules for compiling java

CLASSPATH     = -classpath "..$(DIR_SEPARATOR)$(CLASSPATH_SEPARATOR)$(JLIB)"
JFLAGS        = $(CLASSPATH) $(OPTIMIZATIONFLAG)

JAVA_SRC        = GLConstants.java CHeapItem.java CallbackObject.java \
                  OpenGLCapabilities.java \
		  GLUConstants.java \
	          GLUNurbs.java GLUQuadric.java \
		  OpenGLNativeException.java \
	          OpenGLNativeMemoryExhaustedException.java TGAFile.java \
	          OpenGLTextureHelp.java GLVertexPointer.java \
		  OpenGLContext.java OpenGLContextException.java GLU.java \
		  GL.java OpenGLpDataAccess.java OpenGLCanvas.java \
		  GLFeedbackBuffer.java  \
	          OpenGLCanvasSetupFailedException.java GLUTesselator.java \
		  GLNativeArray.java GLNativeFloatArray.java \
		  GLNativeIntArray.java GLSelectionBuffer.java 


JAVA_CLASSES    = GLConstants.class CallbackObject.class CHeapItem.class \
                  OpenGLCapabilities.class \
		  GLUConstants.class \
	          GLUNurbs.class GLUQuadric.class \
		  OpenGLNativeException.class \
	          OpenGLNativeMemoryExhaustedException.class TGAFile.class \
	          OpenGLTextureHelp.class GLVertexPointer.class \
	          OpenGLContext.class OpenGLContextException.class GLU.class \
		  GL.class OpenGLpDataAccess.class OpenGLCanvas.class \
		  GLFeedbackBuffer.class \
		  OpenGLCanvasSetupFailedException.class GLUTesselator.class \
		  GLNativeArray.class GLNativeFloatArray.class \
		  GLNativeIntArray.class GLSelectionBuffer.class 


all : $(JAVA_CLASSES)

checkout :
	$(CO) $(JAVA_SRC)
clean :
	$(RM) $(JAVA_CLASSES) $(JAVA_CLASSES) *~


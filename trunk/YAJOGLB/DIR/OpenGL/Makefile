# Some Cygnus tools stuff

# Some rules for compiling java
JAVAH         = javah
JAVAC         = javac
JLIB          = C:\jdk1.1.4\lib\classes.zip
CLASSPATH     = -classpath "..;$(JLIB)"
JFLAGS        = $(CLASSPATH) -g
SUFFIXES     += .class .java
COMPILE.java  = $(JAVAC) $(JFLAGS) 
%.class: %.java
	$(COMPILE.java) $<

JAVA_SRC        = GLConstants.java \
                  OpenGLCapabilities.java \
		  GLUConstants.java \
	          GLUNurbs.java GLUQuadric.java \
		  CHeapItem.java OpenGLNativeException.java \
	          OpenGLNativeMemoryExhaustedException.java TGAFile.java \
	          OpenGLTextureHelp.java GLVertexPointer.java \
		  OpenGLContext.java OpenGLContextException.java GLU.java \
		  GL.java OpenGLpDataAccess.java OpenGLCanvas.java \
		  GLFeedbackBuffer.java CallbackObject.java \
	          OpenGLCanvasSetupFailedException.java GLUTesselator.java \
		  GLNativeArray.java GLNativeFloatArray.java \
		  GLNativeIntArray.java GLSelectionBuffer.java

JAVA_CLASSES    = GLConstants.class \
                  OpenGLCapabilities.class \
		  GLUConstants.class \
	          GLUNurbs.class GLUQuadric.class \
		  CHeapItem.class OpenGLNativeException.class \
	          OpenGLNativeMemoryExhaustedException.class TGAFile.class \
	          OpenGLTextureHelp.class GLVertexPointer.class \
	          OpenGLContext.class OpenGLContextException.class GLU.class \
		  GL.class OpenGLpDataAccess.class OpenGLCanvas.class \
		  GLFeedbackBuffer.class CallbackObject.class \
		  OpenGLCanvasSetupFailedException.class GLUTesselator.class \
		  GLNativeArray.class GLNativeFloatArray.class \
		  GLNativeIntArray.class GLSelectionBuffer.class

NATIVE_CLASSES  = OpenGLWidget
NATIVE_DIR      = ../CNativeCode
all : $(JAVA_CLASSES)

clean :
	$(RM) $(JAVA_CLASSES) $(JAVA_CLASSES) *~


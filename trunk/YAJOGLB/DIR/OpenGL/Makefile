# Some Cygnus tools stuff

include ../Makefile.common
include ../Makefile.config

# Some rules for compiling java

CLASSPATH     = -classpath "..$(DIR_SEPARATOR)$(CLASSPATH_SEPARATOR)$(JLIB)"
JFLAGS        = $(CLASSPATH) $(OPTIMIZATIONFLAG)

JAVA_SRC      = GLConstants.java CHeapItem.java CallbackObject.java	\
                Capabilities.java GLUConstants.java			\
	        NativePackageLoader.java				\
	        GLUNurbs.java GLUQuadric.java				\
		NativeException.java					\
	        NativeMemoryExhaustedException.java TGAFile.java	\
	        TextureHelp.java GLVertexPointer.java			\
		Context.java ContextException.java GLU.java		\
		GL.java OpenGLpDataAccess.java Canvas.java		\
		GLFeedbackBuffer.java					\
	        CanvasSetupFailedException.java GLUTesselator.java	\
		GLNativeArray.java GLNativeFloatArray.java		\
		GLNativeIntArray.java GLSelectionBuffer.java		\
		UnsupportedMethodException.java

JAVA_CLASSES    = $(JAVA_SRC:.java=.class)

all : $(JAVA_CLASSES)


checkout :
	$(CO) $(JAVA_SRC)
clean :
	$(RM) $(JAVA_CLASSES) $(JAVA_CLASSES) *~


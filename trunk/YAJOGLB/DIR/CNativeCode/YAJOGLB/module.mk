
CFLAGS += $(JNI_GENERIC_HEADERS) $(JNI_SPECIFIC_HEADERS) $(GL_INCLUDES) -DUSE_JAWT
CSRCS += CNativeCode/YAJOGLB/CallbackObject.c			\
	 CNativeCode/YAJOGLB/OpenGL_GLUQuadric.c		\
	 CNativeCode/YAJOGLB/ErrorHandling.c			\
	 CNativeCode/YAJOGLB/JNIInterface.c			\
         CNativeCode/YAJOGLB/OpenGL_GLVertexPointer.c		\
	 CNativeCode/YAJOGLB/OpenGL_CallbackObject.c		\
         CNativeCode/YAJOGLB/OpenGL_Canvas.c			\
	 CNativeCode/YAJOGLB/OpenGL_GL.c			\
	 CNativeCode/YAJOGLB/OpenGL_GLFeedbackBuffer.c		\
         CNativeCode/YAJOGLB/CapabilitiesAccessors.c		\
	 CNativeCode/YAJOGLB/OpenGL_GLNativeFloatArray.c	\
	 CNativeCode/YAJOGLB/OpenGL_GLNativeIntArray.c		\
	 CNativeCode/YAJOGLB/OpenGL_GLSelectionBuffer.c		\
         CNativeCode/YAJOGLB/OpenGL_GLUTesselator.c		\
	 CNativeCode/YAJOGLB/OpenGL_GLU.c			\
         CNativeCode/YAJOGLB/OpenGL_GLUNurbs.c			\
	 CNativeCode/YAJOGLB/linux_OpenGL_Canvas.c		\
         CNativeCode/YAJOGLB/linux_OpenGL_Context.c		\
	 CNativeCode/YAJOGLB/linuxDPYDictionary.c		\
         CNativeCode/YAJOGLB/linuxMemory.c			\
         CNativeCode/YAJOGLB/linuxSystemError.c			\
	 CNativeCode/YAJOGLB/linuxEnvDictionary.c		\
         CNativeCode/YAJOGLB/linux_OpenGL_GL.c


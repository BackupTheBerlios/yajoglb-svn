# This is the portion of the makefile for the native code
CSRCS:=
include CNativeCode/YAJOGLB/module.mk

# The header files for our native code
NATIVEHEADERS := OpenGL_GLUQuadric.h OpenGL_GLUNurbs.h OpenGL_Context.h OpenGL_GLUTesselator.h OpenGL_GLU.h OpenGL_GL.h OpenGL_GLVertexPointer.h OpenGL_Canvas.h OpenGL_GLFeedbackBuffer.h OpenGL_CallbackObject.h OpenGL_GLNativeFloatArray.h OpenGL_GLNativeIntArray.h OpenGL_GLSelectionBuffer.h OpenGL_GLUT.h
NATIVEHEADERS := $(NATIVEHEADERS:%.h=$(NATIVECODEDIR)/%.h)

# How to actually build the automatic Java headers.  On my system
# javah isn't updating the timestamp, so I've added the touch.
$(NATIVECODEDIR)/OpenGL_%.h: $(PACKAGEDIR)/%.class
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(subst /,.,$(basename $<))
	touch $@

OBJS := $(CSRCS:.c=.o)

%.d: %.c
	python bin$(DIR_SEPARATOR)depend.py $(CFLAGS) $< > $@


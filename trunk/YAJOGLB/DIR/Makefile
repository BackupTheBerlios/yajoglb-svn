# Some rules and constants for compiling java
PACKAGEDIR    = OpenGL
JAVAC         = javac
JAVAH         = javah
JAVADOC       = javadoc
JFLAGS        = 
TAR           = tar
RM            = rm
SUFFIXES     += .class .java
COMPILE.java  = $(JAVAC) $(JFLAGS) 
%.class: %.java
	$(COMPILE.java) $<

DOCDIR          = documentation
JAVA_SRC        = OpenGLWidgetTest.java MatrixModifiers.java \
                  SizeChanger.java OpenGLSphereAndCube.java \
                  OpenGLSphereAndTexturedCube.java
JAVA_CLASSES    = OpenGLWidgetTest.class MatrixModifiers.class \
                  SizeChanger.class OpenGLSphereAndCube.class \
                  OpenGLSphereAndTexturedCube.class
NATIVECODEDIR   = CNativeCode      		  

# Some Cygnus tools stuff
SHELL=/gnuwin32/b18/H-i386-cygwin32/bin/sh

# The header files for our native code
NATIVEHEADERS = OpenGL_OpenGLWidget.h \
		OpenGL_GLUQuadric.h OpenGL_GLUNurbs.h \
	        OpenGL_GLUTriangulator.h OpenGL_OpenGLContext.h \
                OpenGL_OpenGLVertexPointer.h

all :   packagedir $(JAVA_CLASSES) nativedir

packagedir:
	(cd $(PACKAGEDIR); $(MAKE))
	jar -cvf0 OpenGL.jar $(PACKAGEDIR)/*.class

nativedir:
	(cd $(NATIVECODEDIR); $(MAKE) install)

dist : clean
	(cd ..; $(RM) -f OpenGL-Java.tar)
	(cd ..; $(TAR) cvf OpenGL-Java.tar Win32-OpenGL-Java)
	(cd ..; gzip -v OpenGL-Java.tar)

clean :
	$(RM) -f $(JAVA_CLASSES) $(JAVA_CLASSES) *~ *.class
	(cd $(PACKAGEDIR); $(MAKE) clean)
	(cd $(NATIVECODEDIR); $(MAKE) clean)
	(cd OpenGLLibFixes; $(MAKE) clean)


documentation ::
	$(JAVADOC) -d $(DOCDIR) OpenGL

OpenGL_OpenGLWidget.h: $(PACKAGEDIR)/OpenGLWidget.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).OpenGLWidget

OpenGL_GLUQuadric.h: $(PACKAGEDIR)/GLUQuadric.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLUQuadric

OpenGL_GLUNurbs.h: $(PACKAGEDIR)/GLUNurbs.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLUNurbs

OpenGL_GLUTriangulator.h: $(PACKAGEDIR)/GLUTriangulator.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLUTriangulator

OpenGL_OpenGLContext.h: $(PACKAGEDIR)/OpenGLContext.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).OpenGLContext

OpenGL_OpenGLVertexPointer.h: $(PACKAGEDIR)/OpenGLVertexPointer.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).OpenGLVertexPointer






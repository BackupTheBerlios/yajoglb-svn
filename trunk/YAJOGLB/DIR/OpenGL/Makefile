# Some Cygnus tools stuff
SHELL         =/gnuwin32/b18/H-i386-cygwin32/bin/sh
# Some rules for compiling java
JAVAH         = javah
JAVAC         = javac
JLIB          = C:\jdk1.1.3\lib\classes.zip
CLASSPATH     = -classpath "..;$(JLIB)"
JFLAGS        = $(CLASSPATH) 
SUFFIXES     += .class .java
COMPILE.java  = $(JAVAC) $(JFLAGS) 
%.class: %.java
	$(COMPILE.java) $<

JAVA_SRC        = OpenGLConstants.java OpenGLWidgetOpenFailedException.java \
		  OpenGLWidget.java OpenGLEvent.java OpenGLUConstants.java \
	          GLUTriangulator.java GLUNurbs.java GLUQuadric.java \
		  CHeapItem.java OpenGLNativeException.java \
	          OpenGLNativeMemoryExhausted.java TGAFile.java \
	          OpenGLTextureHelp.class

JAVA_CLASSES    = OpenGLConstants.class OpenGLWidgetOpenFailedException.class \
		  OpenGLWidget.class OpenGLEvent.class OpenGLUConstants.class \
	          GLUTriangulator.class GLUNurbs.class GLUQuadric.class \
		  CHeapItem.class OpenGLNativeException.class \
	          OpenGLNativeMemoryExhausted.class TGAFile.class \
	          OpenGLTextureHelp.class

NATIVE_CLASSES  = OpenGLWidget
NATIVE_DIR      = ../CNativeCode
all : $(JAVA_CLASSES)

clean :
	$(RM) $(JAVA_CLASSES) $(JAVA_CLASSES) *~


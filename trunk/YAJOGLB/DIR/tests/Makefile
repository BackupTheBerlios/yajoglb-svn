# Some Cygnus tools stuff
SHELL         =/gnuwin32/b18/H-i386-cygwin32/bin/sh
# Some rules for compiling java
JAVAH         = javah
JAVAC         = javac
JLIB          = C:\jdk1.1.4\lib\classes.zip
CLASSPATH     = -classpath ".;..;$(JLIB)"
JFLAGS        = $(CLASSPATH) -g
SUFFIXES     += .class .java
COMPILE.java  = $(JAVAC) $(JFLAGS) 
%.class: %.java
	$(COMPILE.java) $<

JAVA_SRC        = VertexPointer.java Stretch.java NurbsSurface.java \
		  GeometryViewer.java GeometryObject.java PlainCube.java \
		  Vec.java OpenGLCanvasTest.java Concurrence.java \
		  ExitableFrame.java MatrixModifiers.java Sphere.java \
		  Feedback.java Axis.java TexturedCube.java

JAVA_CLASSES    = VertexPointer.class Stretch.class NurbsSurface.class \
		  GeometryViewer.class GeometryObject.class PlainCube.class \
		  Vec.class OpenGLCanvasTest.class Concurrence.class \
		  ExitableFrame.class MatrixModifiers.class Sphere.class \
		  Feedback.class Axis.class TexturedCube.class

all : $(JAVA_CLASSES)

clean :
	$(RM) $(JAVA_CLASSES) $(JAVA_CLASSES) *~


# Some Cygnus tools stuff

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
		  Feedback.java Axis.java TexturedCube.java Simplest.java \
		  TessVertex.java QuadricError.java NurbsCallback.java \
		  Select.java


JAVA_CLASSES    = VertexPointer.class Stretch.class NurbsSurface.class \
		  GeometryViewer.class GeometryObject.class PlainCube.class \
		  Vec.class OpenGLCanvasTest.class Concurrence.class \
		  ExitableFrame.class MatrixModifiers.class Sphere.class \
		  Feedback.class Axis.class TexturedCube.class Simplest.class \
		  TessVertex.class QuadricError.class NurbsCallback.class \
		  Select.class 

all : $(JAVA_CLASSES)


GeometryObject.class: GeometryViewer.java Vec.class MatrixModifiers.class
GeometryViewer.class: GeometryObject.java Vec.class MatrixModifiers.class
baseClasses: GeometryObject.class GeometryViewer.class ExitableFrame.class Axis.class
VertexPointer.class: baseClasses
NurbsSurface.class: baseClasses
PlainCube.class: baseClasses
Concurrence.class: baseClasses Sphere.class
Sphere.class: baseClasses
TexturedCube.class: baseClasses


clean :
	$(RM) $(JAVA_CLASSES) $(JAVA_CLASSES) *~


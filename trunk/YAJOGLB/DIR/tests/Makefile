# Some Cygnus tools stuff

include ../Makefile.common
include ../Makefile.config

# Some rules for compiling java
CLASSPATH     = -classpath "..$(CLASSPATH_SEPARATOR).$(CLASSPATH_SEPARATOR)$(JLIB)"
JFLAGS        = $(CLASSPATH) $(OPTIMIZATIONFLAG)

JAVA_SRC        = VertexPointer.java Stretch.java NurbsSurface.java \
		  GeometryViewer.java GeometryObject.java PlainCube.java \
		  Vec.java OpenGLCanvasTest.java Concurrence.java \
		  ExitableFrame.java MatrixModifiers.java Sphere.java \
		  Feedback.java Axis.java TexturedCube.java Simplest.java \
		  TessVertex.java QuadricError.java NurbsCallback.java \
		  Select.java TurningAxis.java InfoPanel.java


JAVA_CLASSES    = VertexPointer.class Stretch.class NurbsSurface.class \
		  GeometryViewer.class GeometryObject.class PlainCube.class \
		  Vec.class OpenGLCanvasTest.class Concurrence.class \
		  ExitableFrame.class MatrixModifiers.class Sphere.class \
		  Feedback.class Axis.class TexturedCube.class Simplest.class \
		  TessVertex.class QuadricError.class NurbsCallback.class \
		  Select.class TurningAxis.class InfoPanel.class

all : $(JAVA_CLASSES)


GeometryObject.class: GeometryViewer.java Vec.java MatrixModifiers.java
GeometryViewer.class: GeometryObject.java Vec.java MatrixModifiers.java InfoPanel.java
baseClasses: GeometryObject.java GeometryViewer.java ExitableFrame.java Axis.java
VertexPointer.class: baseClasses Vec.java MatrixModifiers.java
NurbsSurface.class: baseClasses
PlainCube.class: baseClasses
Concurrence.class: baseClasses Sphere.java TurningAxis.java
Sphere.class: baseClasses
TexturedCube.class: baseClasses
GeometryViewer.java: InfoPanel.java

checkout:
	$(CO) $(JAVA_SRC)

clean :
	$(RM) $(JAVA_CLASSES) $(JAVA_CLASSES) *.class TAGS


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
		  Select.java TurningAxis.java InfoPanel.java \
		  StretchTexture.java


JAVA_CLASSES    = $(JAVA_SRC:.java=.class)

all : $(JAVA_CLASSES)

clean :
	$(RM) *.class TAGS


This directory containts tests (mostly taken from various C OpenGL
examples) I've used to make sure that my OpenGL bindings are working
properly.  Currently I don't have anything like complete coverage, but
I do have tests for the areas I'm worried about.

Stretch.java		This should come up with a image that you can stretch
			by clicking with the mouse.

NurbsSurface.java	This produces a hill with the GLU nurbs functions.

VertexPointerTest.java	Uses the vertex pointer routines to draw a cube.

FeedbackTest.java	Make sure that feedback mode actually works.

If you want to run the tests you need to use a command line something
like this:

	jre -cp .;.. className


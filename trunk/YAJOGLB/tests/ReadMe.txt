This directory contains tests (mostly taken from various C OpenGL
examples) I've used to make sure that my OpenGL bindings are working
properly.  Currently I don't have anything like complete coverage, but
I do have tests for the areas I'm worried about.

Concurrence.java	Tests the binding's ability to render in multiple
			canvases concurrently.

FeedbackTest.java	Makes sure that feedback mode actually works.

PlainCube.java	Draws a simple plain cube with an axis.

Stretch.java		This should come up with a image that you can stretch
			by clicking with the mouse.

NurbsSurface.java	This produces a hill with the GLU nurbs functions.

OpenGLCanvasTest.java	Demonstrates the ability to embed an
			OpenGLCanvas in a window with other AWT components.
		
VertexPointerTest.java	Uses the vertex pointer routines to draw a cube.




Most of the demos use the GeometryViewer, which allows you to navigate
through the rendered geometry.  Dragging the mouse will drag your view
along with it, and the keys are set up as follows:

    A           - move forward
    Z           - move backward
    .           - rotate the Z axis
    /           - rotate the Z axis
    Q	        - do an orbit view (rotate around a point in front of you).
    E	        - do an orbit view, in the opposite direction.
    I		- display information about the OpenGL library being used.
    W		- write out a TGA image of the screen to test.tga.
    Up arrow    - rotate up
    Down arrow  - rotate down
    Left arrow  - rotate left
    Right arrow - rotate right



If you want to run the tests you need to use a command line something
like this:

	jre -cp .;.. className


/* 
 * GLVertexPointer class
 *
 * $Id: GLVertexPointer.java,v 1.2 1998/11/01 02:17:30 razeh Exp $
 *
 * Copyright 1997
 * Robert Allan Zeh (razeh@balr.com)
 */

package OpenGL;

/**
*
 * OpenGL's vertex pointers present a simple problem for Java
 * bindings: persistent arrays.  The Java Native Interface allows you
 * to map Java array's to C arrays, but the mapping may be different
 * from call to call, or from thread to thread.  If you don't release
 * the array outside of a JNI call, you run the risk of a memory
 * leak. If The C array pointer may even point to a copy of the actual
 * Java array, rather than the actual array. <P>
 *
 * The approach I've taken is to gather up all of the OpenGL vertex
 * pointers into this class, and add some native methods that draw the
 * vertices. <P>
 *
 * @author Robert Allan Zeh (razeh@balr.com)
 *
 * @version 0.1 */

public class GLVertexPointer extends Object {

  private Object vertexPointer;
  private int    vertexPointerSize   = 4;
  private int    vertexPointerStride = 0;

  private Object normalPointer;
  private int    normalPointerStride;
  
  private Object colorPointer;
  private int    colorPointerSize   = 3;
  private int    colorPointerStride = 0;

  private Object indexPointer;
  private int    indexPointerStride = 0;

  private Object texCoordPointer;
  private int    texCoordPointerSize   = 4;
  private int    texCoordPointerStride = 0;

  private boolean edgeFlagPointer[];
  private int     edgeFlagPointerStride;

  /*
   *
   *  Vertex pointer methods
   *
   */

  /** Sets the vertex pointer to the supplied float array.
    @param pointer an array of vertices */
  public void setVertexPointer(float pointer[]) {
    vertexPointer = pointer;
  }
  /** Sets the vertex pointer to the supplied double array. 
    @param pointer an array of vertices 
    */
  public void setVertexPointer(double pointer[]) {
    vertexPointer = pointer;
  }
  /** This sets the vertex pointer to the supplied int array.
    @param pointer an array of vertices */
  public void setVertexPointer(int pointer[]) {
    vertexPointer = pointer;
  }
  /** Sets the vertex pointer to the supplied short array.
    @param pointer an array of vertices */
  public void setVertexPointer(short pointer[]) {
    vertexPointer = pointer;
  }
  /** Returns the vertex pointer, which will be a nil, a pointer
      to an array of floats, doubles, integers, or shorts. */
  public Object vertexPointer() {
    return vertexPointer;
  }
  /** Sets the stride used for the vertex array.  By default it is 0.
    @param newStride the future vertex array stride
    @exception IllegalArgumentException thrown if newStride is negative */
  public void setVertexPointerStride(int newStride) {
    if (newStride >= 0) 
      vertexPointerStride = newStride;
    else 
      throw new 
	java.lang.IllegalArgumentException("A stride must be positive");
  }
  /** Returns the current stride for the vertex array. */
  public int vertexPointerStride() {
    return vertexPointerStride;
  }
  /** Sets the number of coordinates per vertex in our vertex
      array.  It must be 2, 3, or 4, and defaults to 4. 
     @param newSize the number of coordinates per vertex in our vertex array.
     @exception IllegalArgumentException thrown if newSize is not 2,3, or 4. */
  public void setVertexPointerSize(int newSize) {
    switch(newSize) {
    case 2:
    case 3:
    case 4:
      vertexPointerSize = newSize;
      break;
    default:
      throw new 
	java.lang.IllegalArgumentException("A vertex pointer size must be 2, 3, or 4");
    }
  }
  /** Returns the current number of coordinates per vertex. */
  public int vertexPointerSize() {
    return vertexPointerSize;
  }

  /*
   *
   *  Normal pointer methods
   *
   */

  /** Sets the normal pointer to the supplied float array. 
    @param pointer the normal pointer array*/
  public void setNormalPointer(float pointer[]) {
    normalPointer = pointer;
  }
  /** Sets the normal pointer to the supplied double array. */
  public void setNormalPointer(double pointer[]) {
    normalPointer = pointer;
  }
  /** Sets the normal pointer to the supplied int array. */
  public void setNormalPointer(int pointer[]) {
    normalPointer = pointer;
  }
  /** Sets the normal pointer to the supplied short array. */
  public void setNormalPointer(short pointer[]) {
    normalPointer = pointer;
  }
  /** This sets the normal pointer to the supplied byte array. */
  public void setNormalPointer(byte pointer[]) {
    normalPointer = pointer;
  }
  /** This sets the stride used for the normal pointer.  By default it is 0. 
   @exception IllegalArgumentException thrown if stride is negative.*/
  public void setNormalPointerStride(int newStride) {
    if (newStride >= 0) 
      normalPointerStride = newStride;
    else
      throw new
	java.lang.IllegalArgumentException("A stride must be non-negative");
  }
  /** This returns the normal array, which is null, or an array of
      bytes, integers, shorts, floats, or doubles. */
  public Object normalPointer() {
    return normalPointer;
  }
  /** This returns the stride being used for the normal array. */
  public int normalPointerStride() {
    return normalPointerStride;
  }

  /*
   *
   *  Color pointer methods
   *
   */

  /** Sets the color pointer to the supplied float array.
    @param pointer an array of colors. */
  public void setColorPointer(float pointer[]) {
    colorPointer = pointer;
  }
  /** Sets the color pointer to the supplied double array,
    @param pointer an array of colors. */
  public void setColorPointer(double pointer[]) {
    colorPointer = pointer;
  }

  /** Sets the color pointer to the supplied integer array.
    @param piinter an array of colors. */
  public void setColorPointer(int pointer[]) {
    colorPointer = pointer;
  }
  
  /** Sets the color pointer to the supplied short array.
    @param pointer an array of colors. */
  public void setColorPointer(short pointer[]) {
    colorPointer = pointer;
  }

  /** Sets the color pointer to the supplied byte array. 
    @param pointer an array of colors. */
  public void setColorPointer(byte pointer[]) {
    colorPointer = pointer;
  }
  /** Returns the color pointer.
    @return the color pointer, which is nil or an array of bytes, shorts,
    floats, ints, or doubles. */
  public Object colorPointer() {
    return colorPointer;
  }
  
  /** Sets the stride used for the color array.  By default it is 0.
    @param newStride the new color array stride.
    @exception IllegalArgumentException thrown if newStride is negative. */
  public void setColorPointerStride(int newStride) {
    if (newStride >= 0)
      colorPointerStride = newStride;
    else
      throw new 
	java.lang.IllegalArgumentException("A stride must be non-negative");
  }

  /** Returns the current stride for the color array.
    @return the current stride for the color array. */
  public int colorPointerStride() {
    return colorPointerStride;
  }

  /** Sets the number of elements per color in our vertex array.  
    @param newSize the number of elements per color.  Must be 3 or 4.
    @exception IllegalArgumentException thrown if newSize is not 3 or 4. */
  public void setColorPointerSize(int newSize) {
    switch(newSize) {
    case 3:
    case 4:
      colorPointerSize = newSize;
      break;
    default:
      throw new 
	java.lang.IllegalArgumentException("A color pointer size must be 3 or 4");
    }
  }

  /** Returns the current color pointer size. 
    @return the number of array elements each color occupies */
  public int colorPointerSize() {
    return colorPointerSize;
  }

  /*
   *
   *  Index pointer methods
   *
   */

  /** Sets the index pointer to the supplied byte array.
    @param pointer an array of vertices */
  public void setIndexPointer(byte pointer[]) {
    indexPointer = pointer;
  }

  /** Sets the index pointer to the supplied short array.
    @param pointer an array of vertices */
  public void setIndexPointer(short pointer[]) {
    indexPointer = pointer;
  }
  /** Sets the index pointer to the supplied int array.
    @param pointer an array of vertices */
  public void setIndexPointer(int pointer[]) {
    indexPointer = pointer;
  }
  /** Sets the index pointer to the supplied float array.
    @param pointer an array of vertices */
  public void setIndexPointer(float pointer[]) {
    indexPointer = pointer;
  }
  /** Sets the index pointer to the supplied double array.
    @param pointer an array of vertices */
  public void setIndexPointer(double pointer[]) {
    indexPointer = pointer;
  }

  /** Returns the index pointer. 
    @returns the index pointer, which is
    either nil or a byte, short, int, float, or double pointer. */
  public Object indexPointer() {
    return indexPointer;
  }

  /** Sets the stride used for the index pointer.  By default the stride is 0. 
    @exception IllegalArgumentException thrown if newStride is negative. */
  public void setIndexPointerStride(int newStride) {
    if (newStride > 0)
      indexPointerStride = newStride;
    else
      throw new 
	java.lang.IllegalArgumentException("A stride must be non-negative");
  }

  /** Returns the stride in use for the index array. */
  public int indexPointerStride() {
    return indexPointerStride;
  }

  /*
   *
   *  Texture coordinate pointer pointer methods
   *
   */
  
  /** Sets the texCoord pointer to the supplied short array.
    @param pointer an array of vertices */
  public void setTexCoordPointer(short pointer[]) {
    texCoordPointer = pointer;
  }
  /** Sets the texCoord pointer to the supplied int array.
    @param pointer an array of vertices */
  public void setTexCoordPointer(int pointer[]) {
    texCoordPointer = pointer;
  }
  /** Sets the texCoord pointer to the supplied float array.
    @param pointer an array of vertices */
  public void setTexCoordPointer(float pointer[]) {
    texCoordPointer = pointer;
  }
  /** Sets the texCoord pointer to the supplied double array.
    @param pointer an array of vertices */
  public void setTexCoordPointer(double pointer[]) {
    texCoordPointer = pointer;
  }

  /** Returns the texCoord pointer. 
    @returns the texCoord pointer, which is
    either nil or a short, int, float, or double pointer. */
  public Object texCoordPointer() {
    return texCoordPointer;
  }

  /** This sets the stride used for the texCoord pointer.  By default
      it is 0. */
  public void setTexCoordPointerStride(int newStride) {
    if (newStride >= 0) 
      texCoordPointerStride = newStride;
    else
      throw new
	java.lang.IllegalArgumentException("A stride must be non-negative");
  }

  /** Returns the stride in use for texture coordinates. */
  public int texCoordPointerStride() {
    return texCoordPointerStride;
  }

  /** Sets the number of coordinates per vertex in our vertex
      array.  It must be 1, 2, 3, or 4, and defaults to 4. 
     @param newSize the number of coordinates per vertex in our vertex array.
     @exception IllegalArgumentException thrown if newSize is not 1, 2,3, or 4. */
  public void setTexCoordPointerSize(int newSize) {
    switch(newSize) {
    case 1:
    case 2:
    case 3:
    case 4:
      vertexPointerSize = newSize;
      break;
    default:
      throw new 
	java.lang.IllegalArgumentException("A texture coordinate pointer size must be 1, 2, 3, or 4");
    }
  }
  /** Returns the current number of coordinates per vertex for the texture
    coordinates. */
  public int texCoordPointerSize() {
    return texCoordPointerSize;
  }

  /*
   *
   *  Edge flag pointer pointer methods
   *
   */
  /** Sets the edge flag pointer array.
    @param pointer an array of edge flags */
  public void setEdgeFlagPointer(boolean pointer[]) {
    edgeFlagPointer = pointer;
  }

  /** Returns the edge flag pointer. */
  public boolean [] edgeFlagPointer() {
    return edgeFlagPointer;
  }
  
  /** Sets the stride used for the edge flag array.  By default it is 0.
    @param newStride the future edge flag pointer stride
    @exception IllegalArgumentException thrown if newStride is negative */
  public void setEdgeFlagPointerStride(int newStride) {
    if (newStride > 0)
      edgeFlagPointerStride = newStride;
    else
      throw new 
	java.lang.IllegalArgumentException("A stride must be positive");
  }

  /** Returns the stride in use for the edge flag array. */
  public int edgeFlagPointerStride() {
    return edgeFlagPointerStride;
  }
 
  private native void drawArrays(int mode, int first, int count,
				 Object vertexPointer, 
				 int vertexPointerSize,
				 int vertexPointerStride,
				 Object normalPointer, 
				 int normalPointerStride,
				 Object colorPointer, 
				 int colorPointerSize,
				 int colorPointerStride,
				 Object indexPointer,
				 int indexPointerStride,
				 Object texCoordPointer,
				 int texCoordPointerSize,
				 int texCoordPointerStride,
				 boolean edgeFlagPointer[],
				 int edgeFlagPointerStride);

  /** Draws our vertices using our array pointers, and corresponds
      to glDrawArrays(). <P> 
      
      The psuedo code for what happens inside of draw looks like this: <P>
      <li>
      Call glEnableClientState for each non-null array.
      </li>
      <li>
      Call glDisableClientState for each null array.
      </li>
      <li>
      Call glVertexPointer, glColorPointer, glEdgePointer, glTexCoordPointer, glNormalPointer, or glIndexPointer as appropriate.
      </li>
      <li>
      Call glDrawArrays.
      </li>
      <li>
      Call glDisableClientState for all of the non-null vertex arrays.
      </li>
      
      <P>

      @param Mode one of POINTS, LINE_STRIP, LINE_LOOP, LINES,
      TRIANGLE_STRIP, TRIANGLE_FAN, TRIANGLES, QUAD_STRIP, QUADS, or
      POLYGON.  
      @param first the index drawing starts at
      @param count the number of indices to draw */
  public void draw(int mode, int first, int count) {

    drawArrays(mode, first, count, 
	       vertexPointer(), vertexPointerSize(), vertexPointerStride(),
	       normalPointer(), normalPointerStride(), 
	       colorPointer(), colorPointerSize(), colorPointerStride(), 
	       indexPointer(), indexPointerStride(),
	       texCoordPointer(), texCoordPointerSize(), texCoordPointerStride(), 
	       edgeFlagPointer(),  edgeFlagPointerStride());
  }
       

  /** Draws the ith element of our arrays, and is equivalent to
   glDrawElement().  */ 
  public native void element(int i); 
}

 




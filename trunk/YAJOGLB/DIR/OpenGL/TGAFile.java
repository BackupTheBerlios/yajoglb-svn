package OpenGL;

import java.io.*;
import java.awt.Dimension;

public class TGAFile {
  /** Construct a TGAFile object from a OpenGL object and a canvas.
      It writes out the entire canvas. */
  public TGAFile(GL gl, OpenGLCanvas canvas) {
    int errorCode;


    setSize(new Dimension(canvas.getSize().width, canvas.getSize().height));
    data = (byte[]) gl.readPixels(0, 0, getSize().width, getSize().height, 
				  GLConstants.RGBA, GLConstants.GL_UNSIGNED_BYTE);

  }

  /** Write out a TGA file. */
  public void write(String filename) throws java.io.IOException {
    BufferedOutputStream output = new BufferedOutputStream(new DataOutputStream(new FileOutputStream(filename)), 10240);

    /* We handle the 18 TGA byte header here. */
    output.write(0); // Field 1: The size of field 6.
    output.write(0); // Field 2: 0 indicates that there is no color map.
    output.write(2); // Field 3: 2 indicates a true color image.
    output.write(0); // Field 4.1: No color map, so we write out zero.
    output.write(0); // Field 4.1: No color map, so we write out zero.
    output.write(0); // Field 4.2: No color map, so we write out zero.
    output.write(0); // Field 4.2: No color map, so we write out zero.
    output.write(0); // Field 4.3: No color map, so we write out zero.
    output.write(0); // Field 5.1: Two byte X-origin of zero.
    output.write(0); // Field 5.1: Two byte X-origin of zero.
    output.write(0); // Field 5.2: Two byte Y-origin of zero.
    output.write(0); // Field 5.2: Two byte Y-origin of zero.
    output.write((byte)(getSize().width & 0xff)); // Field 5.3: LSB of the image width.
    output.write((byte)(getSize().width >> 8));   // Field 5.3: MSB of the image width.
    output.write((byte)(getSize().height & 0xff)); // Field 5.3: LSB of the image height.
    output.write((byte)(getSize().height >> 8));   // Field 5.3: MSB of the image height.
    output.write(24); // Field 5.5: The number of bits per pixel.
    output.write(0); // Field 5.6: 0 bits of alpha per pixel, with the image starting
                     // in the lower left.

    // Write out the data buffer.
    int index = 0;
    for(int j = 0; j < getSize().height; j++) {
      for(int i = 0; i < getSize().width; i++) {
	output.write(data[index+2]);
	output.write(data[index+1]);
	output.write(data[index+0]);
	// No alpha, so no ouput write(data[index+3]);
	index += 4;
      }
    }
    output.close();
  }

  /** Read in a TGAFile from a named file. */
  public TGAFile(String filename){
    byte headerInformation[] = new byte[18];
    int MSWidthByte, LSWidthByte, MSHeightByte, LSHeightByte;
    byte imageType;
    int w, h;
    BufferedInputStream in = null;
    try {
      in = new BufferedInputStream(new FileInputStream(new File(filename)), 10240);
      for(int i = 0; i < 18; i++) {
	headerInformation[i] = (byte) in.read();
      }

      /*imageType = headerInformation[3];
      if (imageType != 2) {
	throw new ;
      }

      */

      MSWidthByte = headerInformation[13];
      LSWidthByte = headerInformation[12];
      if (MSWidthByte < 0) MSWidthByte += 256;
      if (LSWidthByte < 0) LSWidthByte += 256;
      w = (256*MSWidthByte) + LSWidthByte;

      MSHeightByte = headerInformation[15];
      LSHeightByte = headerInformation[14];
      if (MSHeightByte < 0) MSHeightByte += 256;
      if (LSHeightByte < 0) LSHeightByte += 256;
      h = (256*MSHeightByte) + LSHeightByte;

      setSize(new Dimension(w, h));
      data = new byte[w*h*4];
      int index = 0;
      for (int j = 0; j < h; j++) {
	for (int i = 0; i < w; i++) {
	  data[index+2] = (byte) in.read();
	  data[index+1] = (byte) in.read();
	  data[index+0] = (byte) in.read();
	  data[index+3] = (byte) 255;
	  index += 4;
	}
      }
      in.close();
    }
    catch(IOException e){
      e.printStackTrace();
    }
  }
  
  public byte[] getData() { return data;}
  public Dimension getSize() { return size; }
  public void setSize(Dimension newSize) { size = newSize; }
  private Dimension size;
  private byte[] data;


};

package OpenGL;

import java.io.*;

class TGAFile {
    public TGAFile(String fname, int w, int h){
        this.w = w;
        this.h = h;
        data = new byte[w*h*4];
        try {
        	FileInputStream in = new FileInputStream(new File(fname));
    		for(int i = 0; i < 18; i++) {
    			byte c = (byte) in.read();
    		}

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
        }
        catch(IOException e){
            e.printStackTrace();
        }
    }

    public int width() { return w;}
    public int height() { return h;}
    public byte[] getData() { return data;}

    private int w;
    private int h;
    private byte[] data;
};

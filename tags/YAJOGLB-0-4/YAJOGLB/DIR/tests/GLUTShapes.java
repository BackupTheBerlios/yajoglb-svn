/*
This draws some nice shapes from the GLUT library, and is a simple
conversion from that library.  The comments for that library include
the following:

 Copyright (c) Mark J. Kilgard, 1994, 1997. 

(c) Copyright 1993, Silicon Graphics, Inc.

ALL RIGHTS RESERVED

Permission to use, copy, modify, and distribute this software
for any purpose and without fee is hereby granted, provided
that the above copyright notice appear in all copies and that
both the copyright notice and this permission notice appear in
supporting documentation, and that the name of Silicon
Graphics, Inc. not be used in advertising or publicity
pertaining to distribution of the software without specific,
written prior permission.

THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU
"AS-IS" AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR
OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  IN NO
EVENT SHALL SILICON GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE
ELSE FOR ANY DIRECT, SPECIAL, INCIDENTAL, INDIRECT OR
CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER,
INCLUDING WITHOUT LIMITATION, LOSS OF PROFIT, LOSS OF USE,
SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD PARTIES, WHETHER OR
NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF THE POSSIBILITY
OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE OR
PERFORMANCE OF THIS SOFTWARE.

US Government Users Restricted Rights

Use, duplication, or disclosure by the Government is subject to
restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
(c)(1)(ii) of the Rights in Technical Data and Computer
Software clause at DFARS 252.227-7013 and/or in similar or
successor clauses in the FAR or the DOD or NASA FAR
Supplement.  Unpublished-- rights reserved under the copyright
laws of the United States.  Contractor/manufacturer is Silicon
Graphics, Inc., 2011 N.  Shoreline Blvd., Mountain View, CA
94039-7311.

OpenGL(TM) is a trademark of Silicon Graphics, Inc.  */


import OpenGL.*;
import java.lang.Math.*;

class GLUTShapes implements GLConstants {
    static protected void doughnut(GL gl, double r, double R, int nsides, int rings) {
	int i, j;
	double theta, phi, theta1;
	double cosTheta, sinTheta;
	double cosTheta1, sinTheta1;
	double ringDelta, sideDelta;

	ringDelta = 2.0 * java.lang.Math.PI / (double)rings;
	sideDelta = 2.0 * java.lang.Math.PI / (double)nsides;

	theta = 0.0;
	cosTheta = 1.0;
	sinTheta = 0.0;
	for (i = rings - 1; i >= 0; i--) {
	    theta1 = theta + ringDelta;
	    cosTheta1 = java.lang.Math.cos(theta1);
	    sinTheta1 = java.lang.Math.sin(theta1);
	    gl.begin(QUAD_STRIP);
	    phi = 0.0;
	    for (j = nsides; j >= 0; j--) {
		double cosPhi, sinPhi, dist;

		phi += sideDelta;
		cosPhi = java.lang.Math.cos(phi);
		sinPhi = java.lang.Math.sin(phi);
		dist = R + r * cosPhi;

		gl.normal(cosTheta1 * cosPhi, -sinTheta1 * cosPhi, sinPhi);
		gl.vertex(cosTheta1 * dist, -sinTheta1 * dist, r * sinPhi);
		gl.normal(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi);
		gl.vertex(cosTheta * dist, -sinTheta * dist,  r * sinPhi);
	    }
	    gl.end();
	    theta = theta1;
	    cosTheta = cosTheta1;
	    sinTheta = sinTheta1;
	}
    }

    static public void solidTorus(GL gl, double innerRadius, double outerRadius,
		    int nsides, int rings) {
	doughnut(gl, innerRadius, outerRadius, nsides, rings);
    }
}

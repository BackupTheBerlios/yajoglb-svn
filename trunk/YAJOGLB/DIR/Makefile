# Some rules and constants for compiling java
PACKAGEDIR       = OpenGL
JAVAC            = javac
JAVAH            = javah
JAVADOC          = javadoc
JFLAGS           = 
CP               = cp
TAR              = tar
NMAKE            = //F/DEVSTUDIO/vc/bin/nmake
CHEATINGWINDIR   = sun/awt/windows
CHEATINGMOTIFDIR = sun/awt/motif
TESTDIR          = tests
SUFFIXES        += .class .java
COMPILE.java     = $(JAVAC) $(JFLAGS) 
PACKAGENAME      = YAJOGLB-0.3.1

%.class: %.java
	$(COMPILE.java) $<

DOCDIR          = documentation
NATIVECODEDIR   = CNativeCode/YAJOGLB      		  

# Some Cygnus tools stuff

# The header files for our native code
NATIVEHEADERS = OpenGL_GLUQuadric.h OpenGL_GLUNurbs.h OpenGL_Context.h OpenGL_GLUTesselator.h OpenGL_GLU.h OpenGL_GL.h OpenGL_GLVertexPointer.h OpenGL_Canvas.h OpenGL_GLFeedbackBuffer.h OpenGL_CallbackObject.h OpenGL_GLNativeFloatArray.h OpenGL_GLNativeIntArray.h OpenGL_GLSelectionBuffer.h

default:
	@echo "Type one of the following:"
	@echo "  make win32 for Microsoft Windows with the Cygnus toolset and Visual C++."
	@echo "  make linux for the Linux systems."
	@echo "  make solaris for Solaris."

packagedir:
	$(MAKE) -C $(PACKAGEDIR)

cheatingwindir:
	$(MAKE) -C $(CHEATINGWINDIR)

cheatingmotifdir:
	$(MAKE) -C $(CHEATINGMOTIFDIR)

jarFile: packagedir
	jar -cvf0 OpenGL.jar $(PACKAGEDIR)/*.class

testdir: 
	$(MAKE) -C $(TESTDIR) 

dist : 
	(cd ..; $(RM) -f $(PACKAGENAME).tar.gz)
	(cd ..; $(TAR) cvf $(PACKAGENAME).tgz --gzip --exclude RCS --exclude "*.obj" --exclude "*~" --exclude "*.idb" --exclude "*.pdb" --exclude "*.ilk" --exclude "*.pch" --exclude "*.class" $(PACKAGENAME))

clean : 
	$(RM) -f *~ *.class *.jar 
	(cd $(NATIVECODEDIR); $(RM) -f $(NATIVEHEADERS))
	$(MAKE) -C $(PACKAGEDIR) clean
	$(MAKE) -C $(CHEATINGWINDIR) clean
	$(MAKE) -C $(CHEATINGMOTIFDIR) clean

# If we are running under Linux we want to use our own clean.
ifeq ($(OSTYPE),"linux-gnu")
	$(MAKE) -C $(NATIVECODEDIR) clean
# Otherwise we assume that we are under Windows.
else
	(cd $(NATIVECODEDIR); MAKEFLAGS= ; $(NMAKE) /F YAJOGLB.MAK CLEAN)
endif

	$(MAKE) -C $(TESTDIR) clean

documentation ::
	$(JAVADOC) -d $(DOCDIR) OpenGL

OpenGL_GLUQuadric.h: $(PACKAGEDIR)/GLUQuadric.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLUQuadric

OpenGL_GLUNurbs.h: $(PACKAGEDIR)/GLUNurbs.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLUNurbs

OpenGL_Context.h: $(PACKAGEDIR)/Context.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).Context

OpenGL_GLU.h: $(PACKAGEDIR)/GLU.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLU

OpenGL_GL.h: $(PACKAGEDIR)/GL.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GL

OpenGL_Canvas.h: $(PACKAGEDIR)/Canvas.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).Canvas

OpenGL_GLUTesselator.h: $(PACKAGEDIR)/GLUTesselator.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLUTesselator

OpenGL_GLFeedbackBuffer.h: $(PACKAGEDIR)/GLFeedbackBuffer.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLFeedbackBuffer

OpenGL_GLVertexPointer.h: $(PACKAGEDIR)/GLVertexPointer.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLVertexPointer

OpenGL_CallbackObject.h: $(PACKAGEDIR)/CallbackObject.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).CallbackObject

OpenGL_GLNativeFloatArray.h: $(PACKAGEDIR)/GLNativeFloatArray.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLNativeFloatArray

OpenGL_GLNativeIntArray.h: $(PACKAGEDIR)/GLNativeIntArray.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLNativeIntArray

OpenGL_GLSelectionBuffer.h: $(PACKAGEDIR)/GLSelectionBuffer.java
	$(JAVAH) -jni -d $(NATIVECODEDIR) $(PACKAGEDIR).GLSelectionBuffer

nativeheaders: $(NATIVEHEADERS)

#
# The native make methods.
#

# Make methods for Microsoft Windows, with the Cygnus environment and
# Visual C++
win32 :   win32-config packagedir cheatingwindir $(NATIVEHEADERS) win32-nativedir testdir

win32-config:
	$(CP) Makefile.config-win32 Makefile.config

win32-nativedir:
	(cd $(NATIVECODEDIR); ./YAJOGLB.BAT)


# Make methods for Linux
linux : linux-config packagedir cheatingmotifdir $(NATIVEHEADERS) linux-nativedir testdir

linux-config:
	$(CP) Makefile.config-linux Makefile.config

linux-nativedir:
	$(MAKE) -C $(NATIVECODEDIR) -f Makefile.linux


# Make methods for Solaris
solaris : packagedir cheatingmotifdir $(NATIVEHEADERS) solaris-nativedir testdir

solaris-config:
	$(CP) Makefile.config-solaris Makefile.config

solaris-nativedir:
	$(MAKE) -C $(NATIVECODEDIR) -f Makefile.solaris


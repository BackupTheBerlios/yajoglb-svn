# $Id: common.mk,v 1.1 2002/04/14 18:30:12 razeh Exp $
# Some common definitions and rules that are shared across
# platforms.

PACKAGEDIR       = OpenGL
JAVAC            = javac
JAVADOC          = javadoc
JFLAGS           = -g
CP               = cp
TAR              = tar
NMAKE            = //F/DEVSTUDIO/vc/bin/nmake
CHEATINGWINDIR   = sun/awt/windows
CHEATINGMOTIFDIR = sun/awt/motif
TESTDIR          = tests
PACKAGENAME      = YAJOGLB-0.4
DOCDIR           = documentation
NATIVECODEDIR    = CNativeCode/YAJOGLB
OPTIMIZATIONFLAG = -g
JAVAH            = javah
SUFFIXES        += .class .java
JAVACC           = $(JAVAC) $(JFLAGS)
CLASSPATH        = .$(CLASSPATH_SEPARATOR)tests
%.class: %.java
	$(JAVACC) -classpath $(CLASSPATH) $<


# Some Cygnus tools stuff
SHELL         =/gnuwin32/b18/H-i386-cygwin32/bin/sh
# Some rules for compiling java
JAVAH         = javah
JAVAC         = javac
JLIB          = C:\jdk1.1.4\lib\classes.zip
CLASSPATH     = -classpath ";..\..\..;$(JLIB)"
JFLAGS        = $(CLASSPATH) -g
SUFFIXES     += .class .java
COMPILE.java  = $(JAVAC) $(JFLAGS) 
%.class: %.java
	$(COMPILE.java) $<

JAVA_SRC        = WindowspDataAccess.java

JAVA_CLASSES    = WindowspDataAccess.class
		  
		  
		  
		  

all : $(JAVA_CLASSES)



clean :
	$(RM) $(JAVA_CLASSES) $(JAVA_CLASSES) *~


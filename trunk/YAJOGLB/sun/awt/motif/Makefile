# Some Cygnus tools stuff

include ../../../Makefile.common
include ../../../Makefile.config

# Some rules for compiling java
CLASSPATH     = -classpath ":../../..:$(JLIB)"
JFLAGS        = $(CLASSPATH) $(OPTIMIZATIONFLAG)

JAVA_SRC      = X11pDataAccess.java

JAVA_CLASSES  = X11pDataAccess.class
		  
all : $(JAVA_CLASSES)

clean :
	$(RM) $(JAVA_CLASSES) $(JAVA_CLASSES) *~

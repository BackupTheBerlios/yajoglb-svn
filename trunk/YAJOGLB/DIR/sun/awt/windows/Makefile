# Some Cygnus tools stuff

include ../../../Makefile.common
include ../../../Makefile.config

# Some rules for compiling java
CLASSPATH     = -classpath ..$(DIR_SEPARATOR)..$(DIR_SEPARATOR)..$(DIR_SEPARATOR)$(CLASSPATH_SEPARATOR)$(JLIB)
CLASSPATH     = -classpath "../../..;$(JLIB)"
JFLAGS        = $(CLASSPATH) $(OPTIMIZATIONFLAG)

JAVA_SRC        = WindowspDataAccess.java

JAVA_CLASSES    = WindowspDataAccess.class
		  
		  
		  
		  

all : $(JAVA_CLASSES)



clean :
	$(RM) $(JAVA_CLASSES) $(JAVA_CLASSES) *~


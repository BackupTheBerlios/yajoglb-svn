SYSTEM:=$(shell uname)


ifeq ($(SYSTEM), Linux)
include config-linux.mk
else 
 ifeq ($(SYSTEM), solaris)
 include config-solaris.mk
 else
  ifeq ($(strip $(SYSTEM)), CYGWIN_NT-5.0)
  include config-win32.mk
  endif
 endif
endif

include common.mk
include native.mk
include OpenGL/module.mk
include tests/module.mk
include doc/module.mk
include bin/module.mk

DEPENDFILES= $(OBJS:.o=.d)
JAVA_CLASS = $(JAVA_SRC:.java=.class)
CLEANUP_FILES = $(JAVA_CLASS) $(OBJS) $(NATIVEHEADERS) $(DEPENDFILES) tests/*.class OpenGL/*.class
YAJOGLB_LIB := libYAJOGLB.so
MODULE_FILES = *.mk */*.mk */*/*.mk


DISTRIBUTED_FILES += $(JAVA_SRC) $(CSRCS) $(MODULE_FILES) Makefile
# Files for historical (pre-JAWT) purposes
DISTRIBUTED_FILES += sun/awt/motif/Makefile sun/awt/motif/X11pDataAccess.java
DISTRIBUTED_FILES += sun/awt/windows/Makefile sun/awt/windows/WindowspDataAccess.java

all: $(JAVA_CLASS) $(NATIVEHEADERS) $(YAJOGLB_LIB) 
alljava: $(JAVA_CLASS)


clean:
	$(RM) $(CLEANUP_FILES)

DISTDIRECTORY=YAJOGLB-0.4
dist:
	- rm -rf $(HOME)$(DIR_SEPARATOR)$(DISTDIRECTORY).old
	- mv $(DISTDIRECTORY) $(HOME)$(DIR_SEPARATOR)$(DISTDIRECTORY).old
	- mkdir $(DISTDIRECTORY)
	tar c $(DISTRIBUTED_FILES) | tar --extract --directory=$(DISTDIRECTORY)
	tar cfj YAJOGLB-0.4.tar.bz2 $(DISTDIRECTORY)

NATIVEHEADERS: $(NATIVEHEADERS)

MAJOR := 1
MINOR := 1

$(YAJOGLB_LIB): $(OBJS) 
	$(MAKELIB) $(YAJOGLB_LIB) $(MAJOR) $(MINOR) $(OBJS)

-include $(DEPENDFILES)



include common.mk
include config.mk
include native.mk
include OpenGL/module.mk
include tests/module.mk
include doc/module.mk

DEPENDFILES= $(OBJS:.o=.d)
JAVA_CLASS = $(JAVA_SRC:.java=.class)
CLEANUP_FILES = $(JAVA_CLASS) $(OBJS) $(NATIVEHEADERS) $(DEPENDFILES) tests/*.class OpenGL/*.class
YAJOGLB_LIB := libYAJOGLB.so
MODULE_FILES = *.mk */*.mk */*/*.mk
DISTRIBUTED_FILES += $(JAVA_SRC) $(CSRCS) $(MODULE_FILES)

all: $(JAVA_CLASS) $(NATIVEHEADERS) $(YAJOGLB_LIB) 
alljava: $(JAVA_CLASS)


clean:
	$(RM) $(CLEANUP_FILES)

dist:
	tar cfj YAJOGLB-0.4.tar.bz2 $(DISTRIBUTED_FILES)

NATIVEHEADERS: $(NATIVEHEADERS)

MAJOR := 1
MINOR := 1

$(YAJOGLB_LIB): $(OBJS) 
	$(MAKELIB) $(YAJOGLB_LIB) $(MAJOR) $(MINOR) $(OBJS)

-include $(DEPENDFILES)


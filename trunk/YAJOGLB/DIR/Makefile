
include common.mk
include config.mk
include native.mk
include OpenGL/module.mk
include tests/module.mk

DEPENDFILES= $(OBJS:.o=.d)
JAVA_CLASS = $(JAVA_SRC:.java=.class)
CLEANUP_FILES = $(JAVA_CLASS) $(OBJS) $(NATIVEHEADERS) $(DEPENDFILES)
YAJOGLB_LIB := libYAJOGLB.so

all: $(JAVA_CLASS) $(YAJOGLB_LIB)

clean:
	$(RM) $(CLEANUP_FILES)

MAJOR := 1
MINOR := 1

$(YAJOGLB_LIB): $(OBJS) 
	$(MAKELIB) $(YAJOGLB_LIB) $(MAJOR) $(MINOR) $(OBJS)

include $(DEPENDFILES)

/* These are preprocessor conversion that allow the Cygnus tools to
   compile with the Java include files that are intended for Microsoft
   tools. */

#ifdef __CYGWIN32__
/* Make sure that we get the JNI headers with JNICALL defined as __stdcall. */
#include <jni.h>
/* Now make sure our own methods do not. */
#ifdef JNICALL
#undef JNICALL
#define JNICALL
#endif
#endif

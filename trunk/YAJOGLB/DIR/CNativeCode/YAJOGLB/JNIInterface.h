#include <jni.h>

int lookupStaticIntField(JNIEnv *env, jclass class,
			 const char *fieldName, int *fieldValue);
int staticIntField(JNIEnv *env, jclass class, const char *fieldName);
jclass getClass(JNIEnv *env,
		const char *className,      /* The class to lookup. */
		const char *errorString);   /* The error to print. */

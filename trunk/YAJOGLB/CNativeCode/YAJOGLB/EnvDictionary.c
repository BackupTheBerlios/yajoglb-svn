/*
 Dictionary mapping for the JNIEnv and threads.
 
 Copyright 2001, 2004 Robert Allan Zeh (razeh@yahoo.com)
 43 Gale
 River Forest, IL 60305
 
 This library is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as
 published by the Free Software Foundation; either version 2 of the
 License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 USA
 
 */

#include "EnvDictionary.h"

static JavaVM *myVM;

/** This is invoked by the Java virtual machine when our
* library is loaded.  We keep a copy of the virtual machine
* pointer so that we can determine which environment to use
* for threads.
*/
jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	myVM = vm;
	return JNI_VERSION_1_2;
}


/* Get the environment pointer for the current thread. */
JNIEnv *environmentPointerForCurrentThread()
{
	JNIEnv *env = NULL;
	if (myVM) {
		(*myVM)->GetEnv(myVM, (void**)&env, JNI_VERSION_1_2); 
	}
	
	if (env == NULL) {
		fprintf(stderr, "Unable to retrieve an environment pointer at %s:%d\n",
				__FILE__, __LINE__);
		fatalUnreportableError("Unable to retrieve an environment pointer");
	}
	
	return env;
}


/*
 * OpenGL_OpenGLContext.c
 *
 // Copyright 2004
 // Alexander Spohr
 // created by atze aet freeport de
 *
 * This implements the native methods for OpenGLContext --- methods that 
 * create, manipulate, and destroy the current OpenGL context.
 */

#import <Foundation/Foundation.h>
#include <OpenGL/OpenGL.h>
// #include <AppKit/NSOpenGL.h>
#include <AppKit/AppKit.h>
#include <ApplicationServices/ApplicationServices.h> // for CoreGraphics
#include "macosx_CanvasInfo.h"

#include "SystemIncludes.h"
#include "OpenGL_Context.h"
#include "SystemError.h"
#include "JNIInterface.h"
#include "Memory.h"
#include "ErrorHandling.h"
#include "CapabilitiesAccessors.h"

/* Our context exception class. */
#define OPENGL_CONTEXT_EXCEPTION "OpenGL/ContextException"

// for NSViewFrameDidChangeNotification
@interface NSOpenGLContext (YAJOGLB)
- (void)viewFrameDidChange:(NSNotification *)aNotification;
@end
@implementation NSOpenGLContext (YAJOGLB)
- (void)viewFrameDidChange:(NSNotification *)aNotification
{
	[self makeCurrentContext];
	[self update];

	NSRect aRect  = [[aNotification object] bounds];
	fprintf(stderr, "viewFrameDidChange (%d, %d)\n", (int)NSWidth(aRect), (int)NSHeight(aRect)); fflush(stderr);
}
@end

////////////////////////////////////////////////////////////////////////
// Functions for our private use.
////////////////////////////////////////////////////////////////////////

/* This throws an OpenGLContextException Java exception that uses the current
system error as the error message. */
static void throwContextException(JNIEnv *env, const char *errorMessage)
{
	handleError(env, OPENGL_CONTEXT_EXCEPTION, errorMessage);
}


/* Get the Capabilities object for the supplied canvas.  We
return 0 if everything worked out and non-zero otherwise. */
static int getCapabilities(JNIEnv *env, jobject canvas, jobject *capabilities)
{
	jclass    canvasClass  = NULL;
	jmethodID methodID     = NULL;
	int       error        = 0;
	
	canvasClass = (*env)->GetObjectClass(env, canvas);
	methodID = getMethodID(env, canvasClass, 
						   "capabilities", "()LOpenGL/Capabilities;",
						   "Unable to get the capabilities method.");
	if (methodID && (NULL != capabilities)) {
		*capabilities = (*env)->CallObjectMethod(env, canvas, methodID);
	} else {
		error = 1;
	}
	
	return !error;
}



/* Return the visual that matches our capabilities most closely. */
static NSOpenGLPixelFormat *findPixelFormat(CGDirectDisplayID aDisplay, JNIEnv *env, jobject capabilities, BOOL wantsFullscreen)
{
	NSOpenGLPixelFormat *aPixelFormat = nil;
	jint alphaDepthSize = 0;
	jint depthBufferSize = 0, stencilBufferSize = 0;
	// jint colorTypeChoice = 0, doubleBufferChoice;
	
	int error = 0;
	
	/* Get the capabilities values. */
	if (!error) {
		alphaDepthSize = alphaDepth(env, capabilities);
		error = (alphaDepthSize < 0);
	}
	
	if (!error) {
		depthBufferSize = depthBuffer(env, capabilities);
		error = (depthBufferSize < 0);
	}
	
	if (!error) {
		stencilBufferSize = stencilBuffer(env, capabilities);
		error = (stencilBufferSize < 0);
	}

	/* defaults to RGBA under mac os x
	if (!error) {
		colorTypeChoice = colorType(env, capabilities);
		error = (colorTypeChoice  < 0);
	}
	*/
	/* defaults to double buffer for mac os x
	if (!error) {
		doubleBufferChoice = isDoubleBufferEnabled(env, capabilities);
		error = (doubleBufferChoice < 0);
	}
	*/
	if (!error)  {
		NSOpenGLPixelFormatAttribute attributes[] =
		{
			wantsFullscreen ? NSOpenGLPFAFullScreen : NSOpenGLPFAWindow,
			NSOpenGLPFADoubleBuffer,
			NSOpenGLPFABackingStore,
			NSOpenGLPFAAccelerated,
			NSOpenGLPFANoRecovery,
			NSOpenGLPFAColorSize, (NSOpenGLPixelFormatAttribute)32,
			// NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)1,
			NSOpenGLPFAScreenMask, (NSOpenGLPixelFormatAttribute)CGDisplayIDToOpenGLDisplayMask(aDisplay),
			// kCGLPFAAlphaSize, alphaDepthSize,  try that later
			// kCGLPFAStencilSize, stencilBufferSize, try that later
			(NSOpenGLPixelFormatAttribute)nil
		};
		aPixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attributes] autorelease];
	}
	
	return aPixelFormat;
}

static BOOL isFullscreenView(NSView *aView)
{
	// atze: if the views window covers the entire screen make the gl-context fullscreen
	NSWindow     *aWindow        = [aView window];
	NSRect       aWindowFrame    = [aWindow frame];
	NSScreen     *aScreen        = [aWindow screen];
	NSDictionary *aDictionary    = [aScreen deviceDescription];
	NSNumber	 *aDisplayNumber = [aDictionary objectForKey:@"NSScreenNumber"];
	CGDirectDisplayID aDisplay = (CGDirectDisplayID)[aDisplayNumber longValue]; // this is kind of ugly
	
	// atze: we can not use NSScreens size, because it's the hardware resolution
	// atze: the GDDisplayPixelsXX returns the soft-resolution
	size_t aScreenWidth  = CGDisplayPixelsWide(aDisplay);
	size_t aScreenHeight = CGDisplayPixelsHigh(aDisplay);
	
	// atze: does the window cover the entire screen?
	if(aScreenWidth == (size_t)NSWidth(aWindowFrame) && aScreenHeight == (size_t)NSHeight(aWindowFrame))
		return YES;
	return NO;
}

////////////////////////////////////////////////////////////////////////
// Implementations of our native methods.
////////////////////////////////////////////////////////////////////////



/* Let the current context go. */
JNIEXPORT void JNICALL Java_OpenGL_Context_nativeReleaseCurrentContext
(JNIEnv *env, jclass class)
{
    int error = 0;
	
    if (!error) {
		NSOpenGLContext *aContext = [NSOpenGLContext currentContext];
		if (NULL == aContext) {
			return; // There is no current context.
		}
    }
	
    if (!error) {
		[NSOpenGLContext clearCurrentContext];
    }
}



/* Make the given context and canvas current. */
JNIEXPORT void JNICALL Java_OpenGL_Context_makeCanvasCurrent
(JNIEnv *env, jobject contextObject, jlong jcontext, jobject canvas)
{
	NSOpenGLContext *aContext = (NSOpenGLContext *)(TO_POINTER(jcontext));
	CanvasInfo info;
	CGLError error = 0;
	
	if (!error && (aContext != 0)) {
		info = getCanvasInfo(env, canvas);
		error = (NULL == info.view);
	}
	
	if (!error) {
		[aContext makeCurrentContext];
		// [aContext setView:info.view]; should we reset the view here?
	}
	
	if (error) {
		/* Something went wrong, and we need to throw an exception. */
		throwContextException(env, "Unable to make the context current.");
	}
	
	freeCanvasInfo(env, info);
}



/* Create the context for a supplied canvas. */
JNIEXPORT jlong JNICALL Java_OpenGL_Context_createCanvasContext(JNIEnv *env, jobject contextObject, jobject canvas, jlong otherContext)
{
	CanvasInfo      info;
	NSOpenGLContext *context = NULL;
	int          error        = 0;
	jobject      capabilities = NULL;
	const char  *errorMessage = NULL;
	
	/* Get our capabilities object. */
	if (0 == getCapabilities(env, canvas, &capabilities)) {
		error = 1;
		errorMessage = "Unable to get the capabilities object for the canvas.";
	}
	
	/* Get the display variable. */
	if (!error) {
		info = getCanvasInfo(env, canvas);
		if (NULL == info.view) {
			error = 1;
			errorMessage = "Unable to get the NSView display for the canvas.";
		}
	}

	BOOL wantsFullscreen = isFullscreenView(info.view);
	/* Find the right visual. */
	NSOpenGLPixelFormat *aPixelFormat = nil;
	if (!error) {
		aPixelFormat = findPixelFormat(kCGDirectMainDisplay/*info.display*/, env, capabilities, wantsFullscreen);
		if (NULL == aPixelFormat) {
			error = 1;
			errorMessage = "Unable to get a matching visual for the canvas's capabilities.";
		}
	}
	
	/* Actually create the context, using our display, pixelFormatObj, and possibly
		the shared context. */
	if (!error) {
		fflush(stdout);
		context = [[[NSOpenGLContext alloc] initWithFormat:aPixelFormat shareContext:(NSOpenGLContext *)(TO_POINTER(otherContext))] retain];
		if (NULL == context) {
			error = 1;
			errorMessage = "Unable to create a context.";
		}
		else {
			[[NSNotificationCenter defaultCenter] addObserver:context selector:@selector(viewFrameDidChange:) name:NSViewFrameDidChangeNotification object:info.view];
			[info.view setPostsFrameChangedNotifications:YES];

			[context makeCurrentContext];
			if(wantsFullscreen)
			{
				fprintf(stdout, "switching to fullscreen");
				[context setFullScreen];
			}
			else
				[context setView:info.view];
		}
		fflush(stdout);
	}
	
	if (error) {
		/* Something went wrong, and we need to throw an exception. */
		throwContextException(env, errorMessage);
	}

	freeCanvasInfo(env, info);
	return FROM_POINTER(context);
}



/* Free the OpenGL context. */
JNIEXPORT void JNICALL Java_OpenGL_Context_deleteContext
(JNIEnv *env, jobject contextObject, jlong context)
{
	NSOpenGLContext *aContext = (NSOpenGLContext *)(TO_POINTER(context));
	[aContext clearDrawable];
	[aContext release];
}


JNIEXPORT void JNICALL Java_OpenGL_Context_nativeSyncToVBL(JNIEnv *env, jobject contextObject, jlong context, jboolean aFlag)
{
	NSOpenGLContext *aContext = (NSOpenGLContext *)(TO_POINTER(context));
	long anInterval = (aFlag == JNI_TRUE? 1 : 0); // vbl-sync
	[aContext setValues:&anInterval forParameter:NSOpenGLCPSwapInterval];
	fprintf(stderr, "Java_OpenGL_Context_nativeSyncToVBL:%d\n", (int)anInterval);
}

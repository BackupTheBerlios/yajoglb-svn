# Microsoft Developer Studio Project File - Name="YAJOGLB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=YAJOGLB - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "YAJOGLB.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "YAJOGLB.MAK" CFG="YAJOGLB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "YAJOGLB - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "YAJOGLB - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "YAJOGLB - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /Ob2 /I "c:\razeh\opengl\oglsdk\include" /I "c:\j2sdk1.4.1_01\include" /I "c:\j2sdk1.4.1_01\include\win32" /I "f:\devstudio\vc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "USE_JAWT" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 opengl32.lib glu32.lib kernel32.lib user32.lib gdi32.lib libcmt.lib jawt.lib /nologo /subsystem:windows /dll /machine:I386 /libpath:"c:\j2sdk1.4.1_01\lib" /libpath:"\devstudio\vc\lib"

!ELSEIF  "$(CFG)" == "YAJOGLB - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "c:\j2sdk1.4.1_01\include" /I "c:\j2sdk1.4.1_01\include\win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "USE_JAWT" /FR /FD /c
# SUBTRACT CPP /X /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib kernel32.lib user32.lib gdi32.lib libcmt.lib jawt.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib /pdbtype:sept /libpath:"c:\j2sdk1.4.1_01\lib" /libpath:"f:\devstudio\vc\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "YAJOGLB - Win32 Release"
# Name "YAJOGLB - Win32 Debug"
# Begin Source File

SOURCE=.\CallbackObject.c
# End Source File
# Begin Source File

SOURCE=.\CallbackObject.h
# End Source File
# Begin Source File

SOURCE=.\CapabilitiesAccessors.c
# End Source File
# Begin Source File

SOURCE=.\cygnusFixes.h
# End Source File
# Begin Source File

SOURCE=.\EnvDictionary.h
# End Source File
# Begin Source File

SOURCE=.\ErrorHandling.c
# End Source File
# Begin Source File

SOURCE=.\ErrorHandling.h
# End Source File
# Begin Source File

SOURCE=.\JNIInterface.c
# End Source File
# Begin Source File

SOURCE=.\JNIInterface.h
# End Source File
# Begin Source File

SOURCE=.\memory.h
# End Source File
# Begin Source File

SOURCE=.\OpenGL_CallbackObject.c
# End Source File
# Begin Source File

SOURCE=.\OpenGL_Canvas.c
# End Source File
# Begin Source File

SOURCE=.\OpenGL_GL.c
# End Source File
# Begin Source File

SOURCE=.\OpenGL_GLFeedbackBuffer.c
# End Source File
# Begin Source File

SOURCE=.\OpenGL_GLNativeFloatArray.c
# End Source File
# Begin Source File

SOURCE=.\OpenGL_GLNativeIntArray.c
# End Source File
# Begin Source File

SOURCE=.\OpenGL_GLSelectionBuffer.c
# End Source File
# Begin Source File

SOURCE=.\OpenGL_GLU.c
# End Source File
# Begin Source File

SOURCE=.\OpenGL_GLUNurbs.c
# End Source File
# Begin Source File

SOURCE=.\OpenGL_GLUQuadric.c
# End Source File
# Begin Source File

SOURCE=.\OpenGL_GLUTesselator.c
# End Source File
# Begin Source File

SOURCE=.\OpenGL_GLVertexPointer.c
# End Source File
# Begin Source File

SOURCE=.\SystemError.h
# End Source File
# Begin Source File

SOURCE=.\SystemIncludes.h
# End Source File
# Begin Source File

SOURCE=.\win32_OpenGL_Canvas.c
# End Source File
# Begin Source File

SOURCE=.\win32_OpenGL_Context.c
# End Source File
# Begin Source File

SOURCE=.\win32_OpenGL_GL.c
# End Source File
# Begin Source File

SOURCE=.\win32DCDictionary.c
# End Source File
# Begin Source File

SOURCE=.\win32DCDictionary.h
# End Source File
# Begin Source File

SOURCE=.\win32EnvDictionary.c
# End Source File
# Begin Source File

SOURCE=.\win32EnvDictionary.h
# End Source File
# Begin Source File

SOURCE=.\win32Init.c
# End Source File
# Begin Source File

SOURCE=.\win32Memory.c
# End Source File
# Begin Source File

SOURCE=.\win32SystemError.c
# End Source File
# End Target
# End Project

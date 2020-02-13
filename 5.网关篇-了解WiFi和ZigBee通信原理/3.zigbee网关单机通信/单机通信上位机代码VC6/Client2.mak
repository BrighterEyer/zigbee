# Microsoft Developer Studio Generated NMAKE File, Based on Client2.dsp
!IF $(CFG)" == "
CFG=Client2 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Client2 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Client2 - Win32 Release" && "$(CFG)" != "Client2 - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Client2.mak" CFG="Client2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Client2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Client2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF $(OS)" == "Windows_NT
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Client2 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\Client2.exe"


CLEAN :
	-@erase "$(INTDIR)\Client2.obj"
	-@erase "$(INTDIR)\Client2.pch"
	-@erase "$(INTDIR)\Client2.res"
	-@erase "$(INTDIR)\Client2Dlg.obj"
	-@erase "$(INTDIR)\Picture.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Client2.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Client2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Client2.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Client2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Client2.pdb" /machine:I386 /out:"$(OUTDIR)\Client2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Client2.obj" \
	"$(INTDIR)\Client2Dlg.obj" \
	"$(INTDIR)\Picture.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Client2.res"

"$(OUTDIR)\Client2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Client2 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\Client2.exe" "$(OUTDIR)\Client2.bsc"


CLEAN :
	-@erase "$(INTDIR)\Client2.obj"
	-@erase "$(INTDIR)\Client2.pch"
	-@erase "$(INTDIR)\Client2.res"
	-@erase "$(INTDIR)\Client2.sbr"
	-@erase "$(INTDIR)\Client2Dlg.obj"
	-@erase "$(INTDIR)\Client2Dlg.sbr"
	-@erase "$(INTDIR)\Picture.obj"
	-@erase "$(INTDIR)\Picture.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Client2.bsc"
	-@erase "$(OUTDIR)\Client2.exe"
	-@erase "$(OUTDIR)\Client2.ilk"
	-@erase "$(OUTDIR)\Client2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Client2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Client2.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Client2.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Client2.sbr" \
	"$(INTDIR)\Client2Dlg.sbr" \
	"$(INTDIR)\Picture.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Client2.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Client2.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Client2.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Client2.obj" \
	"$(INTDIR)\Client2Dlg.obj" \
	"$(INTDIR)\Picture.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Client2.res"

"$(OUTDIR)\Client2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Client2.dep")
!INCLUDE "Client2.dep"
!ELSE 
!MESSAGE Warning: cannot find "Client2.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Client2 - Win32 Release" || "$(CFG)" == "Client2 - Win32 Debug"
SOURCE=.\Client2.cpp

!IF  "$(CFG)" == "Client2 - Win32 Release"


"$(INTDIR)\Client2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client2.pch"


!ELSEIF  "$(CFG)" == "Client2 - Win32 Debug"


"$(INTDIR)\Client2.obj"	"$(INTDIR)\Client2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client2.pch"


!ENDIF 

SOURCE=.\Client2.rc

"$(INTDIR)\Client2.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Client2Dlg.cpp

!IF  "$(CFG)" == "Client2 - Win32 Release"


"$(INTDIR)\Client2Dlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client2.pch"


!ELSEIF  "$(CFG)" == "Client2 - Win32 Debug"


"$(INTDIR)\Client2Dlg.obj"	"$(INTDIR)\Client2Dlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client2.pch"


!ENDIF 

SOURCE=.\Picture.cpp

!IF  "$(CFG)" == "Client2 - Win32 Release"


"$(INTDIR)\Picture.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client2.pch"


!ELSEIF  "$(CFG)" == "Client2 - Win32 Debug"


"$(INTDIR)\Picture.obj"	"$(INTDIR)\Picture.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client2.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Client2 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Client2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Client2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Client2 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Client2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Client2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 


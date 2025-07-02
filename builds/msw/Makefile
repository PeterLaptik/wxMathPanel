# Mandatory parameters:
# WX_INCLUDE
# WX_SETUP - path to root for setup.h file
# WX_LIBS
# 
# Example:
#
# nmake WX_INCLUDE=C:\wxWidgets\include WX_SETUP=C:\wxWidgets\lib\vc_dll\mswu WX_LIBS=C:\wxWidgets\lib\vc_dll
#
BUILD_VERSION = 1.0.0

BUILD_DIR = ..\..\Build
BUILD_DIR_OBJ = $(BUILD_DIR)\obj
BUILD_DIR_LIB = $(BUILD_DIR)\lib
BUILD_DIR_BIN = $(BUILD_DIR)\bin
BUILD_DIR_INCLUDE = $(BUILD_DIR)\include
BUILD_DIR_SAMPLES = $(BUILD_DIR)\samples

SRC_DIR = ..\..\src
INCLUDE_DIR = ..\..\include
SAMPLES_DIR = ..\..\samples

OBJS = $(BUILD_DIR_OBJ)\wxmathpanel.obj  \
	$(BUILD_DIR_OBJ)\wxmathpanelgraph.obj \
	$(BUILD_DIR_OBJ)\wxmathpanelpointgraph.obj \
	$(BUILD_DIR_OBJ)\mathlegend.obj \
	$(BUILD_DIR_OBJ)\interpolation.obj \
    
RES = $(BUILD_DIR_OBJ)\wxmathpanel.res
	
INCLUDES = $(INCLUDE_DIR)\ifunction.h \
	$(INCLUDE_DIR)\mathlegend.h \
	$(INCLUDE_DIR)\wxmathpanel.h \
	$(INCLUDE_DIR)\interpolation.h \
	$(INCLUDE_DIR)\mouseevent.h \
	$(INCLUDE_DIR)\wxmathpanelgraph.h \
	$(INCLUDE_DIR)\ipointset.h \
	$(INCLUDE_DIR)\pointlabel.h \
	$(INCLUDE_DIR)\wxmathpanelpointgraph.h


CXXFLAGS = -I$(INCLUDE_DIR) -I$(WX_INCLUDE) -I$(WX_SETUP) /EHsc 
LIBS = /LIBPATH:$(WX_LIBS) $(WX_LIBS)\*.lib
CPPFLAGS =  -D_WINDLL \
            -DWINVER=0x0400 \
            -D__WXMSW__ \
            -D_WINDOWS \
            -DWXUSINGDLL -DwxUSE_GUI=1 \
            -D_UNICODE -D_CRT_SECURE_NO_DEPRECATE \
            -D_CRT_NONSTDC_NO_DEPRECATE

!IFDEF DEBUG
!IF $(DEBUG) != 0
!MESSAGE Debug config
NAME_POSTFIX = d
CPPFLAGS = $(CPPFLAGS) -D_DEBUG 
CXXFLAGS = $(CXXFLAGS) /MDd /Od
!ELSE
!MESSAGE Release config
CXXFLAGS = $(CXXFLAGS) /O2
!ENDIF
!ELSE
!MESSAGE Release config
CXXFLAGS = $(CXXFLAGS) /O2
!ENDIF

OUT_FILE_NAME = wx_mathpanel-$(BUILD_VERSION)$(NAME_POSTFIX).dll

all: prepare $(OBJS) $(RES) post-build
    $(CC) /LD /DLL $(OBJS) $(RES) /Fe$(BUILD_DIR_BIN)\$(OUT_FILE_NAME) /link $(LIBS)
    move $(BUILD_DIR_BIN)\*.lib $(BUILD_DIR_LIB)
    move $(BUILD_DIR_BIN)\*.exp $(BUILD_DIR_LIB)

$(BUILD_DIR_OBJ)\wxmathpanel.obj: $(SRC_DIR)\wxmathpanel.cpp
	$(CC) -c $(SRC_DIR)\wxmathpanel.cpp $(CXXFLAGS) $(CPPFLAGS) /Fo$(BUILD_DIR_OBJ)\wxmathpanel.obj
	
$(BUILD_DIR_OBJ)\wxmathpanelgraph.obj: $(SRC_DIR)\wxmathpanelgraph.cpp
	$(CC) -c $(SRC_DIR)\wxmathpanelgraph.cpp $(CXXFLAGS) $(CPPFLAGS) /Fo$(BUILD_DIR_OBJ)\wxmathpanelgraph.obj
	
$(BUILD_DIR_OBJ)\wxmathpanelpointgraph.obj: $(SRC_DIR)\wxmathpanelpointgraph.cpp
	$(CC) -c $(SRC_DIR)\wxmathpanelpointgraph.cpp $(CXXFLAGS) $(CPPFLAGS) /Fo$(BUILD_DIR_OBJ)\wxmathpanelpointgraph.obj
	
$(BUILD_DIR_OBJ)\mathlegend.obj: $(SRC_DIR)\mathlegend.cpp
	$(CC) -c $(SRC_DIR)\mathlegend.cpp $(CXXFLAGS) $(CPPFLAGS) /Fo$(BUILD_DIR_OBJ)\mathlegend.obj
	
$(BUILD_DIR_OBJ)\interpolation.obj: $(SRC_DIR)\interpolation.cpp
	$(CC) -c $(SRC_DIR)\interpolation.cpp $(CXXFLAGS) $(CPPFLAGS) /Fo$(BUILD_DIR_OBJ)\interpolation.obj
    
$(BUILD_DIR_OBJ)\wxmathpanel.res: wxmathpanel.rc
	$(RC) -fo $(BUILD_DIR_OBJ)\wxmathpanel.res  wxmathpanel.rc 
    
post-build: $(INCLUDES)
    copy ..\..\include\*.* $(BUILD_DIR_INCLUDE)\

prepare:
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	if not exist $(BUILD_DIR_OBJ) mkdir $(BUILD_DIR_OBJ)
	if not exist $(BUILD_DIR_LIB) mkdir $(BUILD_DIR_LIB)
    if not exist $(BUILD_DIR_BIN) mkdir $(BUILD_DIR_BIN)
	if not exist $(BUILD_DIR_INCLUDE) mkdir $(BUILD_DIR_INCLUDE)
	if not exist $(BUILD_DIR_SAMPLES) mkdir $(BUILD_DIR_SAMPLES)
    
clean:
    if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)


# Demo and samples
samples: prepare makeres DemoBase DemoGraph DemoInterpolation DemoLegend demodeps

SAMPLES_CPPFLAGS =  -DWINVER=0x0400 \
            -D__WXMSW__ -D_WINDOWS \
            -DWXUSINGDLL -DwxUSE_GUI=1 \
            -D_UNICODE -D_CRT_SECURE_NO_DEPRECATE \
            -D_CRT_NONSTDC_NO_DEPRECATE
            
SAMPLES_CXXLAGS = $(CXXFLAGS) -I../../include
DEMO_SAMPLES_DIR = ../../samples

makeres:
    $(RC) -fo $(BUILD_DIR_OBJ)\demo.res  $(DEMO_SAMPLES_DIR)\res\demo.rc 

DemoBase: $(DEMO_SAMPLES_DIR)/DemoBehavior/DemoBehaviorApp.cpp $(DEMO_SAMPLES_DIR)/DemoBehavior/DemoBehaviorMain.cpp
	$(CC) -c $(DEMO_SAMPLES_DIR)/DemoBehavior/DemoBehaviorApp.cpp /Fo$(BUILD_DIR_OBJ)\DemoBehaviorApp.obj $(SAMPLES_CXXLAGS) $(SAMPLES_CPPFLAGS)
    $(CC) -c $(DEMO_SAMPLES_DIR)/DemoBehavior/DemoBehaviorMain.cpp /Fo$(BUILD_DIR_OBJ)\DemoBehaviorMain.obj $(SAMPLES_CXXLAGS) $(SAMPLES_CPPFLAGS)
	$(CC) $(BUILD_DIR_OBJ)\DemoBehaviorApp.obj $(BUILD_DIR_OBJ)\DemoBehaviorMain.obj $(BUILD_DIR_OBJ)\demo.res \
    /Fe$(BUILD_DIR_SAMPLES)\DemoBehavior /link $(LIBS) $(BUILD_DIR_LIB)\*.lib

DemoGraph: $(DEMO_SAMPLES_DIR)/DemoGraph/DemoGraphApp.cpp $(DEMO_SAMPLES_DIR)/DemoGraph/DemoGraphMain.cpp
	$(CC) -c $(DEMO_SAMPLES_DIR)/DemoGraph/DemoGraphApp.cpp /Fo$(BUILD_DIR_OBJ)\DemoGraphApp.obj $(SAMPLES_CXXLAGS) $(SAMPLES_CPPFLAGS)
    $(CC) -c $(DEMO_SAMPLES_DIR)/DemoGraph/DemoGraphMain.cpp /Fo$(BUILD_DIR_OBJ)\DemoGraphMain.obj $(SAMPLES_CXXLAGS) $(SAMPLES_CPPFLAGS)
	$(CC) $(BUILD_DIR_OBJ)\DemoGraphApp.obj $(BUILD_DIR_OBJ)\DemoGraphMain.obj $(BUILD_DIR_OBJ)\demo.res \
    /Fe$(BUILD_DIR_SAMPLES)\DemoGraph /link $(LIBS) $(BUILD_DIR_LIB)\*.lib
	
DemoInterpolation: $(DEMO_SAMPLES_DIR)/DemoInterpolation/DemoInterpolationApp.cpp $(DEMO_SAMPLES_DIR)/DemoInterpolation/DemoInterpolationMain.cpp
	$(CC) -c $(DEMO_SAMPLES_DIR)/DemoInterpolation/DemoInterpolationApp.cpp /Fo$(BUILD_DIR_OBJ)\DemoInterpolationApp.obj $(SAMPLES_CXXLAGS) $(SAMPLES_CPPFLAGS)
    $(CC) -c $(DEMO_SAMPLES_DIR)/DemoInterpolation/DemoInterpolationMain.cpp /Fo$(BUILD_DIR_OBJ)\DemoInterpolationMain.obj $(SAMPLES_CXXLAGS) $(SAMPLES_CPPFLAGS)
	$(CC) $(BUILD_DIR_OBJ)\DemoInterpolationApp.obj $(BUILD_DIR_OBJ)\DemoInterpolationMain.obj $(BUILD_DIR_OBJ)\demo.res \
    /Fe$(BUILD_DIR_SAMPLES)\DemoInterpolation /link $(LIBS) $(BUILD_DIR_LIB)\*.lib 
	
DemoLegend: $(DEMO_SAMPLES_DIR)/DemoLegend/DemoLegendApp.cpp $(DEMO_SAMPLES_DIR)/DemoLegend/DemoLegendMain.cpp
	$(CC) -c $(DEMO_SAMPLES_DIR)/DemoLegend/DemoLegendApp.cpp /Fo$(BUILD_DIR_OBJ)\DemoLegendApp.obj $(SAMPLES_CXXLAGS) $(SAMPLES_CPPFLAGS)
    $(CC) -c $(DEMO_SAMPLES_DIR)/DemoLegend/DemoLegendMain.cpp /Fo$(BUILD_DIR_OBJ)\DemoLegendMain.obj $(SAMPLES_CXXLAGS) $(SAMPLES_CPPFLAGS)
	$(CC) $(BUILD_DIR_OBJ)\DemoLegendApp.obj $(BUILD_DIR_OBJ)\DemoLegendMain.obj $(BUILD_DIR_OBJ)\demo.res \
    /Fe$(BUILD_DIR_SAMPLES)\DemoLegend /link $(LIBS) $(BUILD_DIR_LIB)\*.lib
    
demodeps:
    copy $(BUILD_DIR_BIN)\$(OUT_FILE_NAME) $(BUILD_DIR_SAMPLES)\$(OUT_FILE_NAME)
    copy $(WX_LIBS)\*.dll $(BUILD_DIR_SAMPLES)\
    

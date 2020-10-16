# wxWidgets library config
# Change value for other versions
# or use an appropriate symbolic link 'wx-config'.
# Note: the classes does not compatible with wx-2.8.
#
WXFLAGS = `wxgtk3u-3.0-config --cxxflags`

CC=clang
FLAGS = -pipe -Wall -O2 -std=c++11

# Output paths
BIN_PATH=./bin/
OBJ_PATH=./bin/obj/

all: createdirs sample_1 sample_2 sample_3 sample_4

sample_1: demobehaviorapp.o demobehaviormain.o wxmathpanel.o
	$(CC) -o $(BIN_PATH)sample_behavior.elf  \
	$(OBJ_PATH)demobehaviorapp.o $(OBJ_PATH)demobehaviormain.o $(OBJ_PATH)wxmathpanel.o \
	-s `wxgtk3u-3.0-config --libs` -lm -lc++

sample_2: demographapp.o demographmain.o mathlegend.o wxmathpanelgraph.o wxmathpanel.o
	$(CC) -o $(BIN_PATH)sample_graph.elf  \
	$(OBJ_PATH)demographapp.o $(OBJ_PATH)demographmain.o \
	$(OBJ_PATH)wxmathpanelgraph.o $(OBJ_PATH)mathlegend.o $(OBJ_PATH)wxmathpanel.o \
	-s `wxgtk3u-3.0-config --libs` -lm -lc++

sample_3: demolegendmain.o demolegendapp.o mathlegend.o wxmathpanelgraph.o wxmathpanel.o
	$(CC) -o $(BIN_PATH)sample_legend.elf  \
	$(OBJ_PATH)demolegendapp.o $(OBJ_PATH)demolegendmain.o \
	$(OBJ_PATH)wxmathpanelgraph.o $(OBJ_PATH)mathlegend.o $(OBJ_PATH)wxmathpanel.o \
	-s `wxgtk3u-3.0-config --libs` -lm -lc++

sample_4: demointerpolationmain.o demointerpolationapp.o mathlegend.o wxmathpanelpointgraph.o \
								wxmathpanel.o interpolation.o
	$(CC) -o $(BIN_PATH)sample_points.elf  \
	$(OBJ_PATH)demointerpolationmain.o $(OBJ_PATH)demointerpolationapp.o $(OBJ_PATH)wxmathpanel.o \
	$(OBJ_PATH)wxmathpanelpointgraph.o $(OBJ_PATH)mathlegend.o $(OBJ_PATH)interpolation.o\
	-s `wxgtk3u-3.0-config --libs` -lm -lc++

demolegendapp.o:
	$(CC) -c ./DemoLegend/DemoLegendApp.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)demolegendapp.o

demolegendmain.o:
	$(CC) -c ./DemoLegend/DemoLegendMain.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)demolegendmain.o

demointerpolationapp.o:
	$(CC) -c ./DemoInterpolation/DemoInterpolationApp.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)demointerpolationapp.o

demointerpolationmain.o:
	$(CC) -c ./DemoInterpolation/DemoInterpolationMain.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)demointerpolationmain.o

demographapp.o:
	$(CC) -c ./DemoGraph/DemoGraphApp.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)demographapp.o

demographmain.o:
	$(CC) -c ./DemoGraph/DemoGraphMain.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)demographmain.o

demobehaviorapp.o:
	$(CC) -c ./DemoBehavior/DemoBehaviorApp.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)demobehaviorapp.o

demobehaviormain.o:
	$(CC) -c ./DemoBehavior/DemoBehaviorMain.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)demobehaviormain.o
	
mathlegend.o:
	$(CC) -c ./../src/mathlegend.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)mathlegend.o

wxmathpanelpointgraph.o:
	$(CC) -c ./../src/wxmathpanelpointgraph.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)wxmathpanelpointgraph.o

wxmathpanelgraph.o:
	$(CC) -c ./../src/wxmathpanelgraph.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)wxmathpanelgraph.o

wxmathpanel.o:
	$(CC) -c ./../src/wxmathpanel.cpp \
	$(FLAGS) $(WXFLAGS) \
	-o $(OBJ_PATH)wxmathpanel.o

interpolation.o:
	$(CC) -c ./../src/interpolation.cpp \
	$(FLAGS) \
	-o $(OBJ_PATH)interpolation.o


createdirs:
	mkdir -p $(OBJ_PATH)


clean:
	rm -r $(BIN_PATH)


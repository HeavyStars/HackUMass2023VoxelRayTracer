CXX=g++
CFLAGS=-Ofast -march=native
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lopengl32

SOURCES=src/main.cpp
CORE=src/core/window.cpp

IMGUI=imgui/imgui.cpp imgui/imgui_widgets.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_demo.cpp imgui/imgui-SFML.cpp
CIMGUI=compiled/imgui/imgui.o compiled/imgui/imgui_widgets.o compiled/imgui/imgui_draw.o compiled/imgui/imgui_tables.o compiled/imgui/imgui_demo.o compiled/imgui/imgui-SFML.o

all:
	$(CXX) $(CFLAGS) -o game.exe $(SOURCES) $(CORE) $(CIMGUI) $(LIBS)

.PHONY: run
run:
	./game.exe
.PHONY: crun
crun: all
	./game.exe
.PHONY: debug
debug:
	$(CXX) -g -o game.exe $(SOURCES) $(CORE) $(CIMGUI) $(LIBS)
.PHONY: clean
clean:
	rm -f game.exe
.PHONY: cimgui
cimgui:
	$(CXX) $(CFLAGS) -o compiled/imgui/imgui.o         -c imgui/imgui.cpp         $(LIBS)
	$(CXX) $(CFLAGS) -o compiled/imgui/imgui_widgets.o -c imgui/imgui_widgets.cpp $(LIBS)
	$(CXX) $(CFLAGS) -o compiled/imgui/imgui_draw.o    -c imgui/imgui_draw.cpp    $(LIBS)
	$(CXX) $(CFLAGS) -o compiled/imgui/imgui_tables.o  -c imgui/imgui_tables.cpp  $(LIBS)
	$(CXX) $(CFLAGS) -o compiled/imgui/imgui_demo.o    -c imgui/imgui_demo.cpp    $(LIBS)
	$(CXX) $(CFLAGS) -o compiled/imgui/imgui-SFML.o    -c imgui/imgui-SFML.cpp    $(LIBS)
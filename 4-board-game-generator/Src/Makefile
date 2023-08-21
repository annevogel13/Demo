CXX = g++
CXXFLAGS += -g -Wall -std=c++11 -pedantic

CAIRO_FLAGS = $(shell pkg-config --cflags librsvg-2.0)
CAIRO_CXXFLAGS = $(if $(CAIRO_FLAGS),$(CAIRO_FLAGS),-DNO_CAIRO)

IMAGICK_FLAGS = $(shell pkg-config --cflags ImageMagick++)
IMAGICK_CXXFLAGS = $(if $(IMAGICK_FLAGS),$(IMAGICK_FLAGS),-DNO_IMAGICK)

CXXFLAGS += $(CAIRO_CXXFLAGS) $(IMAGICK_CXXFLAGS)

DRAW_LDFLAGS = $(shell pkg-config --libs librsvg-2.0)
DRAW_LDFLAGS += $(shell pkg-config --libs ImageMagick++)

LDFLAGS += $(DRAW_LDFLAGS)

.DEFAULT_GOAL := all

SOURCES = 
SOURCES += melangeur.cpp
SOURCES += couleurs.cpp
SOURCES += case.cpp
SOURCES += mur.cpp
SOURCES += site.cpp
SOURCES += direction.cpp
SOURCES += console_pad.cpp
SOURCES += draw.cpp
SOURCES += tuile.cpp
SOURCES += unionfind.cpp
SOURCES += noeud_case.cpp
SOURCES += graph_tuile.cpp
SOURCES += coup.cpp
SOURCES += graph_supermarket.cpp 
#SOURCES += dijkstra.cpp enleve car le dijkstra.cpp ne compile pas du tout 

OBJECTS = $(SOURCES:.cpp=.o)

$(OBJECTS) : %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

CLEAN_OBJECTS = $(OBJECTS)
TARGETS = 



########## test_draw ##########

TEST_DRAW_SOURCES = test_draw.cpp
TEST_DRAW_OBJECTS = $(TEST_DRAW_SOURCES:.cpp=.o)

test_draw : $(TEST_DRAW_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(TEST_DRAW_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(TEST_DRAW_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

all : test_draw
TARGETS += test_draw
CLEAN_OBJECTS += $(TEST_DRAW_OBJECTS)

################ test tuile depart ####################
TEST_TUILE_SOURCES = test_tuile.cpp
TEST_TUILE_OBJECTS = $(TEST_TUILE_SOURCES:.cpp=.o)

test_tuile : $(TEST_TUILE_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(TEST_TUILE_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(TEST_TUILE_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@


############### test tuile classqiue ########################
TEST_TUILE_CL_SOURCES = test_tuileCL.cpp
TEST_TUILE_CL_OBJECTS = $(TEST_TUILE_CL_SOURCES:.cpp=.o)

test_tuileCL : $(TEST_TUILE_CL_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(TEST_TUILE_CL_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(TEST_TUILE__CL_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

################### test rotation ###########################
TEST_ROTATION_SOURCES = test_rotation.cpp
TEST_ROTATION_OBJECTS = $(TEST_ROTATION_SOURCES:.cpp=.o)

test_rotation : $(TEST_ROTATION_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(TEST_ROTATION_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(TEST_ROTATION_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

################### test graph ###########################
TEST_GRAPH_SOURCES = test_graph.cpp
TEST_GRAPH_OBJECTS = $(TEST_GRAPH_SOURCES:.cpp=.o)

test_graph : $(TEST_GRAPH_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(TEST_GRAPH_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(TEST_GRAPH_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@

################### test graph ###########################
TEST_P_SOURCES = test_parcoueur.cpp
TEST_P_OBJECTS = $(TEST_P_SOURCES:.cpp=.o)

test_p : $(TEST_P_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CXX) $(TEST_P_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)
	
$(TEST_P_OBJECTS): %.o : %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c $< -o $@



########## cleanup ##########
DEPS = $(CLEAN_OBJECTS:.o=.d)

clean:
	@rm -f $(DEPS) $(TARGETS) $(CLEAN_OBJECTS)

-include $(DEPS)


CXX = g++
CXXFLAGS = -Wall -g -lX11 -lXi -lXmu -lGLEW -lglut -lGL -lGLU -lm -lstdc++ -ldl -std=c++11 $$(pkg-config --cflags --libs libxml++-2.6)

SRCS = Math.cpp CelestialBody.cpp SolSysBody.cpp Comet.cpp SolarSystem.cpp TextureManager.cpp Drawable.cpp main.cpp 

OBJS = $(SRCS:.cpp=.o)

default: khoom

#.INTERMEDIATE: %.o $(OBJS)

%.o: %.cpp %.hpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

khoom: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ 

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCS) 
	$(CXX) -MM $^ > $@

run: khoom
	./khoom
clean:
	rm -rf *.o 

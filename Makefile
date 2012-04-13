INCLUDE = -I/usr/include/
LIBDIR= -L/usr/X11R6/lib

CXX = g++
CFLAGS = -Wall -g -lX11 -lXi -lXmu -lGLEW -lglut -lGL -lGLU -lm -lstdc++ -ldl 

#SRCS = TextureManager.cpp lesson18.cpp 
SRCS = Math.cpp TextureManager.cpp Drawable.cpp main.cpp 
OBJS = $(SRCS:.cpp=.o)
default: khoom

%.o: %.cpp %.hpp 
	$(CXX) $(CFLAGS)  -c $< -o $@ 

khoom: $(OBJS)
	$(CXX) $(CFLAGS) $^ -o $@

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCS) 
	$(CXX) -MM $^ > $@

run: khoom
	./khoom
clean:
	rm -f *.o 

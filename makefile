CC= g++ 
CFLAGS= -Wall \
		-pedantic \
		-ansi \
		-g \
		-framework GLUT \
		-framework OpenGL \
		-framework Cocoa \
		-lGLEW \
		-lglfw3 \
		-lIOKit \
		-std=c++11
SRC= main.cpp \
	mesh.cpp \
	shader.cpp \
	app.cpp \
	renderer.cpp \
	material.cpp \
	geometry.cpp \
	camera.cpp 
OBJ= $(SRC:.cpp=.o)
EXE= a.out

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.cpp
	$(CC) -o $@ -c $< 

clean :
	rm -f $(EXE) *.o

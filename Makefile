#OBJS specifies which files to compile as part of the project
OBJS = src/*.cpp

#OBJ_NAME specifies the name of the executable
OBJ_NAME = 2048

#CC specifies which compiler to use
CC = g++

#INCLUDE_PATHS specifies the additional include paths to use
INCLUDE_PATHS = -IC:\msys2\mingw64\bin\SDL2 -I..

#LIBRARY_PATHS specifies the additional library paths to usre
LIBRARY_PATHS = -LC:\msys2\mingw64\lib

#COMPILER_FLAGS specifies additional compilation options
# -w supresses all warnings
# -Wl,-subsystem,windows get rid of the console window
# COMPILER_FLAGS = -w -Wl,subsystem,windows
COMPILER_FLAGS =

#LINKER_FLAGS specifies the libraries to link against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

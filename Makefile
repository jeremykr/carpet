PROG = prog
CC = g++
INCLUDE_DIR = src/include
LIB_DIR = lib
CFLAGS = -std=c++1y -I $(INCLUDE_DIR)
LDFLAGS = -L $(LIB_DIR) -lsfml-system-d-2 -lsfml-window-d-2 -lsfml-graphics-d-2 -lopengl32 -lglu32
SRC_DIR = src
OBJ_DIR = obj
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(PROG): $(OBJ_FILES)
	$(CC) glew.o $(OBJ_FILES) $(LDFLAGS) -o $(PROG)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

#glew.o: glew.c
#	gcc -w -g -O -c glew.c

.PHONY : clean
clean :
	del $(PROG).exe > nul 2> nul
	del $(OBJ_DIR)\*.o > nul 2> nul
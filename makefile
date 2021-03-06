# OBJS specifies which files to compile as part of the project
OBJS = src/*.cpp

# CC specifies which compiler we're using
CC = g++

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libraries we're linking against
# Not using LINKER_FLAGS

# OBJ_NAME specifies the name of our executable
OBJ_NAME = dmesg_logger

# This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

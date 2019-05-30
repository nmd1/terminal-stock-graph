INCLUDES=includes
OBJECTS=build
SOURCE=src
OUT=bin
NAME=stock-graph

DIR_CREATE = @mkdir -p 


CC=g++
CL=clang++
DEBUG=gdb -tui
CFLAGS=-I$(INCLUDES) -g -std=c++11 -Wall -Wextra -pedantic
LIBS= -lcurl -lncurses -rdynamic


SRCS=$(wildcard $(SOURCE)/*.cpp)
HEAD=$(wildcard $(INCLUDES)/*.h)
OBJS=$(patsubst $(SOURCE)/%.cpp,$(OBJECTS)/%.o,$(SRCS))	

.PHONY: clean makesourcetree run debug


$(OBJECTS)/%.o: $(SOURCE)/%.cpp $(HEAD)
	@$(MAKE) -s makesourcetree
	@$(CC) -c $< $(CFLAGS) $(LIBS) -o $@ 



all: $(OBJS)
	@$(CC)  $^ $(LIBS) -o $(OUT)/$(NAME)

alt: $(OBJS)
	@$(CL)  $^ $(LIBS) -o $(OUT)/$(NAME)

loud: $(OBJS)
	$(CC)  $^ $(LIBS) -o $(OUT)/$(NAME)

run:
	@$(OUT)/$(NAME)

debug:
	@$(DEBUG) $(OUT)/$(NAME)

makesourcetree:
	@$(DIR_CREATE) $(OBJECTS) $(OUT)

clean:
	@rm -rf $(OBJECTS) $(OUT)
	@rm -f $(SOURCE)/*~  $(INCDIR)/*~ 
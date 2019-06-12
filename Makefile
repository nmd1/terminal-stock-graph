# names for repo folders
INCLUDES:=includes
SOURCE:=src
OUT:=bin
NAME:=stock-graph

# Flags to set/add 
CFLAGS:=-I$(INCLUDES) -g -std=c++11 -Wall -Wextra -pedantic
LIBS:= -lcurl -lncurses -rdynamic

# Handling build folders and depenecy files
OBJECTS:=build
DEPENDS:=$(OBJECTS)/deps

# Setting the path where make should look for src files
space :=
space +=
VPATH := $(subst $(space),:,$(shell find $(SOURCE) -type d))

# Defining the tools we'll need
DIR_CREATE := @mkdir -p 
CC:=g++
CL:=clang++
DEBUG:=gdb -tui

# Generating list of files we'll need to worry about
SRCS:=$(shell find $(SOURCE) -name '*.cpp') # src/render/window.cpp
#HEAD:=$(shell find $(INCLUDES) -name '*.h') # includes/render/window.h
OBJS:=$(patsubst %.cpp,$(OBJECTS)/%.o,$(notdir $(SRCS)))	# build/window.o
#DEPS:=$(patsubst %.cpp,$(DEPENDS)/%.d,$(notdir $(SRCS)))	# build/deps/window.d

# list what recipes are phony and shouldn't tip off include 
.PHONY: clean run debug setup $(OBJECTS), $(OUT)

# Our goal (linking step)
all: $(OBJS)
	@$(CC)  $^ $(CFLAGS) $(LIBS) -o $(OUT)/$(NAME)

-include $(patsubst %.cpp,$(DEPENDS)/%.d,$(notdir $(SRCS)))

# Generating Object files (include will add header deps)
$(OBJECTS)/%.o: %.cpp | $(OBJECTS) $(OUT)
	@$(CC) -c $< $(CFLAGS) $(LIBS) -o $@ 
	@$(CC) $(CFLAGS) -MP -MM -MT '$(patsubst %.cpp,$(OBJECTS)/%.o,$(notdir $<))' $< -o $(patsubst %.cpp,$(DEPENDS)/%.d,$(notdir $<))  

alt: $(OBJS)
	@$(CL)  $^ $(LIBS) -o $(OUT)/$(NAME)

loud: $(OBJS)
	$(CC)  $^ $(LIBS) -o $(OUT)/$(NAME)

run:
	@$(OUT)/$(NAME)

debug:
	@$(DEBUG) $(OUT)/$(NAME)

clean:
	@rm -rf $(OBJECTS) $(OUT)

# Following two recipes are for creating directory structure 
$(OBJECTS):
	@$(DIR_CREATE) $(OBJECTS) $(DEPENDS)

$(OUT):
	@$(DIR_CREATE) $(OUT)
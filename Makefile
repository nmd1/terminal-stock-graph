# names for repo folders
INCLUDES:=includes
SOURCE:=src
TESTS:=tests
OUT:=bin
NAME:=stock-graph

# Flags to set/add 
CFLAGS:=-I$(INCLUDES) -g -std=c++11 -Wall -Wextra -pedantic -pg
LIBS:= -lcurl -lncursesw -rdynamic

# Handling build folders and depenecy files
OBJECTS:=build
DEPENDS:=$(OBJECTS)/deps

# Setting the path where make should look for src files
space :=
space +=
VPATH := $(subst $(space),:,$(shell find $(SOURCE) -type d))
VPATH += $(subst $(space),:,$(shell find $(TESTS) -type d))

# Defining the tools we'll need
DIR_CREATE := @mkdir -p 
CC:=g++
DEBUG:=gdb -tui

# Generating list of files we'll need to worry about
SRCS:=$(shell find $(SOURCE) -name '*.cpp') # src/render/window.cpp
TSRCS += $(shell find $(TESTS) -name '*.cpp') # src/render/window.cpp

#HEAD:=$(shell find $(INCLUDES) -name '*.h') # includes/render/window.h
OBJS:=$(patsubst %.cpp,$(OBJECTS)/%.o,$(notdir $(SRCS)))	# build/window.o
TOBJS:= $(filter-out $(OBJECTS)/main.o, $(OBJS))
TOBJS+=$(patsubst %.cpp,$(OBJECTS)/%.o,$(notdir $(TSRCS)))	# build/window.o

#DEPS:=$(patsubst %.cpp,$(DEPENDS)/%.d,$(notdir $(SRCS)))	# build/deps/window.d

# list what recipes are phony and shouldn't tip off include 
.PHONY: clean run debug setup $(OBJECTS), $(OUT)

# Our goal (linking step)
all: $(OBJS)
	@$(MAKE) build-binary
	@$(MAKE) build-tests

build-binary: $(OBJS)
	@$(CC) $(CFLAGS) $^  $(LIBS) -o $(OUT)/$(NAME)

build-tests: $(TOBJS)
	@$(CC) $(CFLAGS) $^  $(LIBS) -o $(OUT)/$(NAME)-test
	
-include $(patsubst %.cpp,$(DEPENDS)/%.d,$(notdir $(SRCS)))
-include $(patsubst %.cpp,$(DEPENDS)/%.d,$(notdir $(TSRCS)))


# Generating Object files (include will add header deps)
$(OBJECTS)/%.o: %.cpp | $(OBJECTS) $(OUT)
	@$(CC) -c $(CFLAGS) $<  $(LIBS) -o $@ 
	@$(CC) $(CFLAGS) -MP -MM -MT '$(patsubst %.cpp,$(OBJECTS)/%.o,$(notdir $<))' $< -o $(patsubst %.cpp,$(DEPENDS)/%.d,$(notdir $<))  


loud: $(OBJS)
	$(MAKE) build-binary
	$(MAKE) build-tests

run:
	@$(OUT)/$(NAME) $(filter-out $@,$(MAKECMDGOALS))

test:
	@$(OUT)/$(NAME)-test $(filter-out $@,$(MAKECMDGOALS))

debug:
	@$(DEBUG) $(OUT)/$(NAME)

clean:
	@rm -rf $(OBJECTS) $(OUT)

# Following two recipes are for creating directory structure 
$(OBJECTS):
	@$(DIR_CREATE) $(OBJECTS) $(DEPENDS)

$(OUT):
	@$(DIR_CREATE) $(OUT)


# The following allows us to run binaries with no args
# Without make yelling 
%:
    @:    
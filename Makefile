# Folder with '.hpp' files (declarations)
INCLUDE_DIR=./include

# Folder with '.cpp' files (definitions)
VPATH=./src

# Compilation flags
CXXFLAGS=-Wall -I$(INCLUDE_DIR) #-Werror -O3

# Linked libraries
LINKFLAGS = -lm

# Files to be included
DEPENDENCIES=main.cpp

# Executable
TARGETS=func_ploter

build: $(TARGETS)

$(TARGETS): $(DEPENDENCIES)
	$(CXX) $(CXXFLAGS) -o $(TARGETS) $^ $(LINKFLAGS)

.PHONY: clean
clean:
	-rm -f $(TARGETS)

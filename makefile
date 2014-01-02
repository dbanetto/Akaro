#Compiler
CPP=g++

#Compiler Flags
CPPFLAGS=-Wall -O0 -g3 -fmessage-length=0 -std=c++0x

#Target
TARGET=Akaro
EXE=Akora
#Libray
LIBS := -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image -lSDL2_net
LIBDIR := 

#Includes
INCLUDE := -I src/

#SRC Folder
SRCDIR = src/
OBJDIR = obj/

#Sub Folders in SRC dir
SUBDIR := $(shell find $(SRCDIR)  -type d -print)

#SRC Files
SRC:=$(shell find $(SRCDIR) -type f | grep .cpp)
OBJ:=$(SRC:$(SRCDIR)%.cpp=$(OBJDIR)%.o)

all : make_dir $(EXE)

$(EXE) : $(OBJ)
	$(CPP) -o $@ $(CPPFLAGS) $(OBJ) $(LIBDIR) $(LIBS)

$(OBJ): $(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(CPP) $(CPPFLAGS) -c $< $(LIB_PATH) $(LIBS) $(INCLUDE) -o $@

make_dir:
	@mkdir -p bin
	@mkdir -p $(SUBDIR:$(SRCDIR)%=$(OBJDIR)%)

clean:
	rm -rf $(EXE)
	rm -rf bin
	rm -rf $(OBJDIR)

.PHONEY: clean
.PHONEY: all

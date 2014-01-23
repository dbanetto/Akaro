#Compiler
CPP=g++

#Compiler Flags
CPPFLAGS = -Wall -fmessage-length=0 -std=c++0x

#Target
OUTDIR=bin/
EXE=Akora
TARGET_OS=None

#Libray
LIBS = -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image -lSDL2_net
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


#OS
windows : LIBS += -lmingw32 -lSDL2main
windows : CPPFLAGS +=
windows : EXE = $(EXE).exe
windows : TARGET_OS=windows	
windows :
	@echo Windows


linux : TARGET_OS=linux
linux :
	@echo Linux

## OS Detection
ifeq ($(TARGET_OS),None)
    ifeq ($(OS),Windows_NT)
        TARGET_OS = windows
    else
        UNAME_S := $(shell uname -s)
        ifeq ($(UNAME_S),Linux)
            TARGET_OS = linux
        endif
        ifeq ($(UNAME_S),Darwin)
            TARGET_OS = osx
        endif
    endif
endif

#Build type
release : CPPFLAGS += -O3 -g0
release : EXE := $(EXE)-release
release : $(OUTDIR)$(EXE)
	@echo Build Type: Release
	@echo $(EXE) $(CPPFLAGS)
	@echo Target OS : $(TARGET_OS)



 
debug : CPPFLAGS += -O0 -g3
debug : EXE := $(EXE)-debug
debug : $(OUTDIR)$(EXE)
	@echo Build Type: Debug
	@echo $(EXE) $(CPPFLAGS)
	@echo Target OS : $(TARGET_OS)

#All
all : make_dir  $(OUTDIR)$(EXE)
	@echo Target OS : $(TARGET_OS)
	@echo $(CPPFLAGS) $(OUTDIR)$(EXE)

$(OUTDIR)$(EXE) : $(OBJ)
	$(CPP) -o $(OUTDIR)$(EXE) $(CPPFLAGS) $(OBJ) $(LIBDIR) $(LIBS)
	cp $(OUTDIR)$(EXE) Akaro

$(OBJ): $(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(CPP) $(CPPFLAGS) -c $< $(LIB_PATH) $(LIBS) $(INCLUDE) -o $@

make_dir:
	@mkdir -p $(OUTDIR)
	@mkdir -p $(SUBDIR:$(SRCDIR)%=$(OBJDIR)%)

clean:
	rm -rf $(OUTDIR)
	rm -rf $(OBJDIR)

.PHONEY: clean
.PHONEY: all

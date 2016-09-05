TARGET_DIR:=bin
HEADER_DIR:=include/views
CFLAGS:=-I../../header -Iinclude/views -isysteminclude/  -Wall -I include/ -pedantic -DDEBUG  -Wextra  -ggdb #-pg #-lprofiler
LFLAGS:=
TEST:=@test -d $(TARGET_DIR) || mkdir $(TARGET_DIR)
ARFLAGS:= rcs
OUTLIB:= ../../$(TARGET_DIR)/libgui.a

ifeq ($(OS),Windows_NT)
	CPP=g++ 
	CFLAGS+= -m64  -fdiagnostics-color=always -std=c++14 -I include/SDL2
	LFLAGS+=  -static-libstdc++ -static-libgcc ../../bin/libsim.a -lmingw32 -mconsole -L libs/SDL2 -L libs/SDL2_ttf -Wl,-Bdynamic -lSDL2main -lSDL2 -lsdl2_ttf  
	TEST:=
	POSTCOPY:= cp dlls/* bin/
else
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CPP=g++-4.9 
	CFLAGS+= -O2 -fdiagnostics-color=always -std-c++14
	LFLAGS+= 
endif
ifeq ($(UNAME_S),Darwin)
        CPP=clang++ 
        CFLAGS+= -stdlib=libc++ -std=c++14 -F../../extlibs/
        LFLAGS+= 
endif
endif

SOURCES:=$(wildcard *.cpp)
OBJECTS:=$(patsubst %.cpp,$(TARGET_DIR)/%.o,$(wildcard *.cpp))

EXE := $(TARGET_DIR)/GUI
all: $(OUTLIB)

$(OUTLIB): $(OBJECTS)
	@echo "LIBRARY $(OUTLIB)"
	$(AR) $(ARFLAGS)  $(OUTLIB) $(OBJECTS) 

$(EXE):	$(OBJECTS)
	@echo "LINK $(EXE)"
	$(CPP)   -o $@ $(OBJECTS) $(LFLAGS)
	$(POSTCOPY)

$(TAREGET_DIR)/sdlbase.o : $(HEADER_DIR)/KeyCodeConverter.hpp
$(TARGET_DIR)/TestGUI.o : $(HEADER_DIR)/AbsoluteLayout.hpp
$(TARGET_DIR)/View.o : $(HEADER_DIR)/Canvas.hpp
$(TARGET_DIR)/TextView.o : $(HEADER_DIR)/View.hpp $(HEADER_DIR)/KeyCodeConverter.hpp
$(TARGET_DIR)/ViewGroup.o : $(HEADER_DIR)/View.hpp $(HEADER_DIR)/LayoutParams.hpp
$(TAREGET_DIR)/AbsoluteLayout.o : $(HEADER_DIR)/ViewGroup.hpp


$(TARGET_DIR)/%.o: %.cpp $(HEADER_DIR)/%.hpp
	$(TEST)
	@echo "COMPILE $<"
	@$(CPP) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXE)
	rm -f $(OBJECTS)

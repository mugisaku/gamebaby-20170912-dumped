BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -Icbes -I/usr/include/SDL2  -Werror -Wno-unused-result


ifeq ($(opt),1)
  CXXFLAGS += -Os -march=i686 -fomit-frame-pointer
  LDFLAGS  += -s
else
  CXXFLAGS += -g
endif


COMMON_LDFLAGS = -lstdc++


ifeq ($(mingw),1)
  EXE_EXT = .exe
  DIR_PREFIX = i686-w64-mingw32
  CMD_PREFIX = $(DIR_PREFIX)-
  LDFLAGS = $(COMMON_LDFLAGS) -lmingw32 -static
else
  LDFLAGS = $(COMMON_LDFLAGS)
endif




ifeq ($(emcc),1)
  CXX      = CCACHE_DIR=/tmp/ccachedir ccache emcc
  CXXFLAGS = -std=gnu++11 -I. -Icbes -Werror -Wno-unused-result -O2 -s USE_SDL=2
  EXE_EXT  = .html
  LDFLAGS  = --shell-file shell.html  --memory-init-file 0
else ifeq ($(ccache),1)
  CXX = CCACHE_DIR=/tmp/ccachedir ccache $(CMD_PREFIX)g++
else
  CXX = $(CMD_PREFIX)g++
endif



STRIP = $(CMD_PREFIX)strip
AR    = $(CMD_PREFIX)ar

CXXFLAGS += -I$(BASE_DIR)/$(DIR_PREFIX)/include
LDFLAGS  += -L$(BASE_DIR)/$(DIR_PREFIX)/lib


ifeq ($(delay),1)
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS)  $< -o $@
	sleep 1
endif


OBJ +=                    \
  game_commandpillar.o    \
  game_tagtable.o         \
  game_message_page.o     \
  game_message.o          \
  game_item.o             \
  game_place.o            \
  game_world.o            \
  game_routine.o          \
  game_routine__basic.o   \
  game_routine__select.o  \
  game_environment.o      \
  game_xx.o               \
  gmbb_controller.o       \
  gmbb.o                  \


all: gmbb$(EXE_EXT)


clean:
	make -C cbes  clean
	rm -f $(OBJ) gmbb$(EXE_EXT)


gmbb$(EXE_EXT): $(OBJ) CBES_OBJ
	$(CXX) -o $@  $(OBJ) cbes/*.o $(CXXFLAGS) $(LDFLAGS) -lSDL2


CBES_OBJ:
	make -C cbes


FORCE:
.PHONY: FORCE CBES_OBJ





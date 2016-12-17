BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -I/usr/include/SDL2  -Werror -Wno-unused-result
LDFLAGS  = -lz -lpng -lSDL2_image -lSDL2 -lSDL2main

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
  LDFLAGS += $(COMMON_LDFLAGS) -lmingw32 -static
else
  LDFLAGS += $(COMMON_LDFLAGS)
endif




ifeq ($(emcc),1)
  CXX      = CCACHE_DIR=/tmp/ccachedir ccache emcc
  CXXFLAGS = -std=gnu++11 -I. -I/usr/include/SDL2 -Werror -Wno-unused-result -O2 -s USE_SDL=2 -s USE_ZLIB=1
  EXE_EXT  = .html
  LDFLAGS  = --embed-file data.bin
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


all: data.bin ta_sample$(EXE_EXT) rpg_sample$(EXE_EXT)


clean:
	make -C core     clean
	make -C text_adv clean
	make -C rpg clean
	rm -f ta_sample$(EXE_EXT) rpg_sample$(EXE_EXT) *.js *.html *.mem makedata.o makedata data.bin


.PHONY: core text_adv rpg data.bin


ifeq ($(emcc),1)
else
makedata: core makedata.cpp
	$(CXX) -o $@  makedata.cpp core/*.o $(CXXFLAGS) $(LDFLAGS)

data.bin: makedata
	./makedata data/*
endif


ta_sample$(EXE_EXT): core text_adv ta_sample.cpp
	$(CXX) -o $@  ta_sample.cpp core/*.o text_adv/*.o $(CXXFLAGS) $(LDFLAGS)

rpg_sample$(EXE_EXT): core rpg rpg_sample.cpp
	$(CXX) -o $@  rpg_sample.cpp core/*.o rpg/*.o $(CXXFLAGS) $(LDFLAGS)



core:
	make -C core

text_adv:
	make -C text_adv

rpg:
	make -C rpg





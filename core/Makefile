BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -Werror -Wno-unused-result


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
  CXXFLAGS = -std=gnu++11 -I. -Werror -Wno-unused-result -O2 -s USE_SDL=2
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
  gmbb_formatted.o        \
  gmbb_image.o            \
  gmbb_image__print.o     \
  gmbb_image__frame.o     \
  gmbb_garden.o           \
  gmbb_sprite.o           \
  gmbb_object.o           \
  gmbb_container.o        \
  gmbb_window.o           \
  gmbb_controller.o       \
  gmbb_font.o             \
  gmbb_environment.o      \
  gmbb_message.o          \
  gmbb_message_page.o     \


all: $(OBJ)


clean:
	rm -f $(OBJ)





BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -I/usr/include -Werror -Wno-unused-result


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
  CXXFLAGS = -std=gnu++11 -I. -Werror -Wno-unused-result -O2 -s USE_SDL=2 -s USE_ZLIB=1
  EXE_EXT  = .html
  LDFLAGS  =
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
  gmbb_filereader.o       \
  gmbb_file.o             \
  gmbb_filewriter.o       \
  gmbb_media.o            \
  gmbb_formatted.o        \
  gmbb_image.o            \
  gmbb_image__png.o       \
  gmbb_image__mgf.o       \
  gmbb_image__print.o     \
  gmbb_image__frame.o     \
  gmbb_garden.o           \
  gmbb_sprite.o           \
  gmbb_object.o           \
  gmbb_container.o        \
  gmbb_window.o           \
  gmbb_controller.o       \
  gmbb_font.o             \
  gmbb_font__large.o      \
  gmbb_environment.o      \
  gmbb_message.o          \
  gmbb_message_page.o     \
  gmbb_unicode.o          \


all: $(OBJ)


clean:
	rm -f $(OBJ)





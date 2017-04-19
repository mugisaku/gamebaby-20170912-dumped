cmake_minimum_required(VERSION 2.8)
project(gmbb)


find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "CCACHE_DIR=/tmp/ccachedir ccache")
endif(CCACHE_FOUND)


set(CMAKE_VERBOSE_MAKEFILE ON)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()


set(CMAKE_C_COMPILER  gcc)
set(CMAKE_C_FLAGS   "-std=c14 -Werror")
set(CMAKE_CXX_COMPILER  g++)
set(CMAKE_CXX_FLAGS "-std=c++14 -Werror")
set(CMAKE_CXX_LINK_FLAGS  "-lstdc++ -lz -lpng -lSDL2 -lSDL2main")


set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS}   -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS}   -Og -g")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -Og -g")


if(EMSCRIPTEN)
  set(EXECUTABLE_EXTENSION ".html")
  set(CMAKE_CXX_COMPILER  em++)
  set(CMAKE_CXX_FLAGS "-std=c++14 -Werror -Wno-switch -O2")
  set(CMAKE_CXX_FLAGS_DEBUG "")
  set(CMAKE_CXX_LINK_FLAGS  "${CMAKE_CXX_LINK_FLAGS} -s USE_ZLIB=1 -s USE_LIBPNG=1 -s USE_SDL=2 --embed-file motion.png")
endif()




set(CORE_SOURCES
  core/gmbb_filereader.cpp
  core/gmbb_file.cpp
  core/gmbb_filewriter.cpp
  core/gmbb_media.cpp
  core/gmbb_formatted.cpp
  core/gmbb_color_table.cpp
  core/gmbb_subimage.cpp
  core/gmbb_subimage__png.cpp
  core/gmbb_image.cpp
  core/gmbb_image__png.cpp
  core/gmbb_image__print.cpp
  core/gmbb_image__frame.cpp
  core/gmbb_garden.cpp
  core/gmbb_sprite.cpp
  core/gmbb_window.cpp
  core/gmbb_controller.cpp
  core/gmbb_font.cpp
  core/gmbb_font__large.cpp
  core/gmbb_environment.cpp
  core/gmbb_text.cpp
  core/gmbb_textmanager.cpp
  core/gmbb_unicode.cpp
  core/gmbb_random_number.cpp
)


set(TRPT_SOURCES
  trpt/trpt_square.cpp
  trpt/trpt_facility.cpp
  trpt/trpt_cursor.cpp
  trpt/trpt_board.cpp
  trpt/trpt_board__load.cpp
  trpt/trpt_piece.cpp
  trpt/trpt_piecemanager.cpp
  trpt/trpt_energy.cpp
  trpt/trpt_porter.cpp
  trpt/trpt_master.cpp
  trpt/trpt_master__draw.cpp
  trpt/trpt_master__process.cpp
)


set(ROGIE_SOURCES
  rogie/rogie_square.cpp
  rogie/rogie_square__search.cpp
  rogie/rogie_firearm.cpp
  rogie/rogie_item.cpp
  rogie/rogie_piece.cpp
  rogie/rogie_piece__callback.cpp
  rogie/rogie_piece__autoplay.cpp
  rogie/rogie_field.cpp
  rogie/rogie_field__manage.cpp
)


set(ACT_SOURCES
  act/act_object.cpp
  act/act_gamemanager.cpp
)


include_directories(./core)
#include_directories(./trpt)
#include_directories(./rogie)
#include_directories(./act)
include_directories(/usr/include/SDL2)
add_executable("Rs${EXECUTABLE_EXTENSION}" rs.cpp ${CORE_SOURCES})
#add_executable("Rogie${EXECUTABLE_EXTENSION}" rogie.cpp ${CORE_SOURCES} ${ROGIE_SOURCES})
#add_executable("Act${EXECUTABLE_EXTENSION}" act.cpp ${CORE_SOURCES} ${ACT_SOURCES})


if(EMSCRIPTEN)
#  set_target_properties("Act${EXECUTABLE_EXTENSION}"  PROPERTIES LINK_FLAGS "--shell-file act_shell.html")
endif()





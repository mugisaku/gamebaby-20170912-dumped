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
set(CMAKE_C_FLAGS   "-std=c11 -Werror")
set(CMAKE_CXX_COMPILER  g++)
set(CMAKE_CXX_FLAGS "-std=c++11 -Werror")
set(CMAKE_CXX_LINK_FLAGS  "-lstdc++ -lz -lpng -lSDL2 -lSDL2main")


set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS}   -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -march=core2 -fomit-frame-pointer")
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS}   -Og -g")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -Og -g")


if(EMSCRIPTEN)
  set(EXECUTABLE_EXTENSION ".html")
  set(CMAKE_CXX_COMPILER  em++)
  set(CMAKE_CXX_FLAGS "-std=c++11 -Werror -O2")
  set(CMAKE_CXX_FLAGS_DEBUG "")
  set(CMAKE_CXX_LINK_FLAGS  "${CMAKE_CXX_LINK_FLAGS} -s USE_SDL=2 --embed-file font.bin")
endif()




set(CORE_SOURCES
  core/gmbb_filereader.cpp
  core/gmbb_file.cpp
  core/gmbb_filewriter.cpp
  core/gmbb_media.cpp
  core/gmbb_formatted.cpp
  core/gmbb_image.cpp
  core/gmbb_image__png.cpp
  core/gmbb_image__mgf.cpp
  core/gmbb_image__print.cpp
  core/gmbb_image__frame.cpp
  core/gmbb_garden.cpp
  core/gmbb_sprite.cpp
  core/gmbb_object.cpp
  core/gmbb_container.cpp
  core/gmbb_window.cpp
  core/gmbb_controller.cpp
  core/gmbb_font.cpp
  core/gmbb_font__large.cpp
  core/gmbb_environment.cpp
  core/gmbb_message.cpp
  core/gmbb_message_page.cpp
  core/gmbb_unicode.cpp
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
  rogie/rogie_piece.cpp
  rogie/rogie_field.cpp
)


include_directories(./core)
include_directories(./trpt)
include_directories(./rogie)
add_executable("Trpt${EXECUTABLE_EXTENSION}" trpt.cpp ${CORE_SOURCES} ${TRPT_SOURCES})
add_executable("Rogie${EXECUTABLE_EXTENSION}" rogie.cpp ${CORE_SOURCES} ${ROGIE_SOURCES})




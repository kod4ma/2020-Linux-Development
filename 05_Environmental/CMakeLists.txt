cmake_minimum_required(VERSION 3.1) 

project(05_Environmental C)

find_library(NCURSES_LIBRARY ncursesw)
find_library(PCRE2_LIBRARY pcre2-8)

find_path(NCURSES_DIR ncurses.h)
find_path(PCRE2_DIR pcre2.h)

include_directories(${NCURSES_DIR} ${PCRE2_DIR}) 

add_executable(pcre pcre.c)

target_link_libraries(pcre ${NCURSES_LIBRARY} ${PCRE2_LIBRARY})

option(without_UTF "disable PCRE2_UCP" OFF)

if(WITHOUT_UTF)
  add_definitions(-DREGEX_USE_UTF=0)
else()
  add_definitions(-DREGEX_USE_UTF=1)
endif()

set (TO_CLEAN ${CMAKE_BINARY_DIR}/CMakeCache.txt 
              ${CMAKE_BINARY_DIR}/cmake_install.cmake
              ${CMAKE_BINARY_DIR}/Makefile
              ${CMAKE_BINARY_DIR}/CMakeFiles
              ${CMAKE_BINARY_DIR}/pcre)

add_custom_target(allclean
COMMAND rm -rf ${TO_CLEAN}
)

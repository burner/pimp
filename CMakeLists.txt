cmake_minimum_required(VERSION 2.8)

## we have some extra modules here
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

## thats our project
project(pimp)

INCLUDE(FindPkgConfig)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
##############################################################################

## our headers
set(pimp_HEADERS 
)

## well and the sources
set(pimp_SOURCES 
	src/main.cpp
)

## some gui stuff
set(pimp_UIS 
	ui/mainwindow.glade
)

set(PIMP_GLADE_HEADER "")
foreach(F ${pimp_UIS})
    add_custom_command(
        OUTPUT "g2cpp_${F}.hpp"
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/g2cpp.py "${CMAKE_CURRENT_SOURCE_DIR}/${F}"
        COMMENT "Compiling ${F} to header"
		DEPENDS "${F}")
	list(APPEND PIMP_GLADE_HEADER "g2cpp_${F}.hpp")
endforeach()

#add_custom_target(pimp_glade_header ALL DEPENDS ${PIMP_GLADE_HEADER})

## we love c++0x and a chatty compiler that comments on our code
set(CMAKE_CXX_FLAGS "-Wall -Werror -ggdb --std=c++0x -std=gnu++0x")

include_directories(
	${CMAKE_CURRENT_BINARY_DIR} 
	${CMAKE_CURRENT_SOURCE_DIR}/includes
	${CMAKE_CURRENT_SOURCE_DIR}/ui
	${CMAKE_CURRENT_SOURCE_DIR}/../sweet.hpp
)

add_executable(pimp
    ${pimp_SOURCES}
	${pimp_HEADERS}
	${PIMP_GLADE_HEADER}

)
add_dependencies(pimp ${PIMP_GLADE_HEADER})

target_link_libraries(pimp ${GTKMM_LIBRARIES})

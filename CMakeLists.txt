# Cmake file to build the application

cmake_minimum_required (VERSION 2.6)
project (Tank)

# I guess you have not released the project yet :p
set (Tank_VERSION_MAJOR 0)
set (Tank_VERSION_MINOR 1)
set (Tank_VERSION_PATCH 0)

set (EXECUTABLE_NAME "Tank")

if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -coverage")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 ")

# Find SFML
# Note: SFML_STATIC_LIBRARIES determines which libraries are found by find_package()
find_package(SFML 2.4.2 COMPONENTS audio graphics window system network)

# If found, include and link; otherwise output error message
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else()
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

# Add boost library
FIND_PACKAGE( Boost 1.40 COMPONENTS python3 REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# Add python library
set(PythonInterp 3)
find_package(PythonLibs 2 REQUIRED)

###################################################################
# enable ExternalProject
include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

# Download and install GoogleTest
ExternalProject_Add(
    googletest
    URL https://github.com/google/googletest/archive/release-1.8.1.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(googletest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(gtest_main IMPORTED STATIC GLOBAL)
add_dependencies(gtest_main googletest)

# Set libgtest properties
set_target_properties(gtest_main PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest_main.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgtest target to be used as a dependency by test programs
add_library(gtest IMPORTED STATIC GLOBAL)
add_dependencies(gtest googletest)

# Set libgtest properties
set_target_properties(gtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(gmock_main IMPORTED STATIC GLOBAL)
add_dependencies(gmock_main googletest)

# Set libgmock properties
set_target_properties(gmock_main PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(gmock IMPORTED STATIC GLOBAL)
add_dependencies(gmock googletest)

# Set libgmock properties
set_target_properties(gmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")


###################################################################
# download and build sol2
ExternalProject_Add(
    sol2-ext
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG develop
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

###################################################################
# download and build lua
ExternalProject_Add(
    lua-ext
    GIT_REPOSITORY https://github.com/LuaDist/lua.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION} -DBUILD_SHARED_LIBS=OFF
)

ADD_LIBRARY(lua IMPORTED STATIC)
SET_TARGET_PROPERTIES(lua PROPERTIES IMPORTED_LOCATION ${EXTERNAL_INSTALL_LOCATION}/lib/liblua.a)
ADD_DEPENDENCIES(lua lua-ext)


##################################
# set project include
include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR} ${source_dir}/include ${PYTHON_INCLUDE_DIRS})

##################################
# Engine
file(GLOB_RECURSE LOGIC_SRC Logic/*.cpp)
add_library(Logic ${LOGIC_SRC})
target_link_libraries(Logic PUBLIC ${Boost_LIBRARIES} ${PYTHON_LIBRARY})
target_include_directories(Logic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Logic/)

##################################
# Define a Main
file(GLOB_RECURSE MAIN_SRC main/*.cpp)
add_executable(Main ${MAIN_SRC})
target_link_libraries(Main sfml-graphics sfml-window sfml-system ${Boost_LIBRARIES} ${PYTHON_LIBRARY} Logic pthread m dl lua)
target_include_directories(Main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main/ ${Boost_INCLUDE_DIR})

##################################
# Define a test
# file(GLOB_RECURSE TEST_SRC Test/*.cpp)
# add_executable(test_all ${TEST_SRC})
# target_link_libraries(test_all gtest_main gtest gmock pthread Logic )
# target_include_directories(test_all PUBLIC ${TEST_DIR} ${source_dir}/include)

##################################
# Just make the test runnable with
#   $ make test
# enable_testing()
# add_test(NAME test COMMAND test_all)

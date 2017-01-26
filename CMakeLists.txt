#This file shows how to link to a PUMI
#installation using CMake
#it represents a simple 'CMakeLists.txt'
#file for a new project

cmake_minimum_required(VERSION 3.0.0)
# Starting here are the critical lines:
project(pumi-intro VERSION 1.0.0)

# Allow the user to indicate where they installed SCOREC
# via "-DSCOREC_PREFIX=/home/somewhere" when calling `cmake`
set(SCOREC_PREFIX "" CACHE STRING "Directory where SCOREC is installed")

# If SCOREC_PREFIX was specified, only link to that directory,
# i.e. don't link to another installation in /usr/lib by mistake
if (SCOREC_PREFIX)
  find_package(SCOREC 2.1.0 REQUIRED CONFIG PATHS ${SCOREC_PREFIX} NO_DEFAULT_PATH)
else()
# IF SCOREC_PREFIX was not specified, look in typical system directories,
# and also in CMAKE_PREFIX_PATH (environment variable)
  find_package(
      SCOREC #package name, has to be SCOREC
      2.1.0  #version. can be omitted, and will match any installed version
             #greater than or equal to this one, as long as the major number
             #is the same
      REQUIRED #indicate that SCOREC is really needed to compile
      CONFIG   #skip the 'MODULE' search system, save some time and confusion
      )
endif()

set(CMAKE_CXX_COMPILER ${SCOREC_COMPILER})
set(CMAKE_CXX_FLAGS ${SCOREC_CXX_FLAGS})

add_executable(pcu1 pcu1.c)
target_link_libraries(pcu1 PRIVATE SCOREC::core)
add_executable(pcu2 pcu2.c)
target_link_libraries(pcu2 PRIVATE SCOREC::core)
add_executable(pumi1 pumi1.cc)
target_link_libraries(pumi1 PRIVATE SCOREC::core)
add_executable(pumi2 pumi2.cc)
target_link_libraries(pumi2 PRIVATE SCOREC::core)
add_executable(pumi3 pumi3.cc)
target_link_libraries(pumi3 PRIVATE SCOREC::core)

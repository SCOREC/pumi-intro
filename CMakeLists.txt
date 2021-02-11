#This file shows how to link to a PUMI
#installation using CMake
#it represents a simple 'CMakeLists.txt'
#file for a new project

cmake_minimum_required(VERSION 3.0.0)

project(pumi-intro VERSION 1.0.0 LANGUAGES CXX)
# Starting here are the critical lines:

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

function(build_example exe src)
  add_executable(${exe} ${src})
  target_link_libraries(${exe} PRIVATE SCOREC::core)
endfunction()

build_example(pcu1 pcu1.cc)
build_example(pcu2 pcu2.cc)
build_example(pumi1 pumi1.cc)
build_example(pumi2 pumi2.cc)
build_example(pumi3 pumi3.cc)

find_package(LATEX COMPONENTS pdflatex)
message("PDFLATEX_COMPILER ${PDFLATEX_COMPILER}")

add_custom_target(pumi_intro ALL
  SOURCES pumi_intro.pdf)
add_custom_command(
  OUTPUT  pumi_intro.pdf
  COMMAND ${PDFLATEX_COMPILER} ARGS pumi_intro.tex
  COMMAND ${PDFLATEX_COMPILER} ARGS pumi_intro.tex
  DEPENDS pumi_intro.tex
)

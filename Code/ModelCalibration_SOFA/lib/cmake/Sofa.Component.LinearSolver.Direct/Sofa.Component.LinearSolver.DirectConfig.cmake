# CMake package configuration file for the Sofa.Component.LinearSolver.Direct module

### Expanded from @PACKAGE_GUARD@ by SofaMacrosInstall.cmake ###
include_guard()
################################################################

####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was Sofa.Component.LinearSolver.DirectConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

find_package(Sofa.Simulation.Core QUIET REQUIRED)
find_package(Sofa.Component.LinearSolver.Iterative QUIET REQUIRED)
find_package(Threads QUIET REQUIRED)

set(SOFA_COMPONENT_LINEARSOLVER_DIRECT_HAVE_METIS 1)
set(SOFA_COMPONENT_LINEARSOLVER_DIRECT_HAVE_CSPARSE 1)

if(SOFA_COMPONENT_LINEARSOLVER_DIRECT_HAVE_METIS)
    find_package(Metis QUIET REQUIRED HINTS "${CMAKE_CURRENT_LIST_DIR}/..")
endif()
if(SOFA_COMPONENT_LINEARSOLVER_DIRECT_HAVE_CSPARSE)
    find_package(CSparse QUIET REQUIRED HINTS "${CMAKE_CURRENT_LIST_DIR}/..")
endif()

if(NOT TARGET Sofa.Component.LinearSolver.Direct)
    include("${CMAKE_CURRENT_LIST_DIR}/Sofa.Component.LinearSolver.DirectTargets.cmake")
endif()

check_required_components(Sofa.Component.LinearSolver.Direct)

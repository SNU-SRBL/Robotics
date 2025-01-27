#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Sofa.Simulation" for configuration "MinSizeRel"
set_property(TARGET Sofa.Simulation APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(Sofa.Simulation PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/Sofa.Simulation.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/Sofa.Simulation.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Sofa.Simulation )
list(APPEND _IMPORT_CHECK_FILES_FOR_Sofa.Simulation "${_IMPORT_PREFIX}/lib/Sofa.Simulation.lib" "${_IMPORT_PREFIX}/bin/Sofa.Simulation.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

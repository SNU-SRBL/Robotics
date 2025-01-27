#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Sofa.Component.LinearSolver.Iterative" for configuration "MinSizeRel"
set_property(TARGET Sofa.Component.LinearSolver.Iterative APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(Sofa.Component.LinearSolver.Iterative PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/Sofa.Component.LinearSolver.Iterative.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/Sofa.Component.LinearSolver.Iterative.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Sofa.Component.LinearSolver.Iterative )
list(APPEND _IMPORT_CHECK_FILES_FOR_Sofa.Component.LinearSolver.Iterative "${_IMPORT_PREFIX}/lib/Sofa.Component.LinearSolver.Iterative.lib" "${_IMPORT_PREFIX}/bin/Sofa.Component.LinearSolver.Iterative.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

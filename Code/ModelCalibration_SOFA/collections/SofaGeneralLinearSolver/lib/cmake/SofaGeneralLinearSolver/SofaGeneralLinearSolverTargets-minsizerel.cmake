#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SofaGeneralLinearSolver" for configuration "MinSizeRel"
set_property(TARGET SofaGeneralLinearSolver APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(SofaGeneralLinearSolver PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/SofaGeneralLinearSolver.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/SofaGeneralLinearSolver.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS SofaGeneralLinearSolver )
list(APPEND _IMPORT_CHECK_FILES_FOR_SofaGeneralLinearSolver "${_IMPORT_PREFIX}/lib/SofaGeneralLinearSolver.lib" "${_IMPORT_PREFIX}/bin/SofaGeneralLinearSolver.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

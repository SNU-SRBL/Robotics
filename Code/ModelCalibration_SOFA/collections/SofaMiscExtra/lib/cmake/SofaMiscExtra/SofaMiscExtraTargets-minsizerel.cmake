#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SofaMiscExtra" for configuration "MinSizeRel"
set_property(TARGET SofaMiscExtra APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(SofaMiscExtra PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/SofaMiscExtra.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/SofaMiscExtra.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS SofaMiscExtra )
list(APPEND _IMPORT_CHECK_FILES_FOR_SofaMiscExtra "${_IMPORT_PREFIX}/lib/SofaMiscExtra.lib" "${_IMPORT_PREFIX}/bin/SofaMiscExtra.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "TestPlugin" for configuration "MinSizeRel"
set_property(TARGET TestPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(TestPlugin PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/TestPlugin.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/TestPlugin.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS TestPlugin )
list(APPEND _IMPORT_CHECK_FILES_FOR_TestPlugin "${_IMPORT_PREFIX}/lib/TestPlugin.lib" "${_IMPORT_PREFIX}/bin/TestPlugin.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

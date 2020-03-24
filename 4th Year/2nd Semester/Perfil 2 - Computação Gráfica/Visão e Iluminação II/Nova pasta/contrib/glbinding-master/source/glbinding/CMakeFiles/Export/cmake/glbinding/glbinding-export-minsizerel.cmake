#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "glbinding::glbinding" for configuration "MinSizeRel"
set_property(TARGET glbinding::glbinding APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(glbinding::glbinding PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/glbinding.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS glbinding::glbinding )
list(APPEND _IMPORT_CHECK_FILES_FOR_glbinding::glbinding "${_IMPORT_PREFIX}/lib/glbinding.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

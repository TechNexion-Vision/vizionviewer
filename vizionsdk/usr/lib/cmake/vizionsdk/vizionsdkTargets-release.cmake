#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vizionsdk::VizionSDK" for configuration "Release"
set_property(TARGET vizionsdk::VizionSDK APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vizionsdk::VizionSDK PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libVizionSDK.so.25.4.1"
  IMPORTED_SONAME_RELEASE "libVizionSDK.so.25"
  )

list(APPEND _IMPORT_CHECK_TARGETS vizionsdk::VizionSDK )
list(APPEND _IMPORT_CHECK_FILES_FOR_vizionsdk::VizionSDK "${_IMPORT_PREFIX}/lib/libVizionSDK.so.25.4.1" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

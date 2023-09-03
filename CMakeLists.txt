cmake_minimum_required(VERSION 3.14)

project("fake-drummer")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(midifile STATIC IMPORTED)

# set_property(
#   TARGET midifile APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG
# )

# set_target_properties(clip PROPERTIES
#   IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
#   IMPORTED_LOCATION_DEBUG "${CLIP_ROOT}/build/Release/clip.lib"
# )

set_property(
  TARGET midifile APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE
)

set_target_properties(midifile PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${MIDIFILE_ROOT}/lib/libmidifile.a"
)
  
set_target_properties(midifile PROPERTIES
  MAP_IMPORTED_CONFIG_MINSIZEREL Release
  MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
)

target_include_directories(midifile INTERFACE "${MIDIFILE_ROOT}/include/midifile")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(${PROJECT_NAME} 
    "src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} midifile)
# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "ArtAction_autogen"
  "CMakeFiles\\ArtAction_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ArtAction_autogen.dir\\ParseCache.txt"
  )
endif()

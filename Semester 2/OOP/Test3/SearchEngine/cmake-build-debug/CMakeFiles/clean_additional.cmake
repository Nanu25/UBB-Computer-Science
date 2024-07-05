# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SearchEngine_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SearchEngine_autogen.dir\\ParseCache.txt"
  "SearchEngine_autogen"
  )
endif()

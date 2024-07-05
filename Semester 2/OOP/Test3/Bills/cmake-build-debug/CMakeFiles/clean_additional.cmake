# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Bills_autogen"
  "CMakeFiles\\Bills_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Bills_autogen.dir\\ParseCache.txt"
  )
endif()

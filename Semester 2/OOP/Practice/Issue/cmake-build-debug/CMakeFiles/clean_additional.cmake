# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TestProfa_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TestProfa_autogen.dir\\ParseCache.txt"
  "TestProfa_autogen"
  )
endif()

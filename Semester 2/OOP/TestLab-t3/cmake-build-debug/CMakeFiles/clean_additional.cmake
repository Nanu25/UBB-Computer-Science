# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TestLab_t3_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TestLab_t3_autogen.dir\\ParseCache.txt"
  "TestLab_t3_autogen"
  )
endif()

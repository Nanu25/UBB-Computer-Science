# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TaskTest_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TaskTest_autogen.dir\\ParseCache.txt"
  "TaskTest_autogen"
  )
endif()

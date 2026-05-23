# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/elsai_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/elsai_autogen.dir/ParseCache.txt"
  "elsai_autogen"
  )
endif()

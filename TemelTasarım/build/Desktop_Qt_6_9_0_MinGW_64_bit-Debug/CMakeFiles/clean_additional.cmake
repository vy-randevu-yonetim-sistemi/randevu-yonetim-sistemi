# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\VeriYapilari_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\VeriYapilari_autogen.dir\\ParseCache.txt"
  "VeriYapilari_autogen"
  )
endif()

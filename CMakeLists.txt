cmake_minimum_required(VERSION 2.8.0)

#project name
set (PROJECT  CgiCpp)

project (${PROJECT})

set(CMAKE_INSTALL_PREFIX   ${PROJECT_BINARY_DIR}/bin)

#增加需要文件夹
ADD_SUBDIRECTORY(tools)
#ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  # add_definitions(-DOS_LINUX)
  MESSAGE(STATUS "Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "QNX")
	message("QNX")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	message("Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "WindowsCE")
	message("WindowsCE")
endif()

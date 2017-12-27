project(Tool)

# "true" or "false"
set(CMAKE_TOOL_TEST  "false")

# include_directories(SYSTEM "inc")

add_definitions(-DLIBTOOL_EXPORTS)
add_definitions(-D_AFXDLL)

set(libTool_HEAD
    Singleton.h
    TConf.h
    TLog.h
    TSocket.h
    TSql.h
    TString.h
    )

set(libTool_SRC
    TConf.cpp
    TLog.cpp
    TSocket.cpp
    TSql.cpp
    TString.cpp
    )

if (CMAKE_TOOL_TEST STREQUAL "false")
    message("=============build libTool.so")
    add_library(Tool SHARED
            ${libTool_HEAD}
            ${libTool_SRC})
else()
    message("=============build test true")
    add_definitions(-DTEST_MAIN)

    add_executable(TestTConf TConf.h TConf.cpp)
    add_executable(TestTLog Singleton.h TLog.h TLog.cpp)
    add_executable(TestTsocket TSocket.h TSocket.cpp)
    add_executable(TestTSql TSql.h TSql.cpp)
    add_executable(TestTString TString.h TString.cpp)

endif()

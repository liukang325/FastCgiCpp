project(Tool)

# "true" or "false"
set(CMAKE_TOOL_TEST  "false")

include_directories(SYSTEM ".")

include_directories("/usr/include/mysql")


add_definitions(-DLIBTOOL_EXPORTS)
add_definitions(-D_AFXDLL)

set(jsoncpp_HEAD
    Json/include/assertions.h
    Json/include/autolink.h
    Json/include/config.h
    Json/include/features.h
    Json/include/forwards.h
    Json/include/json.h
    Json/include/reader.h
    Json/include/value.h
    Json/include/version.h
    Json/include/writer.h
    Json/include/json_tool.h
    )
set(jsoncpp_SRC
    Json/src/json_reader.cpp
    Json/src/json_value.cpp
    Json/src/json_valueiterator.inl
    Json/src/json_writer.cpp
    )

set(libTool_HEAD
    ${jsoncpp_HEAD}
    Singleton.h
    TConf.h
    TLog.h
    TSocket.h
    TSql.h
    TString.h
    TJson.h
    TCookie.h
    TEncode.h
    )

set(libTool_SRC
    ${jsoncpp_SRC}
    TConf.cpp
    TLog.cpp
    TSocket.cpp
    TSql.cpp
    TString.cpp
    TJson.cpp
    TCookie.cpp
    TEncode.cpp
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
    add_executable(TestTLog Singleton.h TLog.h TLog.cpp TSocket.h TSocket.cpp)
#    add_executable(TestTsocket TSocket.h TSocket.cpp)
#    add_executable(TestTSql TSql.h TSql.cpp)
    add_executable(TestTString TString.h TString.cpp)
    add_executable(TestTJson TJson.h TJson.cpp ${jsoncpp_HEAD} ${jsoncpp_SRC})


endif()

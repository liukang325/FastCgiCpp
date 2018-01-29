project(Tool)

# "true" or "false"
set(CMAKE_TOOL_TEST  "false")

#C++11 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

include_directories(SYSTEM ".")

include_directories("/usr/include/mysql")
include_directories("${PROJECT_SOURCE_DIR}/websocketpp")

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
    ToolGlobal.h
    Singleton.h
    TConf.h
    TLog.h
    TSocket.h
    TSql.h
    TString.h
    TJson.h
    TEncode.h
    TDateTime.h
    TWebSocket.h
    Template.h
    )

set(libTool_SRC
    ${jsoncpp_SRC}
    TConf.cpp
    TLog.cpp
    TSocket.cpp
    TSql.cpp
    TString.cpp
    TJson.cpp
    TEncode.cpp
    TDateTime.cpp
    TWebSocket.cpp
    Template.cpp
    )

if (CMAKE_TOOL_TEST STREQUAL "false")
    message("=============build libTool.so")
    add_library(Tool SHARED
            ${libTool_HEAD}
            ${libTool_SRC})

    target_link_libraries(Tool
            boost_system
            boost_chrono
            mysqlclient
            sqlite3)

else()
    message("=============build test true")
    add_definitions(-DTEST_MAIN)

    add_executable(TestTConf TConf.h TConf.cpp)
    add_executable(TestTLog Singleton.h TLog.h TLog.cpp TSocket.h TSocket.cpp)
#    add_executable(TestTsocket TSocket.h TSocket.cpp)
    add_executable(TestTSql TSql.h TSql.cpp)
    target_link_libraries(TestTSql mysqlclient)
    target_link_libraries(TestTSql sqlite3)

#    add_executable(TestTString TString.h TString.cpp)
    add_executable(TestTJson TJson.h TJson.cpp ${jsoncpp_HEAD} ${jsoncpp_SRC})

    add_executable(TestTWebSocket TWebSocket.h TWebSocket.cpp )
    target_link_libraries(TestTWebSocket boost_system boost_chrono)

    add_executable(TestTEncode TEncode.h TEncode.cpp)

    add_executable(TestTemplate Template.h Template.cpp TString.h TString.cpp)


endif()

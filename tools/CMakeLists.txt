project(libTool)

# include_directories(SYSTEM "inc")

add_definitions(-DLIBTOOL_EXPORTS)
add_definitions(-D_AFXDLL)

set(libTool_HEAD
    TFile.h
    TLog.h
    TSocket.h
    TSql.h
    )

set(libTool_SRC
    TFile.cpp
    TLog.cpp
    TSocket.cpp
    TSql.cpp
    )

add_library(libTool SHARED
        ${libTool_HEAD}
        ${libTool_SRC})


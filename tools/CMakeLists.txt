project(Tool)

# include_directories(SYSTEM "inc")

add_definitions(-DLIBTOOL_EXPORTS)
add_definitions(-D_AFXDLL)

set(libTool_HEAD
    TGlobal.h
    TConf.h
    TFile.h
    TLog.h
    TSocket.h
    TSql.h
    )

set(libTool_SRC
    TConf.cpp
    TFile.cpp
    TLog.cpp
    TSocket.cpp
    TSql.cpp
    )

add_library(Tool SHARED
        ${libTool_HEAD}
        ${libTool_SRC})


project (TestTool)

set(APP_HEAD
    TestTConf.h
    )

set(APP_SRC
    TestTConf.cpp
    main.cpp
    )

# 指定头文件路径
include_directories("${PROJECT_SOURCE_DIR}/../tools")
# 指定库文件路径
link_directories("${PROJECT_BINARY_DIR}/tools")

# 生成的可执行文件的路径
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin)

# 将所有源程序编译为可执行文件
add_executable(TestTool
        ${APP_HEAD}
        ${APP_SRC})

 target_link_libraries(TestTool
         Tool)

# 安装程序到${CMAKE_INSTALL_PREFIX}/bin目录
install(TARGETS TestTool RUNTIME DESTINATION bin)

# 设定安装的可执行文件所需的库文件路径，如果没有该项设置，会出错：cannot open shared object file: No such file or directory
set_property(TARGET TestTool PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)

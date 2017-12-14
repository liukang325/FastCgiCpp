project (${PROJECT})

# 指定头文件路径
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
MESSAGE(STATUS "==========" ${PROJECT_SOURCE_DIR})


set(APP_HEAD

    )

set(APP_SRC
    main.cpp
    )

# 指定库文件路径
link_directories(${PROJECT_SOURCE_DIR}/tools)

# 把当前目录的所有文件名赋值给APP_SRC
#AUX_SOURCE_DIRECTORY(.  APP_SRC)

# 生成的可执行文件的路径
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin)

# 将所有源程序编译为可执行文件
add_executable(${PROJECT}
#        ${APP_HEAD})
        ${APP_SRC})

target_link_libraries(${PROJECT}
        fcgi)


# 安装程序到${CMAKE_INSTALL_PREFIX}/bin目录
install(TARGETS ${PROJECT} RUNTIME DESTINATION bin)

# 设定安装的可执行文件所需的库文件路径，如果没有该项设置，会出错：cannot open shared object file: No such file or directory
set_property(TARGET ${PROJECT}  PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)

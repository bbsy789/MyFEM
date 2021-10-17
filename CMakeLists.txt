cmake_minimum_required(VERSION 3.0.0)
project(MyFEM VERSION 0.1.0)#工程名字必须与代码路径文件夹名称一致，其导出文件也必须一致

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)#头文件
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib )#库文件
#AUX_SOURCE_DIRECTORY( ./ DIR_SRCS)#收集目录中的文件名并赋值给变量
enable_testing()
#SET(TMP_SRCS ${DIR_SRCS} )

add_subdirectory(src)#子文件夹
# 设置MSVC编译编码
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

ADD_EXECUTABLE(MyFEM src/main.cpp)
#输出exe文件
set(CMAKE_BUILD_TYPE DEBUG)#配置build模式
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

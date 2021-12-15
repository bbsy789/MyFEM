IF(WIN32)
cmake_minimum_required(VERSION 3.0.0)
set( CMAKE_CXX_COMPLIER "D:/x86_64-w64-mingw32/bin/g++.exe")#设置g++编译器,必须写在project之前否则无效
set( CMAKE_CXX_FLAGS "-std=c++20")#参数含义是 set compliler for c++ language
set( CMAKE_BUILD_TYPE "release")#debug/release两种编译模式
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
project(MyFEM VERSION 0.1.0)#工程名字必须与代码路径文件夹名称一致，其导出文件也必须一致
#${PROJECT_SOURCE_DIR}代表了CMakeLists.txt的绝对路径
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)#包含头文件
INCLUDE_DIRECTORIES(D:/x86_64-w64-mingw32/include)
LINK_DIRECTORIES( D:/x86_64-w64-mingw32/lib)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib )#把${PROJECT_SOURCE_DIR}设为链接目录
#find_package(OpenCV REQUIRED)添加依赖，去寻找该库头文件位置以及库文件名称，将其设为变量，返回提供给CMakeLists.txt
#在CMakeLists.txt中使用第三方库的三部曲
#find_package 、include_directories、target_link_libraries
#include_directories($(OpenCV_INCLUDE_DIRS))
#去哪里找头文件
#target_link_libraries(<target> [item1] [item2] [...]
#上述指令中的<target>是指通过add_executable()和add_library()指令生成已经创建的目标文件。
#而[item]表示库文件没有后缀的名字。默认情况下，库依赖项是传递的。
#当这个目标链接到另一个目标时，链接到这个目标的库也会出现在另一个目标的连接线上。
#这个传递的接口存储在interface_link_libraries的目标属性中，可以通过设置该属性直接重写传递接口。
#LINK_DIRECTORIES()
#去哪里找库文件(.so/.lib/.ddl等)



#AUX_SOURCE_DIRECTORY( ./ DIR_SRCS)#收集指定路径中这里是./也就是所有的文件名并赋值给变量
#SET(TMP_SRCS ${DIR_SRCS} )

enable_testing()
add_subdirectory(src)#增加子文件夹
# 设置MSVC编译编码
#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

ADD_EXECUTABLE(MyFEM demo/pre_test/pre_test.cpp
								   src/point.cpp
								   src/pre.cpp
								   src/point.cpp 
								   src/matrix.cpp 
								   src/element.cpp)
#输出exe文件
#target_link_libraries(${PROJECT_NAME})#链接关键指令
set(CMAKE_BUILD_TYPE release)#配置build模式
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/bin)#设置生成的可执行二进制文件存放的存放目录
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/lib)
include(CPack)
ENDIF()

IF(UNIX)
set( CMAKE_CXX_COMPLIER "g++")
set( CMAKE_C_COMPLIER "gcc")
cmake_minimum_required(VERSION 3.0.0)
PROJECT(MyFEM VERSION 0.1.0)
ADD_SUBDIRECTORY(src)
set( CMAKE_CXX_COMPLIER "g++")#设置g++编译器
set( CMAKE_CXX_FLAGS "-std=c++20")#参数含义是 set compliler for c++ language
set( CMAKE_BUILD_TYPE "release")#debug/release两种编译模式
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
enable_testing()
ADD_EXECUTABLE(MyFEM demo/pre_test/pre_test.cpp
								   src/point.cpp
								   src/pre.cpp
								   src/point.cpp 
								   src/matrix.cpp 
								   src/element.cpp)
set(CMAKE_BUILD_TYPE release)#配置build模式
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/bin)#设置生成的可执行二进制文件存放的存放目录
include(CPack)
ENDIF()
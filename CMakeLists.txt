cmake_minimum_required(VERSION 3.0)     #指定 cmake最小版本要求为3.0
 

SET (CMAKE_C_COMPILER             "/usr/bin/gcc") # 填写绝对路径 mac此处改为clang
SET (CMAKE_C_FLAGS                "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
SET (CMAKE_CXX_COMPILER             "/usr/bin/g++") # 填写绝对路径 mac此处改为clang++
SET (CMAKE_CXX_FLAGS                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g -pthread")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG -pthread")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_EXE_LINKER_FLAGS " -no-pie")
project(HelloHttp)  #指定项目名称，习惯用大写指定项目名称
 
 #等价于g++  helloworld.cpp -o helloworld；helloworld_cmake帮助区分以前生成的helloword
 #第一个参数指定生成可执行文件名称helloworld_cmake，第二参数要编译的源文件helloworld.cpp
 
#INCLUDE_DIRECTORIES(C:/vcpkg/installed/x86-windows/include)
# 需包含的库文件
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
	MESSAGE("windows")
elseif (CMAKE_HOST_APPLE)
    set(MACOS 1)
	MESSAGE("macos")
elseif (CMAKE_HOST_UNIX)
    set(LINUX 1)
	MESSAGE("linux")
endif ()


if (WIN32 OR MSVC)
	
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

	#定义 WIN32_LEAN_AND_MEAN 避免winsock.h 和 winsock2.h冲突导致的重定义
	add_definitions(-DWIN32_LEAN_AND_MEAN=1)
elseif (MACOS)
	link_directories(
			./lib/macos
		)
	include_directories(
			./include/macos
		)
    # 仅查找静态库，强制后缀为 .a
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

    # 如果只是优先查找静态库，保证 .a 后缀在前面即可，把默认的后缀加上
    # set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
elseif (LINUX)
	link_directories(
			./lib/linux
		)
	include_directories(
			./include/linux
		)
    # 仅查找静态库，强制后缀为 .a
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
endif()


# 指定为C++11 版本
set(CMAKE_CXX_STANDARD 11)

#AUX_SOURCE_DIRECTORY(. mq_list)



add_executable(${PROJECT_NAME} http-server.cpp)
target_link_libraries(${PROJECT_NAME}  
	libwfrest.a
 	libworkflow.a
	libz.a
	libssl.a
	libcrypto.a
	dl
	)


  find_package(Threads REQUIRED)
  target_link_libraries(${PROJECT_NAME}  Threads::Threads)

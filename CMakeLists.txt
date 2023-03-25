# cmake最低版本要求
CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

# 设置工程名称
PROJECT(sudoku)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # 添加c++11标准支持

SET(CMAKE_BUILD_TYPE "Debug")  # Debug模式 选项: Release Debug MinSizeRel RelWithDebInfo

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  # debug模式下 gdb相关选项
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") # release模式下 gdb相关选项

add_definitions(-DDEBUG) # 相当于代码中 #define DEBUG

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin") # 可执行文件输出目录

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include") # 头文件包含目录

MESSAGE("Identifying the OS...")
if(WIN32)
  MESSAGE("This is Windows.")
elseif(APPLE)
  MESSAGE("This is MacOS.")
elseif(UNIX)
  MESSAGE("This is Linux.")
endif()


# 添加源代码文件夹, 自动扫描所有文件
AUX_SOURCE_DIRECTORY(sudoku-yan DIR_SRCS)


add_executable(sudoku  # 输出名为sudoku的可执行文件
   ${DIR_SRCS}
)


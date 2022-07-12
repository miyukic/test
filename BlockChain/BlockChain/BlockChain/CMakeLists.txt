# CMakeList.txt : BlockChain の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.8)

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (BlockChain "BlockChain.cpp" "BlockChain.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BlockChain PROPERTY CXX_STANDARD 20)
endif()

# https://qiita.com/sunrise_lover/items/589c4353d9547effc74b#3-cmake%E3%81%AE%E5%9F%BA%E6%9C%AC%E3%83%AB%E3%83%BC%E3%83%AB
#set(PROJECT_VERSION 1.0.0)
## C++バージョン
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
#
#
#
##find_package(Boost REQUIRED 
##  COMPONENTS
##    context
##    filesystem
##    program_options
##    regex
##    system
##    thread
##)
#
##if(Boost_FOUND)
##  message (STATUS "Found Boost")
##else()
##  message(WARNING "Boost not found")
##endif()
#
## find_package(OpenCV REQUIRED)
## if(OpenCV_FOUND)
##   message (STATUS "Found OpenCV")
## else(OpenCV_FOUND)
##   message(WARNING "OpenCV not found")
## endif()
#
## リスト型変数の定義 cmake_training_STCという変数にソースコードを2枚渡している。
##set(cmake_training_SRC src/my_class.cpp src/my_main.cpp)
#
##set(cmake_training_HEADERS include/cmake_training/my_class.h)
#
##add_executable(main ${cmake_training_SRC} ${cmake_training_HEADERS})
#
## コンパイラにincludeのパスを通します。gccで言う -l オプション
##target_include_directories(main PUBLIC include/cmake_training ${BOOST_INCLUDE_DIRS})
#
#
##target_link_libraries(main PUBLIC ${Boost_LIBRARIES})
#
#
#MESSAGE(STATUS "--------------------------------------------")
#MESSAGE(STATUS "Info :")
#MESSAGE(STATUS "  Project Name = ${PROJECT_NAME}")
#MESSAGE(STATUS "  Version =     ${PROJECT_VERSION}")
#MESSAGE(STATUS "  CMAKE_VERSION =        ${CMAKE_VERSION}")
#MESSAGE(STATUS "  CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")
#MESSAGE(STATUS "  CMAKE_BUILD_TYPE =     ${CMAKE_BUILD_TYPE}")
#MESSAGE(STATUS "  CMAKE_INSTALL_LIBDIR = ${CMAKE_INSTALL_LIBDIR}")
#message(STATUS "  Boost_LIBRARIES =        ${Boost_LIBRARIES}")
#message(STATUS "  OpenCV_VERSION =       ${OpenCV_VERSION}")
#
## TODO: テストを追加し、必要な場合は、ターゲットをインストールします。

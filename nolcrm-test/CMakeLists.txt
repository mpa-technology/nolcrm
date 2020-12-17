cmake_minimum_required(VERSION 3.5)
project(nolcrm-test CXX)

set(CMAKE_CXX_STANDARD 17)
set_target_properties(${TARGET} PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS ON
            )



set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Sql PrintSupport)

add_executable(${PROJECT_NAME} "main.cpp")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)


target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Sql Qt5::PrintSupport pthread gtest)

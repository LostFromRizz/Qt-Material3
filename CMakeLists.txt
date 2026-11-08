cmake_minimum_required(VERSION 3.18)

project(Material3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Qt6 6.8 COMPONENTS Gui Qml Quick Core QuickControls2 REQUIRED)

qt_standard_project_setup(REQUIRES 6.8)

add_compile_options(-Wall -Wextra -Wno-vla-cxx-extension)

function(sourceslist out_var prefix)
    set(result "")
    foreach(item IN LISTS ARGN)
        list(APPEND result "${prefix}/${item}")
    endforeach()
    set(${out_var} "${result}" PARENT_SCOPE)
endfunction()

add_subdirectory(src)

qt6_add_resources(${PROJECT_NAME} "icons" PREFIX / BASE assets FILES assets/icons/MaterialSymbolsRounded.ttf)

include(GNUInstallDirs)

set(_QML_INSTALL_DIR "${QT6_INSTALL_PREFIX}/${QT6_INSTALL_QML}")

install(
    DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/
    DESTINATION "${_QML_INSTALL_DIR}/${PROJECT_NAME}"
)

# install(
#     FILES ${CMAKE_SOURCE_DIR}/MaterialConfig.cmake
#     DESTINATION lib/cmake/${PROJECT_NAME}
# )





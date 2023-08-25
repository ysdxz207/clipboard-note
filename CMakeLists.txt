cmake_minimum_required(VERSION 3.26)
project(clipnote)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

SET(GLFW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW/glfw-3.3.8.zip)
SET(ImgUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui-1.89.8)
SET(ImgUI_BACKENDS_DIR ${ImgUI_DIR}/backends)
SET(IMGUI_FILES
        ${ImgUI_DIR}/imgui.cpp
        ${ImgUI_DIR}/imgui_draw.cpp
        ${ImgUI_DIR}/imgui_tables.cpp
        ${ImgUI_DIR}/imgui_widgets.cpp
        ${ImgUI_BACKENDS_DIR}/imgui_impl_glfw.cpp # platform
        ${ImgUI_BACKENDS_DIR}/imgui_impl_opengl3.cpp # render
)

include_directories(
        ${ImgUI_DIR}
        ${ImgUI_BACKENDS_DIR}
)

include(FetchContent)
# cmake 3.11 above
FetchContent_Declare(glfw URL ${GLFW_PATH})
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    # Fetch the content using previously declared details
    FetchContent_Populate(glfw)

    # Set custom variables
    set(BUILD_SHARED_LIBS OFF)
    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_TESTS OFF)
    set(GLFW_BUILD_DOCS OFF)
    set(GLFW_INSTALL OFF)
    set(GLFW_VULKAN_STATIC OFF)

    # Bring the populated content into the build
    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

add_executable(${PROJECT_NAME} src/win/main.cpp ${IMGUI_FILES})


if(WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32 glfw)
else()
    target_link_libraries(${PROJECT_NAME} GL glfw)
endif()



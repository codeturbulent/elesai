cmake_minimum_required(VERSION 3.16)

project(elsai VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets Network)
find_package(GLEW REQUIRED)

# Live2D SDK Paths
set(LIVE2D_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/Live2D)
set(LIVE2D_FRAMEWORK_DIR ${LIVE2D_ROOT}/Framework)
set(LIVE2D_CORE_DIR ${LIVE2D_ROOT}/Core)

# Platform definitions for Live2D
if(WIN32)
    add_definitions(-DCSM_TARGET_WIN_GL)
elseif(APPLE)
    add_definitions(-DCSM_TARGET_MAC_GL)
else()
    add_definitions(-DCSM_TARGET_LINUX_GL)
endif()

# Include directories
include_directories(
    src
    ${LIVE2D_FRAMEWORK_DIR}/src
    ${LIVE2D_CORE_DIR}/include
)

# Live2D Framework Sources (Common ones)
# Live2D Framework Sources (Filtered to avoid platform-specific errors)
file(GLOB_RECURSE LIVE2D_FRAMEWORK_SOURCES
    ${LIVE2D_FRAMEWORK_DIR}/src/*.cpp
)

# Filter out platform-specific renderers that do not match the current system
if(WIN32)
    # On Windows, we might want D3D or OpenGL. 
    # But let\s at least exclude Mac/Vulkan if not explicitly requested.
    list(FILTER LIVE2D_FRAMEWORK_SOURCES EXCLUDE REGEX "Rendering/Metal/.*")
    list(FILTER LIVE2D_FRAMEWORK_SOURCES EXCLUDE REGEX "Rendering/Vulkan/.*")
elseif(APPLE)
    list(FILTER LIVE2D_FRAMEWORK_SOURCES EXCLUDE REGEX "Rendering/D3D11/.*")
    list(FILTER LIVE2D_FRAMEWORK_SOURCES EXCLUDE REGEX "Rendering/D3D9/.*")
    list(FILTER LIVE2D_FRAMEWORK_SOURCES EXCLUDE REGEX "Rendering/OpenGL/.*")
    list(FILTER LIVE2D_FRAMEWORK_SOURCES EXCLUDE REGEX "Rendering/Vulkan/.*")
else()
    # Linux and others
    list(FILTER LIVE2D_FRAMEWORK_SOURCES EXCLUDE REGEX "Rendering/D3D11/.*")
    list(FILTER LIVE2D_FRAMEWORK_SOURCES EXCLUDE REGEX "Rendering/D3D9/.*")
    list(FILTER LIVE2D_FRAMEWORK_SOURCES EXCLUDE REGEX "Rendering/Metal/.*")
    list(FILTER LIVE2D_FRAMEWORK_SOURCES EXCLUDE REGEX "Rendering/Vulkan/.*")
endif()

add_executable(elsai
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/Live2DWidget.cpp
    src/Live2DWidget.h
    src/Live2DManager.cpp
    src/Live2DManager.h
    src/LLMClient.cpp
    src/LLMClient.h
    src/ChatOverlay.cpp
    src/ChatOverlay.h
    src/SystemController.cpp
    src/SystemController.h
    ${LIVE2D_FRAMEWORK_SOURCES}
)

# Link Core Library (Platform dependent - assuming Linux x86_64 for now)
target_link_libraries(elsai PRIVATE 
    Qt6::Widgets 
    Qt6::OpenGLWidgets 
    Qt6::Network
    GLEW::GLEW
    ${LIVE2D_CORE_DIR}/lib/linux/x86_64/libLive2DCubismCore.a
    GL
)

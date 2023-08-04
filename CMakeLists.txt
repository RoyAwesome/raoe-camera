cmake_minimum_required(VERSION 3.26)

if(NOT COMMAND raoe_add_module)
    include(cmake/add-module.cmake)
endif()

raoe_add_module(
    STATIC
    NAME "camera"
    NAMESPACE "raoe"
    TARGET_VARIABLE MODULE_TARGET
    DEPENDENCIES
    PUBLIC
        glm::glm
    COMPILE_DEFINITIONS
    "GLM_ENABLE_EXPERIMENTAL"
    INCLUDE_DIRECTORIES
    PUBLIC
    "include"
    CPP_SOURCE_FILES
    "src/drivers.cpp"
)

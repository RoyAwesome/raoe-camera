cmake_minimum_required(VERSION 3.26)

if(NOT COMMAND CPMAddPackage)
    if(NOT DEFINED CPM_DOWNLOAD_VERSION)
        set(CPM_DOWNLOAD_VERSION 0.38.0)
    endif()

    if(CPM_SOURCE_CACHE)
        set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    elseif(DEFINED ENV{CPM_SOURCE_CACHE})
        set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    else()
        set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    endif()
endif()

CPMAddPackage("gh:g-truc/glm#master")
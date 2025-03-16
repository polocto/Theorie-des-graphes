cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(TP1)

# Spécifier la version de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Options de build
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the build type: Debug, Release")

# Vérifier le type de build et configurer les options de compilation
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

# Ajouter les fichiers sources récursivement depuis le répertoire src
file(GLOB_RECURSE SOURCES "../src/*.cpp")

# Ajouter les répertoires d'inclusion
include_directories(src)

# Ajouter un exécutable
add_executable(TP1 ${SOURCES})

# Lier les options de compilation au type de build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(TP1 PRIVATE ${CMAKE_CXX_FLAGS_DEBUG})
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(TP1 PRIVATE ${CMAKE_CXX_FLAGS_RELEASE})
endif()

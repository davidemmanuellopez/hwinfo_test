project(MiProyecto LANGUAGES CXX)  # Asegúrate de especificar CXX

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.16)
find_package(fmt QUIET)

if (NOT fmt_FOUND)
    message(" -> libfmt not found. Fetching from github...")
    include(FetchContent)
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 11.0.1)
    FetchContent_MakeAvailable(fmt)
else ()
    message(" -> using installed libfmt")
endif ()


add_subdirectory(deps/hwinfo)

# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(deps/nlohmann_json)

# Encontrar el paquete pkg-config para udev
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(UDEV REQUIRED libudev)
#find_library(UDEV_LIBRARIES NAMES udev)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/deps/hwinfo/include")

#add_executable(system_info system_infoMain.cpp)
add_executable(main main.cpp)



if (UNIX)
    add_library(system_info_lib SystemInfo.cpp "${CMAKE_CURRENT_SOURCE_DIR}/LinuxSystemInfo.hpp")
    target_link_libraries(system_info_lib PRIVATE systemd)

elseif(WIN32)
    add_library(system_info_lib SystemInfo.cpp "${CMAKE_CURRENT_SOURCE_DIR}/WindowsSystemInfo.hpp")
    #target_link_libraries(system_info_lib PRIVATE systemd)
endif()


target_link_libraries(system_info_lib PRIVATE lfreist-hwinfo::hwinfo fmt::fmt nlohmann_json::nlohmann_json)
#target_link_libraries(system_info PRIVATE lfreist-hwinfo::hwinfo fmt::fmt)
target_link_libraries(main PRIVATE  system_info_lib)

#target_link_libraries(libudev_test PRIVATE libudev-zero)
#target_link_libraries(libudev_test2 udev)
#target_link_libraries(sd_service_test systemd)
#install(TARGETS system_info)

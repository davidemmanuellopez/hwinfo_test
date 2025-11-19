cmake_minimum_required(VERSION 3.2)
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

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/libudev-zero)


#add_library(libudev-zero
#    ${CMAKE_CURRENT_SOURCE_DIR}/deps/libudev-zero/udev_enumerate.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/deps/libudev-zero/udev.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/deps/libudev-zero/udev_list.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/deps/libudev-zero/udev_monitor.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/deps/libudev-zero/udev_device.c
#    )

#add_executable(system_info system_infoMain.cpp)
#add_executable(main main.cpp)
add_executable(win_smbios_uuid win_smbios_uuid.cpp)
#add_executable(libudev_test libudev_test.cpp)
#add_executable(from_sys from_sys.cpp)
#add_executable(libudev_test2 libudev_test2.cpp)
#add_executable(sd_service_test sd_service_test.cpp)


#target_link_libraries(system_info PRIVATE lfreist-hwinfo::hwinfo fmt::fmt)
#target_link_libraries(main PRIVATE lfreist-hwinfo::hwinfo fmt::fmt nlohmann_json::nlohmann_json)
#if (UNIX)
#	target_link_libraries(main PRIVATE systemd)
#endif()
#target_link_libraries(libudev_test PRIVATE libudev-zero)
#target_link_libraries(libudev_test2 udev)
#target_link_libraries(sd_service_test systemd)
#install(TARGETS system_info)


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

add_executable(system_info system_infoMain.cpp)
add_executable(custom_info system_info_in_struct.cpp)
target_link_libraries(system_info PRIVATE lfreist-hwinfo::hwinfo fmt::fmt)
target_link_libraries(custom_info PRIVATE lfreist-hwinfo::hwinfo fmt::fmt)


install(TARGETS system_info)

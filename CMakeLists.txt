
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

add_executable(system_info system_infoMain.cpp)
add_executable(custom_info system_info_in_struct.cpp)
target_link_libraries(system_info PRIVATE lfreist-hwinfo::hwinfo fmt::fmt)
target_link_libraries(custom_info PRIVATE lfreist-hwinfo::hwinfo fmt::fmt nlohmann_json::nlohmann_json)


install(TARGETS system_info)

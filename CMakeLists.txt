cmake_minimum_required(VERSION 3.13)
project(card_game)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig QUIET)
if (PKG_CONFIG_FOUND)
    pkg_check_modules(sodium_PKG QUIET libsodium)
endif ()

if (sodium_USE_STATIC_LIBS)
    if (sodium_PKG_STATIC_LIBRARIES)
        foreach (_libname ${sodium_PKG_STATIC_LIBRARIES})
            if (NOT _libname MATCHES "^lib.*\\.a$") # ignore strings already ending with .a
                list(INSERT sodium_PKG_STATIC_LIBRARIES 0 "lib${_libname}.a")
            endif ()
        endforeach ()
        list(REMOVE_DUPLICATES sodium_PKG_STATIC_LIBRARIES)
    else ()
        # if pkgconfig for libsodium doesn't provide
        # static lib info, then override PKG_STATIC here..
        set(sodium_PKG_STATIC_LIBRARIES libsodium.a)
    endif ()

    set(XPREFIX sodium_PKG_STATIC)
else ()
    if (sodium_PKG_LIBRARIES STREQUAL "")
        set(sodium_PKG_LIBRARIES sodium)
    endif ()

    set(XPREFIX sodium_PKG)
endif ()

find_path(sodium_INCLUDE_DIR sodium.h
        HINTS ${${XPREFIX}_INCLUDE_DIRS}
        )
find_library(sodium_LIBRARY_DEBUG NAMES ${${XPREFIX}_LIBRARIES}
        HINTS ${${XPREFIX}_LIBRARY_DIRS}
        )
find_library(sodium_LIBRARY_RELEASE NAMES ${${XPREFIX}_LIBRARIES}
        HINTS ${${XPREFIX}_LIBRARY_DIRS}
        )

find_package(Boost REQUIRED)

add_executable(card_game main.cpp classes/card.cpp classes/card.h toolbox/toolbox.cpp libraries/enums.h toolbox/toolbox.h classes/Player.cpp classes/Player.h)
target_link_libraries(card_game sodium)
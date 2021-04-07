project(sqlite-corrupt)
cmake_minimum_required(VERSION 3.16)

set(TARGET sqlite-corrupt)

find_package(PkgConfig)
find_package(Threads REQUIRED)

pkg_search_module(SQLITE REQUIRED sqlite3)

add_executable(${TARGET}
        sqlite-corrupt.cpp
        db/db.cpp
        db/dbholder.cpp
        db/keycache.cpp
        users/reader.cpp
        users/writer.cpp
        users/moderator.cpp
        users/cleaner.cpp
        fileutils.cpp
        )

set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED YES
        )

add_definitions(${SQLITE_CFLAGS_OTHER})
link_directories(${SQLITE_LIBRARY_DIRS})

target_link_libraries(${TARGET}
        PRIVATE
        ${SQLITE_LIBRARIES}
        Threads::Threads
        )

target_include_directories(${TARGET}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
        ${SQLITE_INCLUDE_DIRS}
        )

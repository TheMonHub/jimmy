#
# jimmy - A multipurpose Discord bot
# =========================================
#

cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
project(jimmy
        VERSION 0.1.0
        DESCRIPTION "A Discord bot that will conquer the world one day..."
        HOMEPAGE_URL "https://github.com/TheMonHub/jimmy"
        LANGUAGES C
)

set(CMAKE_C_STANDARD 17)

find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(jimmy
        src/main.c
        src/token.c
        src/token.h
        src/main.h
        src/command.c
        src/command.h
        src/commands/ping.c
        src/commands/ping.h
        src/commands/index.c
        src/commands/index.h
        src/database.c
        src/database.h
        src/commands/about.c
        src/commands/about.h
        src/colors.h
        src/images.h
)

target_link_libraries(jimmy PRIVATE
        discord
        CURL::libcurl
        SQLite::SQLite3
)

target_compile_definitions(jimmy PRIVATE PROJECT_VERSION="${CMAKE_PROJECT_VERSION}")
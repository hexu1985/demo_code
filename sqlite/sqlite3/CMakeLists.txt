# CMake file for compiling the sqlite3 static library under Windows (for ease of use)
#
# Copyright (c) 2012-2016 Sebastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT) 

# add sources of the "sqlite3" static library
add_definitions(-DSQLITE_HAS_CODEC)

add_library(sqlite3
 sqlite3.c
 sqlite3.h
)

add_library(sqlite-see
 sqlite-see.c
 sqlite3.h
)

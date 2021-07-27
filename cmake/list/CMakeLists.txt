cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(HELLO)

set(list1 a d c e b g f)
set(list2 a c b h)

message("list1: ${list1}")
message("list2: ${list2}")

set(list1_list2 ${list1})
list(REMOVE_ITEM list1_list2 ${list2})
message("list1-list2: ${list1_list2}")

set(list2_list1 ${list2})
list(REMOVE_ITEM list2_list1 ${list1})
message("list2-list1: ${list2_list1}")

set(union_list "")
list(APPEND union_list ${list1} ${list2})
list(REMOVE_DUPLICATES union_list)
message("union list of 1 and 2: ${union_list}")

set(intersection_list ${union_list})
list(REMOVE_ITEM intersection_list ${list1_list2} ${list2_list1})
message("intersection list of 1 and 2: ${intersection_list}")

set(EXE_NAME hello.exe)
set(SRC_LIST main.c)
add_executable(${EXE_NAME} ${SRC_LIST})

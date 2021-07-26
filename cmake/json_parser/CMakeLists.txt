cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(HELLO LANGUAGES C)

include(JSONParser.cmake)

file(STRINGS test.json jsonTest NEWLINE_CONSUME)
message("test.json: ${jsonTest}")

# name of variable not string itself is passed to macro sbeParseJson
sbeParseJson(example jsonTest)

# Now you can use parsed variables.
foreach(var ${example})
    message("${var} = ${${var}}")
endforeach()

# when you want to access concrete JSON object, use the names in JSON, the array indexes for JSON object MUST be given after '_'
# e.g if you want to store value of object 'id' of first element of array 'items' in object 'menu'
set(FirstItemId ${example.menu.items_0.id})

# e.g if you want to store 1-th element of array 'short' in object 'label' of 5-th element of array items in object menu 
set(ShortLabel ${example.menu.items_5.label.short_0})

# When you are done, clean parsed variables
sbeClearJson(example)

set(EXE_NAME hello.exe)
set(SRC_LIST main.c)
add_executable(${EXE_NAME} ${SRC_LIST})

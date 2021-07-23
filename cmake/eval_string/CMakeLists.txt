
# THE_VALUE should be "foo"

project(HELLO)

set(MY_SECRET_VAR "foo")

# later only the name of the variable is known.
set(THE_NAME "MY_SECRET_VAR")

# Now i'm looking for a way to get the value "foo" from the name
# something like:
set(THE_VALUE "${${THE_NAME}}")

message("THE_VALUE: ${THE_VALUE}")

set(SRC_LIST main.c)
add_executable(${EXE_NAME} ${SRC_LIST})

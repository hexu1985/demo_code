#!/bin/bash

function foo() {
    local b="b"
    echo "in foo, a=$a"
    echo "in foo, b=$b"
}

function main() {
    local a="a"
    echo "in main before foo, a=$a"
    echo "in main before foo, b=$b"

    foo

    echo "in main after foo, a=$a"
    echo "in main after foo, b=$b"
}

main

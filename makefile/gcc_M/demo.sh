#!/bin/sh

echo "#include <stdio.h>" > stdio.c
gcc -M stdio.c

#!/usr/bin/env bash
valgrind --tool=memcheck --leak-check=full ./main

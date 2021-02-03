#!/usr/bin/env bash
valgrind --tool=memcheck --leak-check=full ./get_screen_info

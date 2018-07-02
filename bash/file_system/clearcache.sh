#!/usr/bin/env bash
sync; echo 3 > /proc/sys/vm/drop_caches

# 1. Clear PageCache only.
# sync; echo 1 > /proc/sys/vm/drop_caches

# 2. Clear dentries and inodes.
# sync; echo 2 > /proc/sys/vm/drop_caches

# 3. Clear PageCache, dentries and inodes.
# sync; echo 3 > /proc/sys/vm/drop_caches

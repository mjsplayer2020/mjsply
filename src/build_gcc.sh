#!/bin/sh
# gcc -Wno-format-zero-length  -Wno-format-overflow main.c mjs.c client.c player.c -o mjs
# gcc -Wno-format-zero-length  main.c mjs.c client.c player.c -o mjs
gcc main.c mjs.c client.c player.c -o mjs

#!/bin/bash

set -e

shopt -s extglob
[ ! -d "build" ] && mkdir build

i686-elf-as src/boot/boot.s -o build/boot.o

object_files="build/boot.o"

for source_file in $(find src -type f -name "*.c"); do
    object_file="build/$(basename "${source_file%.*}").o"
    i686-elf-gcc -c "$source_file" -o "$object_file" -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I src/include
    object_files="$object_files $object_file"
done

i686-elf-gcc -T src/linker/linker.ld -o build/build.bin -ffreestanding -O2 -nostdlib $object_files -lgcc

rm -f build/*.o

qemu-system-i386 -kernel build/build.bin -m 256M

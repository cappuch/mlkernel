@echo off
REM "there is much more efficient ways of doing this - will do so in a later PR"
i686-elf-as src/boot.s -o build/boot.o
i686-elf-gcc -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/keyboard.c -o build/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/cpu_info.c -o build/cpu_info.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/vga.c -o build/vga.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -c src/string.c -o build/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T src/linker.ld -o build/build.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o build/cpu_info.o build/vga.o build/string.o build/keyboard.o -lgcc

del build\*.o

@echo on
REM "qemu because of the fact that it's the most lightweight for constant recompiling"
qemu-system-i386 -kernel build/build.bin -m 256M 
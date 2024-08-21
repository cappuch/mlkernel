@echo off
setlocal enabledelayedexpansion

if not exist build mkdir build

i686-elf-as src\boot\boot.s -o build\boot.o

set "object_files=build\boot.o"
for /r "src" %%F in (*.c) do (
    set "source_file=%%F"
    set "object_file=build\%%~nF.o"
    i686-elf-gcc -c "!source_file!" -o "!object_file!" -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I src\include
    set "object_files=!object_files! !object_file!"
)

i686-elf-gcc -T src\linker\linker.ld -o build\build.bin -ffreestanding -O2 -nostdlib %object_files% -lgcc

del build\*.o

qemu-system-i386 -kernel build\build.bin -m 256M

endlocal
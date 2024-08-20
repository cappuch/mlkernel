@echo off
setlocal enabledelayedexpansion

REM
set SRC_DIR=src
set BUILD_DIR=build

if not exist %BUILD_DIR% mkdir %BUILD_DIR%

REM assembly compilation
for %%f in (%SRC_DIR%\*.s) do ( 
    echo Compiling %%f
    i686-elf-as %%f -o %BUILD_DIR%\%%~nf.o
)

REM for c file compile
for %%f in (%SRC_DIR%\*.c) do (
    echo Compiling %%f
    i686-elf-gcc -c %%f -o %BUILD_DIR%\%%~nf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
)

set OBJ_FILES=
for %%f in (%BUILD_DIR%\*.o) do set OBJ_FILES=!OBJ_FILES! %%f

i686-elf-gcc -T %SRC_DIR%\linker.ld -o %BUILD_DIR%\build.bin -ffreestanding -O2 -nostdlib %OBJ_FILES% -lgcc
del %BUILD_DIR%\*.o

qemu-system-i386 -kernel %BUILD_DIR%\build.bin -m 256M

endlocal
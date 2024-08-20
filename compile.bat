@echo off
setlocal enabledelayedexpansion

set SRC_DIR=src
set BUILD_DIR=build
set OBJ_DIR=%BUILD_DIR%\compile

if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if not exist %OBJ_DIR% mkdir %OBJ_DIR%

set MODE=fast

if "%1"=="--fast" set MODE=fast
if "%1"=="--recompile" set MODE=recompile

if "%MODE%"=="fast" (
    goto :fastcompile
) else if "%MODE%"=="recompile" (
    goto :recompile1
) else (
    echo Wrong mode. Use --fast or --recompile.
    exit /b 1
)

qemu-system-i386 -kernel %BUILD_DIR%\build.bin -m 256M

exit /b 0

:fastcompile
for %%f in (%SRC_DIR%\*.s) do (
    if not exist %OBJ_DIR%\%%~nf.o (
        i686-elf-as %%f -o %OBJ_DIR%\%%~nf.o
    ) else (
        for %%a in (%%f) do (
            for %%b in (%OBJ_DIR%\%%~nf.o) do (
                if %%~ta gtr %%~tb (
                    i686-elf-as %%f -o %OBJ_DIR%\%%~nf.o
                )
            )
        )
    )
)

for %%f in (%SRC_DIR%\*.c) do (
    if not exist %OBJ_DIR%\%%~nf.o (
        i686-elf-gcc -c %%f -o %OBJ_DIR%\%%~nf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
    ) else (
        for %%a in (%%f) do (
            for %%b in (%OBJ_DIR%\%%~nf.o) do (
                if %%~ta gtr %%~tb (
                    i686-elf-gcc -c %%f -o %OBJ_DIR%\%%~nf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
                )
            )
        )
    )
)

set OBJ_FILES=
for %%f in (%OBJ_DIR%\*.o) do set OBJ_FILES=!OBJ_FILES! %%f

set LINK_NEEDED=0
if not exist %BUILD_DIR%\build.bin set LINK_NEEDED=1
for %%f in (%OBJ_DIR%\*.o) do (
    for %%b in (%BUILD_DIR%\build.bin) do (
        if %%~tf gtr %%~tb set LINK_NEEDED=1
    )
)

if %LINK_NEEDED%==1 (
    i686-elf-gcc -T %SRC_DIR%\linker.ld -o %BUILD_DIR%\build.bin -ffreestanding -O2 -nostdlib %OBJ_FILES% -lgcc
)
exit /b 0

:recompile1
for %%f in (%SRC_DIR%\*.s) do (
    i686-elf-as %%f -o %OBJ_DIR%\%%~nf.o
)

for %%f in (%SRC_DIR%\*.c) do (
    i686-elf-gcc -c %%f -o %OBJ_DIR%\%%~nf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
)

set OBJ_FILES=
for %%f in (%OBJ_DIR%\*.o) do set OBJ_FILES=!OBJ_FILES! %%f

i686-elf-gcc -T %SRC_DIR%\linker.ld -o %BUILD_DIR%\build.bin -ffreestanding -O2 -nostdlib %OBJ_FILES% -lgcc
exit /b 0
@echo off

:: Cleanup
rmdir /s /q bin
rmdir /s /q dist

:: Cleanup
mkdir bin
mkdir dist


SET GBDK_HOME=C:/gbdk

SET LCC_COMPILE_BASE=%GBDK_HOME%\bin\lcc -debug -Iheaders/main -Iheaders/gen -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG
SET LCC_COMPILE=%LCC_COMPILE_BASE% -c -o 

:: Required to concatenate the "COMPILE_OBJECT_FILES" via a for loop
SETLOCAL ENABLEDELAYEDEXPANSION

SET "COMPILE_OBJECT_FILES="

call generate-graphics.bat

:: loop for all files in the default source folder
FOR /R "source/gen/" %%X IN (*.c) DO (
    SET "COMPILE_OBJECT_FILES=%%X !COMPILE_OBJECT_FILES!"

)


:: loop for all files in the default source folder
FOR /R "source/main/" %%X IN (*.c) DO (
    SET "COMPILE_OBJECT_FILES=%%X !COMPILE_OBJECT_FILES!"

)


:: Compile a .gb file from the compiled .o files
%LCC_COMPILE_BASE% -Wm-yc -Wl-yo2 -Wl-yt3 -o dist/1942.gb !COMPILE_OBJECT_FILES!

endlocal

:: Use the romusage.exe to show the size of the ROM and what makes it up
"lib/romusage" dist\1942.noi -a
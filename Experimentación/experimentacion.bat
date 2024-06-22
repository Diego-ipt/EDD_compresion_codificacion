@echo off
setlocal enabledelayedexpansion

set "command=testHuffman.exe"
set "times=20"
set "outputFile=output.txt"
set "tempFile=temp_output.txt"

:: Borrar el archivo de salida si ya existe
if exist %outputFile% del %outputFile%

:: Ejecutar el programa n veces y guardar las salidas
for /L %%i in (1,1,%times%) do (
    echo Ejecución %%i: >> %outputFile%
    %command% > %tempFile%
    type %tempFile% >> %outputFile%
    echo. >> %outputFile%
)

:: Borrar el archivo temporal
if exist %tempFile% del %tempFile%

endlocal
@echo off
setlocal EnableDelayedExpansion

rem Archivo CSV para guardar los resultados
set outputFile=resultado_tiempos.csv
echo "Ejecución","Tiempo testHuffman (ms)","Tiempo testLz (ms)" > %outputFile%
set numEjecuciones=20

for /L %%i in (1,1,%numEjecuciones%) do (
    set startTime=!TIME!
    testHuffman.exe < entrada.txt > salida_testHuffman.txt
    set endTime=!TIME!
    call :getElapsedTime !startTime! !endTime! huffmanTime
    set startTime=!TIME!
    testLz.exe < entrada.txt > salida_testLz.txt
    set endTime=!TIME!
    call :getElapsedTime !startTime! !endTime! lzTime
    echo %%i,!huffmanTime!,!lzTime! >> %outputFile%
)

endlocal
exit /b

:getElapsedTime
setlocal
set start=%1
set end=%2
set /a startH=(1%start:~0,2% - 100) * 3600000 + (1%start:~3,2% - 100) * 60000 + (1%start:~6,2% - 100) * 1000 + (1%start:~9,2% - 100)
set /a endH=(1%end:~0,2% - 100) * 3600000 + (1%end:~3,2% - 100) * 60000 + (1%end:~6,2% - 100) * 1000 + (1%end:~9,2% - 100)
set /a elapsed=endH - startH
endlocal & set %3=%elapsed%
exit /b

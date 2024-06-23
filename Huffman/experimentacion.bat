@echo off
setlocal enabledelayedexpansion

REM Verificar si testLz.cpp existe en el directorio actual
if not exist "testHuffman.cpp" (
    echo Error: testHuffman.cpp no se encuentra en el directorio actual.
    exit /b 1
)

REM Compilar el archivo testLz.cpp
g++ -o testHuffman.exe testHuffman.cpp
if %errorlevel% neq 0 (
    echo Error: la compilación de testLz.cpp falló.
    exit /b 1
)

REM Crear o limpiar el archivo de log
> experiment_results_ID_open.log echo.

REM Imprimir el encabezado CSV en el archivo de salida final
echo Tamaño_MB,Codificación_Promedio_ms,Codificación_Desviación_Estándar_ms,Decodificacion_Promedio_ms, Decodificación_Desviación_Estándar_ms > huffman_experiments.csv


:: Lista de tamaños de entrada en MB
set "sizes=1 5 7 10 15 17 20"
set "archivo_a_leer=ADN.txt"
:: Ejecutar el programa para cada tamaño y guardar las salidas
for %%s in (%sizes%) do (
    echo %%s >> experiment_results_ID_open.log
    :: Ejecutar el programa y guardar salida en archivo temporal
    .\testHuffman.exe %%s %archivo_a_leer% >> experiment_results_ID_open.log
)
REM Redirigir la salida del log al archivo CSV final
type experiment_results_ID_open.log >> huffman_experiments.csv

:: Borrar el archivo temporal
if exist experiment_results_ID_open.log del experiment_results_ID_open.log

REM Eliminar los archivos .exe
del testHuffman.exe

endlocal

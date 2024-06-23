@echo off
setlocal enabledelayedexpansion

REM Verificar si testHuffman.cpp existe en el directorio actual
if not exist "testHuffman.cpp" (
    echo Error: testHuffman.cpp no se encuentra en el directorio actual.
    exit /b 1
)

REM Compilar el archivo testHuffman.cpp
g++ -o testHuffman.exe testHuffman.cpp
if %errorlevel% neq 0 (
    echo Error: la compilación de testHuffman.cpp falló.
    exit /b 1
)

REM Crear o limpiar el archivo de log
> experiment_results_ID_open.log echo.

REM Imprimir el encabezado CSV en el archivo de salida final
echo Nombre_archivo,Size_archivo,Size_codificado_Bytes,Codificacion_Promedio_ms,Codificacion_Desv_Estandar,Decodificacion_Promedio_ms,Decodificacion_Desv_Estandar > huffman_experiments.csv


:: Lista de tamaños de entrada en MB
set "sizes=1 5"
set "archivos=..\Textos\dna.txt ..\Textos\xml.txt ..\Textos\english.txt ..\Textos\pitches.txt ..\Textos\proteins.txt ..\Textos\sources.txt"

:: Ejecutar el programa para cada tamaño y guardar las salidas
for %%f in (%archivos%) do (
    for %%s in (%sizes%) do (
        :: Ejecutar el programa y guardar salida en archivo temporal
        echo Test file %%f with size %%s on Huffman
        .\testHuffman.exe %%s %%f >> experiment_results_ID_open.log
    )
)

REM Redirigir la salida del log al archivo CSV final
type experiment_results_ID_open.log >> huffman_experiments.csv

:: Borrar el archivo temporal
if exist experiment_results_ID_open.log del experiment_results_ID_open.log

REM Eliminar los archivos .exe
del testHuffman.exe

endlocal

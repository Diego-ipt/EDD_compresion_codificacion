@echo off
setlocal enabledelayedexpansion

REM Verificar si testLz.cpp existe en el directorio actual
if not exist "testLz.cpp" (
    echo Error: testLz.cpp no se encuentra en el directorio actual.
    exit /b 1
)

REM Compilar el archivo testLz.cpp
g++ -o testLz.exe testLz.cpp
if %errorlevel% neq 0 (
    echo Error: la compilación de testLz.cpp falló.
    exit /b 1
)

REM Crear o limpiar el archivo de log
> experiment_results_ID_open.log echo.

REM Imprimir el encabezado CSV en el archivo de salida final
echo Nombre_archivo,Size_archivo,Size_Comprimido_Bytes,Compresion_Promedio_ms,Compresion_Desv_Estandar,Descompresion_Promedio_ms,Descompresion_Desv_Estandar > lempel_ziv_experiments.csv


:: Lista de tamaños de entrada en MB
set "sizes=1 5"
set "archivos=..\Textos\dna.txt ..\Textos\xml.txt ..\Textos\english.txt ..\Textos\pitches.txt ..\Textos\proteins.txt ..\Textos\sources.txt"

:: Ejecutar el programa para cada tamaño y guardar las salidas
for %%f in (%archivos%) do (
    for %%s in (%sizes%) do (
        :: Ejecutar el programa y guardar salida en archivo temporal
        echo Test file %%f with size %%s on Lempel Ziv
        .\testLz.exe %%s %%f >> experiment_results_ID_open.log
    )
)

REM Redirigir la salida del log al archivo CSV final
type experiment_results_ID_open.log >> lempel_ziv_experiments.csv

:: Borrar el archivo temporal
if exist experiment_results_ID_open.log del experiment_results_ID_open.log

REM Eliminar los archivos .exe
del testLz.exe

endlocal

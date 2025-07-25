#!/bin/bash


# Variables de entorno             #
# -------------------------------- #
CC=gcc
CFLAGS_TEST="-g -Wall -O2"
CFLAGS_LIB="-Wall -O2 -fPIC -shared"

SRC_ARRAY=$1.c
SRC_TEST=test_$1.c

TEST_PROG=test_$1.elf
LIB_PROG=$1.so
# -------------------------------- #


# Lógica de uso                    #
# -------------------------------- #
if [ "$2" == "test" ]; then
    echo
    echo "[BUILD-ARRAY-TEST]: Compilando programa de prueba de array..."
    if $CC $CFLAGS_TEST $SRC_TEST $SRC_ARRAY -o $TEST_PROG; then
        echo "[BUILD-ARRAY-TEST]: Compilación completada."
        echo "[BUILD-ARRAY-TEST]: Ejecutando programa de prueba..."
        echo
        ./$TEST_PROG
        echo
        echo "[BUILD-ARRAY-TEST]: Ejecución de programa de prueba finalizado."
    else
        echo "[BUILD-ARRAY-TEST][ERR]: Error de compilación, ejecución abortada."
    fi
    echo

elif [ "$2" == "lib" ]; then
    echo
    echo "[BUILD-ARRAY-LIB]: Compilando la librería de array..."
    if $CC $CFLAGS_LIB $SRC_ARRAY -o $LIB_PROG; then
        mv $LIB_PROG ./lib
        echo "[BUILD-ARRAY-LIB]: Librearía compilada."
    else
        echo "[BUILD-ARRAY-LIB][ERR]: Error de compilación, librería no generada."
    fi
    echo

elif [ "$2" == "clean" ]; then
    echo
    echo "[BUILD-ARRAY-CLEAN]: Limpiando espacio de trabajo..."
    rm -f ./$TEST_PROG ./lib/$LIB_PROG
    echo "[BUILD-ARRAY-CLEAN]: Espacio de trabajo limpio."
    echo

else
    echo
    echo "[BUILD-ARRAY][ERR]: Uso incorrecto u opciones inválidas."
    echo -e "\n\t[Uso]:"
    echo -e "\t\t-> ./build.sh <tipo> test: \tCompila y ejecuta el programa de test (.elf)"
    echo -e "\t\t-> ./build.sh <tipo> lib: \tCompila y genera la librería compartida (.so) bajo la carpeta lib/"
    echo -e "\t\t-> ./build.sh <tipo> clean: \tLimpia el espacio de trabajo eliminando archivos generados"
    echo -e "\n\n\t<tipo>:"
    echo -e "\t\tsllist: \tEjecuta el script para el tipo de lista 'single linked lists'"
    echo
    exit 1
fi
# -------------------------------- #
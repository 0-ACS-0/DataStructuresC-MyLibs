#!/bin/bash


# Variables de entorno             #
# -------------------------------- #
CC=gcc
CFLAGS_TEST="-g -Wall -O2"
CFLAGS_LIB="-Wall -O2 -fPIC -shared"

SRC_STACK=stack.c
SRC_TEST=test_stack.c

TEST_PROG=test_stack.elf
LIB_PROG=stack.so
# -------------------------------- #


# Lógica de uso                    #
# -------------------------------- #
if [ "$1" == "test" ]; then
    echo
    echo "[BUILD-STACK-TEST]: Compilando programa de prueba de stack..."
    if $CC $CFLAGS_TEST $SRC_TEST $SRC_STACK -o $TEST_PROG; then
        echo "[BUILD-STACK-TEST]: Compilación completada."
        echo "[BUILD-STACK-TEST]: Ejecutando programa de prueba..."
        echo
        ./$TEST_PROG
        echo
        echo "[BUILD-STACK-TEST]: Ejecución de programa de prueba finalizado."
    else
        echo "[BUILD-STACK-TEST][ERR]: Error de compilación, ejecución abortada."
    fi
    echo

elif [ "$1" == "lib" ]; then
    echo
    echo "[BUILD-STACK-LIB]: Compilando la librería de stack..."
    if $CC $CFLAGS_LIB $SRC_STACK -o $LIB_PROG; then
        mv $LIB_PROG ./lib
        echo "[BUILD-STACK-LIB]: Librearía compilada."
    else
        echo "[BUILD-STACK-LIB][ERR]: Error de compilación, librería no generada."
    fi
    echo

elif [ "$1" == "clean" ]; then
    echo
    echo "[BUILD-STACK-CLEAN]: Limpiando espacio de trabajo..."
    rm -f ./$TEST_PROG ./lib/$LIB_PROG
    echo "[BUILD-STACK-CLEAN]: Espacio de trabajo limpio."
    echo

else
    echo
    echo "[BUILD-STACK][ERR]: Uso incorrecto u opciones inválidas."
    echo -e "\n\t[Uso]:"
    echo -e "\t\t-> ./build.sh test: \tCompila y ejecuta el programa de test (.elf)"
    echo -e "\t\t-> ./build.sh lib: \tCompila y genera la librería compartida (.so) bajo la carpeta lib/"
    echo -e "\t\t-> ./build.sh clean: \tLimpia el espacio de trabajo eliminando archivos generados"
    echo
    exit 1
fi
# -------------------------------- #
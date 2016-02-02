#!/bin/bash

if [ -z "$DIR_HERRAMIENTAS_PROYECTO" ]; then
    echo "Es necesario setear DIR_HERRAMIENTAS_PROYECTO a la raiz de las herramientas del proyecto con export DIR_HERRAMIENTAS_PROYECTO=valor"
    exit 1
fi

if [ -z "$DIR_LIBDAN2" ]; then
    echo "Es necesario setear DIR_LIBDAN2 a la raiz de libdans2l con export DIR_LIBDAN2=valor"
    exit 1
fi

g++ extractor_test.cpp -o extractor_test.out $DIR_HERRAMIENTAS_PROYECTO/objects/dnot_token.o $DIR_HERRAMIENTAS_PROYECTO/objects/dnot_parser.o  -I $DIR_HERRAMIENTAS_PROYECTO -I $DIR_LIBDAN2 -Wall -pedantic -std=c++11 -L$DIR_LIBDAN2 -lDanSDL2

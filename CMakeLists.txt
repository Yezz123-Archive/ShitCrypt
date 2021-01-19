cmake_minimum_required(VERSION 3.17)
project(ShitCrypt)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ShitCrypt
        ShitCrypt.py
        encrypt.c include/gpg-error.h include/gcrypt.h include/gcrypt-module.h
        keygen.c include/gpg-error.h include/gcrypt.h include/gcrypt-module.h)

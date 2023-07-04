cmake_minimum_required(VERSION 3.25)
project(Asm2Hack C)

set(CMAKE_C_STANDARD 23)

add_executable(HackAssembler main.c src/common.h src/parser.c src/parser.h src/openfile.c src/openfile.h src/TranslateIntoBinary.c src/TranslateIntoBinary.h)

cmake_minimum_required(VERSION 3.12)
project(Aleskin_IU4_22B_BIG_DZ C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(Aleskin_IU4_22B_BIG_DZ
        src/main.c
        src/user.c
        src/book/book.c
        src/student/student.c
        src/loan/loan.c)
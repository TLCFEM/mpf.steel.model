project(MPF C Fortran)

add_executable(MPFC MAIN.c MPF.c STEELBRB.c)
add_executable(MPFF MAIN.FOR MPF.FOR)
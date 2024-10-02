cmake_minimum_required(VERSION 3.5)

project(manual_tests VERSION 0.1)

add_executable(tests
    main.c
        retrieve_data.c
        retrieve_data.h
)

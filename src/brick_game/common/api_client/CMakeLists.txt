# This file is for tests purposes

cmake_minimum_required(VERSION 3.5)

project(manual_tests VERSION 0.1)

add_executable(tests
    main.c
        api_client.c
        api_client.h
)

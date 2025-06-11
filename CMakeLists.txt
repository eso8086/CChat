cmake_minimum_required(VERSION 3.31)
project(Chat C)

set(CMAKE_C_STANDARD 11)

add_executable(Server server.c)
add_executable(Client client.c)

cmake_minimum_required(VERSION 3.25)
project(load_balancer C)

set(CMAKE_C_STANDARD 99)

add_executable(load_balancer src/User.c headers/InstanceHost.h headers/LoadBalancer.h src/InstanceHost.c src/InstanceHost.c src/LoadBalancer.c)

cmake_minimum_required(VERSION 3.25)
project(load_balancer C)

set(CMAKE_C_STANDARD 99)

add_executable(load_balancer User.c HakobyanInstanceHost.h HakobyanLoadBalancer.h HakobyanInstanceHost.c HakobyanInstanceHost.c HakobyanLoadBalancer.c)

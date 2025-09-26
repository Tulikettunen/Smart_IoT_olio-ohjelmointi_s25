cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled
#main.cpp
        "Lab 1/Lab 1-Task 1-simple c++ program.cpp"
        "Lab 2/Lab 2-Task 1-String streams.cpp"
        "Lab 2/Lab 2-Task 2-File system.cpp"
        "Lab 1/Lab 1-Task 2-using reference parameter.cpp"
        "Lab 3/Lab 3-Task 1-Using std map and std pair.cpp"
        "Lab 3/Lab 3-Task 2-Composition.cpp"
        "Lab 4/Lab 4-Operator overloading.cpp"
        "Lab 4/Testi ja esimerkki koodipätkiä.cpp"
        testing/TEstailua.cpp
        "Lab 6/Lab 6-Smart pointers.cpp"
)
target_include_directories(${PROJECT_NAME} PRIVATE
 #"C:\\Users\\tuuli\\CLionProjects\\Own_headers"
        "C:/Users/tuuli/CLionProjects/Own_headers"
)

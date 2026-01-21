

cmake_minimum_required(VERSION 4.0.2)    #minimum cmake version
project(btechFieldComputer)

set(CMAKE_CXX_STANDARD 23)      #use c++23
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(btech_computer main.cpp mech.cpp die.cpp data.cpp sqlite3.o)  #build an executable from my program files


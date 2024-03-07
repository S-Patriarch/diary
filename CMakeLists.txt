# 
# (c) 2024 S-Patriarch
# 

cmake_minimum_required(VERSION 3.25)

project(diary)

set(CMAKE_BUILD_TYPE Release)

set(SOURCES
   main.cc
   src/diary.cc
   src/other.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
   ${PROJECT_NAME} PRIVATE
#   -lz
#   -lm
#   -ldl
   -lssl
   -lcrypto
)

set_target_properties(
   ${PROJECT_NAME} PROPERTIES
   CXX_STANDARD 17
   CXX_STANDARD_REQUIRED ON
)


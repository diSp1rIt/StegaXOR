project(StegaXOR)

set (SOURCES libs/stegaxor.cpp libs/argparser.cpp libs/keygen.cpp)
add_executable(main main.cpp ${SOURCES})
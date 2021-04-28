CC=g++
LIBS=libs/stegaxor.cpp libs/keygen.cpp
EXECUTABLE=crypt

default:
	$(CC) main.cpp $(LIBS) -o $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) main.cpp $(LIBS) -o $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE) "test message"
	hexdump output

clear:
	rm -rf output
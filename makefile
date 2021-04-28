CC=g++
LIBS=libs/stegaxor.cpp
EXECUTABLE=crypt

default:
	$(CC) main.cpp $(LIBS) -o $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) main.cpp $(LIBS) -o $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE) "test message"
	clear
	hexdump output

clear:
	rm -rf output
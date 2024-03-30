CC = g++
# compiler flags:
#  -g      - this flag adds debugging information to the executable file
#  -Wall   - this flag is used to turn on most compiler warnings
#  -Wextra - this flag is used to turn on even more compiler warnings
CFLAGS  = -g -Wall -Wextra
TARGET = fixing
EXT = cxx

all: $(TARGET)

$(TARGET): $(TARGET).$(EXT)
	$(CC) $(CFLAGS) -o $(TARGET) ./$(TARGET).$(EXT)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)

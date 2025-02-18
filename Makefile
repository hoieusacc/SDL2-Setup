TARGET = main.exe

all:
	g++ -Isrc/Include -Lsrc/lib -o $(TARGET) main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	$(TARGET) run

run $(TARGET):
	.\$(TARGET)

clean:
	rm -f $(TARGET)
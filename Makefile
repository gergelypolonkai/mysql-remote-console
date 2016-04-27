CFLAGS = -O2 -Wall `pkg-config --cflags --libs gtk+-2.0`
EXE = mysql_console

all:
	$(CC) -o $(EXE) $(CFLAGS) main.c

debug:
	$(CC) -DDEBUG -o $(EXE) $(CFLAGS) -g main.c

clean:
	rm -f $(EXE)

.PHONY: clean all debug


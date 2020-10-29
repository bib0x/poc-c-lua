BIN     =   cfunctions.so
SRCS	=   cfunctions.c
LIBS	=   lua5.1
INCS	=   /usr/include/$(LIBS)

all:
	gcc -shared $(SRCS) -I $(INCS) -l $(LIBS) -o $(BIN)

clean:
	rm -vf $(BIN)

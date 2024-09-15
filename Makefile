CC = gcc
CFLAGS = -Wall -Wextra -g -L/usr/lib64/mysql/ -lmysqlclient -lncursesw -lform -lmenu -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = bin/expenses

all: src/expenses.c lib/libdb_functions.so lib/libwindows.so lib/libutils.so
	$(CC) -Wall -Wextra -g -L./lib/ -L/usr/lib64/mysql/ -lmysqlclient \
	-lncursesw -ldb_functions -lform -lmenu -lwindows -lutils -Iinclude \
	 ./src/expenses.c -o ./bin/expenses




./lib/libdb_functions.so: ./src/db_functions.c
	$(CC) -g -fPIC -shared  ./src/db_functions.c -o ./lib/libdb_functions.so -Iinclude

./lib/libwindows.so: ./src/windows.c
	$(CC) -g -fPIC -shared  ./src/windows.c -o ./lib/libwindows.so -Iinclude

./lib/libutils.so: ./src/utils.c
	$(CC) -g -fPIC -shared  ./src/utils.c -o ./lib/libutils.so -Iinclude	

clean:
	rm -f bin/expenses lib/libdb_functions.so lib/libwindows.so lib/libutils.so

run:
	export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH;export DB_SERVER=192.168.1.110;export DBUSER=anar;export PASSWORD=password;bin/expenses
	
	
	
	
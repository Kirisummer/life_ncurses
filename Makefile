all:
	$(CC) life.c -c -fPIE -oliblife.a
	$(CC) intf.c -c -fPIE -olibintf.a
	$(CC) main.c -L. -llife -lintf -lncurses -omain
clean:
	$(RM) *.a main

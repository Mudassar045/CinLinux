#this is a comment
myexe : prog1.o driver.o prog2.o  prog3.o prog4.o
	gcc  *.o -o myexe
prog1.o: prog1.c
	gcc -c prog1.c
prog2.o: prog2.c
	gcc -c prog2.c
prog3.o: prog3.c
	gcc -c prog3.c
prog4.o: prog4.c
	gcc -c prog4.c
driver.o: driver.c myfuncs.h
	gcc -c -I ./  driver.c
clean:
	rm -f *.o
install: myexe
	@cp myexe /usr/bin
	@chmod a+x /usr/bin/myexe
	@chmod og-w /usr/bin/myexe
	@echo "myexe successfully installed in /usr/bin"
uninstall:
	@rm -f /usr/bin/myexe
	@echo "myexe successfully un-installed from /usr/bin"

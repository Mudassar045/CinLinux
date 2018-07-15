mdserver: temp-server.o 
	gcc -o mdserver temp-server.o 
temp-server.o: temp-server.c
	gcc -c temp-server.c 
clean:
	rm -f *.o
	rm -f ./src/*.o
install: mdrm
	@cp mdrm /usr/bin
	@chmod a+x /usr/bin/mdrm
	@chmod og-w /usr/bin/mdrm
	@echo "mdrm installed successfully in /usr/bin"
uninstall:
	@rm -f /usr/bin/mdrm
	@echo "mdrm successfully un-installed from /usr/bin"

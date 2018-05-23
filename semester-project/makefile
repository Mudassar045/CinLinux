mdrm: driver.o ./src/getDir.o ./src/getFile.o ./src/getFileType.o ./src/moveDir.o ./src/moveFile.o ./src/removeFile.o ./src/removeDir.o
	gcc -o mdrm driver.o ./src/getDir.o ./src/getFile.o ./src/getFileType.o ./src/moveDir.o ./src/moveFile.o ./src/removeFile.o ./src/removeDir.o
driver.o: driver.c ./include/rmutils.h ./include/urmutils.h
	gcc -c driver.c -I ./include
include: ./src/makefile
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

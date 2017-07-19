install:
	@echo Compiling the program source code. Please wait
	@gcc fntreconstructor.c -g0 -O0 -o fntreconstructor
	@echo Compilation successfuly complete
	@chmod ugo+rx fntreconstructor
	@echo Enter you user password for do last installation step
	@sudo cp -f -p fntreconstructor /bin/
	@echo Installation complete
uninstall:
	@echo Enter you user password for uninstall this software
	@sudo rm -f /bin/fntreconstructor
	@echo Uninstallation complete
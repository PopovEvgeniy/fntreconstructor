install:
	@echo Installation in progress. Please wait
	@gcc fntreconstructor.c -g0 -O0 -o fntreconstructor
	@chmod ugo+rx fntreconstructor
	@cp -f -p fntreconstructor /bin/
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/fntreconstructor
	@echo Uninstallation was successfuly complete
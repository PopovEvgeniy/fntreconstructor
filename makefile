install:
	@echo Installation in progress. Please wait
	@$(CC) fntreconstructor.c -g0 -O0 -o /bin/fntreconstructor
	@chmod ugo+rx /bin/fntreconstructor
	@echo Installation was successfully completed
uninstall:
	@rm /bin/fntreconstructor
	@echo Uninstallation was successfully completed
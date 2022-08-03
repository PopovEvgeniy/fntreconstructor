install:
	@echo Installation in progress. Please wait
	@gcc fntreconstructor.c -g0 -O0 -o /bin/fntreconstructor
	@chmod ugo+rx /bin/fntreconstructor
	@echo Installation successfully complete
uninstall:
	@rm -f /bin/fntreconstructor
	@echo Uninstallation successfully complete
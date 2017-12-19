make: clean scrambler
	@echo 'Finished'

scrambler:
	@echo 'compiling main.c ...'
	@gcc ./src/main.c -o scrambler
	@echo 'done'
clean:
	@-rm scrambler
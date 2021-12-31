CC= gcc
test: ccitt16
	./ccitt16
ccitt16: ccitt16.c
	$(CC) $< -o $@

clean:
	rm -rf ccitt16

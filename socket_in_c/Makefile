PID := $(shell lsof -i :12345 | awk '$$1 == "COMMAND" {next} {print $$2}')

build:
	gcc server.c -o server
	gcc client.c -o client

server:
	./server

client:
	./client

kill:
	kill $(PID)

clean:
	@rm server client
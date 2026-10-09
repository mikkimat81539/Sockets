server:
	g++ server.cpp -o server

client:
	g++ client.cpp -o client

clean:
	rm -f client

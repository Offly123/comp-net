all:
	g++ ./clients/client.cpp -o ./clients/1/client.out
	g++ ./clients/client.cpp -o ./clients/2/client.out
	g++ ./server/server.cpp -o ./server/server.out

client1:
	gnome-terminal --working-directory=/home/offly/Desktop/comp-net/3/clients/1 -t Client1 -- ./client.out

client2:
	gnome-terminal --working-directory=/home/offly/Desktop/comp-net/3/clients/2 -t Client2 -- ./client.out

server1:
	gnome-terminal --working-directory=/home/offly/Desktop/comp-net/3/server -t Server  -- ./server.out
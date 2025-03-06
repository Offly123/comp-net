<<<<<<< HEAD
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
=======
$(N):
	rm -rf $(N)
	g++ $(N).cpp -o $(N).out
	./$(N).out

clean:
	rm -rf *.out
>>>>>>> b55097313007647372b4d940fffd45dcdb7278c7

all:
	gcc Part2_p1_socket.c -o p1Socket 
	gcc Part2_p2_socket.c -o p2Socket 
	gcc Part2_p1_fifo.c -o p1fifo
	gcc Part2_p2_fifo.c -o p2fifo
	gcc Part2_p1_sharedMemory.c -o p1sharedMemory
	gcc Part2_p2_sharedMemory.c -o p2sharedMemory

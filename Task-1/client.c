#include "client.h"
#include <ctype.h>
int main()
{
// initialize server and client FIFO
int server_fifo_fd, client_fifo_fd;
// struct create to get client pid and BufferSize from client.h
struct data_to_pass_st my_data;

int times_to_send;
// client FIFO string size
char client_fifo[256];
// create server FIFO name and set Write only
server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
// If Server FIFO equals to -1 
if (server_fifo_fd == -1) 
{
fprintf(stderr, "Sorry, no server\n");
exit(EXIT_FAILURE);
}
// Getting Client Process ID 
my_data.client_pid = getpid();
// Concatenate the Client FIFO Name with Client Process ID
sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
// Make client Pipe and set to read only in condition
if (mkfifo(client_fifo, 0777) == -1) 
{
fprintf(stderr, "Sorry, can’t make %s\n", client_fifo);
exit(EXIT_FAILURE);
}

// Client sents data to server 5 times 
for (times_to_send = 0; times_to_send < 5; times_to_send++) 
{
// Client Data and Client ID in my_data
sprintf(my_data.some_data, "GetOSMessage from %d", my_data.client_pid); 
printf("%d sent By: %s, ", my_data.client_pid, my_data.some_data);
write(server_fifo_fd, &my_data, sizeof(my_data));
// Client FIFO open and sets Read only
client_fifo_fd = open(client_fifo, O_RDONLY);
// If Client FIFO value != -1
if (client_fifo_fd != -1) 
{
// Read message from server pipe and sent to client 
if (read(client_fifo_fd, &my_data, sizeof(my_data)) > 0)
{
printf("received By: %s\n", my_data.some_data);
}
// Close client FIFO
close(client_fifo_fd);
}
}
// Close Server FIFO
close(server_fifo_fd);
// Unlink Client FIFO from System File
unlink(client_fifo);
exit(EXIT_SUCCESS);
}


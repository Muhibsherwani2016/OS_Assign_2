#include "client.h"
#include <ctype.h>
int main()
{
// initialize server and client FIFO
int server_fifo_fd, client_fifo_fd;

// struct create to get client pid and BufferSize from client.h
struct data_to_pass_st my_data;

int read_res;
// client FIFO string size
char client_fifo[256]; 
// temporary var use for data save
char *tmp_char_ptr;
// create server FIFO name and set read only
mkfifo(SERVER_FIFO_NAME, 0777); 
// open server FIFO and set Read Only
server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY);
if (server_fifo_fd == -1) 
{
fprintf(stderr, "Server fifo failure\n");
exit(EXIT_FAILURE);
}
sleep(10); /* lets clients queue for demo purposes */
do {
read_res = read(server_fifo_fd, &my_data, sizeof(my_data));
if (read_res > 0) 
{
// Getting Data from server FIFO to client FIFO
tmp_char_ptr = my_data.some_data;
while (*tmp_char_ptr) 
{
// changing message LowerCase to UpperCase
*tmp_char_ptr = toupper(*tmp_char_ptr);
tmp_char_ptr++;
}
// Concatenate the Client FIFO Name with Client Process ID
sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
// Open Client FIFO and set Write only
client_fifo_fd = open(client_fifo, O_WRONLY);
// check FIFO value != -1 then write data and close it
if (client_fifo_fd != -1) 
{
write(client_fifo_fd, &my_data, sizeof(my_data));
close(client_fifo_fd);
}
}
}
// prints all output results and then Shutdown the server FIFO
while (read_res > 0) ;
close(server_fifo_fd);
// Remove Server FIFO from File System
unlink(SERVER_FIFO_NAME);
exit(EXIT_SUCCESS);
}



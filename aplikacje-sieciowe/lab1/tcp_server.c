/* A TCP server */
#include <arpa/inet.h>
#include <bits/types/struct_timeval.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>

int main(int argc, char ** argv, char ** env)
{
  // Create a socket
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == socket_fd) {
    printf("Could not create a socket\n");
    return -1;
  }

  // Prepare the sockaddr_in structure
  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(8888);

  // Bind the socket
  if (0 > bind(socket_fd, (struct sockaddr*)&server, sizeof server)) {
    printf("Bind failed\n");
    close(socket_fd);
    return -1;
  }

  // Start listening
  int backlog = 3; // max queue size
  if (listen(socket_fd, backlog)) {
    printf("Listening failed\n");
    close(socket_fd);
    return -1;
  }

  // Start accpeting incomming connections
  printf("Listening...\n");

  // Select, i.e., wait for the socet to be ready for an I/O operation
  int retval;
  fd_set rfds;
  struct timeval tv;

  // Watch socket_fd to see when it could be read from
  FD_ZERO(&rfds);
  FD_SET(socket_fd, &rfds);

  // Wait up to 30 seconds
  tv.tv_sec = 30;
  tv.tv_usec = 0;

  retval = select(socket_fd+1, &rfds, NULL, NULL, &tv);

  if (retval == -1) {
    printf("error select()\n");
  }
  else if (retval) {
    printf("Data is available now.\n");
    // Handle I/O
    int c = sizeof(struct sockaddr_in);
    struct sockaddr_in client;
    int new_socket = accept(socket_fd, (struct sockaddr*)&client, (socklen_t*)&c);
    if (0 > new_socket) {
      printf("Accept failed\n");
    }
    else {
      printf("Connection accepted\n");
      // Reply to the client
      char *client_ip = inet_ntoa(client.sin_addr);
      int client_port = ntohs(client.sin_port);
      const char *message = "Hello client\n";
      write(new_socket, message, strlen(message));
    }
  }
  else {
    printf("No data within 30 seconds.\n");
  }

  close(socket_fd);

  return 0;
}

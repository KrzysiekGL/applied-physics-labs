/* A TCP client which connects to a given ipv4 address */
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char ** argv, char ** env)
{
  // Check if an ipv4 address was given (don't assert that it's really an ipv4)
  if (argc < 2) {
    printf("Usage: %s ipv4_address [port]\n", argv[0]);
    return 0;
  }

  // Create a new socket; ipv4, tcp, protocol: ip
  int in_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == in_socket_fd) {
    printf("Could not create a socket\n");
    return -1;
  }

  // Server
  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  server.sin_family = AF_INET;
  int port;
  if (argc > 2)
    port = atoi(argv[2]);
  else
    port = 80;
  server.sin_port = htons(port);

  // Connect to a remote server
  if (-1 == connect(in_socket_fd, (struct sockaddr*)&server, sizeof server)) {
    printf("Connection error\n");
  }
  else {
    printf("Connection success\n");
    // Send a message
    const char *message = "GET / HTTP/1.1\r\n\r\n";
    if (-1 == send(in_socket_fd, message, strlen(message), 0)) {
      printf("Send failed\n");
    }
    else {
      printf("Data send\n");
      // Try to get a reply
      char reply[2048];
      if (-1 == recv(in_socket_fd, reply, sizeof reply, 0)) {
	printf("Recieve failed\n");
      }
      else {
	printf("Recieved reply:\n%s\n", reply);
      }
    }
  }

  // Close the socket
  close(in_socket_fd);

  return 0;
}

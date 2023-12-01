#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

const char * uart0_filename = "/dev/ttyUSB0";

int main(int argc, char ** argv, char ** env) {
  char uart_filename[256];
  if (argc > 1)
    strcpy(uart_filename, argv[1]);
  else
    strcpy(uart_filename, uart0_filename);

  printf("Using ttyUSB dev %s\n", uart_filename);

  int uart0_fd = open(uart_filename, O_RDWR);
  if (uart0_fd < 0) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  struct termios tty;
  if (tcgetattr(uart0_fd, &tty)) {
    perror("tcgetattr");
    exit(EXIT_FAILURE);
  }

  // Control modes
  tty.c_cflag &= ~PARENB; // disable parity
  tty.c_cflag &= ~CSTOP; // clear stop, one stop bit used in communication
  tty.c_cflag &= ~CSIZE; // clear all the size bit (bits transmitted per byte) and set anew
  tty.c_cflag |= CS8; // set anew to 8 bits per byte
  tty.c_cflag |= CRTSCTS; // set RTS/CTS hardware control flow ***
  tty.c_cflag |= CREAD | CLOCAL; // tunr on READ & ignore ctrl lines

  // Local modes
  tty.c_lflag &= ~ICANON; // disable cannonical communication (set non-cannoical mode)
  tty.c_lflag &= ~ECHO; // disable echo
  tty.c_lflag &= ~ECHOE; // disable erasure
  tty.c_lflag &= ~ECHONL; // disable new-line echo
  tty.c_lflag &= ~ISIG; // disable interpretation of INTR, QUIT and SUSP

  // Input modes
  tty.c_iflag |= IXON | IXOFF | IXANY; // Turn on s/w flow ctrl ***
  tty.c_iflag &= // Disable any special handling of received bytes
    ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

  // Output modes
  tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
  tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

  // VIMN and VTIME
  tty.c_cc[VTIME] = 10; // Wait for up to 1s, returning as soon as any data is received.
  tty.c_cc[VMIN] = 0;

  // Baud rate
  // Set in/out baud rate to be 9600
  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);

  if (tcsetattr(uart0_fd, TCSANOW, &tty) != 0) {
    perror("tcsetattr");
    exit(EXIT_FAILURE);
  }

  printf("1 to write, else to read\n");
  int ch = getchar();

  switch (ch) {
  case 1: // write
    const char * msg = "Hello";
    write(uart0_fd, msg, strlen(msg));
    break;
  default: // read
    char buf[256];
    read(uart0_fd, &buf, sizeof buf);
    break;
  }

  close(uart0_fd);
  return 0;
}

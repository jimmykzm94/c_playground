#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int main(int argc, char *argv[])
{
    // Check argument
    if (argc < 2)
    {
        printf("No serial port found\n");
        return 1;
    }

    int serial_port;
    char buffer[256];

    // Open serial port
    serial_port = open(argv[1], O_RDONLY);
    if (serial_port < 0)
    {
        perror("Failed to open serial port");
        return 1;
    }

    // Configure serial port
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(serial_port, &tty) != 0)
    {
        perror("Error from tcgetattr");
        close(serial_port);
        return 1;
    }

    // Set baud rate
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    // Set other serial port parameters
    tty.c_cflag &= ~PARENB;        // No parity
    tty.c_cflag &= ~CSTOPB;        // 1 stop bit
    tty.c_cflag &= ~CSIZE;         // Clear data size bits
    tty.c_cflag |= CS8;            // 8 bits per byte
    tty.c_cflag &= ~CRTSCTS;       // Disable hardware flow control
    tty.c_cflag |= CREAD | CLOCAL; // Turn on receiver and ignore control lines

    // Set input mode (non-canonical, no echo)
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // Set minimum characters to read
    tty.c_cc[VMIN] = 1;

    // Set timeout (0.1 seconds)
    tty.c_cc[VTIME] = 1;

    // Apply settings
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        perror("Error from tcsetattr");
        close(serial_port);
        return 1;
    }

    // Read from serial port
    int buffer_index;
    char recv;
    while (1)
    {
        memset(&recv, 0, sizeof(recv));
        int num_bytes = read(serial_port, &recv, 1);
        if (num_bytes < 0)
        {
            perror("Error reading from serial port");
            close(serial_port);
            return 1;
        }
        else if (num_bytes > 0)
        {
            if (recv == '\n')
            {
                buffer[buffer_index] = '\0';
                printf("Received: %s\n", buffer);
                buffer_index = 0;

                // If done message, break
                if (strncmp(buffer, "Done", 4) == 0)
                {
                    break;
                }
            }
            else
            {
                buffer[buffer_index++] = recv;
            }
        }
    }

    // Close serial port
    close(serial_port);
    return 0;
}

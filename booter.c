#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define COLOR_CYAN "\033[36m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_MAGENTA "\033[31m"

const int IMPOSSIBLE_CONNECTION = -1;

int main() {
    char address[50];
    int port;

    printf(COLOR_CYAN);
    printf("Enter IP Address: ");
    printf(COLOR_MAGENTA);
    scanf("%s", &address);

    printf(COLOR_CYAN);
    printf("Enter IP Port: ");
    printf(COLOR_MAGENTA);
    scanf("%d", &port);

    int epicsocket = socket(AF_INET, SOCK_STREAM, 0); //socket creation

    struct sockaddr_in connection;
    connection.sin_family = AF_INET; //Internet Protocol IPV4
    connection.sin_addr.s_addr = inet_addr(address);
    connection.sin_port = htons(port);

    int status = connect(epicsocket, (struct sockaddr*) &connection, sizeof(connection));

    if (status == IMPOSSIBLE_CONNECTION) {
        printf(COLOR_RED);
        printf("Impossible to connect.\n");
    } else {
        char packets[] = "GET / HTTP/1.1\r\n\r\n";

        printf(COLOR_GREEN);
        printf("Connected to ");
        printf(address);
        printf("\n");

        int x;

	while (status != IMPOSSIBLE_CONNECTION) {
            send(epicsocket, packets, sizeof(packets), 0);
            printf(COLOR_GREEN);
            printf("Packet sent!\n");
	}

        if (status == IMPOSSIBLE_CONNECTION) {
            printf(COLOR_RED);
            printf("Host is down.\n");
        }
    }
    return 0;
}

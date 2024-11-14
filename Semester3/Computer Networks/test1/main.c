#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <stdint.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;
    int c;
    struct sockaddr_in server;
    uint16_t n, x;
    char result[256];

    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c == INVALID_SOCKET) {
        perror("Error creating client socket");
        WSACleanup();
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr("172.30.247.53");

    if(connect(c, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Error connecting to the server");
        closesocket(c);
        WSACleanup();
        return 1;
    }
//    for(int i = 0; i < 3; i++) {
        printf("\n");
        memset(result, 0, sizeof(result));
        recv(c, (char *) result, sizeof(result), 0);
        printf("Recived word %s \n", result);
        while (1) {
            printf("\nInput a word: ");
            char s[256];
//            memset(s, 0, sizeof(s));
            fgets(s, sizeof(s), stdin);
            s[strcspn(s, "\n")] = 0;
            send(c, s, strlen(s), 0);


            char res[256];
            memset(res, 0, sizeof(res));
            if (recv(c, (char *) res, sizeof(res), 0) > 0) {
                printf("%s\n", res);
                if (strcmp(res, "You are right! Bonus points!\n") == 0) {
                    char points[256];
                    memset(points, 0, sizeof(points));
                    recv(c, (char *) points, sizeof(points), 0);
                    printf("%s \n", points);
                    break;
                }
                if (strcmp(res, "correct") == 0) {
                    char points[256];
                    memset(points, 0, sizeof(points));
                    recv(c, (char *) points, sizeof(points), 0);
                    printf("%s \n", points);
                    break;
                }
                char points[256];
                memset(points, 0, sizeof(points));
                recv(c, (char *) points, sizeof(points), 0);
                printf("%s \n", points);
            } else {
                printf("Failed to receive data from server\n");
            }
        }
    //}

//    if (recv(c, (char *)result, sizeof(result), 0) > 0) {
//        printf("The concatenate number is: %s\n", result);
//    } else {
//        printf("Failed to receive data from server\n");
//    }

    closesocket(c);
    WSACleanup();
    return 0;
}

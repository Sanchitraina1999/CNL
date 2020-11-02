#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER "127.0.0.1"
#define BUFLEN 503
#define PORT 8885

void die(char *s) // used to quit
{
    perror(s);
    exit(1);
}
unsigned long fsize(char *file)
{
    FILE *f = fopen(file, "r");
    fseek(f, 0, SEEK_END);                       //used to take the function pointer to the starting of the file or end of the file or to        any position specified by the user.
    unsigned long len = (unsigned long)ftell(f); // used to find out the position of file pointer in the file with        respect to starting of the file.
    fclose(f);
    return len;
}

int main(void)
{
    struct sockaddr_in si_other;
    int s, i, slen = sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    memset((char *)&si_other, 0, sizeof(si_other));

    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER, &si_other.sin_addr) == 0) //converts the specified string, in the Internet standard         dot notation, to a network address, and stores the address in         the structure provided.
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    char fname[20];
    printf("Enter Filename with extension: ");
    scanf("%s", &fname); //add.txt
    sendto(s, fname, 20, 0, (struct sockaddr *)&si_other, slen);
    memset(message, 0, 503);
    unsigned long siz = fsize(fname); //fsize(add.txt)=20
    printf("%ld", (siz % 503));       //20%503=20
    char str[10];
    sprintf(str, "%d", siz);
    sendto(s, str, 20, 0, (struct sockaddr *)&si_other, slen);
    FILE *f;
    f = fopen(fname, "rb");
    memset(message, 0, 503);
    fread(message, 503, 1, f);
    int itr = 1;
    while (itr * 503 < siz)
    {
        //fread(message, 503,1,f);
        if (sendto(s, message, 503, 0, (struct sockaddr *)&si_other, slen) == -1)
        {
            die("sendto()");
        }
        memset(message, 0, 503);
        fread(message, 503, 1, f);
        itr++;
    }
    fread(message, (siz % 503), 1, f);
    sendto(s, message, (siz % 503), 0, (struct sockaddr *)&si_other, slen);
    memset(message, 0, 503);
    fclose(f);
    close(s);
    return 0;
}
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define BUF_SIZE 255

int main(void)
{
    int fd = 0;
    int counter = 0;
    char symbol = 0;
    char buf[BUF_SIZE] = {0};
    struct stat statbuf = {0};

    fd = open("file.txt", O_RDWR);
    if (-1 == fd)
    {
        perror("OPEN FILE ERROR!");
        exit(1);
    }

    fgets(buf, BUF_SIZE, stdin);

    if (-1 == write(fd, buf, strlen(buf)))
    {
        perror("WRITE FILE ERROR!");
        close(fd);
        exit(1); 
    }

    if (-1 == lseek(fd, 0, SEEK_SET))
    {
        perror("WRITE FILE ERROR!");
        close(fd);
        exit(1); 
    }

    while (symbol != '\n')
    {
        if (-1 == read(fd, &symbol, 1))
        {
            perror("READ FILE ERROR!");
            close(fd);
            exit(1); 
        }
        printf("%c", symbol);      
    }

    do
    {   
        counter++;
        if (-1 == lseek(fd, -counter, SEEK_END))
        {
            perror("BACKSEEK FILE ERROR!");
            close(fd);
            exit(1); 
        }  

        if (-1 == read(fd, &symbol, 1))
        {
            perror("BACKREAD FILE ERROR!");
            close(fd);
            exit(1); 
        }  
        if (symbol == '\n')
        {
            continue;
        }
        printf("%c", symbol);   
    } while (counter != strlen(buf));
    printf("\n");

    close(fd);

    return 0;
}

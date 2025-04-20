#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
    FILE *fp;
    char filename[100];

    cout << "Enter the name of the file to create: ";
    cin >> filename;

    fp = fopen(filename, "w");

    if (fp == NULL) {
        cout << "Error creating file." << endl;
        return 1;
    }

    cout << "File created successfully." << endl;

    fclose(fp);
    
    int x = atoi(argv[1]);
    mkfifo("mypipe", 0666);

    int fd = open("mypipe", O_WRONLY);
    write(fd, &x, sizeof(x));
    close(fd);

    return 0;
}

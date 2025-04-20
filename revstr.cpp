#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
    char str[100];
    int i, j;  
    cout << "Enter a string: ";
    cin.getline(str, 100);
    j = strlen(str) - 1;
    for (i = 0; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    cout << "Reversed string: " << str << endl;

    int x = atoi(argv[1]);
    mkfifo("mypipe", 0666);

    int fd = open("mypipe", O_WRONLY);
    write(fd, &x, sizeof(x));
    close(fd);
    return 0;
}

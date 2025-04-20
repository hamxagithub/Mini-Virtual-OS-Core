#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <cctype>

using namespace std;

int main(int argc, char *argv[]) {
    char str[100];
    int count = 0;

    cout << "Enter a string: ";
    cin.getline(str, 100);

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            count++;
        }
    }

    cout << "Number of letters: " << count << endl;

    int x = atoi(argv[1]);
    mkfifo("mypipe", 0666);

    int fd = open("mypipe", O_WRONLY);
    write(fd, &x, sizeof(x));
    close(fd);

    return 0;
}

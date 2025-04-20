#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    char old_file[100];
    char new_file[100];

    cout << "Enter the name of the file to move: ";
    cin.getline(old_file, 100);

    cout << "Enter the new name of the file: ";
    cin.getline(new_file, 100);

    int result = rename(old_file, new_file);

    if (result == 0) {
        cout << "File moved successfully." << endl;
    } else {
        cout << "Error moving file." << endl;
    }

    int x = atoi(argv[1]);
    mkfifo("mypipe", 0666);

    int fd = open("mypipe", O_WRONLY);
    write(fd, &x, sizeof(x));
    close(fd);

    return 0;
}

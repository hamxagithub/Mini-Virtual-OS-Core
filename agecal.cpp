#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
    int birth_year, current_year, age;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    current_year = t->tm_year + 1900;
    
    cout << "Enter your birth year: ";
    cin >> birth_year;

    age = current_year - birth_year;
    cout << "Your age is: " << age << endl;

    sleep(2);

    int x = atoi(argv[1]);
    mkfifo("mypipe", 0666);

    int fd = open("mypipe", O_WRONLY);
    write(fd, &x, sizeof(x));
    close(fd);
    
    return 0;
}

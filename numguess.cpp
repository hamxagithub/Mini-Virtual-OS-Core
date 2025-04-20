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
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
    int secret_number, user_guess;

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate a random number between 1 and 100
    secret_number = rand() % 100 + 1;

    cout << "I'm thinking of a number between 1 and 100." << endl;

    do {
        cout << "Enter your guess: ";
        cin >> user_guess;

        if (user_guess > secret_number) {
            cout << "Too high! Try again." << endl;
        } else if (user_guess < secret_number) {
            cout << "Too low! Try again." << endl;
        } else {
            cout << "Congratulations! You guessed the correct number: " << secret_number << endl;
        }
    } while (user_guess != secret_number);

    int x = atoi(argv[1]);
    mkfifo("mypipe", 0666);

    int fd = open("mypipe", O_WRONLY);
    write(fd, &x, sizeof(x));
    close(fd);

    return 0;
}

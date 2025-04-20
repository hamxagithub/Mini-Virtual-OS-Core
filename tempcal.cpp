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
    int choice;
    float temperature;
    
    cout << "Enter temperature: "; 
    cin >> temperature;
    
    cout << "Choose conversion:" << endl;
    cout << "1. Celsius to Fahrenheit" << endl;
    cout << "2. Fahrenheit to Celsius" << endl;
    cin >> choice;
    
    switch(choice) {
        case 1:
            temperature = temperature * 9/5 + 32;
            cout << "Temperature in Fahrenheit: " << fixed << temperature << endl;
            break;
        case 2:
            temperature = (temperature - 32) * 5/9;
            cout << "Temperature in Celsius: " << fixed << temperature << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }
    sleep(5);
    
    int x = atoi(argv[1]);
    mkfifo("mypipe", 0666);

    int fd = open("mypipe", O_WRONLY);
    write(fd, &x, sizeof(x));
    close(fd);
    
    return 0;
}

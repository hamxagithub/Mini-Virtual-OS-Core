#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include<iomanip>

using namespace std;

int main(int argc, char *argv[]) {
    char oper;
    double num1, num2, result;

    cout << "Enter an operator (+, -, *, /): ";
    cin >> oper;

    cout << "Enter two numbers: ";
    cin >> num1 >> num2;

    switch (oper) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                cerr << "Error: division by zero" << endl;
                return 1;
            } else {
                result = num1 / num2;
            }
            break;
        default:
            cerr << "Error: invalid operator" << endl;
            return 1;
    }

    cout << fixed << setprecision(2);
    cout << num1 << ' ' << oper << ' ' << num2 << " = " << result << endl;
    sleep(5);

    int x = atoi(argv[1]);
    mkfifo("mypipe", 0666);

    int fd = open("mypipe", O_WRONLY);
    write(fd, &x, sizeof(x));
    close(fd);

    return 0;
}

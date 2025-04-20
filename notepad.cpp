#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <value>" << endl;
        return 1;
    }

    int x = atoi(argv[1]);
    char filename[100];
    char text[1000];
    ofstream outFile;
    
    cout << "Enter file name: ";
    cin >> filename;
    outFile.open(filename, ios::app);
    if (!outFile.is_open()) {
        cerr << "Error creating file!" << endl;
        return 1;
    }

    cout << "Enter text (press '=' to save and exit):\n";
    outFile.seekp(0, ios::beg);
    while (cin.getline(text, sizeof(text))) {
        if (text[0] == '=') {
            break;
        }
        outFile << text << endl;
        outFile.flush();
    }
    outFile.close();

    mkfifo("mypipe", 0666);
    int fd = open("mypipe", O_WRONLY);
    write(fd, &x, sizeof(x));
    close(fd);

    return 0;
}

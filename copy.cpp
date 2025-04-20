#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {
    FILE *src_file, *dest_file;
    char src_filename[100], dest_filename[100], buffer[1024];
    size_t bytes_read;

    while (true) {
        cout << "Enter the source filename: ";
        cin >> src_filename;

        src_file = fopen(src_filename, "rb");
        if (src_file != NULL) {
            break;
        } else {
            cout << "Error: Cannot open source file '" << src_filename << "'" << endl;
        }
    }
    
    while (true) {
        cout << "Enter the destination filename: ";
        cin >> dest_filename;

        dest_file = fopen(dest_filename, "wb");
        if (dest_file != NULL) {
            break;
        } else {
            cout << "Warning: Cannot open destination file '" << dest_filename << "', creating a new file..." << endl;
            dest_file = fopen(dest_filename, "wb");
            if (dest_file == NULL) {
                cout << "Error: Cannot create destination file '" << dest_filename << "'" << endl;
                fclose(src_file);
                return 1;
            }
        }
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);

    cout << "File copied successfully!" << endl;

    int x = atoi(argv[1]);
    mkfifo("mypipe", 0666);

    int fd = open("mypipe", O_WRONLY);
    write(fd, &x, sizeof(x));
    close(fd);

    return 0;
}

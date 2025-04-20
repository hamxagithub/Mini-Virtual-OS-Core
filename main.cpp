#include <iostream>  // Include the input/output stream library
#include <chrono>    // Include the chrono library for time-related operations
#include <thread>    // Include the thread library for multi-threading support
#include <iomanip>   // Include the iomanip library for input/output formatting
#include <stdlib.h>  // Include the stdlib library for general utilities
#include <unistd.h>  // Include the unistd library for POSIX API access
#include <sys/types.h>  // Include the sys/types.h header for system data types
#include <ncurses.h>    // Include the ncurses library for console manipulation
#include <sys/wait.h>   // Include the sys/wait.h header for process management
#include <semaphore.h>  // Include the semaphore library for synchronization
#include <fcntl.h>      // Include the fcntl library for file control
#include <pthread.h>    // Include the pthread library for POSIX threads
#include <string>       // Include the string library for string operations

#include <cstring>      
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <sys/stat.h>



using namespace std;  // Use the standard namespace


#define SIZE_OF_QUEUE 100  // Define the size of the queue

struct Process_info  // Define a structure for process information
{
    int ram;           // RAM information for the process
    long int hard;     // Hard disk space for the process
    string name;       // Name of the process
    int processs_id;   // Process ID

};

Process_info obj1,*ptr=NULL;

Process_info processQueue[SIZE_OF_QUEUE];  // Define an array to hold process information

int ram = 2000, cores = 8, activecores;  // Initialize variables for RAM and cores
long int hard = 256000;                  // Initialize variable for hard disk space
int front = -1, rear = -1;                // Initialize front and rear pointers for the queue

int forpipe[2];


sem_t *semaphore = NULL;



void activeprocesses() {
    cout << "Active processes on Cores : \n";
    for (int i = 0; i < cores; i++) {
        if (ptr[i].processs_id != 0) {
            cout << "The process " << ptr[i].name << " with process id " << ptr[i].processs_id << endl;
        }
    }
}

void compilefile(string filename) {
    char command[100];
    sprintf(command, "g++ -o %s.out %s", filename.c_str(), filename.c_str()); 
    if (system(command) != 0) {
        perror("g++"); 
        exit(EXIT_FAILURE);
    }
}

void runfile(string filename, int pid) {
    char cmd[100];
    sprintf(cmd, "x-terminal-emulator -e './%s.out %d' &", filename.c_str(), pid);
    system(cmd);
}



bool Empty_Queue()  // Check if the queue is empty
{
    if (front == -1 && rear == -1)  // If both front and rear are -1
    {
        return true;  // The queue is empty
    }
    else
    {
        return false;  // Otherwise, the queue is not empty
    }
}

bool Full_Queue()  // Check if the queue is full
{
    if ((rear + 1) % SIZE_OF_QUEUE == front)  // If rear is just behind front
    {
        return true;  // The queue is full
    }
    else
    {
        return false;  // Otherwise, the queue is not full
    }
}

void enqueue_process(Process_info p)  // Enqueue a process into the queue
{
    if (Full_Queue())  // If the queue is full
    {
        cout << "Queue is full" << endl;  // Display an error message
    }
    else
    {
        if (Empty_Queue())  // If the queue is empty
        {
            front = 0;  // Set front to the first position
            rear = 0;   // Set rear to the first position
        }
        else
        {
            rear = (rear + 1) % SIZE_OF_QUEUE;  // Move rear circularly
        }
        processQueue[rear].processs_id= p.processs_id;  // Insert the process at the rear position
        processQueue[rear].hard= p.hard;  // Insert the process at the rear position
        processQueue[rear].name= p.name;  // Insert the process at the rear position
        processQueue[rear].ram= p.ram;


    }
}


void Dequeue(int pid)  // Remove a process from the queue
{
    for (int i = front; i != rear; i = (i + 1) % SIZE_OF_QUEUE)  // Iterate through the queue
    {
        if (processQueue[i].processs_id == pid)  // If the process ID matches
        {
            processQueue[i].processs_id = 0;  // Set the process ID to 0 to mark as removed
            break;  // Exit the loop
        }
    }
    if (processQueue[rear].processs_id == pid)  // If the last process ID matches
    {
        processQueue[rear].processs_id = 0;  // Set the process ID to 0 to mark as removed
    }
}


void displayqueue()  // Display the contents of the queue
{
    cout << "Current queue:\n";  // Display header for the queue
    int i = front;  // Start from the front of the queue
    while (i != rear)  // Loop until reaching the rear of the queue
    {
        // Display process information
        cout << processQueue[i].processs_id << ", " << processQueue[i].name << ", " << processQueue[i].ram << ", " << processQueue[i].hard << endl;
        i = (i + 1) % SIZE_OF_QUEUE;  // Move to the next position circularly
    }
    // Display information for the last process in the queue
    cout << processQueue[rear].processs_id << ", " << processQueue[rear].name << ", " << processQueue[rear].ram << ", " << processQueue[rear].hard << endl;
}




// int emptycore()
// {
//     for (int i = 0; i < cores; i++)
//     {
//         if (ptr[i].processs_id == 0)
//         {
//             return i;
//         }
//     }
// }



// void *idreturn(void *arg) {
//     while (1) {
//         int flag = 0;
//         int fd = open("mypipe", O_RDONLY);

//         int x = 0;
//         read(fd, &x, sizeof(x));
//         close(fd);

//         if (x != 0) {
//             flag = 1;
//             for (int i = 0; i < cores; i++) {
//                 if (ptr[i].processs_id == x) {
//                     ptr[i]. processs_id= 0;
//                     ram = ram + ptr[i].ram;
//                     activecores++;
//                     break;
//                 }
//             }
//         }

//         int y = Empty_Queue();

//         if (y != 1 && flag == 1) {
//             pthread_t p;
//             pthread_create(&p, NULL, threading, semaphore);
//             pthread_join(p, NULL);
//         }
//     }
// }

void intro()  // Display introductory message
{
    system("clear");  // Clear the console screen
    cout << "\t\tWelcome to my operating system project!" << endl;  // Display welcome message
    cout << "\t\tThank you for your interest in my project!" << endl;  // Display thank you message
    this_thread::sleep_for(chrono::seconds(5));  // Pause execution for 5 seconds
    system("clear");  // Clear the console screen
}

int opening()  // Display opening animation
{
    system("clear");  // Clear the console screen
    cout << "PAWA is opening...";  // Display opening message
    char chars[] = {'\\', '|', '/', '-'};  // Define animation characters
    for (int i = 0; i < 20; i++)  // Loop for animation frames
    {
        cout << "\t[" << chars[i % 4] << "]";  // Display animation frame
        this_thread::sleep_for(chrono::milliseconds(500));  // Pause for 500 milliseconds
        cout << "\r";  // Move cursor back to start of line
        cout.flush();  // Flush output to ensure immediate display
    }
    system("clear");  // Clear the console screen
    return 0;  // Return 0 to indicate successful execution
}

int shuttingdown()  // Display shutdown animation
{
    system("clear");  // Clear the console screen
    cout << "PAWA is shutting down...";  // Display shutdown message
    char chars[] = {'\\', '|', '/', '-'};  // Define animation characters
    for (int i = 0; i < 20; i++)  // Loop for animation frames
    {
        cout << "\t[" << chars[i % 4] << "]";  // Display animation frame
        this_thread::sleep_for(chrono::milliseconds(500));  // Pause for 500 milliseconds
        cout << "\r";  // Move cursor back to start of line
        cout.flush();  // Flush output to ensure immediate display
    }
    this_thread::sleep_for(chrono::seconds(5));  // Pause execution for 5 seconds
    system("clear");  // Clear the console screen
    return 0;  // Return 0 to indicate successful execution
}

int cloc()  // Display current time
{
    auto now = chrono::system_clock::now();  // Get current time
    auto now_c = chrono::system_clock::to_time_t(now);  // Convert to time_t
    auto timeinfo = localtime(&now_c);  // Get local time
    cout << "The current time is " << put_time(timeinfo, "%H:%M:%S") << endl;  // Display current time
    return 0;  // Return 0 to indicate successful execution
}




int main()  // Main function
{

    // pthread_t checkid, checkready;
    // pthread_create(&checkid, NULL, idreturn, NULL);

    // ptr = new Process_info[cores * sizeof(Process_info)];
    // for (int i = 0; i < cores; i++) {
    //     ptr[i].processs_id = 0;
    // }
    // activecores = cores;


            compilefile("notepad.cpp");
            runfile("notepad.cpp", 456);


    //intro();  // Display introductory message
    //opening();  // Display opening animation

   // cloc();  // Display current time
   // shuttingdown();  // Display shutdown animation


    //    Process_info p1 = {1024, 2048, "Process1", 1};
    //     Process_info p2 = {2048, 4096, "Process2", 2};
    //     Process_info p3 = {4096, 8192, "Process3", 3};

    //     enqueue_process(p1);
    //     enqueue_process(p2);
    //     enqueue_process(p3);

    //     displayqueue();

    //     Dequeue(2);

    //     cout << "Queue after removing process 2:\n";
    //     displayqueue();




    return 0;  // Return 0 to indicate successful execution
}
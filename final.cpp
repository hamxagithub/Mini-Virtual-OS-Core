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


sem_t *semaphore = NULL;          //     COUNTING SEMAPHORE 





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
            front = -1 ;  // Set front to the first position
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


void Dequeue2() {
    if (Empty_Queue()) {  // Check if the queue is empty
        cout << "Queue is empty. Cannot dequeue." << endl;
        return;
    }

    if (front == rear) {  // If there is only one element in the queue
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % SIZE_OF_QUEUE;  // Move front circularly
    }
}



void displayqueue()  // Display the contents of the queue
{
    cout << "Current queue:\n";  // Display header for the queue
    int i = front;  // Start from the front of the queue
    while (i != rear)  // Loop until reaching the rear of the queue
    {
        // Display process information
        cout <<i<<"    " <<processQueue[i].processs_id << ", " << processQueue[i].name << ", " << processQueue[i].ram << ", " << processQueue[i].hard << endl;
        i = (i + 1) % SIZE_OF_QUEUE;  // Move to the next position circularly
    }
    // Display information for the last process in the queue
    cout << processQueue[rear].processs_id << ", " << processQueue[rear].name << ", " << processQueue[rear].ram << ", " << processQueue[rear].hard << endl;
}

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


bool check_cores(){

    if (activecores>0)
    {
        return true;
    }
    else{
        return false;
    }
    
}

int emptycore()
{
    for (int i = 0; i < cores; i++)
    {
        if (ptr[i].processs_id == 0)
        {
            return i;
        }

       
    }
    cout<<"NO EMPTY CORES "<<endl;
            return-1;
    
}



void *Threads_creation(void *arg) {
    sem_t *semaphore = (sem_t *)arg;

    sem_wait(semaphore); // Wait for available cores

    if (check_cores()) { // Check if there are available cores
        activecores--;

        // Ensure that there are processes in the queue
        if (!Empty_Queue()) {
            front = (front + 1) % SIZE_OF_QUEUE;

            // Check resource availability before dequeuing the process
            while (ram < processQueue[front].ram || hard < processQueue[front].hard) {
                // Enqueue the process back if resources are not available
                enqueue_process(processQueue[front]);
                front = (front + 1) % SIZE_OF_QUEUE;
            }

            // Dequeue the process
            int x = emptycore();
            ptr[x].processs_id = processQueue[front].processs_id;
            ptr[x].ram = processQueue[front].ram;
            ptr[x].name = processQueue[front].name;
            ptr[x].hard = processQueue[front].hard;


            // Update RAM and Hard Disk usage
            ram -= processQueue[front].ram;
            hard -= processQueue[front].hard;

            
                //  cout<<x<<endl;
                //  cout<<ptr[x].processs_id<<endl;
                //  cout<<ptr[x].ram<<endl;
                // cout<<ptr[x].name<<endl;
                //  cout<<ptr[x].hard<<endl;

            // Compile and run the dequeued process
            compilefile(processQueue[front].name);
            runfile(processQueue[front].name, processQueue[front].processs_id);

            // Update queue pointers
            if (front == rear) {
                // Reset queue pointers if there is only one process in the queue
                front = -1;
                rear = -1;
            }
            else {
                front = (front + 1) % SIZE_OF_QUEUE;
            }
        }
        else {
            // If queue is empty, release the semaphore and return
            sem_post(semaphore);
            return NULL;
        }
    }

    sem_post(semaphore); // Release the semaphore
    return NULL;
}



void create_process(string file,int ram, long int hard)
{
     pthread_t t;


    if (pipe(forpipe) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t p;
    p=fork();

    if (p==0)
    {
        /* child  PROCESS*/

         int x = getpid();

        close(forpipe[0]);                // close reading end of pipe
        write(forpipe[1], &x, sizeof(x)); // writing the PROCESS ID IN THE pipe
        close(forpipe[1]);                // close

        exit(EXIT_SUCCESS);
    }
    else if (p>0)
    {
        /* PARENT PROCESS */

        int P_ID;
        close(forpipe[1]);                // close reading end of pipe
        read(forpipe[0], &P_ID, sizeof(P_ID)); // writing the PROCESS ID IN THE pipe
        close(forpipe[0]);                // close

        // temporary object

        Process_info p;
        p.processs_id=P_ID;
        p.name=file;
        p.ram=ram;
        p.hard=hard;

        enqueue_process(p);

    }
    else
    {
        /* FAILED  CREATING PROCESS  */
        cout<<"THE "<<file<<" IS NOT RUNNING (CREATION FAILED)"<<endl;

    }

    pthread_create(&t,NULL,Threads_creation,semaphore);
    pthread_join(t,NULL);

   


}



int main()

{


    ptr = new Process_info[cores * sizeof(Process_info)];
    for (int i = 0; i < cores; i++) {
        ptr[i].processs_id = 0;
    }
    activecores = cores;

     char semaphore_name[100];
    sprintf(semaphore_name, "semaphore_%d", getpid());

    semaphore = sem_open(semaphore_name, O_CREAT | O_EXCL, 0644, cores);
    if (semaphore == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

        create_process("notepad.cpp",10,20);
        
}
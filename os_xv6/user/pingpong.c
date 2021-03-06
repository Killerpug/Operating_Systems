// created by Killerpug
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
//ping pong should perform Inter-Process Communication(IPC) to share a byte between parent and child processes. 

int main(int argc, char *argv[])
{
    int pid;
    char buffer[10];
    int ipc_child_to_parent[2];
    int ipc_parent_to_child[2];    // create read and write file descriptors for dual communication
    pipe(ipc_child_to_parent);   
    pipe(ipc_parent_to_child);

    pid = fork();

    if(pid == 0)
    { //child process
        read(ipc_parent_to_child[0], buffer, sizeof(buffer));      //receive ping
        printf("pid: %d. child reads: %s\n", pid, buffer);
        write(ipc_child_to_parent[1], "pong", 4);                 // write pong
    } else { //parent process
        printf("pid: %d. parent sends ping\n", pid);
        write(ipc_parent_to_child[1], "ping", 4);                  // write ping
        read(ipc_child_to_parent[0], buffer, sizeof(buffer));     //receive pong
        printf("pid: %d. parent receives: %s\n", pid, buffer);
    }

    sleep(20);
    exit(0);
}

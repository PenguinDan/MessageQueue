/*
 - Sends each event to only ONE RECEIVER
 - Does not accept any acknowledgement messages
 - Terminates on "KILL" COMMAND FROM A SEPARATE TERMINAL
*/


//Initialize Constants
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <stdlib.h>

using namespace std;
//Message sender ID
const int SENDER_ID = 251;
const int MESSAGE_SIZE = 50;

int generateRandomNum();
void initializeSRand();

//Create a struct for message buffer
struct buf{
    long mtype;
    //Define message size
    char message[MESSAGE_SIZE];
};

int main(){
    int qid = msgget(ftok(".",'u'), SENDER_ID);
    buf msg;
    initializeSRand();
}

/*
 Generate a random number
 @Param: None
 @Return: An integer value from 0 to 2,147,483,647
 */
int generateRandomNum(){
    return rand() % INT_MAX;
}

/*
 Inititalize srand to the internal with the internal clokc of the computer
 @Param: None
 @Return: None
 */
void initializeSRand(){
    srand((int) time(NULL));
}

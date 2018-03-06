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
const int SENT_TO = 1;

int generateRandomNum();
void initializeSRand();
int allocateQueue();



int main(){
    int qid = msgget(ftok(".",'u'), 0);
    //Create a struct for message buffer
    struct buf{
        //Define the mtype
        long mtype;
        //Define the sender id number
        long senderID;
        //Define message size
        char message[MESSAGE_SIZE];
        
    };buf msg;
    int size = sizeof(msg) - sizeof(long) - sizeof(long);
    msg.mtype = 1;
    msg.senderID = 251;
    strcpy(msg.message, "This is sender 251.");
    cout << "Sender 251: Sent message" << endl;
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
    
    exit(0);
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

/*
 *    Allocates a queue where message objects are saved
 *
 * @Param: None
 *
 *    @Return: A message queue identifier
 */
int allocateQueue() {
    int id = 'u';
    return msgget(ftok(".", id), 0);
}

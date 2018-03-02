/*
 - Send each event to ALL RECEIVERS
 - Requires acknowledgement for each message from BOTH RECEIVERS before it continues execution
 - Terminates when it gets/observes a RANDOM NUMBER SMALLER THAN 100
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int SENDER_ID = 997;
const int MESSAGE_SIZE = 50;

int generateRandomNum();
void initializeSRand();

int main(){

    int qid = msgget(ftok(".",'u'), 0);

    struct buf{
        long mtype;
        long senderID;
        //Define message size
        char message[MESSAGE_SIZE];
    };buf msg;
    initializeSRand();

    msg.mtype = 0;
    msg.SENDER_ID = senderID;
    strcpy(msg.message, "Sender 997 to Reciver 1")
    cout<< " Message Sent to Reciever 1" <<endl;
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);

    msg.mtype = 1;
    msg.SENDER_ID = senderID;
    strcpy(msg.message, "Sender 997 to Reciver 2")
    cout<< " Message Sent to Reciever 2" <<endl;
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);

    msgrcv(qid, (struct msgbuf *)&msg, size, 2, 0);
  	cout << "Response Recived 1" << endl;
  	cout << "reply: " << msg.greeting << endl;
  	cout << ": now exits" << endl;

    msgrcv(qid, (struct msgbuf *)&msg, size, 2, 0);
  	cout << "Response Recived 2" << endl;
  	cout << "reply: " << msg.greeting << endl;
  	cout << ": now exits" << endl;

}

//Generate a random number
int generateRandomNum(){
    return rand() % INT_MAX;
}

//Inititalize srand to the internal with the internal clokc of the computer
void initializeSRand(){
    srand((int) time(NULL));
}

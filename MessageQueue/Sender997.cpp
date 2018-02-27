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

    int qid = msgget(ftok(".",'u'), SENDER_ID);

    struct buf{
        long mtype;
        //Define message size
        char message[MESSAGE_SIZE];
    };buf msg;
    initializeSRand();

    msg.mtype = 0; //add mtype
    strcpy(msg.message, "Hello")
    cout<< getpid() << ":sends greeting" <<endl;
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);

    msgrcv(qid, (struct msgbuf *)&msg, size, 314, 0);
  	cout << getpid() << ": gets reply" << endl;
  	cout << "reply: " << msg.greeting << endl;
  	cout << getpid() << ": now exits" << endl;

  	msg.mtype = 117;
  	msgsnd (qid, (struct msgbuf *)&msg, size, 0);
}

//Generate a random number
int generateRandomNum(){
    return rand() % INT_MAX;
}

//Inititalize srand to the internal with the internal clokc of the computer
void initializeSRand(){
    srand((int) time(NULL));
}

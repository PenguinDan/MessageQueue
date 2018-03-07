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
#include <climits>
using namespace std;

const int SENDER_ID = 997;
const int MESSAGE_SIZE = 50;

int generateRandomNum();
void initializeSRand();

struct message{
    long mtype;
    long senderID;
    char message[MESSAGE_SIZE];
    };

int main(){

    int qid = msgget(ftok(".",'u'), 0);

    message msg1;
    message msg2;

    initializeSRand();

    int messageSize = retrieveMessageSize(msg);
    msg1.mtype = 1;
    msg1.senderID = SENDER_ID;
    strcpy(msg1.message, "Sender 997 to Reciver 1");
    cout<< " Message Sent to Reciever 1" <<endl;
    msgsnd(qid, (struct msgbuf *)&msg1, messageSize, 0);


    msg2.mtype = 3;
    msg2.senderID = SENDER_ID;
    strcpy(msg2.message, "Sender 997 to Reciver 2");
    cout<< " Message Sent to Reciever 2" <<endl;
    msgsnd(qid, (struct msgbuf *)&msg2, messageSize, 0);


    msgrcv(qid, (struct msgbuf *)&msg, messageSize, 2, 0);
  	cout << "Response Recived 1" << endl;
  	cout << "reply: " << msg.message << endl;
  	cout << ": now exits" << endl;

    /*
    msgrcv(qid, (struct msgbuf *)&msg, messageSize, 2, 0);
  	cout << "Response Recived 2" << endl;
  	cout << "reply: " << msg.message << endl;
  	cout << ": now exits" << endl;
    */

}
int retrieveMessageSize(buffer message) {
    return sizeof(message) - sizeof(long) - sizeof(long);
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
 Inititalize srand to the internal with the internal clock of the computer
 @Param: None
 @Return: None
 */
void initializeSRand(){
    srand((int) time(NULL));
}

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

const long SENDER_ID = 997;
const int MESSAGE_SIZE = 50;
const int RECEIVABLE_MESSAGE_TYPE = 3;
const int MESSAGE_TYPE_FOR_RECEIVER_1 = 1;
const int MESSAGE_TYPE_FOR_RECEIVER_2 = 2;

struct message{
    long mtype;
    long senderID;
    char message[MESSAGE_SIZE];
    };
int generateRandomNum();
void initializeSRand();
int retrieveMessageSize(message);

int main(){

    int messageQueueId = msgget(ftok(".",'u'), 0);
    cout << "Connect to message queue id: " << messageQueueId << endl;
    initializeSRand();

    //Initialize message for Receiver 1
    message msg;
    msg.mtype = 1;
    msg.senderID = SENDER_ID;
    strcpy(msg.message, "Sender 997 to Receiver 1");

    //Initialize message for Receiver 2
    message msg2;
    msg2.mtype = 2;
    msg.senderID = SENDER_ID;
    strcpy(msg2.message, "Sender 997 to Receiver 2");

    //Retrieve the size of the message
    int messageSize = retrieveMessageSize(msg);
    
    //sends message
    msgsnd(messageQueueId, (struct message *)&msg, messageSize, 0);
    msgsnd(messageQueueId, (struct message *)&msg2, messageSize, 0);
    //prints confirmation message
    cout<< " Message Sent to Receiver 1 and 2" <<endl;

    /*
    msg.mtype = 3;
    msg.senderID = SENDER_ID;
    strcpy(msg.message, "Sender 997 to Reciver 2");
    cout<< " Message Sent to Reciever 2" <<endl;
    msgsnd(qid, (struct msgbuf *)&msg, messageSize, 0);
    */

    //recieves message of mtype 2
    msgrcv(messageQueueId, (struct msgbuf *)&msg, messageSize, RECEIVABLE_MESSAGE_TYPE, 0);
  	cout << "Response Received from Receiver #" << msg.senderID << ": " <<
      msg.message << endl;
  	cout << "exiting..." << endl;

    /*
    msgrcv(qid, (struct msgbuf *)&msg, messageSize, 2, 0);
  	cout << "Response Recived 2" << endl;
  	cout << "reply: " << msg.message << endl;
  	cout << ": now exits" << endl;
    */

}

int retrieveMessageSize(message msg) {
    return sizeof(msg) - sizeof(long) - sizeof(long);
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

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
const int ARRAY_SIZE = 50;
const int RECEIVABLE_MESSAGE_TYPE = 3;
const int MESSAGE_TYPE_FOR_RECEIVER_1 = 1;
const int MESSAGE_TYPE_FOR_RECEIVER_2 = 2;
const int MESSAGE_FLAG = 0;
bool receiver1Acknowledge = false;
bool receiver2Acknowledge = false;

struct buffer{
    //Define the mtype
    long messageType;
    //Define the sender id number
    long senderID;
    //Define messge size
    char message[ARRAY_SIZE];
};
int generateRandomNum();
void initializeSRand();
int retrieveMessageSize(buffer);

int main(){

    int messageQueueId = msgget(ftok(".",'u'), 0);
    buffer sentMessage1, sentMessage2, receivedMessage;
    cout << "Connect to message queue id: " << messageQueueId << endl;
    //Retrieve the size of the message
    const int MESSAGE_SIZE = retrieveMessageSize(sentMessage1);
    initializeSRand();
    int numGenerated = generateRandomNum();
    while(numGenerated >= 50){
        //Only sent a message if the random generated number less than 200
        if(numGenerated < 5000){
            //Initialize message for Receiver 1
            sentMessage1.messageType = 1;
            sentMessage1.senderID = SENDER_ID;
            strcpy(sentMessage1.message, to_string(numGenerated).c_str());
            cout << "Sent to receiver " << 1 << ": " << numGenerated << endl;

            //Initialize message for Receiver 2
            sentMessage2.messageType = 2;
            sentMessage2.senderID = SENDER_ID;
            strcpy(sentMessage2.message, to_string(numGenerated).c_str());
            cout << "Sent to receiver " << 2 << ": " << numGenerated << endl;

            //sends message
            msgsnd(messageQueueId, (struct message *)&sentMessage1, MESSAGE_SIZE, MESSAGE_FLAG);
            msgsnd(messageQueueId, (struct message *)&sentMessage2, MESSAGE_SIZE, MESSAGE_FLAG);
            //Loop unitl both receiver 1 and 2 sent an acknowleagement message

        	  msgrcv(messageQueueId, (struct msgbuf *)&receivedMessage, MESSAGE_SIZE, RECEIVABLE_MESSAGE_TYPE, MESSAGE_FLAG);
        		    cout << receivedMessage.message << endl;
        	  msgrcv(messageQueueId, (struct msgbuf *)&receivedMessage, MESSAGE_SIZE, RECEIVABLE_MESSAGE_TYPE, MESSAGE_FLAG);
        		    cout << receivedMessage.message << endl;


            //Reset the acknowledgement back to false
            receiver1Acknowledge = false;
            receiver2Acknowledge = false;
        }
        numGenerated = generateRandomNum();
    }
//    Send a terminate notification to receiver 1
    cout << "This is the num to exit the loop: "<<numGenerated << endl;
    strcpy(sentMessage1.message, "Terminated");
    sentMessage1.senderID = SENDER_ID;
    msgsnd(messageQueueId, (struct message *)&sentMessage1, MESSAGE_SIZE, MESSAGE_FLAG);
    cout << "Connection disconected..." << endl;

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

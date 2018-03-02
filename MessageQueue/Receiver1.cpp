/*
 * Each receiver repeatedly gets a message and displays the value and the Sender’s identity
 * Receiver #1
 *    Accepts from who:
 *       Only accepts messages from 251 AND 997 SENDERS
 *    Termination cause:
 *       Terminates after BOTH OF ITS SENDERS HAVE TERMINATED
 */

//All of the necessary libraries for the program to run
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <string>
using namespace std;

//Constants that define the Senders in which this Receiver listens to
const int ACCEPT_FROM_1 = 251;
const int ACCEPT_FROM_2 = 997;
//Defines the size of the character array to be received
const int MESSAGE_SIZE = 50;
//Defines the maximum amount of messages that this Receiver could receive
const int MAX_MESSAGES = 5000;
//Defines the message type in which this message could receive
const int RECEIVABLE_MESSAGE_TYPE = 0;
//Defines the message flag stating that the first message on the queue is received
const int MESSAGE_FLAG = 0;
//Message buffer
struct buffer {
    long mType;
    long senderId;
    char message[MESSAGE_SIZE];
};
//Forward declaring methods
int allocateQueue();
int retrieveMessageSize(buffer);
void sendMessageAcknowledgement(int , buffer , int , int);
void receiveMessage(int, buffer, int, long, int);

/*
 * The main starting point of the application
 */
int main() {

    //The Queue ID of the message queue
    int messageQueueId = allocateQueue();

    //Build buffer for message acknowledgement to sender 997
    buffer ackMessage;
    ackMessage.mType = 2;
    ackMessage.senderId = 997;
    strcpy(ackMessage.message, "Acknowledgement from Receiver 1");

    buffer rMessage;
    int messageSize = retrieveMessageSize(rMessage);

    //Variable that keeps track of total received messages
    int receivedMessagesCount = 0;

    // while(receivedMessagesCount < 5000) {
        receiveMessage(
                       messageQueueId,
                       rMessage,
                       messageSize,
                       RECEIVABLE_MESSAGE_TYPE,
                       MESSAGE_FLAG
                       );

        //Print out the received message
        cout << rMessage.message << endl;
        receivedMessagesCount += 1;

        if(rMessage.senderId == ackMessage.senderId) {
            cout << "Sending acknowledgement message to Sender 997" << endl;
            sendMessageAcknowledgement(messageQueueId, ackMessage, messageSize, MESSAGE_FLAG);
        }
    // }

    cout << "Closing message queue" << endl;
    msgctl(messageQueueId, IPC_RMID, NULL);
    exit(0);
}

/*
 *    Wrapper method that allocates and creates a queue where message objects are
 * saved
 *
 * @Param: None
 *
 *    @Return: A message queue identifier
 */
int allocateQueue() {
    cout << "Allocating Message Queue" << endl;
    return msgget(ftok(".", 'u'), IPC_EXCL|IPC_CREAT|0777);
}

/*
 * Wrapper method that outputs the size of the message to be received
 *
 *    @Param:
 *    buffer message: The message buffer to be received
 *
 * @Return: The size of the message to be received
 */
int retrieveMessageSize(buffer message) {
    return sizeof(message) - sizeof(long) - sizeof(long);
}

/*
 * Receives a message specifically through the given arguments
 *
 *@Param:
 *int queueId: The message queue id
 *buffer message: The message buffer object received
 *int messageSize: The size of the message to be received
 *long messageType: The message type specified by the received object
 *int messageFlag: The flag that specifies the type of the message requested
 *
 *@Return: None
 *
 */
void receiveMessage(int queueId, buffer message, int messageSize, long messageType, int messageFlag) {
    msgrcv(queueId, (struct buffer *)&message, messageSize, messageType, messageFlag);
}

void sendMessageAcknowledgement(int queueId, buffer message, int messageSize, int messageFlag) {
    msgsnd(queueId, (struct msgbuf *)&message, messageSize, messageFlag);
}

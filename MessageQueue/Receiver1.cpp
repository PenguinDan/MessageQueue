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
const int RECEIVABLE_MESSAGE_TYPE = 1;
//Defines the message flag stating that the first message on the queue is received
const int MESSAGE_FLAG = 0;
//Message buffer
struct buffer {
    long messageType;
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

    //The Message Queue ID that other programs connect to
    int messageQueueId = allocateQueue();
    //Message that prints out the message queue ID for easy deallocation
    //from the terminal
    cout << "Create Message Queue ID: " << messageQueueId << endl;
    //Build buffer for message acknowledgement to sender 997
    //Sender 997 only receives messages of messageType 2
    buffer acknowledgementMessage;
    acknowledgementMessage.messageType = 2;
    acknowledgementMessage.senderId = 997;
    strcpy(acknowledgementMessage.message, "Acknowledgement from Receiver 1");
    //Create a buffer object to store the received messages
    buffer receivedMessage;
    int messageSize = retrieveMessageSize(receivedMessage);

    //Variable that keeps track of total received messages, once it reaches
    //4999, it will force the loop to exit and terminate the message queue
    int receivedMessagesCount = 0;

    cout << "Entering while loop" << endl;

    while(receivedMessagesCount < 5000) {
        //Waits until a message with the proper message type specified by
        //the constant RECEIVABLE_MESSAGE_TYPE is the current first message
        //in the message queue
        receiveMessage(
                       messageQueueId,
                       receivedMessage,
                       messageSize,
                       RECEIVABLE_MESSAGE_TYPE,
                       MESSAGE_FLAG
                       );
        //The message has been received, specify which sender the message
        //was received from and the message
        cout << "Message from Sender #" << receivedMessage.senderId <<
          ": " << receivedMessage.message << endl;
        //Increment the message received counter by one
        receivedMessagesCount += 1;
        //Check if the message was sent from Sender #997
        if(receivedMessage.senderId == acknowledgementMessage.senderId) {
            //The message was received from Sender #997
            cout << "Sending acknowledgement message to Sender 997" << endl;
            //Send the acknowledgement message to Sender 997
            sendMessageAcknowledgement(messageQueueId, acknowledgementMessage,
              messageSize, MESSAGE_FLAG);
        }
    }
    //This receiver has received 5000 messages, begin closing the queue
    cout << "Closing message queue" << endl;
    msgctl(messageQueueId, IPC_RMID, NULL);
    //Exit the program
    exit(0);
}

/*
 * Wrapper method that allocates and creates a queue where message objects are
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
 * @Param:
 *    buffer message: The message buffer to be received
 *
 * @Return:
 *    The size of the message to be received
 */
int retrieveMessageSize(buffer message) {
    return sizeof(message) - sizeof(long) - sizeof(long);
}

/*
 * Receives a message specifically through the given arguments
 *
 *@Param:
 *  int queueId: The message queue id
 *  buffer message: The message buffer object received
 *  int messageSize: The size of the message to be received
 *  long messageType: The message type specified by the received object
 *  int messageFlag: The flag that specifies the type of the message requested
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

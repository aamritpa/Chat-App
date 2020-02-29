# Chat-App
Chat App designed in C through socket programming between two local machine terminals.

Requirements:

(1)Linux or Mac terminal

(2)Port Number [Both the local and remote machines]*

(3) Machine name[Name of the machines of local and remote]

(4)*Port Number can be decided by the users during the time of making connection

Running the Chat-App:

(1). Run the make file in the terminal. Command- $make

(2). Get the machine name and port number of remote person.

(3). Make connection. Command- $./s-talk (myPortNumber) (remoteMachineName) (RemotePortNumber)

(4). Start Chatting.

(5). To terminate the chat just Enter '!'.

(6). Termination message will be sent to Remote Person.

Working:-

Designed on User Datagram Protocol (UDP).

(1)-Pthreads has been used to communicate.

(2)-List C data structure used. 

(3) 4 threads designed.

    (1) First Thread used to store our message into list.
    
    (2) Second Thread used to take out our message and send to remote person.
    
    (3) Third Thread used to store message of remote person into another list.
    
    (4) Forth Thread used to take out remote person message from list and print on my screen.
    
(4) Socket establishing and binding used.

(5) Using IPV4.

Construction of List Data Structure for storing Messages.

(1) Major Focus on Memory management.

(2) Two arrays one for List headers and one for Nodes.

(3) All List shares same memory.

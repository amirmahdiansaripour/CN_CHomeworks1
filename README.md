# Assignments of computer network course (Fall 2022)

1: FTP_server

A server in which multiple clients can connect and send requires to. Each sub-module is explained in the following part.

1) Server: The core module of the FTP_server, which has the responsibility of binding to two ports (data and command channel). Server then handles multiple connections through allocating a thread to each client. 

![1-2](https://user-images.githubusercontent.com/92050925/212425875-b7edf9a3-2f34-431e-8b85-ee8993ede07d.png)

2) Client: The client side of the connection, which sends requests to the server and gets the proper response. Each client should login before entering other requests.


3) ConfigReader: Its duty is to read the json file given in command argument. Based on what it has read, it assigns admin files, users, command channel, and data channel. 

4) EvenLogger: Its function is to write down each request that is made by the clients, requests like downloading or uploading a file, logging in, logging out, etc.

5) MessageHandler: This sub-module gets each request from the server and fragments it into substrings (handle method). The substrings are then processed, and the type of request with its arguments are detected. Finally, the request's response is provided through handle functions (handleDownload, handleQuit, and so on) and sent back to the server.

![1-1](https://user-images.githubusercontent.com/92050925/212425098-800f6766-d97b-43c2-8008-031ca9a67d08.png)

6) Response: A simple module which provides the feedback message to clients' commands. This message is sent to messageHandler, and based on the type of command, is appended to another main response or not. For example, in retr command, the message "Successful Download" is appended to the downloaded file content and sent to server. Server then splits the response and sends the content via data channel and the feedback via command channel.

7) User: A simple module which resembles the server's clients. Each client has a username, password, isAdmin, and MaxDownloadSize which are obtained through scanning the json input file.

How to run
### Go to server and client directories, and compile their respective MakeFiles
```make```

### Then in the server terminal, enter the following command:

``` ./Server.out config.json  ```

### Also enter this in the client side:

``` ./Client.out ```




2: Web Server
How to run
### Compile and run in terminal
```make```

```./Server.out 127.0.0.1:<port number>```

### Open in browser
Open localhost:"port number"/ in a browser

For example:
  ```./Server.out 127.0.0.1:4000```
   http://localhost:4000

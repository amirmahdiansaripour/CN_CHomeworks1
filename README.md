# Assignments of computer network course (Fall 2022)

1: FTP_server

It is a server in which multiple clients can connect and send requires to. Each sub-module is explained in the following part.

1) ConfigReader: Its duty is to read the json file given in command argument. Based on what it has read, it assigns admin files, users, command channel, and data channel. 

2) EvenLogger: Its function is to write down each request that is made by the clients, requests like downloading or uploading a file, logging in, logging out, etc.

3) messageHandler: This sub-module gets each request from the server and fragments it into substrings (handle method). The substrings are then processed, and the type of request with its arguments are detected. Finally, the request's response is provided through handle functions (handleDownload, handleQuit, and so on) and sent back to the server.

![readme1] ![1-1](https://user-images.githubusercontent.com/92050925/212425098-800f6766-d97b-43c2-8008-031ca9a67d08.png)



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

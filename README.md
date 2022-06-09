# FTP-Server

### How to run?

#### Server
Using the terminal, cd to the ```server/``` directory and then
```shell
$ make
$ ./Server.out config.json
```

#### Client
Using another terminal window, cd to the ```client/``` directory and then

```shell
$ make
$ ./Client
```
Now that the client is connected to the server, it can start entering commands. Multiple clients are able to connect to the server simultaneously. 


A report and a project description (including supported commands) in Persian are available in the Documentation folder. 

### Usage

#### Authentication
 - ```user <username>```
 - ```pass <password>```
    
#### Supported Commands
 - ```pwd```: outputs current directory
 - ```mkd <directory path>```: makes new directory
 - ```dele -f <filename>```: deletes a file
 - ```dele -d <directory path>```: deletes a directory
 - ```ls```: outputs contents of the current directory
 - ```cwd <path>``` : navigates to given path
 - ```rename <from><to>```: renames a file/directory
 - ```retr <name>```: downloads the given file
 - ```help```: outputs user manual
 - ```quit```: quits
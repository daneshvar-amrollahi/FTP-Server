#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <string>

const int USERNAME_FOUND    =  331;
const int USER_LOGGED_IN    =  230;
const int PWD_OK            =  257;
const int MKD_OK            =  258;
const int DELE_OK           =  250;
const int LS_OK             =  226;
const int CWD_OK            =  250;
const int RENAME_OK         =  250;
const int HELP_OK           =  241;
const int QUIT_OK           =  221;

const std::string HELP_MESSAGE = "USER [name], Its argument is used to specify the users string. It is used for users authentication\n\nPASS [password], Its argument is used to specify the users string. It is used for users authentication and must be used after USER.\n\nPWD, returns current directory\n\nMKD [directory path], it is used to create a new directory in directory path\n\nDELE -f [filename] it is used to delete a file\n\nDELE -d, it is used to delete a directory\n\nLS, it is used to get the list of the contents of the current directory\n\nCWD [path], it is used to move from the current direcotry to the directory in input path\n\nRENAME [from] [to],changes the name of the folder. First argument indicates the current name of the file, second argument indicates the new name.\n\nRETR [name], used to download the file with the name given as argument.\n\nHELP, used to list the commands and their usage\n\nQUIT, used to quit the server"; 

class Response
{
public:
    std::string getMessage(int code);
    std::string getMessage(int code, std::string response);
};

#endif
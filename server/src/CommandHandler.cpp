#include "CommandHandler.hpp"

CommandHandler::CommandHandler(int data_fd, std::vector<User*> users, std::vector<std::string> private_files) 
    : data_fd(data_fd), 
    users(users), 
    private_files(private_files) {
    current_user = NULL;
    logged_in = false;
    logging_in = false;
    is_admin = false;
    current_directory = execShellCommand("pwd", std::vector<std::string> {});
}

std::vector<std::string> CommandHandler::getSplitted(const std::string& s) {
    std::vector<std::string> res;
    std::string tmp = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            res.push_back(tmp);
            tmp = "";
        } else {
            tmp += s[i];
        }
    }
    res.push_back(tmp);
    return res;
}

std::string CommandHandler::runCommand(std::string input) {
    std::vector<std::string> splitted = getSplitted(input);
    std::string command = splitted[0];
    std::vector<std::string> args(splitted.begin() + 1, splitted.end());
    Response response;
    try
    {
        if (command == "user"){
            return response.getMessage(handleUser(args[0]));
        } else
        if (command == "pass"){
            return response.getMessage(handlePass(args[0]));
        } else
        if (command == "pwd") {
            return response.getMessage(PWD_OK, handlePwd(args));
        } else
        if (command == "mkd") {
            return response.getMessage(MKD_OK, handleMkd(args));
        } else
        if (command == "dele") {
            return response.getMessage(DELE_OK, handleDele(args));
        } else
        if (command == "ls") {
            return response.getMessage(LS_OK) + ";" + handleLs(args);
        } else
        if (command == "cwd") {
            return response.getMessage(handleCwd(args));
        }
        else
        if (command == "rename") {
            return response.getMessage(handleRename(args));
        }
        else
        if (command == "retr") {
            return response.getMessage(RETR_OK) + ";" + handleRetr(args);
        }
        else
        if (command == "help") {
            return response.getMessage(HELP_OK);
        }
        else
        if (command == "quit") {
            return response.getMessage(handleQuit(args));
        }
        else
            throw SyntaxErrorInParamsOrArgs();
        
    }
    catch(Exception& e) {
        return e.getError();
    }
}

int CommandHandler::handleUser(std::string username)
{
    if (logged_in)
        throw Exception();

    bool found = false;
    for (User* user: users) {
         if (user->username == username)
         {
            found = true;
            logging_in_user = user;
            logging_in = true;
            is_admin = user->admin;
         }
    }

    if (!found)
        throw InvalidUsernameOrPassword();
    return USERNAME_FOUND;
}

int CommandHandler::handlePass(std::string password) {
    if (!logging_in)
        throw BadSequenceOfCommands();
    
    if (logging_in_user->password == password)
    {
        logging_in = false;
        logged_in = true;
        current_user = logging_in_user;
        if (logging_in_user->admin)
            is_admin = true;
        return USER_LOGGED_IN;
    }
    throw InvalidUsernameOrPassword();
}

//stackoverflow
std::string CommandHandler::execShellCommand(const char *command, std::vector<std::string> args) {
    
    char tmpname [L_tmpnam];
    std::tmpnam ( tmpname );
    std::string scommand = command;
    scommand += " ";
    for(std::string arg : args)
        scommand += arg + " ";

    // std::cout << "executing " << scommand << "\n";

    std::string cmd = scommand + " >> " + tmpname;
    std::system(cmd.c_str());
    std::ifstream file(tmpname, std::ios::in | std::ios::binary );
    std::string result;
    if (file) {
        while (!file.eof()) 
            result.push_back(file.get());
        file.close();
    }
    remove(tmpname);
    return result.substr(0, result.size() - 2);
}

std::string CommandHandler::handlePwd(std::vector<std::string> args) { //args will be empty
    if (!logged_in)
        throw NotLoggedIn();
    try {
        return current_directory;
    } catch(...) {
        throw Exception();
    }
}

std::string CommandHandler::handleMkd(std::vector<std::string> args) {
    if (!logged_in)
        throw NotLoggedIn();
    try {
        execShellCommand(("cd " + current_directory + " && mkdir").c_str(), args);
    } catch (...) {
        throw Exception();
    }
    return args[0];
}

bool CommandHandler::isPrivateFile(std::string file_name) {
    for (std::string file: private_files)
        if (file == file_name)
            return true;
    return false;
}

std::string CommandHandler::handleDele(std::vector<std::string> args) {
    if (!logged_in)
        throw NotLoggedIn();
    std::string file_name = args[1];
    if (isPrivateFile(file_name) && !current_user->admin)
        throw FileUnavailable();
    if (args.size() < 2)
        throw SyntaxErrorInParamsOrArgs();

    if (args[0] == "-f")
    {
        args.erase(args.begin()); //remove -f/-d
        try {
            execShellCommand(("cd " + current_directory + " && rm").c_str(), args);
        } 
        catch (...){ 
            throw Exception();
        }
    }

    if (args[0] == "-d")
    {
        args.erase(args.begin()); //remove -f/-d
        try {
            execShellCommand(("cd " + current_directory + " && rm -r").c_str(), args);
        }
        catch (...){
            throw Exception();
        }
    }

    return args[0];

    throw SyntaxErrorInParamsOrArgs();
}

std::string CommandHandler::handleLs(std::vector<std::string> args) {
    if (!logged_in)
        throw NotLoggedIn();
    try {
        return execShellCommand(("cd " + current_directory + " && ls ").c_str(), args); 
    } catch(...) {
        throw Exception();
    }
}

int CommandHandler::handleCwd(std::vector<std::string> args) {
    if (!logged_in)
        throw NotLoggedIn();
    try {
        args[0] = current_directory + "/" + args[0];
        args.push_back("&&");
        args.push_back("pwd");
        current_directory = execShellCommand("cd", args); 
        // current_directory = execShellCommand("pwd", std::vector<std::string> {});
        // std::cout << "current_dir = " << current_directory << "\n";
    } catch(...) {
        throw Exception();
    }
    return CWD_OK;
}

int CommandHandler::handleRename(std::vector<std::string> args) {
    if (!logged_in)
        throw NotLoggedIn();
    try {
        args[0] = current_directory + "/" + args[0];
        args[1] = current_directory + "/" + args[1];
        execShellCommand("mv", args); 
    } catch(...) {
        throw Exception();
    }
    return RENAME_OK;
}

int CommandHandler::getFileSize(std::string file_name) {
    FILE* fp = fopen((current_directory + "/" + file_name).c_str(), "r");
    if (fp == NULL) //file not found
        throw FileUnavailable();
    fseek(fp, 0L, SEEK_END);
    long int file_size = ftell(fp);
    fclose(fp);
    return file_size;
}

std::string CommandHandler::handleRetr(std::vector<std::string> args) {
    if (!logged_in)
        throw NotLoggedIn();
    try {
        std::string file_name = args[0];
        if (isPrivateFile(file_name) && !current_user->admin)
            throw FileUnavailable();
        int file_size = getFileSize(file_name);
        if (file_size > current_user->download_capacity)
            throw NotEnoughDownloadCapacity();
        current_user->download_capacity = current_user->download_capacity - file_size;
        return execShellCommand(("cd " + current_directory + " && cat ").c_str(), args); 
    } catch(...) {
        throw Exception();
    }
}

int CommandHandler::handleQuit(std::vector<std::string> args) {
    if (!logged_in)
        throw NotLoggedIn();
    try {
        logged_in = false;
        current_user = NULL;
        is_admin = false;
        return QUIT_OK;
    } catch(...) {
        throw Exception();
    }
}
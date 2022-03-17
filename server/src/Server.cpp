#include "Server.hpp"


Server::Server(const std::string& config_path) : 
    configReader(ConfigReader(config_path))
{
    users = configReader.getUsers();
    private_files = configReader.getPrivateFiles();
}

int setupServer(int port) {
    struct sockaddr_in address;
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    
    listen(server_fd, 4);

    return server_fd;
}

int acceptClient(int server_fd) {
    int client_fd;
    struct sockaddr_in client_address;
    int address_len = sizeof(client_address);
    client_fd = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t*) &address_len);
    return client_fd;
}

struct arg_struct {
    int _command_fd;
    int _data_fd;
}args;

std::vector<User*> server_users;
std::vector<std::string> server_private_files;

std::string getCommandChMessage(std::string message) {
    std::string result = "";
    for (int i = 0; i < message.size(); i++)
    {
        if (message[i] == ';')
            return result;
        result += message[i];
    }
    return result;
}

std::string getDataChMessage(std::string message) {
    int i = 0;
    while (message[i] != ';')
        i++;
    i++;
    std::string result = "";
    for (i; i < message.size(); i++)
        result += message[i];
    return result;
}

bool needsDataChannel(std::string message) {
    for (int i = 0; i < message.size(); i++)
        if (message[i] == ';')
            return true;
    return false;
}

void* handleConnection(void* arguments) {
    int command_fd = args._command_fd;
    int data_fd = args._data_fd;
    CommandHandler* commandHandler = new CommandHandler(data_fd, server_users, server_private_files);

    char read_buffer[1024];
    std::string send_buffer;
    int client_in_len;
    while (true)
    {
        memset(read_buffer, 0, 1024);
        if (recv(command_fd, read_buffer, sizeof(read_buffer), 0) > 0)
            send_buffer = commandHandler->runCommand(std::string(read_buffer));

        if (!needsDataChannel(send_buffer))
        {
            if (send(command_fd, send_buffer.c_str(), sizeof(read_buffer), 0) == -1)
                std::cout << "ERROR on sending command result back to client\n";
        }
        else
        {
            std::string dataChMessage = getDataChMessage(send_buffer);
            std::string commandChMessage = getCommandChMessage(send_buffer);

            if (send(command_fd, commandChMessage.c_str(), sizeof(read_buffer), 0) == -1)
                std::cout << "ERROR on sending command result back to client\n";

            if (send(data_fd, dataChMessage.c_str(), sizeof(read_buffer), 0) == -1)
                std::cout << "ERROR on sending command result back to client\n";
        }
        
        
    }

    pthread_exit(NULL);
}

void Server::run() {
    int data_fd, command_fd;
    char buffer[1024];

    command_fd = setupServer(COMMAND_PORT);
    data_fd = setupServer(DATA_PORT);
    
    pthread_t threads[MAX_THREADS];
    int return_code;
    int thread_cnt = 0;

    server_users = users;
    server_private_files = private_files;

    while (true)
    {
        int command_fd_new = acceptClient(command_fd);
        int data_fd_new = acceptClient(data_fd);

        if (command_fd_new == -1 || data_fd_new == -1)
            std::cout << "ERROR in accepting connection from client" << std::endl;
        
        args._command_fd = (int)command_fd_new;
        args._data_fd = (int)data_fd_new;
        return_code = pthread_create(&threads[thread_cnt], NULL, handleConnection, (void*)&args);
        thread_cnt++;
        
        if (return_code)
		{
            std::cout << "ERROR; return code from pthread_create() is " << return_code << "\n";
			exit(-1);
		}
    }
    for (int tid = 0 ; tid < thread_cnt ; tid++)
    {
        return_code = pthread_join(threads[tid], NULL);
		if (return_code)
		{
			std::cout << "ERROR; return code from pthread_join() is "<< return_code << "\n";
			exit(-1);
		}
    }
}


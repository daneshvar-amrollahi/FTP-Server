#include "Server.hpp"
#include "CommandHandler.hpp"


Server::Server(const std::string& config_path) 
    : 
    configReader(ConfigReader(config_path)),
    private_files(configReader.getPrivateFiles()),
    users(configReader.getUsers()) {
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
    int _tid;
    int _command_fd;
    int _data_fd;
};

void* handleConnection(void* arguments) {
    struct arg_struct *args = (struct arg_struct *)arguments;
    int tid = args->_tid;
    int command_fd = args->_command_fd;
    int data_fd = args->_data_fd;

    CommandHandler* commandHandler = new CommandHandler(data_fd);

    char read_buffer[1024];
    std::string send_buffer;
    int client_in_len;
    while (true)
    {
        memset(read_buffer, 0, 1024);
        bzero(read_buffer, 1024);
        if (recv(command_fd, read_buffer, sizeof(read_buffer), 0) > 0)
        {
            std::cout << "SERVER received command " << std::string(read_buffer) << " from CLIENT (" << command_fd << ", " << data_fd << ")\n";
            send_buffer = commandHandler->runCommand(std::string(read_buffer));
            // std::cout << "Response: " << send_buffer << "\n";
            pthread_exit(NULL);
        }
    
        //ToDo: send send_buffer back to client (Also modify Client.cpp for receiving it)
    }

    pthread_exit(NULL);
}

void Server::run() {
    int data_fd, command_fd;
    char buffer[1024];

    command_fd = setupServer(COMMAND_PORT);
    data_fd = setupServer(DATA_PORT);
    std::cout << "server is ready" << std::endl;
    
    pthread_t threads[MAX_THREADS];
    int return_code;
    int thread_cnt = 0;

    while (true)
    {
        int command_fd_new = acceptClient(command_fd);
        int data_fd_new = acceptClient(data_fd);

        if (command_fd_new == -1 || data_fd_new == -1)
            std::cout << "ERROR in accepting connection from client" << std::endl;
        
        struct arg_struct args;
        args._tid = (int)thread_cnt;
        args._command_fd = (int)command_fd_new;
        args._data_fd = (int)data_fd_new;

        
        return_code = pthread_create(&threads[thread_cnt], NULL, &handleConnection, (void*)&args);
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
			printf("ERROR; return code from pthread_join() is %d\n", return_code);
			exit(-1);
		}
    }
}


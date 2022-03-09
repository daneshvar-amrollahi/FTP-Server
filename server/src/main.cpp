#include "Server.hpp"

using namespace std;

const int CONFIG_PATH_IDX = 1;

int main(int argc, char const *argv[]) {
    Server server = Server(argv[CONFIG_PATH_IDX]);
    server.run();
    return 0;
}
#include "User.hpp"

User::User(
        const std::string& username,
        const std::string& password,
        const int& download_capacity,
        const bool& admin
    ): 
        username(username), 
        password(password), 
        download_capacity(download_capacity),
        admin(admin) {

}

#ifndef chat_h
#define chat_h
#include "sha1.h"
#include <string>
#include "Authdata.h"
#include "hash.h"

#define SIZE 10

class Chat {
public:
    Chat();
    void reg(std::string _login, std::string _pwd);
    bool login(std::string _login, std::string _pwd);

    friend void test(Chat& c);
private:
    HashTable data;
};



#endif /* chat_h */

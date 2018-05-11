#include <iostream>

class myexception{
    public:
        myexception(){
            std::cout << "Throwing myexception" << std::endl;
        }
};

class read{
    public:
        char readmethod() throw (myexception){
            char c;
            std::cout << "Type-in (y/n)" << std::endl;
            std::cin >> c;
            if (c != 'y' && c!= 'n') {
                throw myexception();
            }
        }
};

int main() {
     char c;
     read r;
     try {
        c = r.readmethod();
     } catch(myexception) {
        std::cout << "Handling myexception\n";
        exit(1);
     }
     if (c=='y') {
        std::cout << "User typed yes." << std::endl;
     } else {
        std::cout << "User typed no." << std::endl;
     }
     return 0;
}

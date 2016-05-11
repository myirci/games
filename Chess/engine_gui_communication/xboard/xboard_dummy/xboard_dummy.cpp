#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <fstream>

int main(void) {

    std::string cmd{""}, first{""};
    bool flag{false};

    std::ofstream ofile("log.txt", std::ios::out);
    if(!ofile.is_open()) {
        std::cerr << "Log file could not be opened" << std::endl;
        return -1;
    }

    while(1) {

        std::getline(std::cin, cmd);
        std::istringstream is{cmd};
        is >> first;

        ofile << cmd << std::endl << std::flush;

        if(first == "xboard") {

        }
        else if(first == "new") {

        }
        else if(first == "random") {

        }
        else if(first == "level") {

        }
        else if(first == "post") {

        }
        else if(first == "hard") {

        }
        else if(first == "otim") {

        }
        else if(first == "time") {

        }
        else if(first == "force") {

        }
        else {
            if(flag) {
                std::cout << "move f6g8" << std::endl << std::flush;
                flag = false;
            }
            else {
                std::cout << "move g8f6" << std::endl << std::flush;
                flag = true;
            }
        }

     //   std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

    ofile.close();

    return 0;

}

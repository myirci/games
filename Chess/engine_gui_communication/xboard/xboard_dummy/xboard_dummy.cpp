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

        ofile << "Received\t: " << cmd << std::endl << std::flush;

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
        else if(first == "quit") {
            break;
        }
        else if(first.length() == 4) {
            if(flag) ofile.close();
            if(first[0] == 'a' || first[0] == 'b' || first[0] == 'c' || first[0] == 'd' || first[0] == 'e' || first[0] == 'f' || first[0] == 'g' || first[0] == 'h')
                if(first[1] == '1' || first[1] == '2' || first[1] == '3' || first[1] == '4' || first[1] == '5' || first[1] == '6' || first[1] == '7' || first[1] == '8')
                    if(first[2] == 'a' || first[2] == 'b' || first[2] == 'c' || first[2] == 'd' || first[2] == 'e' || first[2] == 'f' || first[2] == 'g' || first[2] == 'h')
                        if(first[3] == '1' || first[3] == '2' || first[3] == '3' || first[3] == '4' || first[3] == '5' || first[3] == '6' || first[3] == '7' || first[3] == '8') {
                            if(flag) {
                                ofile << "Send\t\t: move f6g8\n";
                                std::cout << "move f6g8\n"<< std::flush;
                                flag = false;
                            }
                            else {
                                ofile << "Send\t\t: move g8f6\n";
                                std::cout << "move g8f6\n"<< std::flush;
                                flag = true;
                            }
                        }
        }

        //   std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

    ofile.close();

    return 0;

}

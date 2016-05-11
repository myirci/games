#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(void)
{
	std::string cmd{""}, first{""};
	while(1) {
		
		std::getline(std::cin, cmd);
		std::istringstream is(cmd);
		is >> first;
		if(first == "isready")
			cout << "readyok\n";
			
		if(first == "quit")
				exit(1);
			
		if(first == "go") {
			
				if(count == 0)
				{
					cout << "bestmove b8a6\n";
					count = 1;
				}	
				else
				{
					cout << "bestmove a6b8\n";
					count = 0;
				}				
		}
	}
	return 0;
	
}

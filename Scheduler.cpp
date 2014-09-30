#include "Scheduler.h"

std::vector < std::vector < std::string > > Scheduler::parseFile(std::string filename) {
	std::vector < std::vector < std::string > > PCBS;
	//content of file
	std::ifstream file;
	//content of line
	std::string line;
	//words
	std::string data;

	int counter = 0;

	file.open(filename);
	if (file.is_open()) {
		while (!file.eof()) {
			PCBS.push_back(std::vector < std::string >());
			std::getline(file, line);
			std::istringstream word(line);
			while (word >> data) {
				PCBS[counter].push_back(data);
			}
			counter++;
		}
	}
	file.close();
	return PCBS;
}
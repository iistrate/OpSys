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
void Scheduler::addPCBS(std::string filename) {
	std::string name;
	int classtype;
	int priority;
	std::vector < std::vector < std::string > > PcbsInfo = parseFile(filename + ".txt");
	for (int i = 0; i < PcbsInfo.size(); i++) {
		//name, class, priority, memory, time remaining, time of arrival, percentage of cpu
		name = PcbsInfo[i][0];
		priority = atoi(PcbsInfo[i][2].c_str());
		classtype = PcbsInfo[i][1].compare("A") ? APPLICATION : SYSTEM_TYPE;
		m_Ready.insertPCBatEnd(m_Ready.setupPCB(name, priority, classtype));
	}
}
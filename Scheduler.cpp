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
	//
	//sort vector by shell sort
	std::vector < std::string > temp;
	//initially divide our length by 2; then each iteration half the gap
	for (int gap = PcbsInfo.size() / 2; gap != 0; gap /= 2) {
		//right side of array ++ < length
		for (int i = gap; i < PcbsInfo.size(); i++) {
			//left side of array ++ < beginning of right side
			for (int j = i - gap; j >= 0 && j < i && (atoi(PcbsInfo[j][5].c_str()) > atoi(PcbsInfo[j + gap][5].c_str())); j -= gap) {
				temp = PcbsInfo[j];
				PcbsInfo[j] = PcbsInfo[j + gap];
				PcbsInfo[j + gap] = temp;
			}
		}
	}
	// end shell sort
	//0 name, 1 class, 2 priority, 3 memory, 4 time remaining, 5 time of arrival, 6 percentage of cpu
	for (int i = 0; i < PcbsInfo.size(); i++) {
		name = PcbsInfo[i][0];
		priority = atoi(PcbsInfo[i][2].c_str());
		classtype = PcbsInfo[i][1].compare("A") ? APPLICATION : SYSTEM_TYPE;
		m_Ready.insertPCBatEnd(m_Ready.setupPCB(name, priority, classtype));
	}
}
//for (int i = 0; i < PcbsInfo.size(); i++) {
//	//0 name, 1 class, 2 priority, 3 memory, 4 time remaining, 5 time of arrival, 6 percentage of cpu
//	for (int j = 0; j < PcbsInfo.size(); j++) {
//		if (atoi(PcbsInfo[i][5].c_str()) < atoi(PcbsInfo[j][5].c_str())) {
//			name = PcbsInfo[i][0];
//			priority = atoi(PcbsInfo[i][2].c_str());
//			classtype = PcbsInfo[i][1].compare("A") ? APPLICATION : SYSTEM_TYPE;
//			m_Ready.insertPCBatEnd(m_Ready.setupPCB(name, priority, classtype));
//			break;
//		}
//	}
//}
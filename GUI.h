#ifndef GUI_H
#define GUI_H

#include "Image.h"
#include <vector>

class GUI {
private:
	int m_vectorY;
	int m_vectorX;

	std::vector <Image *> m_Images;
public:
	GUI();
	void buildPanel(int, int);
	void getImages(std::vector < Image* > &f_Images);
};

#endif // end GUI.h
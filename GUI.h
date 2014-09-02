#ifndef GUI_H
#define GUI_H

#include "Image.h"
#include <vector>

class GUI {
private:

	//size
	int m_vectorY;
	int m_vectorX;

	//position
	int m_ipanelx;
	int m_ipanely;

	//flags
	bool m_bvisible;

	std::vector <Image *> m_Images;
public:
	GUI(int h, int w, int x, int y);
	~GUI();

	void getImages(std::vector < Image* > &f_Images);

	int getX();
	int getY();
	void setX(int);
	void setY(int);

	bool isVisible();
	void setVisible(bool);
};

#endif // end GUI.h
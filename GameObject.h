#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Image.h"

class GameObject {
protected:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	Image* m_Image;

public:
	//setters
	void setY(int);
	void setX(int);
	void setW(int);
	void setH(int);
	//getters
	int getY();
	int getX();
	int getW();
	int getH();
	Image* getImage();
};

#endif // end GameObject.h
#include "GUI.h"
#include <iostream>
#include "Globals.h"

GUI::GUI(int h, int w, int x, int y): m_bvisible(true) {



	//size of vector, figure out how many tiles we need
	int tileHeight = 32;
	int tileWidth = 96;
	m_vectorY = h / tileHeight;
	m_vectorX = (w / tileWidth);

	int starting_x = x / tileWidth;
	int starting_y = y / tileHeight;
	int ending_y = m_vectorY + starting_y;
	int ending_x = m_vectorX + starting_x;

	//store position
	m_ipanelx = starting_x;
	m_ipanely = starting_y;

	//custom images for left panel
	for (int i = starting_y; i < ending_y; i++) {
		for (int j = starting_x; j < ending_x; j++) {
			//bordered left
			if (j == starting_x) {
				//top row
				if (i == starting_y) {
					m_Images.push_back(new Image("assets/sprites-ui.png", j * tileWidth, i * tileHeight, 32, 36, 34, 16, 2, 0, 0, 0, true));
				}
				//second row
				else if (i == starting_y + 1) {
					m_Images.push_back(new Image("assets/sprites-ui.png", j * tileWidth, i * tileHeight, 32, 36, 34, 53, 2, 0, 0, 0, true));
				}
				//bottom row
				else if (i == (ending_y - 1)) {
					m_Images.push_back(new Image("assets/sprites-ui.png", j * tileWidth, i * tileHeight, 32, 36, 34, 136, 2, 0, 0, 0, true));
				}
				//everything else
				else {
					m_Images.push_back(new Image("assets/sprites-ui.png", j * tileWidth, i * tileHeight, 32, 36, 34, 96, 2, 0, 0, 0, true));
				}
			}
			//bordered right
			else if (j == (ending_x - 1)) {
				//top row
				if (i == starting_y) {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, 32, 36, 176, 16, 2, 0, 0, 0, true));
				}
				//second row
				else if (i == starting_y + 1) {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, 32, 36, 176, 53, 2, 0, 0, 0, true));
				}
				//bottom row
				else if (i == (ending_y - 1)) {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, 32, 36, 176, 136, 2, 0, 0, 0, true));
				}
				//everything else
				else {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, 32, 36, 176, 96, 2, 0, 0, 0, true));
				}
			}
			//gray area 
			else {
				//top row
				if (i == starting_y) {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, tileWidth, tileHeight, 72, 16, 2, 0, 0, 0, true));
				}
				//second row
				else if (i == starting_y + 1) {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, tileWidth, tileHeight, 72, 53, 2, 0, 0, 0, true));
				}
				//bottom row
				else if (i == (ending_y - 1)) {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, tileWidth, tileHeight, 72, 136, 2, 0, 0, 0, true));
				}
				//everything else
				else {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, tileWidth, tileHeight, 72, 96, 2, 0, 0, 0, true));
				}
			}
		}
	}
	/*
	//add play btn
	m_Images.push_back(new Image("assets/sprites-ui.png", 125, 890, 20, 33, 438, 222, 3, 0, 0, 0, true));
	//add back btn
	m_Images.push_back(new Image("assets/sprites-ui.png", 75, 890, 33, 33, 320, 222, 3, 0, 0, 0, true));
	//add forward btn
	m_Images.push_back(new Image("assets/sprites-ui.png", 225, 890, 33, 33, 467, 222, 3, 0, 0, 0, true));
	//add pause btn
	m_Images.push_back(new Image("assets/sprites-ui.png", 175, 890, 22, 33, 399, 222, 3, 0, 0, 0, true));
	*/
}

void GUI::getImages(std::vector < Image* > &f_Images) {
	for (int i = 0; i < m_Images.size(); i++) {
		f_Images.push_back(m_Images[i]);
	}
}
int GUI::getX() {
	return m_ipanelx;
}
int GUI::getY() {
	return m_ipanely;
}
void GUI::setX(int x) {
	m_ipanelx = x;
}
void GUI::setY(int y) {
	m_ipanely = y;
}
bool GUI::isVisible() {
	return m_bvisible;
}
void GUI::setVisible(bool b) {
	m_bvisible = b;
}
int GUI::clicked(int x, int y) {
	//check menus
	//x is for all, only y changes
	if (x >= 485 && x <= 725) {
		//show version
		if (y >= 330 && y <= 350) {
			return CONTROLS::SHOW_VERSION;
		}
		//show date
		if (y >= 360 && y <= 380) {
			return CONTROLS::SHOW_DATE;
		}
		//show help
		if (y >= 390 && y <= 410) {
			return CONTROLS::SHOW_HELP;
		}
		//show directory
		if (y >= 420 && y <= 440) {
			return CONTROLS::SHOW_DIRECTORY;
		}
		//show debug mode
		if (y >= 450 && y <= 470) {
			return CONTROLS::DEBUG_MODE;
		}
		//quit
		if (y >= 480 && y <= 500) {
			return CONTROLS::QUIT;
		}
	}
	return 0;
}
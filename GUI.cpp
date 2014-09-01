#include "GUI.h"

GUI::GUI() {

}

void GUI::buildPanel(int h, int w) {

	//size of vector, figure out how many tiles we need
	int tileHeight = 32;
	int tileWidth = 96;
	m_vectorY = h / tileHeight;
	m_vectorX = (w / tileWidth) * 0.45;

	//custom images for left panel
	for (int i = 0; i < m_vectorY; i++) {
		for (int j = 0; j < m_vectorX; j++) {
			//bordered left
			if (j == 0) {
				//top row
				if (i == 0) {
					m_Images.push_back(new Image("assets/sprites-ui.png", j * tileWidth, i * tileHeight, 32, 36, 34, 16, 2, 0, 0, 0, true));
				}
				//second row
				else if (i == 1) {
					m_Images.push_back(new Image("assets/sprites-ui.png", j * tileWidth, i * tileHeight, 32, 36, 34, 53, 2, 0, 0, 0, true));
				}
				//bottom row
				else if (i == (m_vectorY - 1)) {
					m_Images.push_back(new Image("assets/sprites-ui.png", j * tileWidth, i * tileHeight, 32, 36, 34, 136, 2, 0, 0, 0, true));
				}
				//everything else
				else {
					m_Images.push_back(new Image("assets/sprites-ui.png", j * tileWidth, i * tileHeight, 32, 36, 34, 96, 2, 0, 0, 0, true));
				}
			}
			//bordered right
			else if (j == (m_vectorX - 1)) {
				//top row
				if (i == 0) {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, 32, 36, 176, 16, 2, 0, 0, 0, true));
				}
				//second row
				else if (i == 1) {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, 32, 36, 176, 53, 2, 0, 0, 0, true));
				}
				//bottom row
				else if (i == (m_vectorY - 1)) {
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
				if (i == 0) {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, tileWidth, tileHeight, 72, 16, 2, 0, 0, 0, true));
				}
				//second row
				else if (i == 1) {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, tileWidth, tileHeight, 72, 53, 2, 0, 0, 0, true));
				}
				//bottom row
				else if (i == (m_vectorY - 1)) {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, tileWidth, tileHeight, 72, 136, 2, 0, 0, 0, true));
				}
				//everything else
				else {
					m_Images.push_back(new Image("assets/sprites-ui.png", (j * tileWidth) - 66, i * tileHeight, tileWidth, tileHeight, 72, 96, 2, 0, 0, 0, true));
				}
			}
		}
	}
	//add play btn
	m_Images.push_back(new Image("assets/sprites-ui.png", 125, 890, 20, 33, 438, 222, 3, 0, 0, 0, true));
	//add back btn
	m_Images.push_back(new Image("assets/sprites-ui.png", 75, 890, 33, 33, 320, 222, 3, 0, 0, 0, true));
	//add forward btn
	m_Images.push_back(new Image("assets/sprites-ui.png", 225, 890, 33, 33, 467, 222, 3, 0, 0, 0, true));
	//add pause btn
	m_Images.push_back(new Image("assets/sprites-ui.png", 175, 890, 22, 33, 399, 222, 3, 0, 0, 0, true));

}
void GUI::getImages(std::vector < Image* > &f_Images) {
	for (int i = 0; i < m_Images.size(); i++) {
		f_Images.push_back(m_Images[i]);
	}
}
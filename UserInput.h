#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <SDL.h>
#include <string>
#include "Globals.h"

class UserInput {
private:
	SDL_Event event;

	int m_ipressed;
	std::string m_scommand;
	//mouse x and y
	int m_imouseX;
	int m_imouseY;

public:
	UserInput();
	~UserInput() {}
	
	std::string getStringCommand();

	void setStringCommand(std::string s);
	int getCommand();
	int getMouseX();
	int getMouseY();

};

#endif // end UserInput.h
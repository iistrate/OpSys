#include "UserInput.h"


UserInput::UserInput() : m_ipressed(0), m_imouseX(0), m_imouseY(0) {
}
int UserInput::getCommand() {
	SDL_StartTextInput();
	//poll for event
	if (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		//if key is pressed
		case SDL_TEXTINPUT:
			m_scommand += event.text.text;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				m_ipressed = QUIT;
				break;
			case SDLK_RETURN:
				m_scommand += "\n";
				break;
			case SDLK_DELETE:
				if (m_scommand.size() > 0) {
					m_scommand += "\\d";
				}
				break;
			case SDLK_BACKSPACE:
				if (m_scommand.size() > 0) {
					m_scommand += "\\d";
				}
				break;
			case SDLK_TAB:
				m_scommand += "    ";
				break;
			case SDLK_LCTRL:
				m_ipressed = CONTROLS::DEBUG_MODE;
				break;
			case SDLK_RCTRL:
				m_ipressed = CONTROLS::CPANEL;
				break;
			}
			break;
		//if key is released
		case SDL_KEYUP:
			m_ipressed = 0;
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&m_imouseX, &m_imouseY);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (SDL_BUTTON_RIGHT) {
				m_ipressed = RIGHT_CLICK;
				break;
			}
		case SDL_MOUSEBUTTONUP:
			m_ipressed = 0;
			break;
		//if pressed window close btn
		case SDL_QUIT:
			m_ipressed = QUIT;
			SDL_StopTextInput();
			break;
		}
	}
	return m_ipressed;
}

std::string UserInput::getStringCommand() {
	return m_scommand;
}
void UserInput::setStringCommand(std::string s) {
	m_scommand = s;
}
int UserInput::getMouseX() {
	return m_imouseX;
}
int UserInput::getMouseY() {
	return m_imouseY;
}

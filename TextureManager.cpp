#include "TextureManager.h"

TextureManager::TextureManager() :m_pTexture(0), m_pTextSurface(0), m_pfont(0), m_icamX(0), m_icamY(0),
									m_ilevelHeight(1800), m_ilevelWidth(2400), m_iscreenHeight(900), m_iscreenWidth(1200){}

void TextureManager::draw(SDL_Renderer* f_prenderer, std::vector < Image* > f_Images, SDL_RendererFlip f_flip) {
	//helper vars
	int cameraModifierX = (-1)* m_icamX;
	int cameraModifierY = (-1)* m_icamY;
	int origX = 0;
	int origY = 0;
	int currentFrame = 1;
	int totalFrames = 2;
	int width = 0;
	int height = 0;
	bool animated = false;
	bool flipped = false;

	const char* fname = "";
	//surface to texture loader
	for (std::vector < Image >::size_type i = 0; i != f_Images.size(); i++) {
		//speed up loading; only load image sprites once per image set; counter says 3 (which is good)
		if (fname != f_Images[i]->getFileName()) {
			fname = f_Images[i]->getFileName();
			m_pTexture = IMG_LoadTexture(f_prenderer, fname);
		}
		//image vars
		animated = f_Images[i]->isAnimated();
		flipped = f_Images[i]->isFlipped();
		width = f_Images[i]->getWidth();
		height = f_Images[i]->getHeight();
		currentFrame = f_Images[i]->getFrame();
		totalFrames = f_Images[i]->getTotalFrames();

		//see if image is flipped 
		if (flipped) {
			f_flip = SDL_FLIP_HORIZONTAL;
		}
		else {
			f_flip = SDL_FLIP_NONE;
		}

		//width and height of image
		m_srcRect.w = m_dstRect.w = width;
		m_srcRect.h = m_dstRect.h = height;
		
		m_srcRect.x = f_Images[i]->isAnimated() ? f_Images[i]->getSpriteX() + (currentFrame * width) : f_Images[i]->getSpriteX();
		m_srcRect.y = f_Images[i]->getSpriteY();


		origX = f_Images[i]->getX();
		origY = f_Images[i]->getY();
		//where to draw at
		m_dstRect.x = f_Images[i]->isStatic() ? origX : origX + cameraModifierX;
		m_dstRect.y = f_Images[i]->isStatic() ? origY : origY + cameraModifierY;

		//magic
		SDL_RenderCopyEx(f_prenderer, m_pTexture, &m_srcRect, &m_dstRect, NULL, NULL, f_flip);

		//see if it is animated
		if (animated) {
			//figure out next frame
			currentFrame = currentFrame + 1 == totalFrames ? 1 : currentFrame + 1;
			//set frame
			f_Images[i]->setCurrentFrame(currentFrame);
			f_Images[i]->animate(false);
		}
	}
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = NULL;
}
void TextureManager::drawText(SDL_Renderer* f_prenderer, std::string s, int x, int y, int wrap, bool showCursor) {
	//set font size
	int fontSize = 16;
	//initalize font
	initFont(fontSize);
	//get line height
	int fontLineSkip = TTF_FontLineSkip(m_pfont);

	//will hold individual lines of strings
	std::vector < std::string > Strings;

	//set color
	SDL_Color tmpfontcolor = { 1, 1, 1, 1 };

	//will hold npos for '/n'
	std::size_t foundCharAt = 0;
	//while we can find new lines
	while (foundCharAt != -1) {
		//create string that will hold cleaned string
		std::string tempString;
		//find occurence of a new line character
		foundCharAt = s.find('\n', 0);
		//break off substring and add to vector of strings
		tempString = s.substr(0, foundCharAt);
		if (foundCharAt != -1) {
			s = s.substr(foundCharAt + 1, -1);
		}
		//add substring to vector of strings
		Strings.push_back(tempString);
	}

	//where to wrap text if user chooses to write essay :P
	Uint32 lineWrap = wrap;

	//original x and y as passed through function
	int yPos = y;
	int xPos = x;

	//turn number gets increased each time function is called
	int static turn = 0;
	for (int i = 0; i < Strings.size(); i++) {
		//if last string/last char, and you want to show cursor, and turn is divisible by 13; add cursor to end of string
		if (i == (Strings.size() - 1) && showCursor && (turn % 13)) {
			Strings[i] += "¶";
		}
		//from string to c string
		m_pcstr = Strings[i].c_str();
		//add each line to surface
		m_pTextSurface = TTF_RenderText_Blended_Wrapped(m_pfont, m_pcstr, tmpfontcolor, lineWrap);
		//add surface to texture
		m_pTexture = SDL_CreateTextureFromSurface(f_prenderer, m_pTextSurface);
		//free surface
		SDL_FreeSurface(m_pTextSurface);
		m_pTextSurface = NULL;
		//figure out width and height
		SDL_QueryTexture(m_pTexture, 0, 0, &m_srcRect.w, &m_srcRect.h);
		//where to draw at
		m_dstRect.x = xPos;
		m_dstRect.y = yPos + (fontLineSkip*i);
		//width and height of text
		m_dstRect.w = m_srcRect.w;
		m_dstRect.h = m_srcRect.h;
		//magic
		SDL_RenderCopy(f_prenderer, m_pTexture, NULL, &m_dstRect);
	}
	turn++;
	//free resources
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = NULL;
	TTF_CloseFont(m_pfont);
	m_pfont = NULL;
}
int TextureManager::getFontWidth() {
	return m_ifontWidth;
}
//on destroy
TextureManager::~TextureManager() {
	//font cleanup
	TTF_Quit();
}
//which layer to be drawn on top z-index style
void TextureManager::sortByLayer(std::vector < Image* > f_Images) {
	for (std::vector < Image >::size_type i = 0; i < f_Images.size(); i++) {
		//std::cout << f_Images[i]->getLayer() << std::endl;
		void;
	}
}
//initialize font
void TextureManager::initFont(int fz) {
	if (TTF_Init() == -1) {
		std::cout << "Fonts failed to initialize" << std::endl;
	}
	else {
		m_pfont = TTF_OpenFont("assets/arounded.ttf", fz);
		//get font width
		m_ifontWidth = TTF_GetFontOutline(m_pfont);
	}
}
//set camera x position
void TextureManager::setCamX(int i) {
	m_icamX = i;
}
//set camera y position
void TextureManager::setCamY(int i) {
	m_icamY = i;
}
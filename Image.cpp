#include "Image.h"

Image::Image() :m_banimated(false), m_bflipped(false), m_bstatic(false) {
}
Image::~Image() {
}
Image::Image(const char* fname, int x, int y, int width, int height, int sX, int sY, int layer, bool a, int cf, int tf, bool f_static) : m_bflipped(false) {
	m_sfname = fname;
	m_ix = x;
	m_iy = y;
	m_iwidth = width;
	m_iheight = height;
	m_ispriteX = sX;
	m_ispriteY = sY;
	m_ilayer = layer;
	m_banimated = a;
	m_icurrentFrame = cf;
	m_itotalFrames = tf;
	m_bstatic = f_static;
}
//setters
void Image::load(const char* fname, int x, int y, int width, int height, int sX, int sY, int layer, bool a, int cf, int tf, bool f_static) {
	m_sfname = fname;
	m_ix = x;
	m_iy = y;
	m_iwidth = width;
	m_iheight = height;
	m_ispriteX = sX;
	m_ispriteY = sY;
	m_ilayer = layer;
	m_banimated = a;
	m_icurrentFrame = cf;
	m_itotalFrames = tf;
}
void Image::setX(int x) {
	m_ix = x;
}
void Image::setY(int y) {
	m_iy = y;
}
void Image::setFlipped(bool b) {
	m_bflipped = b;
}
void Image::setCurrentFrame(int i) {
	m_icurrentFrame = i;
}
void Image::setStatic(bool b) {
	m_bstatic = b;
}


//getters
bool Image::isFlipped() {
	return m_bflipped;
}
int Image::getX() {
	return m_ix;
}
int Image::getY() {
	return m_iy;
}
int Image::getWidth() {
	return m_iwidth;
}
int Image::getHeight() {
	return m_iheight;
}
int Image::getLayer() {
	return m_ilayer;
}
bool Image::isAnimated() {
	return m_banimated;
}
int Image::getFrame() {
	return m_icurrentFrame;
}
int Image::getTotalFrames() {
	return m_itotalFrames;
}
const char* Image::getFileName() {
	return m_sfname;
}
int Image::getSpriteX() {
	return m_ispriteX;
}
int Image::getSpriteY() {
	return m_ispriteY;
}
bool Image::isStatic() {
	return m_bstatic;
}
void Image::animate(bool b) {
	m_banimated = b;
}
#include "tower.h"

tower::tower() {

}

tower::tower(std::string type): type(type) {

}

tower::~tower() {

}

std::string tower::GetType() {
	return type;
}
std::string tower::GetBasePicPath() {
	return basepicpath;
}
std::string tower::GetBarrelPicPath() {
	return barrelpicpath;
}

void tower::loadPic() {
	LoadBitmapByString({ basepicpath }, RGB(255, 255, 255));
}
void tower::show(int scale) {
	ShowBitmap(scale);
}
void tower::resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY,int x,int y) {
	SetTopLeft(int(LEFT + moveX + x * TILE_SIZE*scale), int(TOP + moveY + y * TILE_SIZE*scale));
}

void tower::SetType(std::string type) {
	this->type = type;
}
void tower::SetBasePicPath(std::string basepicpath) {
	this->basepicpath = basepicpath;
}
void tower::SetBarrelPicPath(std::string barrelpicpath) {
	this->barrelpicpath = barrelpicpath;
}
#include "stdafx.h"
#include "tower.h"

tower::tower() {
	type = "None";
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
std::string tower::GetTowerName() {
	return towerName;
}
void tower::loadPic() {
	LoadBitmapByString({ basepicpath }, RGB(255, 255, 255));
	Barrel->loadPic();
}
void tower::show(double scale) {
	ShowBitmap(scale);
	Barrel->show(scale);
}
void tower::resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY,int x,int y) {
	SetTopLeft(int(LEFT + moveX + x * TILE_SIZE*scale), int(TOP + moveY + y * TILE_SIZE*scale));
	Barrel->resetShow(TOP,LEFT,TILE_SIZE,scale,moveX,moveY, x,y);
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
void tower::SetTowerName(std::string towerName) {
	this->towerName = towerName;
}
emptytower::emptytower() {

}
////////////////////////////////basictower////////////////////////////

basictower::basictower() {
	SetType("basictower");
	SetBasePicPath("resources/Base_Basic.bmp");
	SetTowerName("°ò¥»");
	Barrel = std::make_shared<basicBarrel>();
}
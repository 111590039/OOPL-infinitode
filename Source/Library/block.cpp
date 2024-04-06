#include "stdafx.h"
#include "block.h"
////////////////////////////////block////////////////////////////
block::block(int x, int y):x(x),y(y) {

}

void block::OnClick() {

}

int block::GetX() {
	return x;
}
int block::GetY() {
	return y;
}
std::string block::GetType() {
	return type;
}
std::string block::GetTitle() {
	return title;
}
std::string block::GetDescribe() {
	return describe;
}
std::string block::GetPicPath() {
	return picPath;
}

void block::SetXY(int x, int y) {
	this->x = x;
	this->y = y;
}

void block::SetType(std::string type) {
	this->type = type;
}
void block::SetTitle(std::string title) {
	this->title = title;
}
void block::SetDescribe(std::string describe) {
	this -> describe = describe;
}
void block::SetPicPath(std::string picPath) {
	this -> picPath = picPath;
}
void block::loadPic() {
	LoadBitmapByString({ picPath }, RGB(255, 255, 255));
}
void block::show(double scale) {
	ShowBitmap(scale);
}
void block::resetShow(int TOP, int LEFT, int TILE_SIZE, double scale,int moveX,int moveY) {
	SetTopLeft(int(LEFT + moveX + x *TILE_SIZE*scale), int(TOP + moveY + y *TILE_SIZE*scale));
}
bool block::ifClickOn(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY, int tarX, int tarY) {
	if (int(LEFT + moveX + x * TILE_SIZE*scale) + TILE_SIZE * scale >= tarX && tarX >= int(LEFT + moveX + x * TILE_SIZE*scale)) {
		if (int(TOP + moveY + y * TILE_SIZE*scale) + TILE_SIZE * scale >= tarY && tarY >= int(TOP + moveY + y * TILE_SIZE*scale)) {
			return true;
		}
	}
	return false;
}
////////////////////////////////tile////////////////////////////
tile::tile(int x, int y):block(x,y) {
	SetTitle("空地");
	SetDescribe("可以在上面建造塔");
	SetType("tile");
	SetPicPath("resources/tile.bmp");
	Tower = make_shared<emptytower>();
}
bool tile::haveTower() {
	if (Tower->GetType().compare("None")) {
		return true;
	}
	return false;
}
void tile::OnClick() {

}
void tile::buildTower(std::shared_ptr<tower> Tower) {
	this->Tower = Tower;
	Tower->loadPic();
}
int tile::sellTower() {
	return 0;
}
void tile::loadPic() {
	LoadBitmapByString({ GetPicPath() }, RGB(255, 255, 255));
	if (haveTower()) {
		Tower->loadPic();
	}
}
void tile::show(double scale) {
	ShowBitmap(scale);
	if (haveTower()) {
		Tower->show(scale);
	}
}
void tile::resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY) {
	SetTopLeft(int(LEFT + moveX + GetX() * TILE_SIZE*scale), int(TOP + moveY + GetY() * TILE_SIZE*scale));
	if (haveTower()) {
		Tower->resetShow(TOP,LEFT,TILE_SIZE,scale,moveX,moveY,GetX(),GetY());
	}

}
std::shared_ptr<tower> tile::GetTower() {
	return Tower;
}
////////////////////////////////road////////////////////////////
road::road(int x, int y) :block(x, y) {
	SetTitle("道路");
	SetDescribe("敵人會沿著道路移動至基地");
	SetType("road");
	SetPicPath("resources/road.bmp");
}
void road::OnClick(){

}
////////////////////////////////base////////////////////////////
base::base(int x, int y) :block(x, y) {
	SetTitle("基地");
	SetDescribe("保護它免受敵人攻擊");
	SetType("base");
	SetPicPath("resources/base.bmp");
}
void base::OnClick(){

}
////////////////////////////////portal////////////////////////////
portal::portal(int x, int y,double difficult) :block(x, y) {
	SetTitle("傳送門");
	SetDescribe("敵人會從傳送門出現");
	SetType("portal");
	SetPicPath("resources/portal.bmp");
}
void portal::OnClick(){

}
double portal::GetDifficult() {
	return difficult;
}
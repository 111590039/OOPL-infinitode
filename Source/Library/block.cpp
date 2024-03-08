#include "stdafx.h"
#include "block.h"

////////////////////////////////block////////////////////////////
block::block(int x, int y):x(x),y(y) {

}

void block::OnClick() {

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
////////////////////////////////tile////////////////////////////
tile::tile(int x, int y):block(x,y) {
	SetTitle("空地");
	SetDescribe("可以在上面建造塔");
	SetType("tile");
	SetPicPath("");
}
bool tile::haveTower() {

}
void tile::OnClick() {

}
////////////////////////////////road////////////////////////////
road::road(int x, int y) :block(x, y) {
	SetTitle("道路");
	SetDescribe("敵人會沿著道路移動至基地");
	SetType("road");
	SetPicPath("");
}
void road::OnClick(){

}
////////////////////////////////base////////////////////////////
base::base(int x, int y) :block(x, y) {
	SetTitle("基地");
	SetDescribe("基地被敵人攻擊時會扣血，血量扣完時遊戲結束");
	SetType("base");
	SetPicPath("");
}
void base::OnClick(){

}
////////////////////////////////portal////////////////////////////
portal::portal(int x, int y,double difficult) :block(x, y) {
	SetTitle("傳送門");
	SetDescribe("敵人會從傳送門出現");
	SetType("portal");
	SetPicPath("");
}
void portal::OnClick(){

}
double portal::GetDifficult() {
	return difficult;
}
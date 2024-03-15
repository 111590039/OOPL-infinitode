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
////////////////////////////////tile////////////////////////////
tile::tile(int x, int y):block(x,y) {
	SetTitle("�Ŧa");
	SetDescribe("�i�H�b�W���سy��");
	SetType("tile");
	SetPicPath("resources/tile.bmp");
}
bool tile::haveTower() {
	//
	return false;
}
void tile::OnClick() {

}
////////////////////////////////road////////////////////////////
road::road(int x, int y) :block(x, y) {
	SetTitle("�D��");
	SetDescribe("�ĤH�|�u�۹D�����ʦܰ�a");
	SetType("road");
	SetPicPath("resources/road.bmp");
}
void road::OnClick(){

}
////////////////////////////////base////////////////////////////
base::base(int x, int y) :block(x, y) {
	SetTitle("��a");
	SetDescribe("��a�Q�ĤH�����ɷ|����A��q�����ɹC������");
	SetType("base");
	SetPicPath("resources/base.bmp");
}
void base::OnClick(){

}
////////////////////////////////portal////////////////////////////
portal::portal(int x, int y,double difficult) :block(x, y) {
	SetTitle("�ǰe��");
	SetDescribe("�ĤH�|�q�ǰe���X�{");
	SetType("portal");
	SetPicPath("resources/portal.bmp");
}
void portal::OnClick(){

}
double portal::GetDifficult() {
	return difficult;
}
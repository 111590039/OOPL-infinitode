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
	SetTitle("�Ŧa");
	SetDescribe("�i�H�b�W���سy��");
	SetType("tile");
	SetPicPath("");
}
bool tile::haveTower() {

}
void tile::OnClick() {

}
////////////////////////////////road////////////////////////////
road::road(int x, int y) :block(x, y) {
	SetTitle("�D��");
	SetDescribe("�ĤH�|�u�۹D�����ʦܰ�a");
	SetType("road");
	SetPicPath("");
}
void road::OnClick(){

}
////////////////////////////////base////////////////////////////
base::base(int x, int y) :block(x, y) {
	SetTitle("��a");
	SetDescribe("��a�Q�ĤH�����ɷ|����A��q�����ɹC������");
	SetType("base");
	SetPicPath("");
}
void base::OnClick(){

}
////////////////////////////////portal////////////////////////////
portal::portal(int x, int y,double difficult) :block(x, y) {
	SetTitle("�ǰe��");
	SetDescribe("�ĤH�|�q�ǰe���X�{");
	SetType("portal");
	SetPicPath("");
}
void portal::OnClick(){

}
double portal::GetDifficult() {
	return difficult;
}
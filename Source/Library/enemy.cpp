#include "stdafx.h"
#include "enemy.h"
enemy::enemy(std::string type, double health, double speed, double bounty, double exp) : type(type), health(health), speed(speed), bounty(bounty), exp(exp){

}
std::string enemy::GetType() {
	return type;
}
double enemy::Gethealth() {
	return health;
}
double enemy::Getspeed() {
	return speed;
}
double enemy::Getbounty() {
	return bounty;
}
double enemy::Getexp() {
	return exp;
}
void enemy::SetXY(int x, int y) {
	this->x = x;
	this->y = y;
}
void enemy::show(double scale) {
	ShowBitmap(scale);
}
void enemy::SetType(std::string type) {
	this->type = type;
}
void enemy::SetPicPath(std::string picPath) {
	this->picPath = picPath;
}
std::string enemy::GetPicPath() {
	return picPath;
}
Regular::Regular(std::string type, double health, double speed, double bounty, double exp) : enemy(type, health, speed, bounty, exp) {
	SetPicPath("resources/enemy_Regular.bmp");
}

void Regular::loadPic() {
	LoadBitmapByString({ GetPicPath() }, RGB(255, 255, 255));
}

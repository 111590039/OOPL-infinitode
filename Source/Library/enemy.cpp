#include "stdafx.h"
#include "enemy.h"
enemy::enemy(double difficulty, int wave, std::vector<CPoint> enemyPath):enemyPath(enemyPath){
	SetX(1.5);
	SetY(0.5);
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
double enemy::GetX() {
	return x;
}
double enemy::GetY() {
	return y;
}
void enemy::SetType(std::string type) {
	this->type = type;
}
void enemy::Sethealth(double health) {
	this->health = health;
}
void enemy::Setspeed(double speed) {
	this->speed = speed;
}
void enemy::Setbounty(double bounty) {
	this->bounty = bounty;
}
void enemy::Setexp(double exp) {
	this->exp = exp;
}
void enemy::SetX(double x) {
	this->x = x;
}
void enemy::SetY(double y) {
	this->y = y;
}
void enemy::show(double scale) {
	ShowBitmap(scale);
}
void enemy::SetPicPath(std::string picPath) {
	this->picPath = picPath;
}
std::string enemy::GetPicPath() {
	return picPath;
}
bool enemy::enemyMove(double time) {
	if (int(y) < abs(enemyPath[targetPos].y)){
		y += time * speed;
	}
	else if (int(y) > abs(enemyPath[targetPos].y)) {
		y -= time * speed;
	}
	else if (int(x) < abs(enemyPath[targetPos].x)) {
		x += time * speed;
	}
	else if (int(x) > abs(enemyPath[targetPos].x)) {
		x -= time * speed;
	}
	else {
		if (targetPos == (int)enemyPath.size() - 1) {
			return true;
		}
		targetPos++;
	}
	return false;
}
Regular::Regular(double difficulty, int wave, std::vector<CPoint> enemyPath) : enemy(difficulty, wave, enemyPath) {
	Sethealth(100.0);
	Setspeed(1.0);
	Setbounty(1.0);
	Setexp(1.0);
	SetPicPath("resources/enemy_Regular.bmp");
}

void Regular::loadPic() {
	LoadBitmapByString({ GetPicPath() }, RGB(255, 255, 255));
}

void enemy::resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY) {
	SetTopLeft(int(LEFT + moveX + GetX() * TILE_SIZE*scale), int(TOP + moveY + GetY()* TILE_SIZE*scale));
}
#include "stdafx.h"
#include "bullet.h"
#include <cmath>

#define PI 3.1415926
bullet::bullet() {

}
void bullet::SetXY(double x, double y) {
	this->x = x;
	this->y = y;
}
void bullet::SetTarXY(double x, double y) {
	tarX = x;
	tarY = y;
}
void bullet::SetPicPath(std::string picPath) {
	this->picPath = picPath;
}
void bullet::SetSpeed(double speed) {
	this->speed = speed;
}
void bullet::loadPic() {
	LoadBitmapByString({ picPath }, RGB(255, 255, 255));
}
void bullet::show(double scale) {
	ShowBitmap(scale);
}
void bullet::resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY) {
	SetTopLeft(int(LEFT + moveX + x * TILE_SIZE*scale), int(TOP + moveY + y * TILE_SIZE*scale));
}
void bullet::move(double time) {
	double r = sqrt(pow(tarX-x,2)+ pow(tarY-y,2));
	double angleX = (tarX - x) / r;
	double angleY = (tarY - y) / r;
	if (abs(speed * time * angleX) < abs(tarX - x)) {
		x = x + speed * time * angleX;
	}
	else {
		x = tarX;
	}
	if (abs(speed * time * angleY) < abs(tarY - y)) {
		y = y + speed * time * angleY;
	}
	else {
		y = tarY;
	}

}
////////////////////////////////basicbullet////////////////////////////
basicbullet::basicbullet() {
	SetPicPath("resources/enemy_Air.bmp");
	SetSpeed(1.0);
	SetTarXY(5, 10);
}
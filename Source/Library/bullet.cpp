#include "stdafx.h"
#include "bullet.h"
#include <cmath>

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
void bullet::SetTarget(std::shared_ptr<enemy> target) {
	this->target = target;
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
	if (target != nullptr) {
		double enemyX = target->GetX();
		double enemyY = target->GetY();
		if (enemyX >= -1 && enemyY >= -1) {
			tarX = enemyX;
			tarY = enemyY;
		}
	}
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
bool bullet::IsPathOver() {
	if (x == tarX && y == tarY) {
		return true;
	}
	return false;
}
////////////////////////////////basicbullet////////////////////////////
basicbullet::basicbullet() {
	SetPicPath("resources/basic_bullet.bmp");
	SetSpeed(1.0);
	
}
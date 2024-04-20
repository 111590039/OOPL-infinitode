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
void tower::showBullets(double scale) {
	for (std::shared_ptr<bullet> b : Bullets) {
		b->show(scale);
	}
}
void tower::resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY,int x,int y) {
	SetTopLeft(int(LEFT + moveX + x * TILE_SIZE*scale), int(TOP + moveY + y * TILE_SIZE*scale));
	Barrel->resetShow(TOP,LEFT,TILE_SIZE,scale,moveX,moveY, x,y);
	for (std::shared_ptr<bullet> b : Bullets) {
		b->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
}
void tower::SetTarget(std::shared_ptr<enemy> target) {
	this->target = target;
}
void tower::newBullet(std::shared_ptr<bullet> bullet) {
	bullet->loadPic();
	Bullets.push_back(bullet);
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
std::shared_ptr<enemy> tower::GetTarget() {
	return target;
}
void tower::move(double time, double x, double y) {
	/*
	//子彈移動
	for (std::shared_ptr<bullet> b : Bullets) {
		b->move(time);
	}
	//刪除已用完的子彈
	for (size_t i = 0; i < Bullets.size(); i++) {
		if (Bullets[i]->IsPathOver()) {
			Bullets.erase(Bullets.begin() + i);
		}
	}
	*/
}
emptytower::emptytower() {

}
////////////////////////////////basictower////////////////////////////

basictower::basictower() {
	SetType("basictower");
	SetBasePicPath("resources/Base_Basic.bmp");
	SetTowerName("基本");
	Barrel = std::make_shared<basicBarrel>();
	coolDown = 1 / attackSpeed;
	range = 2.0;
}
void basictower::move(double time,double x, double y) {
	if (coolDown == 0) {
		std::shared_ptr<basicbullet> Bullet = std::make_shared<basicbullet>();
		Bullet->SetTarget(GetTarget());
		Bullet->SetXY(x+0.5, y+0.5);
		Bullet->SetSpeed(projectileSpeed);
		if (target != nullptr) {
			newBullet(Bullet);
			coolDown = 1 / attackSpeed;
		}
	}
	else {
		coolDown = max(0, coolDown - time);
	}
	//子彈移動
	for (std::shared_ptr<bullet> b : Bullets) {
		b->move(time);
	}
	//刪除已用完的子彈
	for (size_t i = 0; i < Bullets.size(); i++) {
		if (Bullets[i]->IsPathOver()) {
			Bullets.erase(Bullets.begin() + i);
		}
	}
}
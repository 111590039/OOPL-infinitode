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
std::vector<int> tower::GetUpgradeLevel() {
	return upgradeLevel;
}
std::vector<int> tower::GetUpgradeIcon() {
	return upgradeIcons;
}
std::vector<int> tower::GetUpgradeCost() {
	return { 0,0,0,0 };
}
std::vector<std::string>  tower::GetAttributeName() {
	return {};
}
std::vector<std::string>  tower::GetAttributeValue() {
	return {};
}
std::vector<std::vector<double>> tower::GetAffected(int type) {
	return {};
}
int tower::GetTotalCost() {
	return totalCost;
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
void tower::upgrade1() {
	return;
}
void tower::upgrade2() {
	return;
}
void tower::upgrade3() {
	return;
}
void tower::upgrade4() {
	return;
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
void tower::move(double time, double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
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
////////////////////////////////emptytower////////////////////////////
emptytower::emptytower() {

}
double emptytower::GetRange() {
	return 0;
}
////////////////////////////////basictower////////////////////////////

basictower::basictower() {
	SetType("basictower");
	SetBasePicPath("resources/Base_Basic.bmp");
	SetTowerName("基本");
	upgradeIcons = { 0,1,2,3 };
	Barrel = std::make_shared<basicBarrel>();
	range = 2.0;
	damage = 2.3;
	attackSpeed = 1.1; //攻擊次數/每秒
	rotataionSpeed = 90; //旋轉速度/每秒 (還沒實作)
	projectileSpeed = 3.0;
	coolDown = 1 / attackSpeed;
	totalCost = 40;
}
void basictower::move(double time,double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	coolDown = max(0, coolDown - time);
	if (coolDown == 0) {
		if (target != nullptr) {
			std::shared_ptr<basicbullet> Bullet = std::make_shared<basicbullet>();
			Bullet->SetTarget(GetTarget());
			Bullet->SetXY(x + 0.5, y + 0.5);
			Bullet->SetSpeed(projectileSpeed);
			Bullet->SetDamage(damage);
			newBullet(Bullet);
			coolDown = 1 / attackSpeed;
		}
	}
	//子彈移動
	for (std::shared_ptr<bullet> b : Bullets) {
		b->move(time);
	}
	//刪除已用完的子彈
	for (size_t i = 0; i < Bullets.size(); i++) {
		if (Bullets[i]->IsPathOver()) {
			if (GetTarget() != nullptr) {
				GetTarget()->GetDamage(Bullets[i]->GetDamage());
			}
			Bullets.erase(Bullets.begin() + i);
		}
	}
}
double basictower::GetRange(){
	return range;
}
std::vector<int> basictower::GetUpgradeCost() {
	std::vector<int> result;
	for (int i = 0; i < 4; i++) {
		if (upgradeLevel[i] != 10) {
			result.push_back(upgradeCost[i][upgradeLevel[i]]);
		}
		else {
			result.push_back(99999999);
		}
	}
	return result;
}
std::vector<std::string> basictower::GetAttributeName() {
	return { "範圍" ,"傷害","攻擊速度","旋轉速度","彈丸速度","#傷害倍數"};
}
std::vector<std::string> basictower::GetAttributeValue() {
	std::vector<std::string> result = {};
	result.push_back(std::to_string(this->range));
	result.push_back(std::to_string(this->damage));
	result.push_back(std::to_string(this->attackSpeed) + "/s");
	result.push_back(std::to_string(this->rotataionSpeed) + "/s");
	result.push_back(std::to_string(this->projectileSpeed));
	result.push_back("x1.00");
	return result;
}
std::vector<std::vector<double>> basictower::GetAffected(int type) {
	//type是升級選項 1/2/3/4 回傳{影響第幾項屬性,影響值}
	if (type == 1) {
		return { {0,rangeUpgrade.at(upgradeLevel[0])} };
	}
	else if (type == 2) {
		return { {1,damageUpgrade.at(upgradeLevel[1])} };
	}
	else if (type == 3) {
		return { {2,attackSpeedUpgrade.at(upgradeLevel[2])} };
	}
	else if (type == 4) {
		return { {3,rotataionSpeedUpgrade.at(upgradeLevel[3])},{4,projectileSpeedUpgrade.at(upgradeLevel[3])} };
	}
	return {};
}
void basictower::upgrade1() {
	range += rangeUpgrade.at(upgradeLevel[0]);
	totalCost += upgradeCost[0].at(upgradeLevel[0]);
	upgradeLevel[0] += 1;
}
void basictower::upgrade2() {
	damage += damageUpgrade.at(upgradeLevel[1]);
	totalCost += upgradeCost[1].at(upgradeLevel[1]);
	upgradeLevel[1] += 1;
}
void basictower::upgrade3() {
	attackSpeed += attackSpeedUpgrade.at(upgradeLevel[2]);
	totalCost += upgradeCost[2].at(upgradeLevel[2]);
	upgradeLevel[2] += 1;
}
void basictower::upgrade4() {
	rotataionSpeed += rotataionSpeedUpgrade.at(upgradeLevel[3]);
	projectileSpeed += projectileSpeedUpgrade.at(upgradeLevel[3]);
	totalCost += upgradeCost[3].at(upgradeLevel[3]);
	upgradeLevel[3] += 1;
}
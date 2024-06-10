#include "stdafx.h"
#include "minigun.h"

minigun::minigun() {
	SetType("minigun");
	SetBasePicPath("resources/Base_minigun.bmp");
	SetTowerName("機關槍");
	upgradeIcons = { 0,1,2,9 };
	Barrel = std::make_shared<minigunBarrel>();
	range = 2.8;
	damage = 3.2;
	maxAttackSpeed = 3.8;
	attackSpeed = 0.76; //20%
	rotationSpeed = 80;
	attacktime = 0;
	speedUpTime = 7;
	coolDown = 1 / attackSpeed;
	last_target = nullptr;
	totalCost = 160;
}
void minigun::move(double time, double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	findTarget(x, y, Enemy);
	if (target == last_target && target != nullptr) {
		attackSpeed = min(maxAttackSpeed, attackSpeed + 0.8*maxAttackSpeed * time / speedUpTime);
	}
	else {
		attackSpeed = max(maxAttackSpeed * 0.2, attackSpeed - 0.8*maxAttackSpeed * time / 3.5);
	}
	coolDown = max(0, coolDown - time);
	if (coolDown == 0 && target != nullptr) {
		std::shared_ptr<minigunbullet> Bullet = std::make_shared<minigunbullet>();
		Bullet->SetTarget(GetTarget());
		Bullet->SetXY(x + 0.5, y + 0.5);
		Bullet->SetSpeed(50);
		Bullet->SetDamage(damage);
		newBullet(Bullet);
		coolDown = 1 / attackSpeed;
	}
	//子彈移動
	for (std::shared_ptr<bullet> b : Bullets) {
		b->move(time);
	}
	//刪除已用完的子彈
	for (size_t i = 0; i < Bullets.size(); i++) {
		if (Bullets[i]->IsPathOver()) {
			if (Bullets[i]->GetTarget() != nullptr) {
				Bullets[i]->GetTarget()->GetDamage(Bullets[i]->GetDamage());
			}
			Bullets.erase(Bullets.begin() + i);
		}
	}
	last_target = target;
}
double minigun::GetRange() {
	return range;
}
std::vector<int> minigun::GetUpgradeCost() {
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
std::vector<std::string> minigun::GetAttributeName() {
	return { "範圍" ,"傷害","攻擊速度","旋轉速度","#加速時間" };
}
std::vector<std::string> minigun::GetAttributeValue() {
	std::vector<std::string> result = {};
	result.push_back(std::to_string(this->range));
	result.push_back(std::to_string(this->damage));
	result.push_back(std::to_string(this->maxAttackSpeed) + "/s");
	result.push_back(std::to_string(this->rotationSpeed) + "/s");
	result.push_back(std::to_string(this->speedUpTime) + "s");
	return result;
}
std::vector<std::vector<double>> minigun::GetAffected(int type) {
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
		return { {3,rotationSpeedUpgrade.at(upgradeLevel[3])} };
	}
	return {};
}
void minigun::upgrade1() {
	range += rangeUpgrade.at(upgradeLevel[0]);
	totalCost += upgradeCost[0].at(upgradeLevel[0]);
	upgradeLevel[0] += 1;
}
void minigun::upgrade2() {
	damage += damageUpgrade.at(upgradeLevel[1]);
	totalCost += upgradeCost[1].at(upgradeLevel[1]);
	upgradeLevel[1] += 1;
}
void minigun::upgrade3() {
	maxAttackSpeed += attackSpeedUpgrade.at(upgradeLevel[2]);
	totalCost += upgradeCost[2].at(upgradeLevel[2]);
	upgradeLevel[2] += 1;
}
void minigun::upgrade4() {
	rotationSpeed += rotationSpeedUpgrade.at(upgradeLevel[3]);
	totalCost += upgradeCost[3].at(upgradeLevel[3]);
	upgradeLevel[3] += 1;
}
void minigun::findTarget(double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	bool findTarget = false;
	for (std::shared_ptr<enemy> e : Enemy) {
		if (sqrt(pow(x + 0.5 - e->GetX(), 2) + pow(y + 0.5 - e->GetY(), 2)) <= GetRange()) {
			SetTarget(e);
			findTarget = true;
			break;
		}
	}
	if (!findTarget) {
		SetTarget(nullptr);
	}
}
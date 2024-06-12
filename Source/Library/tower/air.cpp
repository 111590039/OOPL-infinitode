#include "stdafx.h"
#include "air.h"

air::air() {
	SetType("air");
	SetBasePicPath("resources/Base_air.bmp");
	SetTowerName("航空");
	upgradeIcons = { 0,1,2,3 };
	Barrel = std::make_shared<airBarrel>();
	range = 4.5;
	damage = 6;
	attackSpeed = 4; //攻擊次數/每秒
	rotataionSpeed = 60; //旋轉速度/每秒 (還沒實作)
	projectileSpeed = 3.2;
	burningChance = 5;
	coolDown = 1 / attackSpeed;
	totalCost = 60;
	srand(unsigned(time(NULL)));
}
void air::move(double time, double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	findTarget(x,y,Enemy);
	coolDown = max(0, coolDown - time);
	if (coolDown == 0 && target != nullptr) {
		std::shared_ptr<airbullet> Bullet = std::make_shared<airbullet>();
		Bullet->SetTarget(GetTarget());
		Bullet->SetXY(x + 0.5, y + 0.5);
		Bullet->SetSpeed(projectileSpeed);
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
				if ((rand() % 100) < 5) {
					Bullets[i]->GetTarget()->GetBurning();
				}
			}
			Bullets.erase(Bullets.begin() + i);
		}
	}
}
double air::GetRange() {
	return range;
}
std::vector<int> air::GetUpgradeCost() {
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
std::vector<std::string> air::GetAttributeName() {
	return { "範圍" ,"傷害","攻擊速度","旋轉速度","彈丸速度","#燃燒機會" };
}
std::vector<std::string> air::GetAttributeValue() {
	std::vector<std::string> result = {};
	result.push_back(std::to_string(this->range));
	result.push_back(std::to_string(this->damage));
	result.push_back(std::to_string(this->attackSpeed) + "/s");
	result.push_back(std::to_string(this->rotataionSpeed) + "/s");
	result.push_back(std::to_string(this->projectileSpeed));
	result.push_back(std::to_string(this->burningChance) + "%");
	return result;
}
std::vector<std::vector<double>> air::GetAffected(int type) {
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
void air::upgrade1() {
	range += rangeUpgrade.at(upgradeLevel[0]);
	totalCost += upgradeCost[0].at(upgradeLevel[0]);
	upgradeLevel[0] += 1;
}
void air::upgrade2() {
	damage += damageUpgrade.at(upgradeLevel[1]);
	totalCost += upgradeCost[1].at(upgradeLevel[1]);
	upgradeLevel[1] += 1;
}
void air::upgrade3() {
	attackSpeed += attackSpeedUpgrade.at(upgradeLevel[2]);
	totalCost += upgradeCost[2].at(upgradeLevel[2]);
	upgradeLevel[2] += 1;
}
void air::upgrade4() {
	rotataionSpeed += rotataionSpeedUpgrade.at(upgradeLevel[3]);
	projectileSpeed += projectileSpeedUpgrade.at(upgradeLevel[3]);
	totalCost += upgradeCost[3].at(upgradeLevel[3]);
	upgradeLevel[3] += 1;
}
void air::findTarget(double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	bool findTarget = false;
	for (std::shared_ptr<enemy> e : Enemy) {
		if (sqrt(pow(x + 0.5 - e->GetX(), 2) + pow(y + 0.5 - e->GetY(), 2)) <= GetRange()) {
			if (!e->GetType().compare("Air") || !e->GetType().compare("Jet")) {
				SetTarget(e);
				findTarget = true;
				break;
			}
		}
	}
	if (!findTarget) {
		SetTarget(nullptr);
	}
}
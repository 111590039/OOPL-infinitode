#include "stdafx.h"
#include "venom.h"

venom::venom() {
	SetType("venom");
	SetBasePicPath("resources/Base_venom.bmp");
	SetTowerName("毒液");
	upgradeIcons = { 0,10,2,3 };
	Barrel = std::make_shared<venomBarrel>();
	range = 2.1;
	poisonDamage = 1.8;
	attackSpeed = 0.85; //攻擊次數/每秒
	rotataionSpeed = 90; //旋轉速度/每秒 (還沒實作)
	projectileSpeed = 3;
	poisonDuration = 5;
	coolDown = 1 / attackSpeed;
	totalCost = 120;
}
void venom::move(double time, double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	findTarget(x,y,Enemy);
	coolDown = max(0, coolDown - time);
	if (coolDown == 0 && target != nullptr) {
		std::shared_ptr<venombullet> Bullet = std::make_shared<venombullet>();
		Bullet->SetTarget(GetTarget());
		Bullet->SetXY(x + 0.5, y + 0.5);
		Bullet->SetSpeed(projectileSpeed);
		Bullet->SetDamage(poisonDamage * 5);
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
				Bullets[i]->GetTarget()->GetPoisoned(poisonDamage, poisonDuration);
			}
			Bullets.erase(Bullets.begin() + i);
		}
	}
}
double venom::GetRange() {
	return range;
}
std::vector<int> venom::GetUpgradeCost() {
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
std::vector<std::string> venom::GetAttributeName() {
	return { "範圍" ,"毒性傷害","攻擊速度","旋轉速度","彈丸速度","#毒藥持續時間" };
}
std::vector<std::string> venom::GetAttributeValue() {
	std::vector<std::string> result = {};
	result.push_back(std::to_string(this->range));
	result.push_back(std::to_string(this->poisonDamage));
	result.push_back(std::to_string(this->attackSpeed) + "/s");
	result.push_back(std::to_string(this->rotataionSpeed) + "/s");
	result.push_back(std::to_string(this->projectileSpeed));
	result.push_back(std::to_string(this->poisonDuration) + "/s");
	return result;
}
std::vector<std::vector<double>> venom::GetAffected(int type) {
	//type是升級選項 1/2/3/4 回傳{影響第幾項屬性,影響值}
	if (type == 1) {
		return { {0,rangeUpgrade.at(upgradeLevel[0])} };
	}
	else if (type == 2) {
		return { {1,poisonDamageUpgrade.at(upgradeLevel[1])} };
	}
	else if (type == 3) {
		return { {2,attackSpeedUpgrade.at(upgradeLevel[2])} };
	}
	else if (type == 4) {
		return { {3,rotataionSpeedUpgrade.at(upgradeLevel[3])},{4,projectileSpeedUpgrade.at(upgradeLevel[3])} };
	}
	return {};
}
void venom::upgrade1() {
	range += rangeUpgrade.at(upgradeLevel[0]);
	totalCost += upgradeCost[0].at(upgradeLevel[0]);
	upgradeLevel[0] += 1;
}
void venom::upgrade2() {
	poisonDamage += poisonDamageUpgrade.at(upgradeLevel[1]);
	totalCost += upgradeCost[1].at(upgradeLevel[1]);
	upgradeLevel[1] += 1;
}
void venom::upgrade3() {
	attackSpeed += attackSpeedUpgrade.at(upgradeLevel[2]);
	totalCost += upgradeCost[2].at(upgradeLevel[2]);
	upgradeLevel[2] += 1;
}
void venom::upgrade4() {
	rotataionSpeed += rotataionSpeedUpgrade.at(upgradeLevel[3]);
	projectileSpeed += projectileSpeedUpgrade.at(upgradeLevel[3]);
	totalCost += upgradeCost[3].at(upgradeLevel[3]);
	upgradeLevel[3] += 1;
}
void venom::findTarget(double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	bool findTarget = false;
	std::shared_ptr<enemy> first = nullptr;
	for (std::shared_ptr<enemy> e : Enemy) {
		if (sqrt(pow(x + 0.5 - e->GetX(), 2) + pow(y + 0.5 - e->GetY(), 2)) <= GetRange()) {
			if (e->GetType().compare("Air") && e->GetType().compare("Jet") && e->GetType().compare("Toxic")) {
				if (!e->GetPoisoned()) {
					SetTarget(e);
					findTarget = true;
					break;
				}
				else {
					if (first == nullptr) {
						first = e;
					}
				}

			}
		}
	}
	if (first != nullptr && !findTarget) {
		SetTarget(first);
		findTarget = true;
	}
	if (!findTarget) {
		SetTarget(nullptr);
	}
}
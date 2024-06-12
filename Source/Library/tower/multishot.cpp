#include "stdafx.h"
#include "multishot.h"
#include <cmath>

#define PI 3.1415926
#define ENEMY_SIZE 0.2

multishot::multishot() {
	SetType("multishot");
	SetBasePicPath("resources/Base_multishot.bmp");
	SetTowerName("多重射擊");
	upgradeIcons = { 0,1,2,3 };
	Barrel = std::make_shared<multishotBarrel>();
	range = 2.5;
	damage = 1.55;
	attackSpeed = 1.1; //攻擊次數/每秒
	rotataionSpeed = 75; //旋轉速度/每秒 (還沒實作)
	projectileSpeed = 3;
	shootingAngle = 25;
	projectileCount = 4;
	coolDown = 1 / attackSpeed;
	totalCost = 90;
}
void multishot::move(double time, double x, double y, std::vector<std::shared_ptr<enemy>> Enemy) {
	findTarget(x,y,Enemy);
	coolDown = max(0, coolDown - time);
	if (coolDown == 0 && target != nullptr) {
		double start_angle = atan2(target->GetY() - y - 0.5, target->GetX() - x - 0.5) - shootingAngle * PI / 360;
		for (int i = 0; i < projectileCount; i++) {
			double angle = start_angle + (shootingAngle * PI / 180) * (i / (projectileCount - 1));
			std::shared_ptr<multishotbullet> Bullet = std::make_shared<multishotbullet>();
			Bullet->SetXY(x + 0.5, y + 0.5);
			Bullet->SetTarXY(x + 0.5 + cos(angle) * range, y + 0.5 + sin(angle) * range);
			Bullet->SetSpeed(projectileSpeed);
			Bullet->SetDamage(damage);
			newBullet(Bullet);
		}
		coolDown = 1 / attackSpeed;
	}
	//刪除已用完的子彈
	for (size_t i = 0; i < Bullets.size(); i++) {
		Bullets[i]->moveNoTrack(time);
		bool done = false;
		for (shared_ptr<enemy> e : Enemy) {
			if (e->GetX() + ENEMY_SIZE >= Bullets[i]->GetX() && e->GetX() - ENEMY_SIZE <= Bullets[i]->GetX() && e->GetY() + ENEMY_SIZE >= Bullets[i]->GetY() && e->GetY() - ENEMY_SIZE <= Bullets[i]->GetY()) {
				e->GetDamage(Bullets[i]->GetDamage());
				Bullets.erase(Bullets.begin() + i);
				done = true;
				break;
			}
		}
		if (!done && Bullets[i]->IsPathOver()) {
			Bullets.erase(Bullets.begin() + i);
		}
	}
}
double multishot::GetRange() {
	return range;
}
std::vector<int> multishot::GetUpgradeCost() {
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
std::vector<std::string> multishot::GetAttributeName() {
	return { "範圍" ,"傷害","攻擊速度","旋轉速度","彈丸速度","#射擊角度","#子彈數量" };
}
std::vector<std::string> multishot::GetAttributeValue() {
	std::vector<std::string> result = {};
	result.push_back(std::to_string(this->range));
	result.push_back(std::to_string(this->damage));
	result.push_back(std::to_string(this->attackSpeed) + "/s");
	result.push_back(std::to_string(this->rotataionSpeed) + "/s");
	result.push_back(std::to_string(this->projectileSpeed));
	result.push_back(std::to_string(this->shootingAngle) + "/s");
	result.push_back(std::to_string(this->projectileCount));
	return result;
}
std::vector<std::vector<double>> multishot::GetAffected(int type) {
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
void multishot::upgrade1() {
	range += rangeUpgrade.at(upgradeLevel[0]);
	totalCost += upgradeCost[0].at(upgradeLevel[0]);
	upgradeLevel[0] += 1;
}
void multishot::upgrade2() {
	damage += damageUpgrade.at(upgradeLevel[1]);
	totalCost += upgradeCost[1].at(upgradeLevel[1]);
	upgradeLevel[1] += 1;
}
void multishot::upgrade3() {
	attackSpeed += attackSpeedUpgrade.at(upgradeLevel[2]);
	totalCost += upgradeCost[2].at(upgradeLevel[2]);
	upgradeLevel[2] += 1;
}
void multishot::upgrade4() {
	rotataionSpeed += rotataionSpeedUpgrade.at(upgradeLevel[3]);
	projectileSpeed += projectileSpeedUpgrade.at(upgradeLevel[3]);
	totalCost += upgradeCost[3].at(upgradeLevel[3]);
	upgradeLevel[3] += 1;
}
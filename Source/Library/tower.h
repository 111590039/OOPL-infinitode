#pragma once

#include <string>
#include <vector>
#include <memory>
#include "stdafx.h"
#include "gameutil.h"
#include "barrel.h"
#include "bullet.h"
#include "enemy.h"

class tower : public game_framework::CMovingBitmap {
public:
	tower();
	tower(std::string type);
	~tower();

	std::string GetType();
	std::string GetBasePicPath();
	std::string GetBarrelPicPath();
	std::string GetTowerName();
	std::vector<int> GetUpgradeLevel();
	std::vector<int> GetUpgradeIcon();
	virtual std::vector<int> GetUpgradeCost();

	virtual void move(double time, double x, double y);	//被OnMove持續調用 處理砲塔工作
	virtual void loadPic();       //讀取圖片
	virtual void show(double scale); //被OnShow調用 持續顯示
	virtual void showBullets(double scale); //顯示子彈
	virtual void resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY,int x ,int y); // 重新設定bitmap 相關設定
	virtual void upgrade1();
	virtual void upgrade2();
	virtual void upgrade3();
	virtual void upgrade4();
	void SetTarget(std::shared_ptr<enemy> target);
	void newBullet(std::shared_ptr<bullet> bullet);

	virtual double GetRange() = 0;
protected:
	void SetType(std::string type);
	void SetBasePicPath(std::string basepicpath);
	void SetBarrelPicPath(std::string barrelpicpath);
	void SetTowerName(std::string);

	std::shared_ptr <barrel> Barrel;
	std::shared_ptr<enemy> GetTarget();
	std::vector<std::shared_ptr<bullet>> Bullets;
	std::shared_ptr<enemy> target;
	std::vector<int> upgradeIcons = { 0,0,0,0 };
	std::vector<int> upgradeLevel = { 0,0,0,0 };
private:
	std::string type = "None";
	std::string basepicpath = "";
	std::string barrelpicpath = "";
	std::string towerName = "";

};

class emptytower : public tower {
public:
	emptytower();
	double GetRange() override;
};

class basictower : public tower {
public:
	basictower();
	void move(double time, double x, double y) override;
	double GetRange() override;
	std::vector<int> GetUpgradeCost() override;
	void upgrade1() override;
	void upgrade2() override;
	void upgrade3() override;
	void upgrade4() override;
private:
	std::vector<std::vector<int>> upgradeCost = { {13,16,20,26,34,46,64,91,133,200},
		{22,29,38,50,66,87,115,152,202,269},
		{10,13,17,23,31,42,57,78,108,152},
		{7,8,10,12,15,19,24,30,38,48}, };
	double coolDown;
	double range = 2;
	double damage = 2.3;
	double attackSpeed = 1.1; //攻擊次數/每秒
	//double rotataionSpeed;
	double projectileSpeed = 3.0;
	//double damageMultiplier;
};
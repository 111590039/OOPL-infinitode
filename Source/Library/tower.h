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
	virtual std::vector<std::string> GetAttributeName();
	virtual std::vector<std::string> GetAttributeValue();
	virtual std::vector<std::vector<double>> GetAffected(int type);

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
	std::vector<std::string> GetAttributeName() override;
	std::vector<std::string> GetAttributeValue() override;
	std::vector<std::vector<double>> GetAffected(int type) override;
	void upgrade1() override;
	void upgrade2() override;
	void upgrade3() override;
	void upgrade4() override;
private:
	std::vector<std::vector<int>> upgradeCost = { {13,16,20,26,34,46,64,91,133,200},
		{22,29,38,50,66,87,115,152,202,269},
		{10,13,17,23,31,42,57,78,108,152},
		{7,8,10,12,15,19,24,30,38,48}, };
	std::vector<double> rangeUpgrade = { 0.14, 0.17, 0.188, 0.208, 0.216, 0.220, 0.230, 0.244, 0.252, 0.270 };
	std::vector<double> damageUpgrade = { 1.26, 1.16, 1.11, 1.06, 1.01, 0.961, 0.911, 0.860, 0.810, 0.759 };
	std::vector<double> attackSpeedUpgrade = { 0.165, 0.185, 0.198, 0.214, 0.230, 0.242, 0.257, 0.245, 0.281, 0.264 };
	std::vector<double> rotataionSpeedUpgrade = { 15.3, 19.3, 19.2, 19.6, 21.5, 22.8, 24.3, 31.2, 35.1, 35.6};
	std::vector<double> projectileSpeedUpgrade = { 0.39, 0.483, 0.486, 0.609, 0.555, 0.723, 0.657, 0.831, 0.882 ,0.969 };
	double coolDown;
	double range = 2;
	double damage = 2.3;
	double attackSpeed = 1.1; //攻擊次數/每秒
	double rotataionSpeed = 90; //旋轉速度/每秒 (還沒實作)
	double projectileSpeed = 3.0;
	//double damageMultiplier;
};
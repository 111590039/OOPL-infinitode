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

	virtual void move(double time, double x, double y);	//被OnMove持續調用 處理砲塔工作
	virtual void loadPic();       //讀取圖片
	virtual void show(double scale); //被OnShow調用 持續顯示
	virtual void showBullets(double scale); //顯示子彈
	virtual void resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY,int x ,int y); // 重新設定bitmap 相關設定
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
private:
	double coolDown;
	double range = 2;
	double damage = 2.3;
	double attackSpeed = 1.1; //攻擊次數/每秒
	//double rotataionSpeed;
	double projectileSpeed = 3.0;
	//double damageMultiplier;
};
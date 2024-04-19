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
	virtual void move(double time, double x, double y);	//�QOnMove����ե� �B�z����u�@
	virtual void loadPic();       //Ū���Ϥ�
	virtual void show(double scale); //�QOnShow�ե� �������
	virtual void resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY,int x ,int y); // ���s�]�wbitmap �����]�w
	void SetTarget(std::shared_ptr<enemy>* target);
	void newBullet(std::shared_ptr<bullet> bullet);
protected:
	void SetType(std::string type);
	void SetBasePicPath(std::string basepicpath);
	void SetBarrelPicPath(std::string barrelpicpath);
	void SetTowerName(std::string);

	std::shared_ptr <barrel> Barrel;
	std::shared_ptr<enemy>* GetTarget();
	std::vector<std::shared_ptr<bullet>> Bullets;
	std::shared_ptr<enemy>* target;
private:
	std::string type = "None";
	std::string basepicpath = "";
	std::string barrelpicpath = "";
	std::string towerName = "";

};

class emptytower : public tower {
public:
	emptytower();
};

class basictower : public tower {
public:
	basictower();
	void move(double time, double x, double y) override;
private:
	double coolDown;
	//double range;
	//double damage;
	double attackSpeed = 1.1; //��������/�C��
	//double rotataionSpeed;
	double projectileSpeed = 3.0;
	//double damageMultiplier;
};
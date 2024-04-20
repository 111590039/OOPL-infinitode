#pragma once

#include <string>
#include <vector>
#include "stdafx.h"
#include "gameutil.h"
#include "enemy.h"

class bullet : public game_framework::CMovingBitmap{
public:
	bullet();
	void SetXY(double x, double y);
	void SetTarXY(double x, double y);
	void SetPicPath(std::string picPath);
	void SetSpeed(double speed);
	void SetTarget(std::shared_ptr<enemy>* target);
	virtual void loadPic();       //讀取圖片
	virtual void show(double scale); //被OnShow調用 持續顯示
	virtual void resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY); // 重新設定bitmap 相關設定
	void move(double time);
	bool IsPathOver();
private:
	double x = 0;	//相對位置
	double y = 0;	//相對位置
	double speed;	//速度(格/每秒)
	double tarX;	//目標位置
	double tarY;
	std::shared_ptr<enemy> *target= nullptr;
	std::string picPath = "";
};

class basicbullet : public bullet {
public:
	basicbullet();
};
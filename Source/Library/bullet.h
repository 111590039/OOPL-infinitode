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
	virtual void loadPic();       //Ū���Ϥ�
	virtual void show(double scale); //�QOnShow�ե� �������
	virtual void resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY); // ���s�]�wbitmap �����]�w
	void move(double time);
	bool IsPathOver();
private:
	double x = 0;	//�۹��m
	double y = 0;	//�۹��m
	double speed;	//�t��(��/�C��)
	double tarX;	//�ؼЦ�m
	double tarY;
	std::shared_ptr<enemy> *target= nullptr;
	std::string picPath = "";
};

class basicbullet : public bullet {
public:
	basicbullet();
};
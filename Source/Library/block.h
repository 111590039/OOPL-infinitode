#pragma once

#include <string>
#include <vector>
#include "stdafx.h"
#include "gameutil.h"
#include "tower/tower.h"
#include "tower/sniper.h"
#include "tower/cannon.h"
#include "tower/freezing.h"
#include "tower/blast.h"

class block : public game_framework::CMovingBitmap {
public:
	block(int x, int y);

	int GetX();
	int GetY();
	std::string GetType();
	std::string GetTitle();
	std::string GetDescribe();
	std::string GetPicPath();

	void SetXY(int x,int y);

	virtual void OnClick();

	virtual void loadPic();       //Ū���Ϥ�
	virtual void show(double scale); //�QOnShow�ե� �������
	virtual void resetShow(int TOP,int LEFT,int TILE_SIZE,double scale, int moveX, int moveY); // ���s�]�wbitmap �����]�w
	bool ifClickOn(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY, int tarX , int tarY);
protected:
	void SetType(std::string type);
	void SetTitle(std::string title);
	void SetDescribe(std::string describe);
	void SetPicPath(std::string picPath);
private:
	int x;
	int y;
	std::string type = "";
	std::string title = "";
	std::string describe = "";
	std::string picPath = "";
};

class tile : public block {
public:
	tile(int x, int y);
	bool haveTower();
	void OnClick() override;
	void buildTower(std::shared_ptr<tower> Tower);
	int sellTower();
	void loadPic() override;       //Ū���Ϥ�
	void show(double scale) override; //�QOnShow�ե� �������
	void resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY) override; // ���s�]�wbitmap �����]�w
	std::shared_ptr<tower> GetTower();
private:
	std::shared_ptr<tower> Tower;
	//std::vector<extraEffect> Effects;
};

class road : public block {
public:
	road(int x, int y);
	void OnClick() override;
private:
	
};

class base : public block {
public:
	base(int x, int y);
	void OnClick() override;
private:

};

class portal : public block {
public:
	portal(int x, int y);
	void OnClick() override;
private:

};




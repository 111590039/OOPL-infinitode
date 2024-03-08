#pragma once

#include <string>
#include <vector>
#include "stdafx.h"
#include "gameutil.h"

class block : public game_framework::CMovingBitmap {
public:
	block(int x, int y);

	virtual void OnClick();

	std::string GetType();
	std::string GetTitle();
	std::string GetDescribe();
	std::string GetPicPath();

	void SetXY(int x,int y);
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
	//void buildTower(Tower tower);
	//void sellTower();
private:
	//Tower tower
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
	portal(int x, int y,double difficult);
	void OnClick() override;
	double GetDifficult();
private:
	double difficult;

};




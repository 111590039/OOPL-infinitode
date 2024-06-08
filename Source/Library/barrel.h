#pragma once

#include <string>
#include <vector>

#include "stdafx.h"
#include "gameutil.h"

class barrel : game_framework::CMovingBitmap{
public:
	barrel();
	barrel(std::string type);

	void SetBarrelPicPaths(std::vector<std::string> barrelPicPaths);

	virtual void loadPic();       //讀取圖片
	virtual void show(double scale); //被OnShow調用 持續顯示
	virtual void resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY, int x, int y); // 重新設定bitmap 相關設定
protected:

private:
	std::vector<std::string> barrelPicPaths;
	int rotation;
	std::string type;
};

class basicBarrel : public barrel {
public:
	basicBarrel();

};

class sniperBarrel : public barrel {
public:
	sniperBarrel();

};

class cannonBarrel : public barrel {
public:
	cannonBarrel();

};

class freezingBarrel : public barrel {
public:
	freezingBarrel();

};

class blastBarrel : public barrel {
public:
	blastBarrel();

};

class minigunBarrel : public barrel {
public:
	minigunBarrel();

};

class airBarrel : public barrel {
public:
	airBarrel();

};
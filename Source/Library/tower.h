#pragma once

#include <string>
#include <vector>
#include "stdafx.h"
#include "gameutil.h"

class tower : public game_framework::CMovingBitmap {
public:
	tower();
	tower(std::string type);
	~tower();

	std::string GetType();
	std::string GetBasePicPath();
	std::string GetBarrelPicPath();

	virtual void loadPic();       //讀取圖片
	virtual void show(int scale); //被OnShow調用 持續顯示
	virtual void resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY,int x ,int y); // 重新設定bitmap 相關設定

protected:
	void SetType(std::string type);
	void SetBasePicPath(std::string basepicpath);
	void SetBarrelPicPath(std::string barrelpicpath);
private:

	std::string type = "None";
	std::string basepicpath = "";
	std::string barrelpicpath = "";
};

class basictower : public tower {

};
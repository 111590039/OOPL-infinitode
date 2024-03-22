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

	void resetShow(int x,int y, double scale);  

protected:
	void SetType(std::string type);
	void SetBasePicPath(std::string basepicpath);
	void SetBarrelPicPath(std::string barrelpicPath);
private:

	std::string type = "None";
	std::string basepicpath = "";
	std::string barrelpicPath = "";
};

class basictower : public tower {

};
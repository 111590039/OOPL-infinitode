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

	virtual void loadPic();       //Ū���Ϥ�
	virtual void show(double scale); //�QOnShow�ե� �������
	virtual void resetShow(int TOP, int LEFT, int TILE_SIZE, double scale, int moveX, int moveY, int x, int y); // ���s�]�wbitmap �����]�w
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
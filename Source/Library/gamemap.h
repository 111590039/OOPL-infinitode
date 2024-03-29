#pragma once

#include "block.h"
#include "enemy.h"
#include <string>
#include <vector>
#include <memory>

class gamemap {
public:
	gamemap();
	gamemap(int size);

	void addScale(double scale);
	void addMoveX(int delta);
	void addMoveY(int delta);

	double GetScale();

	
	void drawmap();           //讓整張地圖顯示
	//void loadmap(std::string level);
	void loadpic();           //初始化地圖
	void resetshow();   //刷新並套用新位置大小
	void buildTower(int x,int y,std::string type);
	void TESTMAP1();
protected:
	void newblock(std::shared_ptr<block> block);
	void newtile(std::shared_ptr<tile> tile);
	void newEnemy(std::shared_ptr<enemy> enemy);
private:
	int size = 32;
	std::vector<std::shared_ptr<block>> map;
	std::vector<std::shared_ptr<tile>> tiles;
	std::vector<std::shared_ptr<enemy>> Enemy;
	double scale = 1.0;
	int moveX = 0;
	int moveY = 0;
};
#pragma once

#include "block.h"
#include "enemy.h"
#include "bullet.h"
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <mmsystem.h>
#include <ddraw.h>
#include "gamecore.h"

class gamemap {
public:
	gamemap();
	gamemap(int size);

	void addScale(double scale);
	void addMoveX(int delta);
	void addMoveY(int delta);

	double GetScale();
	double GetElapsedTime();
	void Setdifficulty(double difficulty);

	void refreshTime();     //更新時鐘時間
	void processMove();     //計算物體
	void drawmap();           //讓整張地圖顯示
	void showtext();		//顯示文字
	//void loadmap(std::string level);
	void loadpic();           //初始化地圖
	void resetshow();   //刷新並套用新位置大小
	void buildTower(int x,int y,std::string type);
	void clickOnMap(CPoint point);
	void TESTMAP1();

protected:
	void newblock(std::shared_ptr<block> block);
	void newtile(std::shared_ptr<tile> tile);
	void newEnemy(std::shared_ptr<enemy> enemy);
	void newBullet(std::shared_ptr<bullet> bullet);
private:
	game_framework::CMovingBitmap controlPanel; //控制面版底座
	game_framework::CMovingBitmap controlPanelButton; //控制面板按鈕
	game_framework::CMovingBitmap selected_box; //蓋塔選單的選擇框
	bool showing_control_panel = false; //控制面板是否被最小化
	bool is_control_panel_invisable = true; //控制面板是否隱藏
	int controlPanelMode = 1;  //控制面板模式 1 = build, 2=info, 3 = tower
	std::vector<string> towernames = {"基本","狙擊手","大炮","寒冰","毒液","噴灑","爆破","多重射擊","機關槍","航空","特斯拉","導彈"};
	std::vector<game_framework::CMovingBitmap> towerButtons; //蓋塔模式的按鈕
	CPoint selected_tile; //目前選擇的地圖格子位置
	int last_selected = -1; //蓋塔模式中上一個選擇的塔
	game_framework::CMovingBitmap selected_block; //地圖格子的選擇框
	int size = 32;
	double difficulty;
	std::vector<std::shared_ptr<block>> map;
	std::vector<std::shared_ptr<tile>> tiles;
	std::vector<std::shared_ptr<enemy>> Enemy;
	std::vector<std::shared_ptr<bullet>> Bullet;
	double scale = 1.0;
	int moveX = 350;
	int moveY = 200;
	chrono::steady_clock::time_point lastTime = chrono::steady_clock::now();
	std::vector<CPoint> enemyPath;
};
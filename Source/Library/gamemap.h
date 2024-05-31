#pragma once

#include "block.h"
#include "enemy.h"
#include "bullet.h"
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <fstream>
#include <mmsystem.h>
#include <ddraw.h>
#include "gamecore.h"
#include "wave.h"

class gamemap {
public:
	gamemap();
	gamemap(int size);

	bool IsGameover();
	void resetGamemap();

	void addScale(double scale);
	void addMoveX(int delta);
	void addMoveY(int delta);

	double GetScale();
	int GetTotalTime();
	int GetWave();
	double GetElapsedTime();
	void Setdifficulty(double difficulty);

	void refreshTime();     //更新時鐘時間
	void processMove();     //計算物體
	void drawmap();           //讓整張地圖顯示
	void showtext();		//顯示文字
	void loadmap(int level);  //讀取地圖
	void loadpic();           //初始化地圖
	void resetshow();   //刷新並套用新位置大小
	void buildTower(int x,int y,std::string type);
	void clickOnMap(CPoint point);
	void TESTMAP1();
	void SummonTestEnemy(); //測試用 生成測試用敵人
	void CheatCoin(); //測試用 設定金錢為99999

protected:
	void newblock(std::shared_ptr<block> block);
	void newtile(std::shared_ptr<tile> tile);
	void newEnemy(std::shared_ptr<enemy> enemy);
private:
	game_framework::CMovingBitmap coinIcon;
	game_framework::CMovingBitmap healthIcon;
	int coins = 2000;
	int health = 100;
	game_framework::CMovingBitmap controlPanel; //控制面版底座
	game_framework::CMovingBitmap controlPanelButton; //控制面板按鈕
	game_framework::CMovingBitmap selected_box; //蓋塔選單的選擇框
	game_framework::CMovingBitmap upgradeButton[4]; //升級模式的升級方塊
	game_framework::CMovingBitmap confirmUpgrade; //升級模式的確認升級綠方塊
	game_framework::CMovingBitmap upgradeIcon[4]; //升級模式的升級圖案
	bool showing_control_panel = false; //控制面板是否被最小化
	bool is_control_panel_invisable = true; //控制面板是否隱藏
	int controlPanelMode = 1;  //控制面板模式 1 = 蓋塔, 2=資訊, 3 = 升級
	game_framework::CMovingBitmap greenCircle; //顯示範圍的綠圈
	game_framework::CMovingBitmap blueCircle; //顯示範圍的藍圈
	double greenScale =0.1; //顯示範圍的綠圈Size
	double blueScale = 0.1; //顯示範圍的藍圈Size
	game_framework::CMovingBitmap sellingTower; //賣塔的確認框
	bool is_selling_visable = false;		//賣塔的確認框是否顯示
	int gameSpeed = 1;  //遊戲速度
	game_framework::CMovingBitmap gameSpeedButton;  //遊戲速度按鈕
	std::vector<double> origin_range = {2.0,4.5,1.75,2.0,2.1,1.85,1.75,2.5,2.8,4.5,2.8,4.0}; //砲塔的基礎射程
	std::vector<int> towerPrice = { 40,100,60,70,120,70,120,90,160,60 };
	std::vector<string> towernames = {"基本","狙擊","大炮","冰凍","毒液","噴灑","爆破","多重射擊","機關槍","航空","特斯拉","導彈"};
	std::vector<game_framework::CMovingBitmap> towerButtons; //蓋塔模式的按鈕
	CPoint selected_tile; //目前選擇的地圖格子位置
	std::shared_ptr<tower> last_selected_tower;
	int last_selected = -1; //蓋塔模式中上一個選擇的塔
	int last_selected_upgrade = -1; //升級模式中上一個選擇的升級
	game_framework::CMovingBitmap selected_block; //地圖格子的選擇框
	double totalTime = 0;
	int size = 32;
	double difficulty;
	std::vector<std::shared_ptr<block>> map;
	std::vector<std::shared_ptr<tile>> tiles;
	std::vector<std::shared_ptr<enemy>> Enemy;
	double scale = 1.0;
	int moveX = 550;
	int moveY = 200;
	chrono::steady_clock::time_point lastTime = chrono::steady_clock::now();
	std::vector<CPoint> enemyPath;
	Wave wave;
};
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

	void refreshTime();     //��s�����ɶ�
	void processMove();     //�p�⪫��
	void drawmap();           //����i�a�����
	void showtext();		//��ܤ�r
	//void loadmap(std::string level);
	void loadpic();           //��l�Ʀa��
	void resetshow();   //��s�îM�ηs��m�j�p
	void buildTower(int x,int y,std::string type);
	void clickOnMap(CPoint point);
	void TESTMAP1();

protected:
	void newblock(std::shared_ptr<block> block);
	void newtile(std::shared_ptr<tile> tile);
	void newEnemy(std::shared_ptr<enemy> enemy);
	void newBullet(std::shared_ptr<bullet> bullet);
private:
	game_framework::CMovingBitmap controlPanel; //��������y
	game_framework::CMovingBitmap controlPanelButton; //����O���s
	game_framework::CMovingBitmap selected_box; //�\���檺��ܮ�
	bool showing_control_panel = false; //����O�O�_�Q�̤p��
	bool is_control_panel_invisable = true; //����O�O�_����
	int controlPanelMode = 1;  //����O�Ҧ� 1 = build, 2=info, 3 = tower
	std::vector<string> towernames = {"��","������","�j��","�H�B","�r�G","�Q�x","�z�}","�h���g��","�����j","���","�S����","�ɼu"};
	std::vector<game_framework::CMovingBitmap> towerButtons; //�\��Ҧ������s
	CPoint selected_tile; //�ثe��ܪ��a�Ϯ�l��m
	int last_selected = -1; //�\��Ҧ����W�@�ӿ�ܪ���
	game_framework::CMovingBitmap selected_block; //�a�Ϯ�l����ܮ�
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
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

	void refreshTime();     //��s�����ɶ�
	void processMove();     //�p�⪫��
	void drawmap();           //����i�a�����
	void showtext();		//��ܤ�r
	void loadmap(int level);  //Ū���a��
	void loadpic();           //��l�Ʀa��
	void resetshow();   //��s�îM�ηs��m�j�p
	void buildTower(int x,int y,std::string type);
	void clickOnMap(CPoint point);
	void TESTMAP1();
	void SummonTestEnemy(); //���ե� �ͦ����եμĤH
	void CheatCoin(); //���ե� �]�w������99999

protected:
	void newblock(std::shared_ptr<block> block);
	void newtile(std::shared_ptr<tile> tile);
	void newEnemy(std::shared_ptr<enemy> enemy);
private:
	game_framework::CMovingBitmap coinIcon;
	game_framework::CMovingBitmap healthIcon;
	int coins = 2000;
	int health = 100;
	game_framework::CMovingBitmap controlPanel; //��������y
	game_framework::CMovingBitmap controlPanelButton; //����O���s
	game_framework::CMovingBitmap selected_box; //�\���檺��ܮ�
	game_framework::CMovingBitmap upgradeButton[4]; //�ɯżҦ����ɯŤ��
	game_framework::CMovingBitmap confirmUpgrade; //�ɯżҦ����T�{�ɯź���
	game_framework::CMovingBitmap upgradeIcon[4]; //�ɯżҦ����ɯŹϮ�
	bool showing_control_panel = false; //����O�O�_�Q�̤p��
	bool is_control_panel_invisable = true; //����O�O�_����
	int controlPanelMode = 1;  //����O�Ҧ� 1 = �\��, 2=��T, 3 = �ɯ�
	game_framework::CMovingBitmap greenCircle; //��ܽd�򪺺��
	game_framework::CMovingBitmap blueCircle; //��ܽd���Ű�
	double greenScale =0.1; //��ܽd�򪺺��Size
	double blueScale = 0.1; //��ܽd���Ű�Size
	game_framework::CMovingBitmap sellingTower; //��𪺽T�{��
	bool is_selling_visable = false;		//��𪺽T�{�جO�_���
	int gameSpeed = 1;  //�C���t��
	game_framework::CMovingBitmap gameSpeedButton;  //�C���t�׫��s
	std::vector<double> origin_range = {2.0,4.5,1.75,2.0,2.1,1.85,1.75,2.5,2.8,4.5,2.8,4.0}; //���𪺰�¦�g�{
	std::vector<int> towerPrice = { 40,100,60,70,120,70,120,90,160,60 };
	std::vector<string> towernames = {"��","����","�j��","�B��","�r�G","�Q�x","�z�}","�h���g��","�����j","���","�S����","�ɼu"};
	std::vector<game_framework::CMovingBitmap> towerButtons; //�\��Ҧ������s
	CPoint selected_tile; //�ثe��ܪ��a�Ϯ�l��m
	std::shared_ptr<tower> last_selected_tower;
	int last_selected = -1; //�\��Ҧ����W�@�ӿ�ܪ���
	int last_selected_upgrade = -1; //�ɯżҦ����W�@�ӿ�ܪ��ɯ�
	game_framework::CMovingBitmap selected_block; //�a�Ϯ�l����ܮ�
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
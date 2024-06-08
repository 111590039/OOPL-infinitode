#include "stdafx.h"
#include "gamemap.h"
#include <algorithm>
#include <cmath>

#define TOP 0
#define LEFT 0
#define PANEL_SPACE 100
#define TILE_SIZE 65
#define ENEMY_SIZE 13
#define TOWER_BUTTON_SIZE 100

gamemap::gamemap() {

}
gamemap::gamemap(int size) {

}
bool gamemap::IsGameover() {
	return health <= 0;
}
void gamemap::resetGamemap() {
	coins = 500;
	health = 100;
	showing_control_panel = false;
	is_control_panel_invisable = true;
	controlPanelMode = 1;
	greenScale = 0.1;
	blueScale = 0.1;
	is_selling_visable = false;
	gameSpeed = 1;
	last_selected_tower = nullptr;
	last_selected = -1;
	last_selected_upgrade = -1;
	scale = 1.0;
	moveX = 550;
	moveY = 200;
	totalTime = 0;
	lastTime = chrono::steady_clock::now();
	controlPanel.SetTopLeft(-600, PANEL_SPACE);
	controlPanelButton.SetTopLeft(-200, PANEL_SPACE + 400);
	selected_box.SetTopLeft(-100, -100);
	selected_block.SetTopLeft(-100, -100);
	confirmUpgrade.SetTopLeft(-100, -100);
	greenCircle.SetTopLeft(-200, -200);
	blueCircle.SetTopLeft(-200, -200);
	gameSpeedButton.SetFrameIndexOfBitmap(0);
	for (std::shared_ptr<tile> t : tiles) {
		if (t->haveTower()) {
			t->sellTower();
		}
	}
	Enemy.clear();
	wave.Restart();
}
void gamemap::addScale(double delta) {
	scale = max(scale + delta, 0.1);
}
void gamemap::addMoveX(int delta) {
	moveX = max(moveX + delta, -100);
}
void gamemap::addMoveY(int delta) {
	moveY  = max(moveY + delta, -100);
}
double gamemap::GetScale() {
	return scale;
}
int gamemap::GetTotalTime() {
	return int(totalTime);
}
int gamemap::GetWave() {
	return wave.GetWave();
}
double gamemap::GetElapsedTime() {
	auto time = std::chrono::duration<double>(lastTime.time_since_epoch());
	auto now = std::chrono::duration<double>(chrono::steady_clock::now().time_since_epoch());
	time = now - time;
	if (double(time.count()) >= 0.1) {
		return 0;
	}
	return time.count();
}
void gamemap::Setdifficulty(double difficulty) {
	this->difficulty = difficulty;
}
void gamemap::refreshTime() {
	lastTime = chrono::steady_clock::now();
}
void gamemap::processMove() {
	//砲塔工作
	double time = GetElapsedTime();
	totalTime += time;
	time = time * gameSpeed;
	for (std::shared_ptr<tile> t : tiles) {
		/*
		if (Enemy.size() != 0){
			bool findTarget = false;
			for (std::shared_ptr<enemy> e : Enemy) {
				if (sqrt(pow(t->GetX()+0.5 - e->GetX(), 2) + pow(t->GetY()+0.5 - e->GetY(), 2)) <= t->GetTower()->GetRange()) {
					t->GetTower()-> SetTarget(e) ;
					findTarget = true;
					break;
				}
			}
			if (!findTarget) {
				t->GetTower()->SetTarget(nullptr);
			}
		}
		else {
			t->GetTower()->SetTarget(nullptr);
		}
		*/
		t->GetTower()->move(time, t->GetX(), t->GetY() ,Enemy);
		t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
	//敵人移動
	for (size_t i = 0; i < Enemy.size(); i++) {
		Enemy[i]->Effect(time);
		if (Enemy[i] -> IsDied() && Enemy[i] -> IsSurvive) {
			Enemy[i]->IsSurvive = false;
			coins += int(Enemy[i]->Getbounty());
			Enemy.erase(Enemy.begin() + i);
			continue;
		}
		bool del;
		Enemy[i]->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
		del = Enemy[i]->enemyMove(time);
		if (del&& Enemy[i]->IsSurvive) {
			Enemy[i]->IsSurvive = false;
			health -= Enemy[i]->GetDamage();
			Enemy.erase(Enemy.begin() + i);
			continue;
		}
	}
	//關卡進行
	if (wave.GetStart()) {
		if (wave.GetRemainingCount() == 0) {
			if (wave.GetCd15() > 0) {
				wave.showCD();
				wave.ReduceCd(time);
			}
			else {
				wave.SetCd15(15.0);
				wave.nextLevel();
				wave.enemyType(wave.GetWave());
				wave.SetRemainingCount(wave.enemyCount(wave.GetEnemyType(), wave.GetWave()));
			}
		}
		else if (wave.GetdelayTime() > 0.5 && wave.GetRemainingCount() > 0) {
			int i = (rand() % enemyPath.size());
			if (wave.GetEnemyType() == "Regular") {
				newEnemy(std::make_shared<Regular>(0.7, wave.GetWave(), enemyPath[i]));
			}
			else if (wave.GetEnemyType() == "Fast") {
				newEnemy(std::make_shared<Fast>(0.7, wave.GetWave(), enemyPath[i]));
			}
			else if (wave.GetEnemyType() == "Strong") {
				newEnemy(std::make_shared<Strong>(0.7, wave.GetWave(), enemyPath[i]));
			}
			else if (wave.GetEnemyType() == "DenseRegular") {
				newEnemy(std::make_shared<DenseRegular>(0.7, wave.GetWave(), enemyPath[i]));
			}
			else if (wave.GetEnemyType() == "Air") {
				newEnemy(std::make_shared<Air>(0.7, wave.GetWave(), enemyPath[i]));
			}
			else if (wave.GetEnemyType() == "Jet") {
				newEnemy(std::make_shared<Jet>(0.7, wave.GetWave(), enemyPath[i]));
			}
			else if (wave.GetEnemyType() == "Light") {
				newEnemy(std::make_shared<Light>(0.7, wave.GetWave(), enemyPath[i]));
			}
			else if (wave.GetEnemyType() == "Icy") {
				newEnemy(std::make_shared<Icy>(0.7, wave.GetWave(), enemyPath[i]));
			}
			else if (wave.GetEnemyType() == "Toxic") {
				newEnemy(std::make_shared<Toxic>(0.7, wave.GetWave(), enemyPath[i]));
			}
			else if (wave.GetEnemyType() == "SuperBoss") {
				newEnemy(std::make_shared<Boss>(0.7, wave.GetWave(), enemyPath[i]));
			}
			else if (wave.GetEnemyType() == "Boss") {
				if (wave.GetRemainingCount() > 4 + int(floor(pow(wave.GetWave() / 8, 0.6)))) {
					newEnemy(std::make_shared<BossArmored>(0.7, wave.GetWave(), enemyPath[i]));
				}
				else if (wave.GetRemainingCount() > 3 + int(floor(pow(wave.GetWave() / 8, 0.6)))) {
					newEnemy(std::make_shared<BossFighter>(0.7, wave.GetWave(), enemyPath[i]));
				}
				else {
					newEnemy(std::make_shared<BossFast>(0.7, wave.GetWave(), enemyPath[i]));
				}
			}
			wave.SetRemainingCount(wave.GetRemainingCount() - 1);
			wave.SetDelayTime(0);
		}
		wave.AccDelayTime(time);
	}
	refreshTime();//一定要在最下面
}
//讓整張地圖顯示
void gamemap::drawmap() {
	for (std::shared_ptr<block> b : map) {
		b->show(scale);
	}
	for (std::shared_ptr<tile> t : tiles) {
		t->show(scale);
	}
	for (std::shared_ptr<tile> t : tiles) {
		if (t->haveTower()) {
			t->GetTower()->showBullets(scale);
		}
	}
	for (std::shared_ptr<enemy> e : Enemy) {
		e->show(scale);
	}
	selected_block.ShowBitmap(scale);
	if (controlPanelMode == 1  || (controlPanelMode == 3 && last_selected_upgrade == 1) && showing_control_panel && !is_control_panel_invisable) {
		greenCircle.ShowBitmap(greenScale * 0.5* scale *(65.0/60.0));
	}
	if (controlPanelMode == 3 && !is_control_panel_invisable) {
		blueCircle.ShowBitmap(blueScale * 0.5* scale * (65.0 / 60.0));
	}
	controlPanel.ShowBitmap();
	controlPanelButton.ShowBitmap();
	if (controlPanelMode == 1) {
		controlPanel.SetFrameIndexOfBitmap(0);
		if (showing_control_panel && !is_control_panel_invisable){
			//選單按鈕圖片
			for (game_framework::CMovingBitmap b : towerButtons) {
				b.ShowBitmap();
			}	
			selected_box.ShowBitmap();
			}
	}
	else if (controlPanelMode == 2) {
		controlPanel.SetFrameIndexOfBitmap(1);
	}
	else if (controlPanelMode == 3) {
		controlPanel.SetFrameIndexOfBitmap(2);
		if (!is_control_panel_invisable && showing_control_panel) {
			std::vector<int> cost = last_selected_tower->GetUpgradeCost();
			for (int i = 0; i < 4; i++) {
				if (cost[i] > coins) {
					upgradeButton[i].SetFrameIndexOfBitmap(1);
				}
				else {
					upgradeButton[i].SetFrameIndexOfBitmap(0);
				}
				upgradeButton[i].ShowBitmap();
			}
			confirmUpgrade.ShowBitmap();
			for (int i = 0; i < 4; i++) {
				upgradeIcon[i].ShowBitmap();
			}
		}
	}
	if (is_selling_visable) {
		sellingTower.ShowBitmap();
	}
	coinIcon.ShowBitmap(0.9);
	healthIcon.ShowBitmap(0.9);
	wave.showClock();
	gameSpeedButton.ShowBitmap(0.6);
}
void gamemap::loadmap() {
	int level;
	ifstream f("Source/Game/Settings.map");
	f >> level;
	f.close();
	std::string filepath = "Source/Map/level" + to_string(level) + ".map";

	ifstream ifs(filepath);
	int mx, my,temp,temp2;
	CPoint p;
	std::vector<CPoint> pathtemp;
	ifs >> temp;
	Setdifficulty(double(temp)/100);
	ifs >> mx;
	for (int i = 0; i < mx; i++) {
		ifs >> my;
		for (int j = 0; j < my; j++) {
			ifs >> temp;
			ifs >> temp2;
			p.x = temp;
			p.y = temp2;
			pathtemp.push_back(p);
		}
		enemyPath.push_back(std::vector<CPoint>(pathtemp));
		pathtemp.clear();
	}
	ifs >> mx;
	ifs >> my;
	for (int y = 0; y < my; y++) {
		for (int x = 0; x < mx; x++) {
			ifs >> temp;
			if (temp == 1) {
				newblock(std::make_shared<road>(x, y));
			}
			else if (temp == 2) {
				newblock(std::make_shared<portal>(x, y));
			}
			else if (temp == 3) {
				newblock(std::make_shared<base>(x, y));
			}
			else if (temp == 4) {
				newtile(std::make_shared<tile>(x, y));
			}
		}
	}
	ifs.close();
}
void gamemap::showtext() {
	CDC *pDC = game_framework::CDDraw::GetBackCDC();
	//選單文字
	game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 1200);
	game_framework::CTextDraw::Print(pDC, 100, 20,std::to_string(coins));
	game_framework::CTextDraw::Print(pDC, 440, 20, std::to_string((int)ceil(health))); //(int)ceil(health))
	if (showing_control_panel && !is_control_panel_invisable) {
		if (controlPanelMode == 1) {
			if (last_selected == -1) {
				game_framework::CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(255, 255, 255), 800);
				game_framework::CTextDraw::Print(pDC, 20, PANEL_SPACE + 20, "點擊塔的圖案以打開描述");
				game_framework::CTextDraw::Print(pDC, 20, PANEL_SPACE + 60, "單擊第二次來建造塔");
			}
			else {
				game_framework::CTextDraw::ChangeFontLog(pDC, 42, "微軟正黑體", RGB(255, 255, 255), 1200);
				game_framework::CTextDraw::Print(pDC, 20 ,PANEL_SPACE+20 , towernames[last_selected]);
			}
			//選單按鈕文字
			game_framework::CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(255, 255, 255), 800);
			int counter = 0;
			for (game_framework::CMovingBitmap b : towerButtons) {
				game_framework::CTextDraw::Print(pDC, b.GetLeft()+70 , b.GetTop()+70 , std::to_string(towerPrice[counter++]));
			}
		}
		else if (controlPanelMode == 2) {
			for (std::shared_ptr<block> b : map) {
				if (selected_tile.x == b->GetX() && selected_tile.y == b->GetY()) {
					game_framework::CTextDraw::ChangeFontLog(pDC, 42, "微軟正黑體", RGB(255, 255, 255), 1200);
					game_framework::CTextDraw::Print(pDC, 20, PANEL_SPACE + 20, b->GetTitle());
					game_framework::CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(255, 255, 255), 800);
					game_framework::CTextDraw::Print(pDC, 20, PANEL_SPACE + 70, b->GetDescribe());
					if (!b->GetType().compare("portal")) {
						std::string D = std::to_string(int(difficulty *100)) + "%";
						game_framework::CTextDraw::Print(pDC, 20, PANEL_SPACE + 100, "等級難度:" + D);
					}
					break;
				}
			}
		}
		else if (controlPanelMode == 3) {
			std::vector<int> cost = last_selected_tower->GetUpgradeCost();
			std::vector<string> names = last_selected_tower->GetAttributeName();
			std::vector<string> values = last_selected_tower->GetAttributeValue();
			game_framework::CTextDraw::ChangeFontLog(pDC, 42, "微軟正黑體", RGB(255, 255, 255), 1200);
			game_framework::CTextDraw::Print(pDC, 20, PANEL_SPACE + 20, last_selected_tower->GetTowerName());
			//印出屬性名
			for (size_t i = 0; i < names.size(); i++) {
				game_framework::CTextDraw::ChangeFontLog(pDC, 19, "微軟正黑體", RGB(255, 255, 255), 600);
				if (names[i].at(0) == '#') {
					game_framework::CTextDraw::ChangeFontLog(pDC, 19, "微軟正黑體", RGB(255, 192, 0), 600);
					names[i] = names[i].substr(1);
				}
				game_framework::CTextDraw::Print(pDC, 20, PANEL_SPACE + 120 + 25*i, names[i]);
			}
			//印出屬性值
			std::vector<std::vector<double>> affected = last_selected_tower->GetAffected(last_selected_upgrade);

			for (size_t i = 0; i < values.size(); i++) {
				std::string D = ""; //升級影響的綠字
				int pos = values[i].find('.');
				if (pos != std::string::npos) {
					values[i] = values[i].substr(0, pos+3);
				}
				for (std::vector<double> j : affected) {
					if (i == size_t(j[0])) {
						D = std::to_string(j[1]);
						int pos = D.find('.');
						if (pos != std::string::npos) {
							D = D.substr(0, pos + 4);
						}
						D = " +" + D;
						for (size_t k = 0; k < D.size(); k++) {
							values[i] = values[i] + " ";
						}
					}
				}
				game_framework::CTextDraw::ChangeFontLog(pDC, 19, "微軟正黑體", RGB(0, 255, 0), 600);
				game_framework::CTextDraw::Print(pDC, 370 - D.size() * 10, PANEL_SPACE + 120 + 25 * i, D);
				game_framework::CTextDraw::ChangeFontLog(pDC, 19, "微軟正黑體", RGB(255, 255, 255), 600);
				game_framework::CTextDraw::Print(pDC, 370 - values[i].size() * 10, PANEL_SPACE + 120 + 25 * i, values[i]);

			}
			//升級費用
			std::vector<CPoint> p;
			p = { CPoint(101,458), CPoint(285,458), CPoint(101,550), CPoint(285,550) };
			for (int i = 0; i < 4; i++) {
				if (cost[i] < 9999999) {

					game_framework::CTextDraw::ChangeFontLog(pDC, 17, "微軟正黑體", RGB(255, 255, 255), 600);
					if (cost[i] > coins) {
						game_framework::CTextDraw::ChangeFontLog(pDC, 17, "微軟正黑體", RGB(255, 0, 0), 600);
					}
					game_framework::CTextDraw::Print(pDC, p[i].x, PANEL_SPACE + p[i].y, std::to_string(cost[i]));
				}
				else {
					game_framework::CTextDraw::ChangeFontLog(pDC, 17, "微軟正黑體", RGB(255, 0, 0), 600);
					game_framework::CTextDraw::Print(pDC, p[i].x, PANEL_SPACE + p[i].y, "MAX");
				}
			}
			//升級等級
			game_framework::CTextDraw::ChangeFontLog(pDC, 17, "微軟正黑體", RGB(255, 255, 255), 600);
			game_framework::CTextDraw::Print(pDC, 141, PANEL_SPACE + 428, std::to_string(last_selected_tower->GetUpgradeLevel()[0]) + " lvl");
			game_framework::CTextDraw::Print(pDC, 325, PANEL_SPACE + 428, std::to_string(last_selected_tower->GetUpgradeLevel()[1]) + " lvl");
			game_framework::CTextDraw::Print(pDC, 141, PANEL_SPACE + 520, std::to_string(last_selected_tower->GetUpgradeLevel()[2]) + " lvl");
			game_framework::CTextDraw::Print(pDC, 325, PANEL_SPACE + 520, std::to_string(last_selected_tower->GetUpgradeLevel()[3]) + " lvl");
			//顯示出售價格
			game_framework::CTextDraw::Print(pDC, 101, PANEL_SPACE + 630, std::to_string(int(last_selected_tower->GetTotalCost() / 2)));
		}
	}
	game_framework::CDDraw::ReleaseBackCDC();
	if (wave.GetStart()) {
		wave.showWaveText();
	}
	else {
		wave.showStartText();
	}
}
void gamemap::loadpic() {
	srand(unsigned(time(NULL)));
	coinIcon.LoadBitmapByString({ "resources/coins.bmp" }, RGB(255, 255, 255));
	coinIcon.SetTopLeft(10,10);
	healthIcon.LoadBitmapByString({ "resources/heart.bmp" }, RGB(255, 255, 255));
	healthIcon.SetTopLeft(350, 10);
	controlPanel.LoadBitmapByString({ "resources/control_panel_1.bmp",
									"resources/control_panel_2.bmp", 
									"resources/control_panel_3.bmp", }, RGB(255, 255, 255));
	controlPanelButton.LoadBitmapByString({ "resources/control_panel_button_minimize.bmp",
											"resources/control_panel_button_build.bmp",
											"resources/control_panel_button_info.bmp",
											"resources/control_panel_button_tower.bmp"}, RGB(255, 255, 255));
	controlPanel.SetTopLeft(-600, PANEL_SPACE);
	controlPanelButton.SetTopLeft(-200, PANEL_SPACE + 400);
	selected_box.LoadBitmapByString({ "resources/selected_box.bmp" }, RGB(255, 255, 255));
	selected_box.SetTopLeft(-100, -100);
	selected_block.LoadBitmapByString({ "resources/selected_block.bmp" }, RGB(255, 255, 255));
	selected_block.SetTopLeft(-100, -100);
	for (int i = 0; i < 4; i++) {
		upgradeButton[i].LoadBitmapByString({ "resources/upgrade_yes.bmp", "resources/upgrade_no.bmp" }, RGB(255, 255, 255));
	}
	upgradeButton[0].SetTopLeft(26, 415 + PANEL_SPACE);
	upgradeButton[1].SetTopLeft(210, 415 + PANEL_SPACE);
	upgradeButton[2].SetTopLeft(26, 507 + PANEL_SPACE);
	upgradeButton[3].SetTopLeft(210, 507 + PANEL_SPACE);
	confirmUpgrade.LoadBitmapByString({ "resources/confirm_upgrade.bmp" }, RGB(255, 255, 255));
	confirmUpgrade.SetTopLeft(-100, -100);
	for (int i = 0; i < 4; i++) {
		upgradeIcon[i].LoadBitmapByString({ "resources/upgrade_range.bmp",
			"resources/upgrade_power.bmp",
			"resources/upgrade_attack_speed.bmp",
			"resources/upgrade_spin_and_projectile_speed.bmp",
			"resources/upgrade_aim_time.bmp",
			"resources/upgrade_freezing%.bmp", 
			"resources/upgrade_freeze_time.bmp", 
			"resources/upgrade_defrosting_time.bmp",
			"resources/upgrade_stun_chance.bmp",
			"resources/upgrade_rotation_speed.bmp",
			"resources/upgrade_poison_damage.bmp" }, RGB(0, 0, 0));
		
	}
	upgradeIcon[0].SetTopLeft(36, 425 + PANEL_SPACE);
	upgradeIcon[1].SetTopLeft(220, 425 + PANEL_SPACE);
	upgradeIcon[2].SetTopLeft(36, 517 + PANEL_SPACE);
	upgradeIcon[3].SetTopLeft(220, 517 + PANEL_SPACE);
	greenCircle.LoadBitmapByString({ "resources/green_circle.bmp" }, RGB(255, 255, 255));
	greenCircle.SetTopLeft(-200, -200);
	blueCircle.LoadBitmapByString({ "resources/blue_circle.bmp" }, RGB(255, 255, 255));
	blueCircle.SetTopLeft(-200, -200);
	sellingTower.LoadBitmapByString({ "resources/selling_tower.bmp" }, RGB(255, 255, 255));
	sellingTower.SetTopLeft(514, 333);
	for (int i = 0; i < 10; i++) {
		std::vector<string> towerpics = {"resources/tower_button_basic.bmp",
			"resources/tower_button_sniper.bmp",
		    "resources/tower_button_cannon.bmp",
			"resources/tower_button_freezing.bmp",
			"resources/tower_button_venom.bmp", 
			"resources/tower_button_splash.bmp", 
			"resources/tower_button_blast.bmp", 
			"resources/tower_button_multishot.bmp", 
			"resources/tower_button_minigun.bmp", 
			"resources/tower_button_air.bmp", };
		towerButtons.push_back(game_framework::CMovingBitmap());
		towerButtons[i].LoadBitmapByString({ towerpics[i] } , RGB(255, 255, 255));
		towerButtons[i].SetTopLeft(((i % 4) * TOWER_BUTTON_SIZE), PANEL_SPACE + 300 + (i/4) * TOWER_BUTTON_SIZE);
	}
	gameSpeedButton.LoadBitmapByString({ "resources/gameSpeed1.bmp",
		"resources/gameSpeed2.bmp",
		"resources/gameSpeed3.bmp" }, RGB(255, 255, 255));
	gameSpeedButton.SetTopLeft(10, 800);
	for (std::shared_ptr<block> b : map) {
		b->loadPic();
		b -> resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
	for (std::shared_ptr<tile> t : tiles) {
		t->loadPic();
		t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
	for (std::shared_ptr<enemy> e : Enemy) {
		e->loadPic();
		e->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
	wave.loadClockPic();
}
void gamemap::resetshow() {
	for (std::shared_ptr<block> b : map) {
		b->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
	for (std::shared_ptr<tile> t : tiles) {
		t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
	for (std::shared_ptr<enemy> e : Enemy) {
		e->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
	selected_block.SetTopLeft(int(LEFT + moveX + selected_tile.x * TILE_SIZE*scale - 2 * scale), int(TOP + moveY + selected_tile.y * TILE_SIZE*scale - 2 * scale));
	greenCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - greenScale + 0.5) * TILE_SIZE*scale)
		, int(TOP + moveY + (selected_tile.y - greenScale + 0.5) * TILE_SIZE*scale));
	blueCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - blueScale + 0.5) * TILE_SIZE*scale)
		, int(TOP + moveY + (selected_tile.y - blueScale + 0.5) * TILE_SIZE*scale));
}
void gamemap::buildTower(int x, int y, std::string type) {
	for (std::shared_ptr<tile> t : tiles) {
		if (x == t->GetX() && y == t->GetY()) {
			if (!type.compare("basictower")) {
				std::shared_ptr<basictower> tower = std::make_shared<basictower>();
				t->buildTower(tower);
				t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);		
			}
			else if (!type.compare("sniper")) {
				std::shared_ptr<sniper> tower = std::make_shared<sniper>();
				t->buildTower(tower);
				t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
			}
			else if (!type.compare("cannon")) {
				std::shared_ptr<cannon> tower = std::make_shared<cannon>();
				t->buildTower(tower);
				t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
			}
			else if (!type.compare("freezing")) {
				std::shared_ptr<freezing> tower = std::make_shared<freezing>();
				t->buildTower(tower);
				t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
			}
			else if (!type.compare("venom")) {
				std::shared_ptr<venom> tower = std::make_shared<venom>();
				t->buildTower(tower);
				t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
			}
			else if (!type.compare("splash")) {
				/*
				std::shared_ptr<splash> tower = std::make_shared<splash>();
				t->buildTower(tower);
				t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
				*/
			}
			else if (!type.compare("blast")) {
				std::shared_ptr<blast> tower = std::make_shared<blast>();
				t->buildTower(tower);
				t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
			}
			else if (!type.compare("multishot")) {
				/*
				std::shared_ptr<multishot> tower = std::make_shared<multishot>();
				t->buildTower(tower);
				t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
				*/
			}
			else if (!type.compare("minigun")) {
				std::shared_ptr<minigun> tower = std::make_shared<minigun>();
				t->buildTower(tower);
				t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
			}
			else if (!type.compare("air")) {
				std::shared_ptr<air> tower = std::make_shared<air>();
				t->buildTower(tower);
				t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
			}
			break;
		}
	}
}
void gamemap::clickOnMap(CPoint point) {
	bool done = false; //表示此次點擊是否已經處理完成
	if (!is_control_panel_invisable) {
		//點到選單開啟時的按鈕
		if (showing_control_panel && 470 >= point.x && point.x >= 400 && PANEL_SPACE+537 >= point.y && point.y >= PANEL_SPACE+400) {
			showing_control_panel = false;
			controlPanel.SetTopLeft(-400, PANEL_SPACE);
			controlPanelButton.SetTopLeft(0, PANEL_SPACE + 400);
			done = true;
		}
		//點到選單關閉時的按鈕
		else if (!showing_control_panel && 70 >= point.x && point.x >= 0 && PANEL_SPACE + 537 >= point.y && point.y >= PANEL_SPACE + 400){
			showing_control_panel = true;
			controlPanel.SetTopLeft(0, PANEL_SPACE);
			controlPanelButton.SetTopLeft(400, PANEL_SPACE + 400);
			done = true;
		}
		//檢查是否點選在選單上
		if (!done && showing_control_panel && 400 >= point.x && point.x >= 0 && PANEL_SPACE + 700 >= point.y && point.y >= PANEL_SPACE) {
			//蓋塔模式
			if (controlPanelMode == 1 && point.y >= PANEL_SPACE + 300) {
				int selected = ((point.y - PANEL_SPACE - 300) / TOWER_BUTTON_SIZE) * 4 + (point.x / TOWER_BUTTON_SIZE);
				if (selected != last_selected && selected >= 0 && selected <= 11) {
					selected_box.SetTopLeft((selected % 4) * TOWER_BUTTON_SIZE, PANEL_SPACE + 300 + (selected / 4) * TOWER_BUTTON_SIZE);
					greenScale = origin_range[selected];
					greenCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - greenScale + 0.5) * TILE_SIZE*scale)
										, int(TOP + moveY + (selected_tile.y - greenScale + 0.5) * TILE_SIZE*scale) );
					last_selected = selected;
				} 
				else {
					bool is_build_success = false;
					if (selected == 0 && coins >= 40) {
						buildTower(selected_tile.x, selected_tile.y, "basictower");
						coins -= 40;
						is_build_success = true;
					}
					else if (selected == 1 && coins >= 100) {
						buildTower(selected_tile.x, selected_tile.y, "sniper");
						coins -= 100;
						is_build_success = true;
					}
					else if (selected == 2 && coins >= 60) {
						buildTower(selected_tile.x, selected_tile.y, "cannon");
						coins -= 60;
						is_build_success = true;
					}
					else if (selected == 3 && coins >= 70) {
						buildTower(selected_tile.x, selected_tile.y, "freezing");
						coins -= 70;
						is_build_success = true;
					}
					else if (selected == 4 && coins >= 120) {
						buildTower(selected_tile.x, selected_tile.y, "venom");
						coins -= 120;
						is_build_success = true;
					}
					else if (selected == 5 && coins >= 70) {
						buildTower(selected_tile.x, selected_tile.y, "splash");
						coins -= 70;
						//is_build_success = true;
					}
					else if (selected == 6 && coins >= 120) {
						buildTower(selected_tile.x, selected_tile.y, "blast");
						coins -= 120;
						is_build_success = true;
					}
					else if (selected == 7 && coins >= 90) {
						buildTower(selected_tile.x, selected_tile.y, "multishot");
						coins -= 90;
						//is_build_success = true;
					}
					else if (selected == 8 && coins >= 160) {
						buildTower(selected_tile.x, selected_tile.y, "minigun");
						coins -= 160;
						is_build_success = true;
					}
					else if (selected == 9 && coins >= 60) {
						buildTower(selected_tile.x, selected_tile.y, "air");
						coins -= 60;
						is_build_success = true;
					}
					//蓋完塔之後跳到升級頁面(tower模式)
					if (is_build_success) {
						controlPanelMode = 3; 
						for (std::shared_ptr<tile> t : tiles) {
							if (t->GetX() == selected_tile.x && t->GetY() == selected_tile.y && t->haveTower()) {
								last_selected_tower = t->GetTower();
							}
						}
						blueScale = origin_range[selected];
						blueCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - blueScale + 0.5) * TILE_SIZE*scale)
							, int(TOP + moveY + (selected_tile.y - blueScale + 0.5) * TILE_SIZE*scale));
						for (int i = 0; i < 4; i++) {
							upgradeIcon[i].SetFrameIndexOfBitmap(last_selected_tower->GetUpgradeIcon()[i]);
						}
						confirmUpgrade.SetTopLeft(-100, -100);
					}
				}
			}
			else if (controlPanelMode == 3) {
				//左上
				if (188 >= point.x && point.x >= 26 && 493 + PANEL_SPACE >= point.y && point.y >= 415 + PANEL_SPACE) {
					if (last_selected_upgrade == 1 && coins >= last_selected_tower->GetUpgradeCost()[0]) {
						coins -= last_selected_tower ->GetUpgradeCost()[0];
						last_selected_tower->upgrade1();
						//由於左上一定是範圍升級 所以只在這裡重置藍圈
						blueScale = last_selected_tower->GetRange();
						blueCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - blueScale + 0.5) * TILE_SIZE*scale)
							, int(TOP + moveY + (selected_tile.y - blueScale + 0.5) * TILE_SIZE*scale));
						if (last_selected_tower->GetUpgradeLevel()[0] >= 10 || coins < last_selected_tower->GetUpgradeCost()[0]) {
							last_selected_upgrade = -1;
							confirmUpgrade.SetTopLeft(-200, -200 + PANEL_SPACE);
						}
						else {
							//由於左上一定是範圍升級 所以只在這裡重置綠圈
							greenScale = last_selected_tower->GetRange() + last_selected_tower->GetAffected(1)[0][1];
							greenCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - greenScale + 0.5) * TILE_SIZE*scale)
								, int(TOP + moveY + (selected_tile.y - greenScale + 0.5) * TILE_SIZE*scale));
						}
					}
					else if (coins >= last_selected_tower->GetUpgradeCost()[0] && last_selected_tower->GetUpgradeLevel()[0] <= 10){
						greenScale = last_selected_tower->GetRange() + last_selected_tower->GetAffected(1)[0][1];
						greenCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - greenScale + 0.5) * TILE_SIZE*scale)
							, int(TOP + moveY + (selected_tile.y - greenScale + 0.5) * TILE_SIZE*scale));
						last_selected_upgrade = 1;
						confirmUpgrade.SetTopLeft(26, 415 + PANEL_SPACE);
					}
				}
				//右上
				else if (372 >= point.x && point.x >= 210 && 493 + PANEL_SPACE >= point.y && point.y >= 415 + PANEL_SPACE) {
					if (last_selected_upgrade == 2 && coins >= last_selected_tower->GetUpgradeCost()[1]) {
						coins -= last_selected_tower->GetUpgradeCost()[1];
						last_selected_tower->upgrade2();
						if (last_selected_tower->GetUpgradeLevel()[1] >= 10 || coins < last_selected_tower->GetUpgradeCost()[1]) {
							last_selected_upgrade = -1;
							confirmUpgrade.SetTopLeft(-200, -200 + PANEL_SPACE);
						}
					}
					else if (coins >= last_selected_tower->GetUpgradeCost()[1] && last_selected_tower->GetUpgradeLevel()[1] <= 10) {
						last_selected_upgrade = 2;
						confirmUpgrade.SetTopLeft(210, 415 + PANEL_SPACE);
					}
				}
				//左下
				else if (188 >= point.x && point.x >= 26 && 586 + PANEL_SPACE >= point.y && point.y >= 507 + PANEL_SPACE) {
					if (last_selected_upgrade == 3 && coins >= last_selected_tower->GetUpgradeCost()[2]) {
						coins -= last_selected_tower->GetUpgradeCost()[2];
						last_selected_tower->upgrade3();
						if (last_selected_tower->GetUpgradeLevel()[2] >= 10 || coins < last_selected_tower->GetUpgradeCost()[2]) {
							last_selected_upgrade = -1;
							confirmUpgrade.SetTopLeft(-200, -200 + PANEL_SPACE);
						}
					}
					else if (coins >= last_selected_tower->GetUpgradeCost()[2] && last_selected_tower->GetUpgradeLevel()[2] <= 10) {
						last_selected_upgrade = 3;
						confirmUpgrade.SetTopLeft(26, 507 + PANEL_SPACE);
					}
				}
				//右下
				else if (372 >= point.x && point.x >= 210 && 586 + PANEL_SPACE >= point.y && point.y >= 507 + PANEL_SPACE) {
					if (last_selected_upgrade == 4 && coins >= last_selected_tower->GetUpgradeCost()[3]) {
						coins -= last_selected_tower->GetUpgradeCost()[3];
						last_selected_tower->upgrade4();
						if (last_selected_tower->GetUpgradeLevel()[3] >= 10 || coins < last_selected_tower->GetUpgradeCost()[3]) {
							last_selected_upgrade = -1;
							confirmUpgrade.SetTopLeft(-200, -200 + PANEL_SPACE);
						}
					}
					else if (coins >= last_selected_tower->GetUpgradeCost()[3] && last_selected_tower->GetUpgradeLevel()[3] <= 10) {
						last_selected_upgrade = 4;
						confirmUpgrade.SetTopLeft(210, 507 + PANEL_SPACE);
					}
				}
				//賣塔
				else if (188 >= point.x && point.x >= 27 && 679 + PANEL_SPACE >= point.y && point.y >= 602 + PANEL_SPACE) {
					is_selling_visable = true;
				}
				blueScale = last_selected_tower->GetRange();
				blueCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - blueScale + 0.5) * TILE_SIZE*scale)
					, int(TOP + moveY + (selected_tile.y - blueScale + 0.5) * TILE_SIZE*scale));
			}
			done = true;
		}
	}
	if (!done && is_selling_visable && 887 >= point.x && point.x >= 514 && 567 >= point.y && point.y >= 333) {
		//否
		if (689 >= point.x && point.x >= 526 && 560 >= point.y && point.y >= 473) {
			is_selling_visable = false;
		}
		//是
		else if (970 >= point.x && point.x >= 709 && 560 >= point.y && point.y >= 473) {
			for (std::shared_ptr<tile> t : tiles) {
				if (t->GetX() == selected_tile.x && t->GetY() == selected_tile.y && t->haveTower()) {
					coins += t->sellTower();
					is_selling_visable = false;
					controlPanelMode = 1;
				}
			}
		}
		done = true;
	}
	if (!done && 85 >= point.x && point.x >= 0 && 875 >= point.y && point.y >= 800) {
		if (gameSpeed == 1) {
			gameSpeed = 2;
			gameSpeedButton.SetFrameIndexOfBitmap(1);
		}
		else if (gameSpeed == 2) {
			gameSpeed = 4;
			gameSpeedButton.SetFrameIndexOfBitmap(2);
		}
		else if (gameSpeed == 4) {
			gameSpeed = 1;
			gameSpeedButton.SetFrameIndexOfBitmap(0);
		}
		done = true;
	}
	if (!done) {
		for (std::shared_ptr<tile> t : tiles) {
			//點在tiles上
			if (t->ifClickOn(TOP, LEFT, TILE_SIZE, scale, moveX, moveY, point.x, point.y)) {
				//處理控制面板及按鈕
				if (showing_control_panel) {
					controlPanel.SetTopLeft(0, PANEL_SPACE);
					controlPanelButton.SetTopLeft(400, PANEL_SPACE + 400);
				}
				else {
					controlPanel.SetTopLeft(-400, PANEL_SPACE);
					controlPanelButton.SetTopLeft(0, PANEL_SPACE + 400);
				}
				selected_tile = CPoint(t->GetX(), t->GetY());
				selected_block.SetTopLeft(int(LEFT + moveX + t->GetX() * TILE_SIZE*scale - 2*scale), int(TOP + moveY + t->GetY() * TILE_SIZE*scale - 2 * scale));

				if (t->haveTower()) {
					last_selected_tower = t->GetTower();
					blueScale = last_selected_tower->GetRange();
					greenCircle.SetTopLeft(-100, 100);
					greenScale = 0.1;
				}
				else {
					blueScale = 0.1;
					if (last_selected != -1) {
						greenScale = origin_range[last_selected];
					}
					greenCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - greenScale + 0.5) * TILE_SIZE*scale)
						, int(TOP + moveY + (selected_tile.y - greenScale + 0.5) * TILE_SIZE*scale));
				}
				blueCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - blueScale + 0.5) * TILE_SIZE*scale)
					, int(TOP + moveY + (selected_tile.y - blueScale + 0.5) * TILE_SIZE*scale));
				//處理控制事件
				if (t->haveTower()) {
					controlPanelMode = 3;
					for (int i = 0; i < 4; i++) {
						upgradeIcon[i].SetFrameIndexOfBitmap(t->GetTower()->GetUpgradeIcon()[i]);
					}
					last_selected_upgrade = -1;
					confirmUpgrade.SetTopLeft(-100, -100);
				}
				else {
					controlPanelMode = 1;
				}
				is_control_panel_invisable = false;
				done = true;
				break;
			}
		}
	}
	if (!done) {
		for (std::shared_ptr<block> b : map) {
			if (b->ifClickOn(TOP, LEFT, TILE_SIZE, scale, moveX, moveY, point.x, point.y)) {
				if (showing_control_panel) {
					controlPanel.SetTopLeft(0, PANEL_SPACE);
					controlPanelButton.SetTopLeft(400, PANEL_SPACE + 400);
				}
				else {
					controlPanel.SetTopLeft(-400, PANEL_SPACE);
					controlPanelButton.SetTopLeft(0, PANEL_SPACE + 400);
				}
				selected_block.SetTopLeft(int(LEFT + moveX + b->GetX() * (TILE_SIZE)*scale - 2 * scale), int(TOP + moveY + b->GetY() * (TILE_SIZE)*scale - 2 * scale));
				controlPanelMode = 2;
				selected_tile = CPoint(b->GetX(), b->GetY());
				is_control_panel_invisable = false;
				done = true;
				break;
			}
		}
	}
	//處理控制面板按鈕圖片
	if (showing_control_panel) {
		controlPanelButton.SetFrameIndexOfBitmap(0);
	}
	else {
		controlPanelButton.SetFrameIndexOfBitmap(controlPanelMode);
	}
	//點到沒有設定的地方
	if (!done) {
		controlPanel.SetTopLeft(-600, PANEL_SPACE);
		controlPanelButton.SetTopLeft(-200, PANEL_SPACE + 400);
		is_control_panel_invisable = true;
		selected_block.SetTopLeft(-100, -100);
		//greenCircle.SetTopLeft(-200, -200);
		//greenScale = 0.1;
		blueCircle.SetTopLeft(-200, -200);
		blueScale = 0.1;
		is_selling_visable = false;
	}
	wave.IsClockClicked(point);
}
void gamemap::newblock(std::shared_ptr<block> block) {
	map.push_back(block);
}
void gamemap::newtile(std::shared_ptr<tile> tile) {
	tiles.push_back(tile);
}
void gamemap::newEnemy(std::shared_ptr<enemy> enemy) {
	Enemy.push_back(enemy);
	enemy->loadPic();
	//enemy->HealthBar.SetTopLeft(int(enemy->GetX()), int(enemy->GetY()));
}
void gamemap::TESTMAP1() {
	newblock(std::make_shared<portal>(1,0));
	newblock(std::make_shared<road>(1, 1));
	newblock(std::make_shared<road>(1, 2));
	newblock(std::make_shared<road>(1, 3));
	newblock(std::make_shared<road>(1, 4));
	newblock(std::make_shared<road>(1, 5));
	newblock(std::make_shared<road>(2, 5));
	newblock(std::make_shared<road>(3, 5));
	newblock(std::make_shared<road>(4, 5));
	newblock(std::make_shared<road>(5, 5));
	newblock(std::make_shared<road>(5, 4));
	newblock(std::make_shared<road>(5, 3));
	newblock(std::make_shared<road>(5, 2));
	newblock(std::make_shared<road>(5, 1));
	newblock(std::make_shared<road>(6, 1));
	newblock(std::make_shared<road>(7, 1));
	newblock(std::make_shared<road>(8, 1));
	newblock(std::make_shared<road>(8, 2));
	newblock(std::make_shared<road>(8, 3));
	newblock(std::make_shared<road>(8, 4));
	newblock(std::make_shared<base>(8, 5));
	newtile(std::make_shared<tile>(0, 3));
	newtile(std::make_shared<tile>(0, 4));
	newtile(std::make_shared<tile>(0, 5));
	newtile(std::make_shared<tile>(2, 1));
	newtile(std::make_shared<tile>(2, 2));
	newtile(std::make_shared<tile>(2, 3));
	newtile(std::make_shared<tile>(2, 4));
	newtile(std::make_shared<tile>(3, 4));
	newtile(std::make_shared<tile>(4, 4));
	newtile(std::make_shared<tile>(1, 6));
	newtile(std::make_shared<tile>(2, 6));
	newtile(std::make_shared<tile>(3, 6));
	newtile(std::make_shared<tile>(4, 6));
	newtile(std::make_shared<tile>(5, 6));
	newtile(std::make_shared<tile>(6, 5));
	newtile(std::make_shared<tile>(6, 4));
	newtile(std::make_shared<tile>(6, 3));
	newtile(std::make_shared<tile>(6, 2));
	newtile(std::make_shared<tile>(7, 2));
	newtile(std::make_shared<tile>(7, 3));
	newtile(std::make_shared<tile>(7, 0));
	newtile(std::make_shared<tile>(8, 0));
	newtile(std::make_shared<tile>(9, 1));
	newtile(std::make_shared<tile>(9, 2));
	Setdifficulty(0.7);
	enemyPath = { { CPoint(1, 0), CPoint(1, 5), CPoint(5, 5), CPoint(5, 1), CPoint(8, 1), CPoint(8, 5) } };
}
void gamemap::SummonTestEnemy() {
	std::shared_ptr<Air> enemy = std::make_shared<Air>(0.7, 25, enemyPath[0]);
	if (enemy) {
		newEnemy(enemy);
	}
}
void gamemap::CheatCoin() {
	coins = 99999;
}
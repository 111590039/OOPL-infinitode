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
	for (std::shared_ptr<tile> t : tiles) {
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
		t->GetTower()->move(time, t->GetX(), t->GetY());
		t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
	//敵人移動
	for (size_t i = 0; i < Enemy.size(); i++) {
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
		greenCircle.ShowBitmap(greenScale * 0.5* scale);
	}
	if (controlPanelMode == 3 && !is_control_panel_invisable) {
		blueCircle.ShowBitmap(blueScale * 0.5* scale);
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
			for (std::shared_ptr<tile> t : tiles) {
				if (selected_tile.x == t->GetX() && selected_tile.y == t->GetY()) {
					std::vector<int> cost = t->GetTower()->GetUpgradeCost();
					for (int i = 0; i < 4; i++) {
						if (cost[i] > coins) {
							upgradeButton[i].SetFrameIndexOfBitmap(1);
						}
						else {
							upgradeButton[i].SetFrameIndexOfBitmap(0);
						}
						upgradeButton[i].ShowBitmap();
					}
					break;
				}
			}
			confirmUpgrade.ShowBitmap();
			for (int i = 0; i < 4; i++) {
				upgradeIcon[i].ShowBitmap();
			}
		}
	}
	coinIcon.ShowBitmap(0.9);
	healthIcon.ShowBitmap(0.9);
}
void gamemap::showtext() {
	CDC *pDC = game_framework::CDDraw::GetBackCDC();
	//選單文字
	game_framework::CTextDraw::ChangeFontLog(pDC, 40, "微軟正黑體", RGB(255, 255, 255), 1200);
	game_framework::CTextDraw::Print(pDC, 100, 20,std::to_string(coins));
	game_framework::CTextDraw::Print(pDC, 440, 20, std::to_string(health));
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
			for (game_framework::CMovingBitmap b : towerButtons) {
				game_framework::CTextDraw::Print(pDC, b.GetLeft()+70 , b.GetTop()+70 , "40");
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
			for (std::shared_ptr<tile> t : tiles) {
				if (selected_tile.x  == t->GetX() && selected_tile.y == t->GetY()) {
					std::shared_ptr<tower> T = t->GetTower();
					std::vector<int> cost = T->GetUpgradeCost();
					std::vector<string> names = T->GetAttributeName();
					std::vector<string> values = T->GetAttributeValue();
					game_framework::CTextDraw::ChangeFontLog(pDC, 42, "微軟正黑體", RGB(255, 255, 255), 1200);
					game_framework::CTextDraw::Print(pDC, 20, PANEL_SPACE + 20, T->GetTowerName());
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
					std::vector<std::vector<double>> affected = T->GetAffected(last_selected_upgrade);

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
					game_framework::CTextDraw::Print(pDC, 141, PANEL_SPACE + 428, std::to_string(T->GetUpgradeLevel()[0]) + " lvl");
					game_framework::CTextDraw::Print(pDC, 325, PANEL_SPACE + 428, std::to_string(T->GetUpgradeLevel()[1]) + " lvl");
					game_framework::CTextDraw::Print(pDC, 141, PANEL_SPACE + 520, std::to_string(T->GetUpgradeLevel()[2]) + " lvl");
					game_framework::CTextDraw::Print(pDC, 325, PANEL_SPACE + 520, std::to_string(T->GetUpgradeLevel()[3]) + " lvl");
					break;
				}
			}
		}
	}
	game_framework::CDDraw::ReleaseBackCDC();
}
void gamemap::loadpic() {
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
			"resources/upgrade_spin_and_projectile_speed.bmp"}, RGB(0, 0, 0));
	}
	upgradeIcon[0].SetTopLeft(36, 425 + PANEL_SPACE);
	upgradeIcon[1].SetTopLeft(220, 425 + PANEL_SPACE);
	upgradeIcon[2].SetTopLeft(36, 517 + PANEL_SPACE);
	upgradeIcon[3].SetTopLeft(220, 517 + PANEL_SPACE);
	greenCircle.LoadBitmapByString({ "resources/green_circle.bmp" }, RGB(255, 255, 255));
	greenCircle.SetTopLeft(-200, -200);
	blueCircle.LoadBitmapByString({ "resources/blue_circle.bmp" }, RGB(255, 255, 255));
	blueCircle.SetTopLeft(-200, -200);
	for (int i = 0; i < 1; i++) {
		std::vector<string> towerpics = {"resources/tower_button_basic.bmp"};
		towerButtons.push_back(game_framework::CMovingBitmap());
		towerButtons[i].LoadBitmapByString({ towerpics[i] } , RGB(255, 255, 255));
		towerButtons[i].SetTopLeft(((i % 4) * TOWER_BUTTON_SIZE), PANEL_SPACE + 300 + (i/4) * TOWER_BUTTON_SIZE);
	}
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
	greenCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - greenScale + 0.5) * TILE_SIZE*scale + 5 * greenScale * scale)
		, int(TOP + moveY + (selected_tile.y - greenScale + 0.5) * TILE_SIZE*scale + 5 * greenScale * scale));
	blueCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - blueScale + 0.5) * TILE_SIZE*scale + 5 * blueScale * scale)
		, int(TOP + moveY + (selected_tile.y - blueScale + 0.5) * TILE_SIZE*scale + 5 * blueScale * scale));
}
void gamemap::buildTower(int x, int y, std::string type) {
	for (std::shared_ptr<tile> t : tiles) {
		if (x == t->GetX() && y == t->GetY()) {
			if (!type.compare("basictower")) {
				std::shared_ptr<basictower> tower = std::make_shared<basictower>();
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
					greenCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - greenScale + 0.5) * TILE_SIZE*scale + 5 * greenScale * scale)
										, int(TOP + moveY + (selected_tile.y - greenScale + 0.5) * TILE_SIZE*scale + 5 * greenScale * scale) );
					last_selected = selected;
				} 
				else {
					bool is_build_success = false;
					if (selected == 0 && coins >= 40) {
						buildTower(selected_tile.x, selected_tile.y, "basictower");
						coins -= 40;
						is_build_success = true;
					}
					//蓋完塔之後跳到升級頁面(tower模式)
					if (is_build_success) {
						controlPanelMode = 3; 
						blueScale = origin_range[selected];
						blueCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - blueScale + 0.5) * TILE_SIZE*scale + 5 * blueScale * scale)
							, int(TOP + moveY + (selected_tile.y - blueScale + 0.5) * TILE_SIZE*scale + 5 * blueScale * scale));
						for (std::shared_ptr<tile> t : tiles) {
							if (t->GetX() == selected_tile.x && t->GetY() == selected_tile.y) {
								for (int i = 0; i < 4; i++) {
									upgradeIcon[i].SetFrameIndexOfBitmap(t->GetTower()->GetUpgradeIcon()[i]);
								}
								confirmUpgrade.SetTopLeft(-100, -100);
								break;
							}
						}
					}
				}
			}
			else if (controlPanelMode == 3) {
				std::shared_ptr<tower> T = nullptr;
				for (std::shared_ptr<tile> t : tiles) {
					if (t->GetX() == selected_tile.x && t->GetY() == selected_tile.y) {
						T = t->GetTower();
						break;
					}
				}
				//左上
				if (188 >= point.x && point.x >= 26 && 493 + PANEL_SPACE >= point.y && point.y >= 415 + PANEL_SPACE) {
					if (last_selected_upgrade == 1 && coins >= T->GetUpgradeCost()[0]) {
						coins -= T->GetUpgradeCost()[0];
						T->upgrade1();
						//由於左上一定是範圍升級 所以只在這裡重置藍圈
						blueScale = T->GetRange();
						blueCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - blueScale + 0.5) * TILE_SIZE*scale + 5 * blueScale * scale)
							, int(TOP + moveY + (selected_tile.y - blueScale + 0.5) * TILE_SIZE*scale + 5 * blueScale * scale));
						if ( T->GetUpgradeLevel()[0] >= 10 || coins < T->GetUpgradeCost()[0]) {
							last_selected_upgrade = -1;
							confirmUpgrade.SetTopLeft(-200, -200 + PANEL_SPACE);
						}
						else {
							//由於左上一定是範圍升級 所以只在這裡重置綠圈
							greenScale = T->GetRange() + T->GetAffected(1)[0][1];
							greenCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - greenScale + 0.5) * TILE_SIZE*scale + 5 * greenScale * scale)
								, int(TOP + moveY + (selected_tile.y - greenScale + 0.5) * TILE_SIZE*scale + 5 * greenScale * scale));
						}
					}
					else if (coins >= T->GetUpgradeCost()[0] && T->GetUpgradeLevel()[0] <= 10){
						greenScale = T->GetRange() + T->GetAffected(1)[0][1];
						greenCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - greenScale + 0.5) * TILE_SIZE*scale + 5 * greenScale * scale)
							, int(TOP + moveY + (selected_tile.y - greenScale + 0.5) * TILE_SIZE*scale + 5 * greenScale * scale));
						last_selected_upgrade = 1;
						confirmUpgrade.SetTopLeft(26, 415 + PANEL_SPACE);
					}
				}
				//右上
				else if (372 >= point.x && point.x >= 210 && 493 + PANEL_SPACE >= point.y && point.y >= 415 + PANEL_SPACE) {
					if (last_selected_upgrade == 2 && coins >= T->GetUpgradeCost()[1]) {
						coins -= T->GetUpgradeCost()[1];
						T->upgrade2();
						if (T->GetUpgradeLevel()[1] >= 10 || coins < T->GetUpgradeCost()[1]) {
							last_selected_upgrade = -1;
							confirmUpgrade.SetTopLeft(-200, -200 + PANEL_SPACE);
						}
					}
					else if (coins >= T->GetUpgradeCost()[1] && T->GetUpgradeLevel()[1] <= 10) {
						last_selected_upgrade = 2;
						confirmUpgrade.SetTopLeft(210, 415 + PANEL_SPACE);
					}
				}
				//左下
				else if (188 >= point.x && point.x >= 26 && 586 + PANEL_SPACE >= point.y && point.y >= 507 + PANEL_SPACE) {
					if (last_selected_upgrade == 3 && coins >= T->GetUpgradeCost()[2]) {
						coins -= T->GetUpgradeCost()[2];
						T->upgrade3();
						if (T->GetUpgradeLevel()[2] >= 10 || coins < T->GetUpgradeCost()[2]) {
							last_selected_upgrade = -1;
							confirmUpgrade.SetTopLeft(-200, -200 + PANEL_SPACE);
						}
					}
					else if (coins >= T->GetUpgradeCost()[2] && T->GetUpgradeLevel()[2] <= 10) {
						last_selected_upgrade = 3;
						confirmUpgrade.SetTopLeft(26, 507 + PANEL_SPACE);
					}
				}
				//右下
				else if (372 >= point.x && point.x >= 210 && 586 + PANEL_SPACE >= point.y && point.y >= 507 + PANEL_SPACE) {
					if (last_selected_upgrade == 4 && coins >= T->GetUpgradeCost()[3]) {
						coins -= T->GetUpgradeCost()[3];
						T->upgrade4();
						if (T->GetUpgradeLevel()[3] >= 10 || coins < T->GetUpgradeCost()[3]) {
							last_selected_upgrade = -1;
							confirmUpgrade.SetTopLeft(-200, -200 + PANEL_SPACE);
						}
					}
					else if (coins >= T->GetUpgradeCost()[3] && T->GetUpgradeLevel()[3] <= 10) {
						last_selected_upgrade = 4;
						confirmUpgrade.SetTopLeft(210, 507 + PANEL_SPACE);
					}
				}
				blueScale = T->GetRange();
				blueCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - blueScale + 0.5) * TILE_SIZE*scale + 5 * blueScale * scale)
					, int(TOP + moveY + (selected_tile.y - blueScale + 0.5) * TILE_SIZE*scale + 5 * blueScale * scale));
			}
			done = true;
		}
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
					blueScale = t->GetTower()->GetRange();
					greenCircle.SetTopLeft(-100, 100);
					greenScale = 0.1;
				}
				else {
					blueScale = 0.1;
					if (last_selected != -1) {
						greenScale = origin_range[last_selected];
					}
					greenCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - greenScale + 0.5) * TILE_SIZE*scale + 5 * greenScale * scale)
						, int(TOP + moveY + (selected_tile.y - greenScale + 0.5) * TILE_SIZE*scale + 5 * greenScale * scale));
				}
				blueCircle.SetTopLeft(int(LEFT + moveX + (selected_tile.x - blueScale + 0.5) * TILE_SIZE*scale + 5 * blueScale * scale)
					, int(TOP + moveY + (selected_tile.y - blueScale + 0.5) * TILE_SIZE*scale + 5 * blueScale * scale));
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
	}
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
	newblock(std::make_shared<road>(1, 5));
	newblock(std::make_shared<road>(2, 5));
	newblock(std::make_shared<road>(3, 5));
	newblock(std::make_shared<road>(4, 5));
	newblock(std::make_shared<road>(5, 5));
	newblock(std::make_shared<road>(6, 5));
	newblock(std::make_shared<road>(6, 4));
	newblock(std::make_shared<road>(6, 3));
	newblock(std::make_shared<road>(6, 2));
	newblock(std::make_shared<road>(7, 2));
	newblock(std::make_shared<road>(8, 2));
	newblock(std::make_shared<road>(9, 2));
	newblock(std::make_shared<road>(9, 3));
	newblock(std::make_shared<road>(9, 4));
	newblock(std::make_shared<road>(9, 5));
	newblock(std::make_shared<base>(9, 6));
	newtile(std::make_shared<tile>(0, 3));
	newtile(std::make_shared<tile>(0, 4));
	newtile(std::make_shared<tile>(0, 5));
	newtile(std::make_shared<tile>(2, 1));
	newtile(std::make_shared<tile>(2, 2));
	newtile(std::make_shared<tile>(2, 3));
	newtile(std::make_shared<tile>(2, 4));
	newtile(std::make_shared<tile>(3, 4));
	newtile(std::make_shared<tile>(4, 4));
	Setdifficulty(0.7);
	enemyPath = { CPoint(1, 0), CPoint(1, 5), CPoint(6, 5), CPoint(6, 2), CPoint(9, 2), CPoint(9, 6) };
	newEnemy(std::make_shared<Regular>(0.7, 1, enemyPath));
}
void gamemap::SummonTestEnemy() {
	std::shared_ptr<Regular> enemy = std::make_shared<Regular>(0.7, 1, enemyPath);
	if (enemy) {
		newEnemy(enemy);
	}
}
void gamemap::CheatCoin() {
	coins = 99999;
}
#include "stdafx.h"
#include "gamemap.h"

#define TOP 0
#define LEFT 0
#define PANEL_SPACE 100
#define TILE_SIZE 65

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
//讓整張地圖顯示
void gamemap::drawmap() {
	for (std::shared_ptr<block> b : map) {
		b->show(scale);
	}
	for (std::shared_ptr<tile> t : tiles) {
		t->show(scale);
	}
	for (std::shared_ptr<enemy> e : Enemy) {
		e->show(scale);
	}
	controlPanel.ShowBitmap();
	controlPanelButton.ShowBitmap();
	if (controlPanelMode ==  1 && showing_control_panel && !is_control_panel_invisable) {
		for (game_framework::CMovingBitmap b : towerButtons) {
			b.ShowBitmap();
		}
	}
}
void gamemap::loadpic() {
	controlPanel.LoadBitmapByString({ "resources/control_panel.bmp" }, RGB(255, 255, 255));
	controlPanelButton.LoadBitmapByString({ "resources/control_panel_button_minimize.bmp",
											"resources/control_panel_button_build.bmp",
											"resources/control_panel_button_info.bmp",
											"resources/control_panel_button_tower.bmp"}, RGB(255, 255, 255));
	controlPanel.SetTopLeft(-600, PANEL_SPACE);
	controlPanelButton.SetTopLeft(-200, PANEL_SPACE + 400);
	for (int i = 0; i < 1; i++) {
		std::vector<string> towernames = { "Basic" };
		std::vector<string> towerpics = {"resources/Base_Basic.bmp"};
		towerButtons.push_back(game_framework::CMovingBitmap());
		towerButtons[i].LoadBitmapByString({ towerpics[i] } , RGB(255, 255, 255));
		towerButtons[i].SetTopLeft(20 +((i % 4) * TILE_SIZE), PANEL_SPACE + 350 + (i/4) * TILE_SIZE); // 未驗證是否正確
	}
	for (std::shared_ptr<block> b : map) {
		b->loadPic();
		b -> resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
	for (std::shared_ptr<block> t : tiles) {
		t->loadPic();
		t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
	for (std::shared_ptr<enemy> e : Enemy) {
		e->loadPic();
	}
}
void gamemap::resetshow() {
	for (std::shared_ptr<block> b : map) {
		b->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
	for (std::shared_ptr<tile> t : tiles) {
		t->resetShow(TOP, LEFT, TILE_SIZE, scale, moveX, moveY);
	}
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
	bool done = false;
	if (!is_control_panel_invisable) {
		//選單開啟時的按鈕
		if (showing_control_panel && 470 >= point.x && point.x >= 400 && PANEL_SPACE+537 >= point.y && point.y >= PANEL_SPACE+400) {
			showing_control_panel = false;
			controlPanel.SetTopLeft(-400, PANEL_SPACE);
			controlPanelButton.SetTopLeft(0, PANEL_SPACE + 400);
			controlPanelButton.SetFrameIndexOfBitmap(lastControlPanelPic);
			done = true;
		}
		//選單關閉時的按鈕
		else if (!showing_control_panel && 70 >= point.x && point.x >= 0 && PANEL_SPACE + 537 >= point.y && point.y >= PANEL_SPACE + 400){
			showing_control_panel = true;
			controlPanel.SetTopLeft(0, PANEL_SPACE);
			controlPanelButton.SetTopLeft(400, PANEL_SPACE + 400);
			controlPanelButton.SetFrameIndexOfBitmap(0);
			done = true;
		}
		//蓋塔模式
		if (controlPanelMode == 1 && showing_control_panel && 400 >= point.x && point.x >= 0 && PANEL_SPACE + 700 >= point.y && point.y >= PANEL_SPACE) {
			//int x = point.x - 20 / TILE_SIZE; //(i % 4);
			//int y = (point.y - PANEL_SPACE - 350) / TILE_SIZE;// (i / 4);
			int selected = ((point.y - PANEL_SPACE - 350) / TILE_SIZE) * 4 + ((point.x - 20) / TILE_SIZE);
			if (selected == 0) {
				buildTower(selected_tile.x, selected_tile.y, "basictower");
			}

			done = true;
		}
	}
	if (!done) {
		for (std::shared_ptr<tile> t : tiles) {
			if (t->ifClickOn(TOP, LEFT, TILE_SIZE, scale, moveX, moveY, point.x, point.y)) {
				//處理控制面板及按鈕
				if (showing_control_panel) {
					controlPanel.SetTopLeft(0, PANEL_SPACE);
					controlPanelButton.SetTopLeft(400, PANEL_SPACE + 400);
					controlPanelButton.SetFrameIndexOfBitmap(0);
				}
				else {
					controlPanel.SetTopLeft(-400, PANEL_SPACE);
					controlPanelButton.SetTopLeft(0, PANEL_SPACE + 400);
					if (t->haveTower()) {
						controlPanelButton.SetFrameIndexOfBitmap(3);
						lastControlPanelPic = 3;
					}
					else {
						controlPanelButton.SetFrameIndexOfBitmap(1);
						lastControlPanelPic = 1;
					}
				}
				//處理控制事件
				if (t->haveTower()) {
					controlPanelMode = 3;
				}
				else {
					controlPanelMode = 1;
				}
				selected_tile = CPoint(t->GetX(), t->GetY());
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
					controlPanelButton.SetFrameIndexOfBitmap(0);
				}
				else {
					controlPanel.SetTopLeft(-400, PANEL_SPACE);
					controlPanelButton.SetTopLeft(0, PANEL_SPACE + 400);
					controlPanelButton.SetFrameIndexOfBitmap(2);
					lastControlPanelPic = 2;
				}
				controlPanelMode = 2;
				is_control_panel_invisable = false;
				done = true;
				break;
			}
		}
	}
	if (!done) {
		controlPanel.SetTopLeft(-600, PANEL_SPACE);
		controlPanelButton.SetTopLeft(-200, PANEL_SPACE + 400);
		is_control_panel_invisable = true;
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
}
void gamemap::TESTMAP1() {
	newblock(std::make_shared<portal>(1,0,0.7));
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
	newEnemy(std::make_shared<Regular>("Regular", 1.0, 1.0, 1.0, 1.0));
}
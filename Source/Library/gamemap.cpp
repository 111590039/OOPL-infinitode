#include "stdafx.h"
#include "gamemap.h"

#define TOP 0
#define LEFT 0
#define PANEL_SPACE 100
#define TILE_SIZE 65
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
	selected_block.ShowBitmap(scale);
	controlPanel.ShowBitmap();
	controlPanelButton.ShowBitmap();
	if (controlPanelMode ==  1 && showing_control_panel && !is_control_panel_invisable) {
		//選單按鈕圖片
		for (game_framework::CMovingBitmap b : towerButtons) {
			b.ShowBitmap();
		}	
		selected_box.ShowBitmap();
	}

}
void gamemap::showtext() {
	CDC *pDC = game_framework::CDDraw::GetBackCDC();
	//選單文字
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
						game_framework::CTextDraw::Print(pDC, 20, PANEL_SPACE + 100, "等級難度:"); //未完成
					}
					break;
				}
			}
		}
		else if (controlPanelMode == 3) {
			for (std::shared_ptr<tile> t : tiles) {
				if (selected_tile.x  == t->GetX() && selected_tile.y == t->GetY()) {
					game_framework::CTextDraw::ChangeFontLog(pDC, 42, "微軟正黑體", RGB(255, 255, 255), 1200);
					game_framework::CTextDraw::Print(pDC, 20, PANEL_SPACE + 20, t->GetTower()->GetTowerName());
					break;
				}
			}
		}
	}
	game_framework::CDDraw::ReleaseBackCDC();
}
void gamemap::loadpic() {
	controlPanel.LoadBitmapByString({ "resources/control_panel.bmp" }, RGB(255, 255, 255));
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
	selected_block.SetTopLeft(int(LEFT + moveX + selected_tile.x * TILE_SIZE*scale - 2 * scale), int(TOP + moveY + selected_tile.y * TILE_SIZE*scale - 2 * scale));

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
					last_selected = selected;
				}
				else {
					if (selected == 0) {
						buildTower(selected_tile.x, selected_tile.y, "basictower");

					}
					controlPanelMode = 3; //蓋完塔之後跳到升級頁面(tower模式)
				}
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
				}
				else {
					controlPanel.SetTopLeft(-400, PANEL_SPACE);
					controlPanelButton.SetTopLeft(0, PANEL_SPACE + 400);
				}
				selected_block.SetTopLeft(int(LEFT + moveX + t->GetX() * TILE_SIZE*scale - 2*scale), int(TOP + moveY + t->GetY() * TILE_SIZE*scale - 2 * scale));
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
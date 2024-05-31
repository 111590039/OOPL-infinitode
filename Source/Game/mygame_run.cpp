#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	
	//測試用 顯示兩幀之間的間隔時間(秒)
	CDC *pDC = game_framework::CDDraw::GetBackCDC();
	game_framework::CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(255, 255, 255), 800);
	game_framework::CTextDraw::Print(pDC, 1200, 20, std::to_string((map.GetElapsedTime())));
	game_framework::CDDraw::ReleaseBackCDC();

	if (!map.IsGameover()) {
		map.processMove();
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	//map.TESTMAP1();
	map.loadmap(1);
	map.loadpic();
	gameoverPage.LoadBitmapByString({ "resources/gameover.bmp" });
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP) {
		map.addMoveY(-50);
		map.resetshow();
	}
	else if (nChar == VK_DOWN) {
		map.addMoveY(50);
		map.resetshow();
	}
	else if (nChar == VK_RIGHT) {
		map.addMoveX(50);
		map.resetshow();
	}
	else if (nChar == VK_LEFT) {
		map.addMoveX(-50);
		map.resetshow();
	}
	else if (nChar == VK_OEM_PLUS) {
		map.addScale(0.1);
		map.resetshow();
	}
	else if (nChar == VK_OEM_MINUS) {
		map.addScale(-0.1);
		map.resetshow();
	}
	//測試用功能
	else if (nChar == 0x50) {
		map.SummonTestEnemy();
	}
	else if (nChar == VK_OEM_4) {
		map.CheatCoin();
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	if (map.IsGameover()) {
		if (1341 >= point.x && point.x >= 1100 && 748 >= point.y && point.y >= 688) {
			map.resetGamemap();
		}
		else if (1341 >= point.x && point.x >= 1100 && 838 >= point.y && point.y >= 773) {
			//回到選擇頁面(未實作)
		}
	}
	else {
		map.clickOnMap(point);
	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{

}

void CGameStateRun::OnShow()
{
	if (map.IsGameover()) {
		gameoverPage.ShowBitmap();
		CDC *pDC = game_framework::CDDraw::GetBackCDC();
		game_framework::CTextDraw::ChangeFontLog(pDC, 48, "微軟正黑體", RGB(255, 255, 255), 1500);
		int T = map.GetTotalTime();
		if (T >= 60) {
			game_framework::CTextDraw::Print(pDC, 770, 374, std::to_string(int(T / 60)) + " 分 " + std::to_string(T % 60) + " 秒" );
		}
		else {
			game_framework::CTextDraw::Print(pDC, 770, 374, std::to_string(T) + " 秒");
		}
		game_framework::CTextDraw::Print(pDC, 770, 464, std::to_string(map.GetWave()));
		game_framework::CDDraw::ReleaseBackCDC();
	}
	else {
		map.drawmap();
		map.showtext();
	}

}

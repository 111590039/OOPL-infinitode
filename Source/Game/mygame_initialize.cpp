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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	//Sleep(100);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
	background.LoadBitmapByString({ "resources/selectlevel.bmp" });
	std::vector<std::string> picPath;
	for (int i = 1; i < 18; i++) {
		picPath.push_back("resources/preview" + to_string(i) + ".bmp");
	}
	previewLevelPic.LoadBitmapByString(picPath);
	previewLevelPic.SetTopLeft(423,134);
	selected_level = 1;
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{	
	if (195 >= point.x && point.x >= 105 && 438 >= point.y && point.y >= 315) {
		//向左箭頭
		if (selected_level == 1) {
			selected_level = 17;
		}
		else {
			selected_level--;
		}
	}
	else if (1305 >= point.x && point.x >= 1215 && 438 >= point.y && point.y >= 315) {
		//向右箭頭
		if (selected_level == 17) {
			selected_level = 1;
		}
		else {
			selected_level++;
		}
	}
	previewLevelPic.SetFrameIndexOfBitmap(selected_level - 1);
	if (1311 >= point.x && point.x >= 1098 && 780 >= point.y && point.y >= 712) {
		ofstream ofs("Source/Game/Settings.map");
		ofs << selected_level;
		ofs.close();
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}
}

void CGameStateInit::OnShow()
{
	if (previewLevelPic.IsBitmapLoaded()) {
		background.ShowBitmap();
		previewLevelPic.ShowBitmap();

		CDC *pDC = game_framework::CDDraw::GetBackCDC();
		game_framework::CTextDraw::ChangeFontLog(pDC, 48, "微軟正黑體", RGB(128, 128, 128), 1500);

		game_framework::CTextDraw::Print(pDC, 600, 734,"關卡:" + to_string(selected_level));
		game_framework::CDDraw::ReleaseBackCDC();
	}
}

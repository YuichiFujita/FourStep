//============================================================
//
//	ゲーム画面ヘッダー [sceneGame.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "scene.h"

//************************************************************
//	前方宣言
//************************************************************
class CGameManager;	// ゲームマネージャークラス
class CScore;		// スコアクラス

//************************************************************
//	クラス定義
//************************************************************
// ゲーム画面クラス
class CSceneGame : public CScene
{
public:
	// コンストラクタ
	explicit CSceneGame(const EMode mode);

	// デストラクタ
	~CSceneGame() override;

	// オーバーライド関数
	HRESULT Init(void) override;	// 初期化
	HRESULT Uninit(void) override;	// 終了
	void Update(void) override;		// 更新
	void Draw(void) override;		// 描画

	// 静的メンバ関数
	static CGameManager	*GetGameManager(void);	// ゲームマネージャー取得
	static CScore		*GetScore(void);		// スコア取得

	static void SetEnableDrawUI(const bool bDraw);		// UIの描画状況設定
	static bool IsDrawUI(void);							// UIの描画状況取得
	static void SetEnableControlCamera(const bool bControl);	// カメラの操作状況設定

private:
	// 静的メンバ変数
	static CGameManager	*m_pGameManager;	// ゲームマネージャー
	static CScore		*m_pScore;			// スコア

	static bool m_bControlCamera;	// カメラの操作状況
	static bool m_bDrawUI;			// UIの描画状況
};

#endif	// _SCENE_GAME_H_

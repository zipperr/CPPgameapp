#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int kemono_NX, kemono_NY, kemono_NGraph;
	int kemono_RX, kemono_RY, kemono_RGraph;
	int kemono_LX, kemono_LY, kemono_LGraph;
	int backX, backY, backGraph;
	int japaX[10], japaY[10], japaGraph;
	int japaflag[10]; //じゃぱりまん 10個の存在フラグ
	int japa_counter; //じゃぱりまんの出現タイミングをはかるためのカウンター 
	int i;
	int kemono_NW, kemono_NH, japaW, japaH;
	int score = 0;
	int score_d = 10;

	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);

	// ＤＸライブラリ初期化
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	//サーバル立ち絵
	kemono_NGraph = LoadGraph("kemono_N.png");
	kemono_NX = 340; kemono_NY = 260;

	//サーバル右移動中
	kemono_RGraph = LoadGraph("kemono_R.png");
	kemono_RX = 340; kemono_RY = 290;

	//サーバル左移動中
	kemono_LGraph = LoadGraph("kemono_L.png");
	kemono_LX = 320; kemono_LY = 290;

	//背景
	backGraph = LoadGraph("back.png");
	backX = 0; backY = 0;

	//じゃぱりまん
	for (i = 0; i<10; i += 1) { //じゃぱりまん 10個分処理を行う
		japaX[i] = 0; //じゃぱりまんの初期座標入力
		japaY[i] = 0;
		japaflag[i] = 0; //じゃぱりまんは最初存在しないため、存在しないようにする
	}
	japa_counter = 0;
	japaGraph = LoadGraph("japa.png");

	// サーバルの画像サイズ
	GetGraphSize(kemono_NGraph, &kemono_NW, &kemono_NH);

	// じゃぱりまんの画像サイズ
	GetGraphSize(japaGraph, &japaW, &japaH);


	for (;;) {
		// 画面初期化とサーバルをNに戻す
		ClearDrawScreen();
		DrawGraph(backX, backY, backGraph, FALSE);
		DrawGraph(kemono_NX, kemono_NY, kemono_NGraph, TRUE);

		//スコアの表示
		DrawFormatString(10, 10, 0xFFFFFF, "SCORE %d", score);

		// サーバルの移動ルーチン
		{
			// ←キーを押していたら左に移動させる
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
				kemono_NX -= 3;
				kemono_RX -= 3;
				kemono_LX -= 3;
				ClearDrawScreen();
				DrawGraph(backX, backY, backGraph, FALSE);
				DrawGraph(kemono_LX, kemono_LY, kemono_LGraph, TRUE);
				DrawFormatString(10, 10, 0xFFFFFF, "SCORE %d", score);
			}
			// サーバルが画面左端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (kemono_LX < 0) kemono_LX = 0;

			// →キーを押していたら右に移動させる
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
				kemono_NX += 3;
				kemono_RX += 3;
				kemono_LX += 3;
				ClearDrawScreen();
				DrawGraph(backX, backY, backGraph, FALSE);
				DrawGraph(kemono_RX, kemono_RY, kemono_RGraph, TRUE);
				DrawFormatString(10, 10, 0xFFFFFF, "SCORE %d", score);

			}

			// サーバルが画面右端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (kemono_RX > 640 - 64) kemono_RX = 640 - 64;

			//じゃぱりまん
			if (japa_counter%30==0) { //30 カウントごとに処理を行う
				for (i = 0; i < 10; i += 1) { //10個のじゃぱりまんの中から出現可能なじゃぱりまんを調べる
					if (japaflag[i] == 0) {
						break;
					}
				}
				
				if (i < 10) { //全てのじゃぱりまんが出現できない場合、
							  //i は１０になっている。i が１０より小さい場合のみ処理を行う
					japaflag[i] = 1; //じゃぱりまんを出現させる
					japaX[i] = GetRand(640); //じゃぱりまんのｘ座標を 0～640 までの値からランダムに決定する
					japaY[i] = 0; //じゃぱりまんの出現位置は画面上端のため、ｙ座標は０とする
				}
			}
			japa_counter += 1;
			
			//じゃぱりまんの移動ルーチン
			for (i = 0; i < 10; i += 1) {
				if (japaflag[i] == 1) {
					japaY[i] += 3; //じゃぱりまんを下方向へ移動させる
					if (japaY[i]  > 480) { //じゃぱりまんが画面外へ移動した場合
						japaflag[i] = 0; //じゃぱりまんを消滅状態にする
					}
				}
			}

			for (i = 0; i < 10; i += 1) { //じゃぱりまん 10 個分処理を行う
				if (japaflag[i] == 1) { //じゃぱりまんが存在している場合
					DrawGraph(japaX[i], japaY[i], japaGraph, TRUE); //じゃぱりまんを描画する 
				}
			}

			// じゃぱりまんとサーバルの当たり判定、じゃぱりまんの数だけ繰り返す
			for (i = 0; i < 10; i++)
			{
				// じゃぱりまんiが存在している場合のみ次の処理に映る
				if (japaflag[i] == 1)
				{
					// サーバルとの当たり判定
					if (((japaX[i] > kemono_NX && japaX[i] < kemono_NX + kemono_NW) ||
						(kemono_NX > japaX[i] && kemono_NX < japaX[i] + japaW)) &&
						((japaY[i] > kemono_NY && japaY[i] < kemono_NY + kemono_NH) ||
						(kemono_NY > japaY[i] && kemono_NY < japaY[i] + japaH)))
					{
						// 接触している場合は当たったじゃぱりまんの存在を消す
						score += score_d; //スコア追加
						japaflag[i] = 0;
					}
				}
			}

				// 裏画面の内容を表画面にコピーする
				ScreenFlip();
			}

			// Windows 特有の面倒な処理をＤＸライブラリにやらせる
			// -1 が返ってきたらループを抜ける
			if (ProcessMessage() < 0) break;

			// もしＥＳＣキーが押されていたらループから抜ける
			if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		}

		// ＤＸライブラリ使用の終了
		DxLib_End();

		// ソフトの終了
		return 0;
	}
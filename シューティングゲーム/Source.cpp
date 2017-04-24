#include "DxLib.h"
#include <math.h>

#define SHOT 20

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int BallX, BallY, BallGraph;
	int Bw, Bh, Sw, Sh;
	int SikakuX, SikakuY, SikakuMuki, SikakuGraph;
	int SikakuDamageFlag, SikakuDamageCounter, SikakuDamageGraph;
	int ShotX[SHOT], ShotY[SHOT], ShotFlag[SHOT], ShotGraph;
	int SikakuW, SikakuH, ShotW, ShotH;
	int ShotBFlag;
	int i;
	double ETamaX, ETamaY;
	int ETamaFlag;
	double ETamaSx, ETamaSy;
	int ETamaW, ETamaH, ETamaGraph;
	int ETamaCounter;


	// 画面モードの設定
	SetGraphMode(640, 480, 16);

	//ウィンドウモードで起動する
	ChangeWindowMode(TRUE);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	// 自機のグラフィックをメモリにロード＆表示座標をセット
	BallGraph = LoadGraph("kemo.png");
	BallX = 288; BallY = 400;

	// 敵のグラフィックをメモリにロード＆表示座標をセット
	SikakuGraph = LoadGraph("kemono.png");
	SikakuX = 0; SikakuY = 50;

	// 敵のダメージ時のグラフィックをメモリにロード
	SikakuDamageGraph = LoadGraph("kemono2.png");

	// 敵が顔を歪めているかどうかの変数に『歪めていない』を表す０を代入
	SikakuDamageFlag = 0;

	// 敵の弾のグラフィックをロード
	ETamaGraph = LoadGraph("japa.png");

	// 敵の弾のグラフィックのサイズを得る
	GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);

	// 敵の弾が飛んでいるかどうかを保持する変数に『飛んでいない』を表す０を代入
	ETamaFlag = 0;

	// 敵が弾を撃つタイミングを取るための計測用変数に０を代入
	ETamaCounter = 0;

	// 弾のグラフィックをメモリにロード
	ShotGraph = LoadGraph("japa.png");

	// 弾が画面上に存在しているか保持する変数に『存在していない』を意味する０を代入しておく
	for (i = 0; i < SHOT; i++)
	{
		ShotFlag[i] = 0;
	}

	// ショットボタンが前のフレームで押されたかどうかを保存する変数に０(押されいない)を代入
	ShotBFlag = 0;

	// 敵の移動方向をセット
	SikakuMuki = 1;

	// 弾のグラフィックのサイズをえる
	GetGraphSize(ShotGraph, &ShotW, &ShotH);

	// 敵のグラフィックのサイズを得る
	GetGraphSize(SikakuGraph, &SikakuW, &SikakuH);

	// 自機と弾の画像のサイズを得る
	GetGraphSize(BallGraph, &Bw, &Bh);
	GetGraphSize(ShotGraph, &Sw, &Sh);


	// 移動ルーチン
	while (1)
	{
		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		// 自機の操作ルーチン
		{
			// ↑キーを押していたらボール君を上に移動させる
			if (CheckHitKey(KEY_INPUT_UP) == 1) BallY -= 8;

			// ↓キーを押していたらボール君を下に移動させる
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) BallY += 8;

			// ←キーを押していたらボール君を左に移動させる
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) BallX -= 8;

			// →キーを押していたらボール君を右に移動させる
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) BallX += 8;

			// スペースキーを押した場合は処理を分岐
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				// 前フレームでショットボタンを押したかが保存されている変数が０だったら弾を発射
				if (ShotBFlag == 0)
				{
					// 画面上にでていない弾があるか、弾の数だけ繰り返して調べる
					for (i = 0; i < SHOT; i++)
					{
						// 弾iが画面上にでていない場合はその弾を画面に出す
						if (ShotFlag[i] == 0)
						{
							// 弾iの位置をセット、位置はボール君の中心にする
							ShotX[i] = (Bw - Sw) / 2 + BallX;
							ShotY[i] = (Bh - Sh) / 2 + BallY;

							// 弾iは現時点を持って存在するので、存在状態を保持する変数に１を代入する
							ShotFlag[i] = 1;

							// 一つ弾を出したので弾を出すループから抜けます
							break;
						}
					}
				}

				// 前フレームでショットボタンを押されていたかを保存する変数に１(おされていた)を代入
				ShotBFlag = 1;
			}
			else
			{
				// ショットボタンが押されていなかった場合は
				// 前フレームでショットボタンが押されていたかを保存する変数に０(おされていない)を代入
				ShotBFlag = 0;
			}

			// 自機が画面左端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (BallX < 0) BallX = 0;

			// 自機が画面右端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (BallX > 640 - 64) BallX = 640 - 64;

			// 自機が画面上端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (BallY < 0) BallY = 0;

			// 自機が画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (BallY > 480 - 64) BallY = 480 - 64;

			// 自機を描画
			DrawGraph(BallX, BallY, BallGraph, TRUE);
		}

		// 弾の数だけ弾を動かす処理を繰り返す
		for (i = 0; i < SHOT; i++)
		{
			// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容が１(存在する)の場合のみ行う )
			if (ShotFlag[i] == 1)
			{
				// 弾iを１６ドット上に移動させる
				ShotY[i] -= 16;

				// 画面外に出てしまった場合は存在状態を保持している変数に０(存在しない)を代入する
				if (ShotY[i] < -80)
				{
					ShotFlag[i] = 0;
				}

				// 画面に弾iを描画する
				DrawGraph(ShotX[i], ShotY[i], ShotGraph, TRUE);
			}
		}

		//　敵の移動ルーチン
		{
			// 顔を歪めているかどうかで処理を分岐
			if (SikakuDamageFlag == 1)
			{
				// 顔を歪めている場合はダメージ時のグラフィックを描画する
				DrawGraph(SikakuX, SikakuY, SikakuDamageGraph, TRUE);

				// 顔を歪めている時間を測るカウンターに１を加算する
				SikakuDamageCounter++;

				// もし顔を歪め初めて ３０ フレーム経過していたら顔の歪んだ状態から
				// 元に戻してあげる
				if (SikakuDamageCounter == 30)
				{
					// 『歪んでいない』を表す０を代入
					SikakuDamageFlag = 0;
				}
			}
			else
			{
				// 歪んでいない場合は今まで通りの処理

				// 敵の座標を移動している方向に移動する
				if (SikakuMuki == 1) SikakuX += 6;
				if (SikakuMuki == 0) SikakuX -= 6;

				// 敵が画面右端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
				if (SikakuX > 576)
				{
					SikakuX = 576;
					SikakuMuki = 0;
				}

				// 敵が画面左端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
				if (SikakuX < 0)
				{
					SikakuX = 0;
					SikakuMuki = 1;
				}

				// 敵を描画
				DrawGraph(SikakuX, SikakuY, SikakuGraph, TRUE);

				// 弾を撃つタイミングを計測するためのカウンターに１を足す
				ETamaCounter++;

				// もしカウンター変数が６０だった場合は弾を撃つ処理を行う
				if (ETamaCounter == 40)
				{
					// もし既に弾が『飛んでいない』状態だった場合のみ発射処理を行う
					if (ETamaFlag == 0)
					{
						// 弾の発射位置を設定する
						ETamaX = SikakuX + SikakuW / 2 - ETamaW / 2;
						ETamaY = SikakuY + SikakuH / 2 - ETamaH / 2;

						// 弾の移動速度を設定する
						{
							double sb, sbx, sby, bx, by, sx, sy;

							sx = ETamaX + ETamaW / 2;
							sy = ETamaY + ETamaH / 2;

							bx = BallX + Bw / 2;
							by = BallY + Bh / 2;

							sbx = bx - sx;
							sby = by - sy;

							// 平方根を求めるのに標準関数の sqrt を使う、
							// これを使うには math.h をインクルードする必要がある
							sb = sqrt(sbx * sbx + sby * sby);

							// １フレーム当たり８ドット移動するようにする
							ETamaSx = sbx / sb * 8;
							ETamaSy = sby / sb * 8;
						}

						// 弾の状態を保持する変数に『飛んでいる』を示す１を代入する
						ETamaFlag = 1;
					}

					// 弾を打つタイミングを計測するための変数に０を代入
					ETamaCounter = 0;
				}
			}
		}

		// 敵の弾の状態が『飛んでいる』場合のみ弾の移動処理を行う
		if (ETamaFlag == 1)
		{
			// 弾を移動させる
			ETamaX += ETamaSx;
			ETamaY += ETamaSy;

			// もし弾が画面からはみ出てしまった場合は弾の状態を『飛んでいない』
			// を表す０にする
			if (ETamaY > 480 || ETamaY < 0 ||
				ETamaX > 640 || ETamaX < 0) ETamaFlag = 0;

			// 画面に描画する( ETamaGraph : 敵の弾のグラフィックのハンドル )
			DrawGraph((int)ETamaX, (int)ETamaY, ETamaGraph, TRUE);
		}

		// 弾と敵の当たり判定、弾の数だけ繰り返す
		for (i = 0; i < SHOT; i++)
		{
			// 弾iが存在している場合のみ次の処理に映る
			if (ShotFlag[i] == 1)
			{
				// 敵との当たり判定
				if (((ShotX[i] > SikakuX && ShotX[i] < SikakuX + SikakuW) ||
					(SikakuX > ShotX[i] && SikakuX < ShotX[i] + ShotW)) &&
					((ShotY[i] > SikakuY && ShotY[i] < SikakuY + SikakuH) ||
					(SikakuY > ShotY[i] && SikakuY < ShotY[i] + ShotH)))
				{
					// 接触している場合は当たった弾の存在を消す
					ShotFlag[i] = 0;

					// 敵の顔を歪めているかどうかを保持する変数に『歪めている』を表す１を代入
					SikakuDamageFlag = 1;

					// 敵の顔を歪めている時間を測るカウンタ変数に０を代入
					SikakuDamageCounter = 0;
				}
			}
		}

		// 裏画面の内容を表画面にコピーする
		ScreenFlip();

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// -1 が返ってきたらループを抜ける
		if (ProcessMessage() < 0) break;

		// もしＥＳＣキーが押されていたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}
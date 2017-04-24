#include "DxLib.h"
#include <math.h>

#define SHOT 20

// WinMain�֐�
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


	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(640, 480, 16);

	//�E�B���h�E���[�h�ŋN������
	ChangeWindowMode(TRUE);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1) return -1;

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	// ���@�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	BallGraph = LoadGraph("kemo.png");
	BallX = 288; BallY = 400;

	// �G�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	SikakuGraph = LoadGraph("kemono.png");
	SikakuX = 0; SikakuY = 50;

	// �G�̃_���[�W���̃O���t�B�b�N���������Ƀ��[�h
	SikakuDamageGraph = LoadGraph("kemono2.png");

	// �G�����c�߂Ă��邩�ǂ����̕ϐ��Ɂw�c�߂Ă��Ȃ��x��\���O����
	SikakuDamageFlag = 0;

	// �G�̒e�̃O���t�B�b�N�����[�h
	ETamaGraph = LoadGraph("japa.png");

	// �G�̒e�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);

	// �G�̒e�����ł��邩�ǂ�����ێ�����ϐ��Ɂw���ł��Ȃ��x��\���O����
	ETamaFlag = 0;

	// �G���e�����^�C�~���O����邽�߂̌v���p�ϐ��ɂO����
	ETamaCounter = 0;

	// �e�̃O���t�B�b�N���������Ƀ��[�h
	ShotGraph = LoadGraph("japa.png");

	// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����O�������Ă���
	for (i = 0; i < SHOT; i++)
	{
		ShotFlag[i] = 0;
	}

	// �V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ��ɂO(�����ꂢ�Ȃ�)����
	ShotBFlag = 0;

	// �G�̈ړ��������Z�b�g
	SikakuMuki = 1;

	// �e�̃O���t�B�b�N�̃T�C�Y������
	GetGraphSize(ShotGraph, &ShotW, &ShotH);

	// �G�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(SikakuGraph, &SikakuW, &SikakuH);

	// ���@�ƒe�̉摜�̃T�C�Y�𓾂�
	GetGraphSize(BallGraph, &Bw, &Bh);
	GetGraphSize(ShotGraph, &Sw, &Sh);


	// �ړ����[�`��
	while (1)
	{
		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		// ���@�̑��샋�[�`��
		{
			// ���L�[�������Ă�����{�[���N����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_UP) == 1) BallY -= 8;

			// ���L�[�������Ă�����{�[���N�����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) BallY += 8;

			// ���L�[�������Ă�����{�[���N�����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) BallX -= 8;

			// ���L�[�������Ă�����{�[���N���E�Ɉړ�������
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) BallX += 8;

			// �X�y�[�X�L�[���������ꍇ�͏����𕪊�
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				// �O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ����O��������e�𔭎�
				if (ShotBFlag == 0)
				{
					// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
					for (i = 0; i < SHOT; i++)
					{
						// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
						if (ShotFlag[i] == 0)
						{
							// �ei�̈ʒu���Z�b�g�A�ʒu�̓{�[���N�̒��S�ɂ���
							ShotX[i] = (Bw - Sw) / 2 + BallX;
							ShotY[i] = (Bh - Sh) / 2 + BallY;

							// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
							ShotFlag[i] = 1;

							// ��e���o�����̂Œe���o�����[�v���甲���܂�
							break;
						}
					}
				}

				// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂP(������Ă���)����
				ShotBFlag = 1;
			}
			else
			{
				// �V���b�g�{�^����������Ă��Ȃ������ꍇ��
				// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂO(������Ă��Ȃ�)����
				ShotBFlag = 0;
			}

			// ���@����ʍ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (BallX < 0) BallX = 0;

			// ���@����ʉE�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (BallX > 640 - 64) BallX = 640 - 64;

			// ���@����ʏ�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (BallY < 0) BallY = 0;

			// ���@����ʉ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (BallY > 480 - 64) BallY = 480 - 64;

			// ���@��`��
			DrawGraph(BallX, BallY, BallGraph, TRUE);
		}

		// �e�̐������e�𓮂����������J��Ԃ�
		for (i = 0; i < SHOT; i++)
		{
			// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e���P(���݂���)�̏ꍇ�̂ݍs�� )
			if (ShotFlag[i] == 1)
			{
				// �ei���P�U�h�b�g��Ɉړ�������
				ShotY[i] -= 16;

				// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ��ɂO(���݂��Ȃ�)��������
				if (ShotY[i] < -80)
				{
					ShotFlag[i] = 0;
				}

				// ��ʂɒei��`�悷��
				DrawGraph(ShotX[i], ShotY[i], ShotGraph, TRUE);
			}
		}

		//�@�G�̈ړ����[�`��
		{
			// ���c�߂Ă��邩�ǂ����ŏ����𕪊�
			if (SikakuDamageFlag == 1)
			{
				// ���c�߂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
				DrawGraph(SikakuX, SikakuY, SikakuDamageGraph, TRUE);

				// ���c�߂Ă��鎞�Ԃ𑪂�J�E���^�[�ɂP�����Z����
				SikakuDamageCounter++;

				// �������c�ߏ��߂� �R�O �t���[���o�߂��Ă������̘c�񂾏�Ԃ���
				// ���ɖ߂��Ă�����
				if (SikakuDamageCounter == 30)
				{
					// �w�c��ł��Ȃ��x��\���O����
					SikakuDamageFlag = 0;
				}
			}
			else
			{
				// �c��ł��Ȃ��ꍇ�͍��܂Œʂ�̏���

				// �G�̍��W���ړ����Ă�������Ɉړ�����
				if (SikakuMuki == 1) SikakuX += 6;
				if (SikakuMuki == 0) SikakuX -= 6;

				// �G����ʉE�[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
				if (SikakuX > 576)
				{
					SikakuX = 576;
					SikakuMuki = 0;
				}

				// �G����ʍ��[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
				if (SikakuX < 0)
				{
					SikakuX = 0;
					SikakuMuki = 1;
				}

				// �G��`��
				DrawGraph(SikakuX, SikakuY, SikakuGraph, TRUE);

				// �e�����^�C�~���O���v�����邽�߂̃J�E���^�[�ɂP�𑫂�
				ETamaCounter++;

				// �����J�E���^�[�ϐ����U�O�������ꍇ�͒e�����������s��
				if (ETamaCounter == 40)
				{
					// �������ɒe���w���ł��Ȃ��x��Ԃ������ꍇ�̂ݔ��ˏ������s��
					if (ETamaFlag == 0)
					{
						// �e�̔��ˈʒu��ݒ肷��
						ETamaX = SikakuX + SikakuW / 2 - ETamaW / 2;
						ETamaY = SikakuY + SikakuH / 2 - ETamaH / 2;

						// �e�̈ړ����x��ݒ肷��
						{
							double sb, sbx, sby, bx, by, sx, sy;

							sx = ETamaX + ETamaW / 2;
							sy = ETamaY + ETamaH / 2;

							bx = BallX + Bw / 2;
							by = BallY + Bh / 2;

							sbx = bx - sx;
							sby = by - sy;

							// �����������߂�̂ɕW���֐��� sqrt ���g���A
							// ������g���ɂ� math.h ���C���N���[�h����K�v������
							sb = sqrt(sbx * sbx + sby * sby);

							// �P�t���[��������W�h�b�g�ړ�����悤�ɂ���
							ETamaSx = sbx / sb * 8;
							ETamaSy = sby / sb * 8;
						}

						// �e�̏�Ԃ�ێ�����ϐ��Ɂw���ł���x�������P��������
						ETamaFlag = 1;
					}

					// �e��ł^�C�~���O���v�����邽�߂̕ϐ��ɂO����
					ETamaCounter = 0;
				}
			}
		}

		// �G�̒e�̏�Ԃ��w���ł���x�ꍇ�̂ݒe�̈ړ��������s��
		if (ETamaFlag == 1)
		{
			// �e���ړ�������
			ETamaX += ETamaSx;
			ETamaY += ETamaSy;

			// �����e����ʂ���͂ݏo�Ă��܂����ꍇ�͒e�̏�Ԃ��w���ł��Ȃ��x
			// ��\���O�ɂ���
			if (ETamaY > 480 || ETamaY < 0 ||
				ETamaX > 640 || ETamaX < 0) ETamaFlag = 0;

			// ��ʂɕ`�悷��( ETamaGraph : �G�̒e�̃O���t�B�b�N�̃n���h�� )
			DrawGraph((int)ETamaX, (int)ETamaY, ETamaGraph, TRUE);
		}

		// �e�ƓG�̓����蔻��A�e�̐������J��Ԃ�
		for (i = 0; i < SHOT; i++)
		{
			// �ei�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
			if (ShotFlag[i] == 1)
			{
				// �G�Ƃ̓����蔻��
				if (((ShotX[i] > SikakuX && ShotX[i] < SikakuX + SikakuW) ||
					(SikakuX > ShotX[i] && SikakuX < ShotX[i] + ShotW)) &&
					((ShotY[i] > SikakuY && ShotY[i] < SikakuY + SikakuH) ||
					(SikakuY > ShotY[i] && SikakuY < ShotY[i] + ShotH)))
				{
					// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
					ShotFlag[i] = 0;

					// �G�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\���P����
					SikakuDamageFlag = 1;

					// �G�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
					SikakuDamageCounter = 0;
				}
			}
		}

		// ����ʂ̓��e��\��ʂɃR�s�[����
		ScreenFlip();

		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// -1 ���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0) break;

		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	}

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}
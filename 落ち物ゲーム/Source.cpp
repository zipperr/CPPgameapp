#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int kemono_NX, kemono_NY, kemono_NGraph;
	int kemono_RX, kemono_RY, kemono_RGraph;
	int kemono_LX, kemono_LY, kemono_LGraph;
	int backX, backY, backGraph;
	int japaX[10], japaY[10], japaGraph;
	int japaflag[10]; //����ς�܂� 10�̑��݃t���O
	int japa_counter; //����ς�܂�̏o���^�C�~���O���͂��邽�߂̃J�E���^�[ 
	int i;
	int kemono_NW, kemono_NH, japaW, japaH;
	int score = 0;
	int score_d = 10;

	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);

	// �c�w���C�u����������
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	//�T�[�o�������G
	kemono_NGraph = LoadGraph("kemono_N.png");
	kemono_NX = 340; kemono_NY = 260;

	//�T�[�o���E�ړ���
	kemono_RGraph = LoadGraph("kemono_R.png");
	kemono_RX = 340; kemono_RY = 290;

	//�T�[�o�����ړ���
	kemono_LGraph = LoadGraph("kemono_L.png");
	kemono_LX = 320; kemono_LY = 290;

	//�w�i
	backGraph = LoadGraph("back.png");
	backX = 0; backY = 0;

	//����ς�܂�
	for (i = 0; i<10; i += 1) { //����ς�܂� 10���������s��
		japaX[i] = 0; //����ς�܂�̏������W����
		japaY[i] = 0;
		japaflag[i] = 0; //����ς�܂�͍ŏ����݂��Ȃ����߁A���݂��Ȃ��悤�ɂ���
	}
	japa_counter = 0;
	japaGraph = LoadGraph("japa.png");

	// �T�[�o���̉摜�T�C�Y
	GetGraphSize(kemono_NGraph, &kemono_NW, &kemono_NH);

	// ����ς�܂�̉摜�T�C�Y
	GetGraphSize(japaGraph, &japaW, &japaH);


	for (;;) {
		// ��ʏ������ƃT�[�o����N�ɖ߂�
		ClearDrawScreen();
		DrawGraph(backX, backY, backGraph, FALSE);
		DrawGraph(kemono_NX, kemono_NY, kemono_NGraph, TRUE);

		//�X�R�A�̕\��
		DrawFormatString(10, 10, 0xFFFFFF, "SCORE %d", score);

		// �T�[�o���̈ړ����[�`��
		{
			// ���L�[�������Ă����獶�Ɉړ�������
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
				kemono_NX -= 3;
				kemono_RX -= 3;
				kemono_LX -= 3;
				ClearDrawScreen();
				DrawGraph(backX, backY, backGraph, FALSE);
				DrawGraph(kemono_LX, kemono_LY, kemono_LGraph, TRUE);
				DrawFormatString(10, 10, 0xFFFFFF, "SCORE %d", score);
			}
			// �T�[�o������ʍ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (kemono_LX < 0) kemono_LX = 0;

			// ���L�[�������Ă�����E�Ɉړ�������
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
				kemono_NX += 3;
				kemono_RX += 3;
				kemono_LX += 3;
				ClearDrawScreen();
				DrawGraph(backX, backY, backGraph, FALSE);
				DrawGraph(kemono_RX, kemono_RY, kemono_RGraph, TRUE);
				DrawFormatString(10, 10, 0xFFFFFF, "SCORE %d", score);

			}

			// �T�[�o������ʉE�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (kemono_RX > 640 - 64) kemono_RX = 640 - 64;

			//����ς�܂�
			if (japa_counter%30==0) { //30 �J�E���g���Ƃɏ������s��
				for (i = 0; i < 10; i += 1) { //10�̂���ς�܂�̒�����o���\�Ȃ���ς�܂�𒲂ׂ�
					if (japaflag[i] == 0) {
						break;
					}
				}
				
				if (i < 10) { //�S�Ă̂���ς�܂񂪏o���ł��Ȃ��ꍇ�A
							  //i �͂P�O�ɂȂ��Ă���Bi ���P�O��菬�����ꍇ�̂ݏ������s��
					japaflag[i] = 1; //����ς�܂���o��������
					japaX[i] = GetRand(640); //����ς�܂�̂����W�� 0�`640 �܂ł̒l���烉���_���Ɍ��肷��
					japaY[i] = 0; //����ς�܂�̏o���ʒu�͉�ʏ�[�̂��߁A�����W�͂O�Ƃ���
				}
			}
			japa_counter += 1;
			
			//����ς�܂�̈ړ����[�`��
			for (i = 0; i < 10; i += 1) {
				if (japaflag[i] == 1) {
					japaY[i] += 3; //����ς�܂���������ֈړ�������
					if (japaY[i]  > 480) { //����ς�܂񂪉�ʊO�ֈړ������ꍇ
						japaflag[i] = 0; //����ς�܂�����ŏ�Ԃɂ���
					}
				}
			}

			for (i = 0; i < 10; i += 1) { //����ς�܂� 10 ���������s��
				if (japaflag[i] == 1) { //����ς�܂񂪑��݂��Ă���ꍇ
					DrawGraph(japaX[i], japaY[i], japaGraph, TRUE); //����ς�܂��`�悷�� 
				}
			}

			// ����ς�܂�ƃT�[�o���̓����蔻��A����ς�܂�̐������J��Ԃ�
			for (i = 0; i < 10; i++)
			{
				// ����ς�܂�i�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
				if (japaflag[i] == 1)
				{
					// �T�[�o���Ƃ̓����蔻��
					if (((japaX[i] > kemono_NX && japaX[i] < kemono_NX + kemono_NW) ||
						(kemono_NX > japaX[i] && kemono_NX < japaX[i] + japaW)) &&
						((japaY[i] > kemono_NY && japaY[i] < kemono_NY + kemono_NH) ||
						(kemono_NY > japaY[i] && kemono_NY < japaY[i] + japaH)))
					{
						// �ڐG���Ă���ꍇ�͓�����������ς�܂�̑��݂�����
						score += score_d; //�X�R�A�ǉ�
						japaflag[i] = 0;
					}
				}
			}

				// ����ʂ̓��e��\��ʂɃR�s�[����
				ScreenFlip();
			}

			// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
			// -1 ���Ԃ��Ă����烋�[�v�𔲂���
			if (ProcessMessage() < 0) break;

			// �����d�r�b�L�[��������Ă����烋�[�v���甲����
			if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		}

		// �c�w���C�u�����g�p�̏I��
		DxLib_End();

		// �\�t�g�̏I��
		return 0;
	}
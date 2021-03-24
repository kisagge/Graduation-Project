#pragma once
//==================================================================
//		## using namespace MY_UTIL ##
//==================================================================

//angle * DEG_TO_RAD
#define DEG_TO_RAD 0.017435f  //degree 1�� (���Ȱ�)
#define PI 3.141592654f
#define PI2		(PI * 2)

#define PI_2		(PI / 2)
#define PI_4		(PI / 4)
#define PI_8		(PI / 8)
#define PI_16	(PI / 16)
#define PI_32	(PI / 32)

namespace MY_UTIL //�̰� ������� ���ӽ����̽� �̸��� �����ص� �ȴ�
{
	//���������� ����
	float getAngle(float startX, float startY, float endX, float endY);
	//���������� �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);

	struct tagZorderImage
	{
		image* img;
		RECT rc;
		int x;
		int y;
		int zorder;

		//������ �̹����� ���
		int frameX;
		int frameY;
		bool isFrameImage;

		//���İ�
		int alpha;
		bool isAlpha;
	};

	enum SCENETYPE
	{
		LOADING,
		TITLE,
		SELECT,
		MAIN
	};

	enum ITEMLIST
	{
		ITEM_WEAPON_1,
		ITEM_WEAPON_2,
		ITEM_WEAPON_3,
		ITEM_HAT_1,
		ITEM_HAT_2,
		ITEM_HAT_3,
		ITEM_SHIELD_1,
		ITEM_SHIELD_2,
		ITEM_SHIELD_3,
		ITEM_ACCESSORY_1,
		ITEM_ACCESSORY_2,
		ITEM_ACCESSORY_3,
		ITEM_DRILL_1,
		ITEM_DRILL_2,
		ITEM_DRILL_3,
		ITEM_SPEND_1,
		ITEM_SPEND_2,
		ITEM_SKILLCARD_1,
		ITEM_SKILLCARD_2,
		ITEM_SKILLCARD_3
	};

	enum ENEMYLIST
	{
		ENEMY_POCHI,
		ENEMY_ADDAX,
		ENEMY_REQUI,
		ENEMY_SPHINX
	};

	struct tagDamageSkin
	{
		image* skinImage;
		int damage;
		int x;
		float y;
		int alpha;
		bool isCritical;

		void damageRender(HDC hdc)
		{
			int l = x;
			if (damage > 0)
			{
				int k = damage;
				while (k > 0)
				{
					skinImage->frameAlphaRender(hdc, l, (int)y, k % 10, 0, alpha);
					k /= 10;
					l -= skinImage->getFrameWidth();
				}
			}
			else
			{
				skinImage = IMAGEMANAGER->findImage("�̽�");
				skinImage->alphaRender(hdc, l, (int)y, alpha);
			}
		}
	};

};


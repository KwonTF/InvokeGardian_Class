#pragma once
#include "cocos2d.h"
#include "Collisioner.h"
#include "Explosion.h"

USING_NS_CC;

/*
base class of Missile
creater : ZeroFe
*/
class Missile : public Collisioner
{
protected:
	Layer* parentLayer;

	// ���ֿ� �ʿ��� �̹���
	std::string *image;
	int imageNum;

	// �ı� �ִϸ��̼� ���� ����
	std::string deathAnimTexture;
	int deathAnimWidth;
	int deathAnimHeight;
	int deathAnimRow;
	int deathAnimColm;
	float deathAnimDelay;

	// �̵��ӵ�
	float speed;

	int penetrationCount;	// ���� Ƚ��
	int range;				// ��Ÿ� ����
	int divideCount;		// �п� ��

	bool isExplode;			// ���� ����
	int explodeRadius;		// ���� ������
	int explodeDamage;		// ���� ������ ����

	float removeTime;		// �Ѿ� �����ִ� �ð�
public:
	Missile();
	~Missile() {};

	static Missile* create(const std::string &filename);

	virtual void collisioned(int damage, std::vector<Condition*> &c);

	void setDeathAnimFile(const std::string * const filename, const int fileNum);
	void setDeathAnimFile2(const std::string filename, const int row, const int colm,
		const int width, const int height, const float delay);

	void make() override;

	// set ability
	inline void setAttack(int atk) { attack = atk; }
	inline void setSpeed(int s) { speed = s; }
	inline void setRange(int movelimit) { range = movelimit; }
	inline void setPenetCount(int count) { penetrationCount = count; }
	inline void setDivideCount(int count) { divideCount = count; }
	inline void setRemoveTime(float time) { removeTime = time; }
	inline void setParentLayer(Layer* const pLayer) { parentLayer = pLayer; }

	inline float getSpeed() { return speed; }
	inline float getRange() { return range; }

	//�̻��� ��� ���� �Լ�
	void castEffect();
	void makeExplosion();
	void deathAnimation();
	void destroy();

	void removeMissile(float f);
};


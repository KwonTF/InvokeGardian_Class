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

	// 유닛에 필요한 이미지
	std::string *image;
	int imageNum;

	// 파괴 애니메이션 관련 변수
	std::string deathAnimTexture;
	int deathAnimWidth;
	int deathAnimHeight;
	int deathAnimRow;
	int deathAnimColm;
	float deathAnimDelay;

	// 이동속도
	float speed;

	int penetrationCount;	// 관통 횟수
	int range;				// 사거리 제한
	int divideCount;		// 분열 수

	bool isExplode;			// 폭발 여부
	int explodeRadius;		// 폭발 반지름
	int explodeDamage;		// 폭발 데미지 설정

	float removeTime;		// 총알 남아있는 시간
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

	//미사일 요소 적용 함수
	void castEffect();
	void makeExplosion();
	void deathAnimation();
	void destroy();

	void removeMissile(float f);
};


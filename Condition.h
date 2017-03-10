#pragma once

// 상태이상 정보 클래스
enum class EffectCode
{
	Slow, Unknown, Knock, PowerUp, Division, Mine, Explode
};
static unsigned int additioalLevel = 7; //추가효과가 붙기 시작하는 레벨
class Condition
{
public:
	virtual EffectCode getCode();//무슨 효과인지를 반환한다
	virtual float castEffect(float input) const;//수치 변경형의 효과를 실행한 결과 반환
	virtual float castSideEffect(float input)const;
	unsigned int conditonLevel;//효과의 레벨을 설정
	virtual void enchance(); //스킬 레벨업
	Condition();
	~Condition() {};
};
class Slow : public Condition {
public:
	Slow();
	float castEffect(float speed)const;
	float castSideEffect(float defence)const;
	EffectCode getCode();
	void enchance();
private:
	float Time, speedReduceRate, deffenceReduceRate;
	EffectCode code;
};

class Knock : public Condition {
public:
	Knock();
	float castEffect(float knock)const;
	float castSideEffect(float defence)const;
	EffectCode getCode();
	void enchance();
private:
	float minusSpeed;
	EffectCode code;
};

class PowerUp : public Condition {
public:
	PowerUp();
	float castEffect(float range)const;
	float castSideEffect(float defence)const;
	EffectCode getCode();
	void enchance();
private:
	float rangeRate;
	unsigned int pierceNum;
	EffectCode code;
};

class Division : public Condition {
public:
	Division();
	float castEffect(float num)const;
	float castSideEffect(float num)const;
	EffectCode getCode();
	void enchance();
private:
	unsigned int divideNum;
	EffectCode code;
};

class Mine : public Condition {
public:
	Mine();
	float castEffect(float num)const;
	float castSideEffect(float num)const;
	EffectCode getCode();
	void enchance();
private:
	unsigned int holdTime;
	EffectCode code;
};
class Explode : public Condition {
public:
	Explode();
	float castEffect(float num)const;
	float castSideEffect(float num)const;
	EffectCode getCode();
	void enchance();
private:
	unsigned int damage;
	EffectCode code;
};
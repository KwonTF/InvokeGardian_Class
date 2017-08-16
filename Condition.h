#pragma once

// 상태이상 정보 클래스
enum class EffectCode
{
	Slow, Unknown, Knock, PowerUp, Division, Mine, Explode
};

static int additioalLevel = 7; //추가효과가 붙기 시작하는 레벨

class Condition
{
public:
	Condition();
	// 정보 복사
	Condition(const Condition&);
	virtual ~Condition() {};

	//무슨 효과인지를 반환한다
	virtual inline EffectCode getCode() { return EffectCode::Unknown; }
	//수치 변경형의 효과를 실행한 결과 반환
	virtual float castEffect(float input) const;
	virtual float castSideEffect(float input)const;
	// 스킬 레벨업
	virtual void enchance();

	int elementDamage;
	int conditionLevel;//효과의 레벨을 설정
};

class Slow : public Condition {
public:
	Slow();
	Slow(const Slow&);
	~Slow() {};
	inline EffectCode getCode() override { return EffectCode::Slow; }
	float castEffect(float speed)const override;
	float castSideEffect(float defence)const override;
	void enchance() override;
private:
	float Time, speedReduceRate, deffenceReduceRate;
};

class Knock : public Condition {
public:
	Knock();
	Knock(const Knock&);
	~Knock() {};
	EffectCode getCode() override { return EffectCode::Knock; }
	// 주요 효과 : 밀치기
	float castEffect(float knock)const override;
	// 부가 효과 : 스턴
	float castSideEffect(float defence)const override;
	void enchance() override;
private:
	float minusSpeed;
	float stunTime;
};

class PowerUp : public Condition {
public:
	PowerUp();
	PowerUp(const PowerUp&);
	~PowerUp() {};
	EffectCode getCode() override { return EffectCode::PowerUp; }
	// 주요 효과 : 사정거리 증가
	float castEffect(float range)const override;
	// 부가 효과 : 관통
	float castSideEffect(float defence)const override;
	void enchance() override;
private:
	float rangeRate;
	int pierceNum;
};

class Division : public Condition {
public:
	Division();
	Division(const Division&);
	~Division() {};
	EffectCode getCode() override { return EffectCode::Division; }
	// 주요 효과 : 총알 분리
	float castEffect(float num)const override; 
	// 부가 효과 : 유도 기능
	float castSideEffect(float num)const override;
	void enchance() override;
private:
	int divideNum;
	
};

class Mine : public Condition {
public:
	Mine();
	EffectCode getCode() override { return EffectCode::Mine; }
	// 주요 효과 : 
	float castEffect(float num)const override;
	float castSideEffect(float num)const override;
	void enchance() override;
private:
	unsigned int holdTime;
};

class Explode : public Condition {
public:
	Explode();
	Explode(const Explode&);
	~Explode() {};
	EffectCode getCode() override { return EffectCode::Explode; }
	// 주요 효과 : 폭발 생성
	float castEffect(float num)const override;
	// 부가 효과 : 폭발 도트뎀 추가
	float castSideEffect(float num)const override;
	void enchance() override;
private:
	int explodeRadius;
	int burnDamage;
};
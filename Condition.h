#pragma once

// 상태이상 정보 클래스
enum class EffectCode
{
	Slow
};
static unsigned int additioalLevel = 7; //추가효과가 붙기 시작하는 레벨
class Condition
{
protected:
	virtual EffectCode getCode() = 0;//무슨 효과인지를 반환한다
	virtual float castEffect(float input) const = 0;//수치 변경형의 효과를 실행한 결과 반환
	unsigned int conditonLevel;//효과의 레벨을 설정
	virtual void enchance() = 0; //스킬 레벨업
public:
	Condition();
	~Condition();
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
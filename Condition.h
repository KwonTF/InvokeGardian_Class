#pragma once

// �����̻� ���� Ŭ����
enum class EffectCode
{
	Slow
};
static unsigned int additioalLevel = 7; //�߰�ȿ���� �ٱ� �����ϴ� ����
class Condition
{
protected:
	virtual EffectCode getCode() = 0;//���� ȿ�������� ��ȯ�Ѵ�
	virtual float castEffect(float input) const = 0;//��ġ �������� ȿ���� ������ ��� ��ȯ
	unsigned int conditonLevel;//ȿ���� ������ ����
	virtual void enchance() = 0; //��ų ������
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
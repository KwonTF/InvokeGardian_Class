#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "MainHeader.h"

class HelloWorld : public cocos2d::Layer
{
private:


public:
	// start function
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	// make PhysicsWorld
	cocos2d::PhysicsWorld* m_world;

	void setPhysicsWorld(cocos2d::PhysicsWorld* world) { m_world = world; }

	// 충돌시 처리
	bool onContactBegin(cocos2d::PhysicsContact& Contact);

	//게임 씬의 구현
	void createGameScene();
	//매 시간마다 스케줄링 되는 함수들
	void onTimeUpdate(float input);
	//마우스 이벤트들
	void onMouseDown(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event) {};
	void onMouseScroll(cocos2d::Event* event) {};
	//키보드 이벤트들
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {};
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void fireMissile();
private:
	Layer* layerMissile;
	Player* player;
	Sprite* statusBar;
	LabelTTF* ttf1;
	Vec2 mouse;
};
//스프라이트의 앵커포인트를 가운데로 맞춰준다.
void setSpriteAnchor_Center(Sprite *input);
//마우스 좌표와 특정 시점과의 각도를 계산
float calculateDegree(Vec2 &current, Vec2 &point);

#endif // __HELLOWORLD_SCENE_H__

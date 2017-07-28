#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "TetrisFigureBase.h"
#include "HudLayer.h"

#include "Box2D/Box2D.h"

using namespace cocos2d;

class TetrisLayer : public CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(TetrisLayer);

private:

	CTetrisFigureBase* _pFigure;
	CTetrisFigureBase* _pNextFigure;

	enum FigureState {Added, Check, Removed, GameOver};
	FigureState _figureState;

	CCSprite* _pSpriteArrowUp;
	CCSprite* _pSpriteArrowDown;
	CCSprite* _pSpriteArrowLeft;
	CCSprite* _pSpriteArrowRight;
	CCSprite* _pSpriteReplay;

	CCFiniteTimeAction* _pActionMove;

	// This layer displays and contains level/lines/score
	HudLayer* _pHudLayer;
	void setHudLayer(HudLayer* pHudLayer) { _pHudLayer = pHudLayer; }

	void ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent);
	// for cocos2d-x scheduler
	void addFigure(float dt); 
	void checkCollision(float dt);
	void figureMoveFinished(CCNode* pSender);

};

#endif  // __HELLOWORLD_SCENE_H__
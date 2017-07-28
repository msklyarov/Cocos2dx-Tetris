#ifndef __HUDLAYER_H__
#define __HUDLAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class HudLayer : public CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	int getLevel() const { return _iLevel; };

	void incrementLevel();
	void incrementLines();
	void incrementScore();

	void showGameOverLabel();
	void hideNextFigureLabel();

	// implement the "static node()" method manually
	CREATE_FUNC(HudLayer);

private:
	
	int _iLevel;
	int _iLines;
	int _iScore;

	// This labels are used to show the current level/lines/score.
	CCLabelTTF*	_pLevelLabel;
	CCLabelTTF*	_pLinesLabel;
	CCLabelTTF*	_pScoreLabel;
	CCLabelTTF* _pNextFigureLabel;
	CCLabelTTF*	_pGameOverLabel;

	void updateLevel();
	void updateLines();
	void updateScore();
};

#endif  // __HUDLAYER_H__
//#include <iostream>
#include <conio.h>
#include "HudLayer.h"
#include "Settings.h"

using namespace cocos2d;

// on "init" you need to initialize your instance
bool HudLayer::init()
{
	_iLevel = 0;
	_iLines = 0;
	_iScore = 0;

	bool bRet = false;
	do
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		// 2. Add a label shows "Hello World".

		// Create a label and initialize with string "Hello World".
		_pLevelLabel = CCLabelTTF::create("Level: 0", "Arial", 15);
		CC_BREAK_IF(! _pLevelLabel);

		// Get window size and place the label upper. 
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// Position the label on the right side of the screen.
		_pLevelLabel->setPosition(ccp(size.width - 80, size.height - 30));

		// Add the label to HelloWorld layer as a child layer.
		this->addChild(_pLevelLabel, 1);

		_pLinesLabel = CCLabelTTF::create("Lines: 0", "Arial", 15);
		CC_BREAK_IF(! _pLinesLabel);

		_pLinesLabel->setPosition(ccp(size.width - 80, size.height - 60));

		this->addChild(_pLinesLabel, 1);

		_pScoreLabel = CCLabelTTF::create("Score: 0", "Arial", 15);
		CC_BREAK_IF(! _pScoreLabel);

		_pScoreLabel->setPosition(ccp(size.width - 80, size.height - 90));

		this->addChild(_pScoreLabel, 1);

		_pNextFigureLabel = CCLabelTTF::create("Next Figure:", "Arial", 15);
		CC_BREAK_IF(! _pNextFigureLabel);

		_pNextFigureLabel->setPosition(ccp(size.width - 60, size.height - 130));

		this->addChild(_pNextFigureLabel, 1);

		_pGameOverLabel = CCLabelTTF::create("", "Arial", 40);
		CC_BREAK_IF(! _pGameOverLabel);

		_pGameOverLabel->setPosition(ccp(size.width / 2 - 10, size.height / 2 + 10));

		this->addChild(_pGameOverLabel, 0);

		bRet = true;
	} while (0);

	return bRet;
}

// Set the new score level/lines/label value.
 
void HudLayer::updateLevel()
{
	const int labelLength = 25;
	char levelLabelText[labelLength];
	sprintf(levelLabelText, "Level: %d", _iLevel);
	_pLevelLabel->setString(levelLabelText);
}

void HudLayer::updateLines()
{
	const int labelLength = 25;
	char linesLabelText[labelLength];
	sprintf(linesLabelText, "Lines: %d", _iLines);
	_pLinesLabel->setString(linesLabelText);
}

void HudLayer::updateScore()
{
	const int labelLength = 25;
	char scoreLabelText[labelLength];
	sprintf(scoreLabelText, "Score: %d", _iScore);
	_pScoreLabel->setString(scoreLabelText);
}

void HudLayer::incrementLevel()
{
	_iLevel++;
	updateLevel();
}

void HudLayer::incrementLines()
{
	_iLines++;
	updateLines();
	if (_iLines * 2 % CSettings::GlassBlocksHeight == 0)
	{
		_iLevel++;
		updateLevel();
	}
}

void HudLayer::incrementScore()
{
	_iScore++;
	updateScore();
}

void HudLayer::showGameOverLabel()
{
	_pGameOverLabel->setString("Game Over");
}

void HudLayer::hideNextFigureLabel()
{
	_pNextFigureLabel->setString("");
}

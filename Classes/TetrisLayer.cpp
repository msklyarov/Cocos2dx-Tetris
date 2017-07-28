#include "TetrisLayer.h"
#include "HudLayer.h"
#include "Settings.h"
#include "TetrisGlass.h"
#include "Log.h"
#include "TetrisFigure_I.h"
#include "TetrisFigureCreator.h"


using namespace cocos2d;

CCScene* TetrisLayer::scene()
{
	CCScene* pScene = NULL;
	do
	{
		// 'scene' is an autorelease object
		pScene = CCScene::create();
		CC_BREAK_IF(! pScene);

		// 'pHudLayer' is an autorelease object
		HudLayer* pHudLayer = HudLayer::create();
		CC_BREAK_IF(! pHudLayer);

		// add the pHudLayer as a child to the scene
		pScene->addChild(pHudLayer, 1);

		// 'pTetrisLayer' is an autorelease object
		TetrisLayer* pTetrisLayer = TetrisLayer::create();
		CC_BREAK_IF(! pTetrisLayer);

		// pass the pHudLayer pointer to the pTetrisLayer so they can communicate
		pTetrisLayer->setHudLayer(pHudLayer);

		// add layer as a child to scene
		pScene->addChild(pTetrisLayer);
	} while (0);

	// return the scene
	return pScene;
}

// on "init" you need to initialize your instance
bool TetrisLayer::init()
{
	srand(time(NULL));
	_figureState = FigureState::Removed;
	_pNextFigure = CTetrisFigureCreator::CreateRandom();
	_pNextFigure->setFigureDirection(rand() % CSettings::FigureDirectionsCount);


	///-----------
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

		// 1. Add a menu item with "X" image, which is clicked to quit the program.

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(TetrisLayer::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);

		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);

		// Get window size and place the label upper. 
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// 3. Add add a splash screen, show the cocos2d splash image.
		CCSprite* pSprite = CCSprite::create(CSettings::BackgroundImgFileName);
		CC_BREAK_IF(! pSprite);

		// Place the sprite on the center of the screen
		pSprite->setPosition(ccp(size.width/2, size.height/2));

		// Add the sprite to TetrisLayer as a child layer.
		this->addChild(pSprite, 0);

		// Add control arrow buttons to layer
		_pSpriteArrowUp = CCSprite::create(CSettings::ArrowUpImgFileName);
		CC_BREAK_IF(! _pSpriteArrowUp);

		_pSpriteArrowUp->setPosition( ccp(size.width - 55, 190) );
		this->addChild(_pSpriteArrowUp);

		_pSpriteArrowLeft = CCSprite::create(CSettings::ArrowUpImgFileName);
		CC_BREAK_IF(! _pSpriteArrowLeft);

		_pSpriteArrowLeft->setRotation(-90);
		_pSpriteArrowLeft->setPosition( ccp(size.width - 85, 135) );
		this->addChild(_pSpriteArrowLeft);

		_pSpriteArrowRight = CCSprite::create(CSettings::ArrowUpImgFileName);
		CC_BREAK_IF(! _pSpriteArrowRight);

		_pSpriteArrowRight->setRotation(90);
		_pSpriteArrowRight->setPosition( ccp(size.width - 30, 135) );
		this->addChild(_pSpriteArrowRight);

		_pSpriteArrowDown = CCSprite::create(CSettings::ArrowUpImgFileName);
		CC_BREAK_IF(! _pSpriteArrowDown);

		_pSpriteArrowDown->setRotation(180);
		_pSpriteArrowDown->setPosition( ccp(size.width - 55, 80) );
		this->addChild(_pSpriteArrowDown);

		// add Replay button on Game Over
		_pSpriteReplay = CCSprite::create(CSettings::ReplayImgFileName);
		CC_BREAK_IF(! _pSpriteReplay);

		_pSpriteReplay->setPosition( ccp(size.width / 2 + 100, size.height / 2 + 80) );
		_pSpriteReplay->setVisible(false);
		this->addChild(_pSpriteReplay, 1);

		this->setTouchEnabled(true);

		///----

		// Call game logic about every second
		this->schedule( schedule_selector(TetrisLayer::addFigure), 1.0 );

		// every frame
		this->schedule( schedule_selector(TetrisLayer::checkCollision) );  

		bRet = true;

	} while (0);

	return bRet;
}

void TetrisLayer::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	//_figureState == FigureState::GameOver; // prevent from entering in scheduled methods

	CTetrisGlass* pGlass = CTetrisGlass::getInstance();
	pGlass->deleteInstance();

	//collected by cocos2d-x garbage collector
	//delete _pNextFigure;
	//delete _pFigure;

	CCDirector::sharedDirector()->end();
}

void TetrisLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{
	if (_figureState == FigureState::Added)
	{
		_pFigure->stopAction(_pActionMove);

		CCSetIterator it;
		for (it = pTouches->begin(); it != pTouches->end(); it++)
		{
			//speed from level
			float actualDuration1 =
				CSettings::InitialFallDuration / CSettings::GlassBlocksHeight
				* _pFigure->getFigureGlassPointY()
				- _pHudLayer->getLevel() * CSettings::FallDurationDecrementPerLevel;

			CCPoint pt = CCDirector::sharedDirector()->convertToGL( ((CCTouch*) (*it))->getLocationInView() );

			if (ccpDistance(pt, _pSpriteArrowUp->getPosition()) < CSettings::ArrowUpImgRadius)
			{
				CLog::add("%s", "Up button clicked");
				//onUpArrowClicked();
				_pFigure->rotateClockwise();
			}
			else if (ccpDistance(pt, _pSpriteArrowDown->getPosition()) < CSettings::ArrowUpImgRadius)
			{
				CLog::add("%s", "Down button clicked");
				//onDownArrowClicked();
				actualDuration1 = 0.3f;
			}
			else if (ccpDistance(pt, _pSpriteArrowLeft->getPosition()) < CSettings::ArrowUpImgRadius)
			{
				CLog::add("%s", "Left button clicked");
				//onLeftArrowClicked();
				_pFigure->moveLeft();
			}
			else if (ccpDistance(pt, _pSpriteArrowRight->getPosition()) < CSettings::ArrowUpImgRadius)
			{
				CLog::add("%s", "Right button clicked");
				//onRightArrowClicked();
				_pFigure->moveRight();
			}

			CCFiniteTimeAction* actionMove = 
					CCMoveTo::actionWithDuration( actualDuration1, 
						ccp( _pFigure->getPositionX(),
								CSettings::GlassMinPxY + CSettings::FigureSpriteSize / 2 - 1
								+ _pFigure->getBottomBlockCount() * CSettings::GlassCellSize
							)
						);

			CCFiniteTimeAction* actionMoveDone = 
				CCCallFuncN::actionWithTarget( this, 
				callfuncN_selector(TetrisLayer::figureMoveFinished));

			_pActionMove = CCSequence::actions(actionMove, actionMoveDone, NULL);

			_pFigure->runAction(_pActionMove);
		}
	}
	else if (_figureState == FigureState::GameOver)
	{
		CCSetIterator it;
		for (it = pTouches->begin(); it != pTouches->end(); it++)
		{
			CCPoint pt = CCDirector::sharedDirector()->convertToGL( ((CCTouch*) (*it))->getLocationInView() );

			if (ccpDistance(pt, _pSpriteReplay->getPosition()) < CSettings::ReplayImgRadius)
			{
				CLog::add("%s", "Replay button clicked");
				//onReplayButtonClicked();

				// clear glass
				CTetrisGlass::getInstance()->clearGlass();

				// Start new game
				CCScene *pScene = TetrisLayer::scene();
				CCDirector::sharedDirector()->replaceScene(pScene);
			}
		}
	}
}

void TetrisLayer::addFigure(float dt)
{
	if (_figureState == FigureState::Removed)
	{
		_pHudLayer->incrementScore();

		_pFigure = _pNextFigure;
		this->removeChild(_pFigure, false);

		_pNextFigure = CTetrisFigureCreator::CreateRandom();
		_pNextFigure->setFigureDirection(rand() % CSettings::FigureDirectionsCount);

		int iNextFigureAverage_dX = (_pNextFigure->getRightBlockCount()
			- _pNextFigure->getLeftBlockCount()) * CSettings::GlassCellSize / 2;

		int iNextFigureAverage_dY = (_pNextFigure->getTopBlockCount()
			- _pNextFigure->getBottomBlockCount()) * CSettings::GlassCellSize / 2;

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		_pNextFigure->setPosition(size.width - 60 - iNextFigureAverage_dX,
									size.height / 2 + 50 - iNextFigureAverage_dY);

		this->addChild(_pNextFigure);

		_pFigure->setFigureGlassPoint(
				CSettings::GlassBlocksWidth / 2,
				CSettings::GlassBlocksHeight + _pFigure->getBottomBlockCount()
			);

		this->addChild(_pFigure);

		// game over here
		if ( !_pFigure->canMoveDown() && _pFigure->isFigureOverGlass() )
		{
			_pHudLayer->hideNextFigureLabel();
			_pNextFigure->setVisible(false);
			_pHudLayer->showGameOverLabel();
			_figureState = FigureState::GameOver;

			_pSpriteReplay->setVisible(true);

			return;
		}

		float actualDuration =
			CSettings::InitialFallDuration
			- _pHudLayer->getLevel() * CSettings::FallDurationDecrementPerLevel;

		// Create the actions
		CCFiniteTimeAction* actionMove = 
			CCMoveTo::actionWithDuration( actualDuration, 
				ccp(_pFigure->getPositionX(),
					CSettings::GlassMinPxY + CSettings::FigureSpriteSize / 2 - 1
					+ _pFigure->getBottomBlockCount() * CSettings::GlassCellSize
					)
				);
			

		CCFiniteTimeAction* actionMoveDone = 
			CCCallFuncN::actionWithTarget( this, 
			callfuncN_selector(TetrisLayer::figureMoveFinished));

		_pActionMove = CCSequence::actions(actionMove, actionMoveDone, NULL);

		_pFigure->runAction( _pActionMove );
		
		_figureState = FigureState::Added;
	}
}

void TetrisLayer::checkCollision(float dt)
{
	if (_figureState == FigureState::Added)
	{
		_figureState = FigureState::Check;

		CTetrisGlass* pGlass = CTetrisGlass::getInstance();

		if ( !_pFigure->canMoveDown() )
		{
			// game over here
			if ( _pFigure->isFigureOverGlass() )
			{
				_pHudLayer->hideNextFigureLabel();
				_pNextFigure->setVisible(false);
				_pHudLayer->showGameOverLabel();

				_pFigure->stopAction(_pActionMove);

				_pFigure->setFigureGlassPointY(_pFigure->getFigureGlassPointY());

				_pSpriteReplay->setVisible(true);

				_figureState = FigureState::GameOver;
			}
			else
			{
				pGlass->addFigure(_pFigure);

				for (int i = pGlass->getRowsCount() - 1; i >= 0 ; i--)
				{
					if (pGlass->isRowFull(i))
					{
						pGlass->removeRow(i);
						_pHudLayer->incrementLines();
					}
				}

				this->removeChild(_pFigure, false);

				_figureState = FigureState::Removed;
			}
		}
		else
		{
			_figureState = FigureState::Added;
		}
	}
}

void TetrisLayer::figureMoveFinished(CCNode* pSender)
{
	if (_figureState == FigureState::Added)
	{
		_figureState = FigureState::Check;

		CTetrisGlass* pGlass = CTetrisGlass::getInstance();

		pGlass->addFigure(_pFigure);

		for (int i = pGlass->getRowsCount() - 1; i >= 0 ; i--)
		{
			if (pGlass->isRowFull(i))
			{
				pGlass->removeRow(i);
				_pHudLayer->incrementLines();
			}
		}

		this->removeChild(_pFigure, false);

		_figureState = FigureState::Removed;
	}
}
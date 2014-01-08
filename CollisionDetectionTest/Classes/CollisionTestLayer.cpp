#include "CollisionTestLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CollisionTestLayer::CollisionTestLayer(){
    CCLOG("CollisionTestLayer()");
}

CollisionTestLayer::~CollisionTestLayer(){
    CCLOG("~CollisionTestLayer()");
    delete collisionDetaction;
}

bool CollisionTestLayer::init(){
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // Create batch node
    batchNode = CCSpriteBatchNode::create("Icon-Small.png");
    addChild(batchNode, 0);
    
    labelBMFontBatch = LabelBMFontBatch::create("default_font.png", "default_font.fnt", 400);
    addChild(labelBMFontBatch, 99);
    
    gridTexture = NULL;
    
    gameObjects = CCArray::create();
    
    // Create collisionDetaction
    collisionDetaction = new CollisionDetaction(gameObjects, 3);
    
    // Create spaceLabel
    spaceLabelArray = CCArray::create();
    
    scheduleUpdate();
    
    return true;
}

void CollisionTestLayer::onEnter(){
    CCLayer::onEnter();
    m_debugLabel->setZOrder(100);
}

// Inter-frame operation
void CollisionTestLayer::update(float dt){
    
    // Create object
    CCPointer<CCSprite> object = CCSprite::createWithTexture(batchNode->getTexture());
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    object->setPosition(ccp((float)(rand() % (int)size.width), (float)(rand() % (int)size.height)));
    batchNode->addChild(object);
    gameObjects->addObject(object);
    CCMoveTo *move = CCMoveTo::create(8.0f, ccp((float)(rand() % (int)size.width), (float)(rand() % (int)size.height)));
    CCSequence *seq = CCSequence::create(move, NULL);
    object->runAction(seq);
    
    // Collision detection
    collisionDetaction->update();
    
    // Collision Handling
    for(int i = 0; i<collisionDetaction->getHitObjectList().size(); i++){
        CCSprite *gameObject1 = (CCSprite*)collisionDetaction->getHitObjectList()[i].getObject1();
        CCSprite *gameObject2 = (CCSprite*)collisionDetaction->getHitObjectList()[i].getObject2();
        gameObject1->setColor(ccRED);
        gameObject2->setColor(ccBLUE);
        deleteObject(gameObject1);
        deleteObject(gameObject2);
    }
    
    // Update label
    m_debugLabel->setString(CCString::createWithFormat("SpaceLevel:%d\nCheckHitCount:%d\nScanSpaceCount:%d\nHitObjectPair:%d\nGameObjectCount:%d\nDelayTime:%.04f",
                                                       collisionDetaction->getUiLevel(),
                                                       collisionDetaction->getCheckHitCount(),
                                                       collisionDetaction->getCheckTreeSpaceCount(),
                                                       (int)collisionDetaction->getHitObjectList().size(),
                                                       gameObjects->count(),
                                                       dt
                                                       )->getCString());
}

// Draw
void CollisionTestLayer::draw(){
    
    // Draw grid
    if(CCDirector::sharedDirector()->getTotalFrames() % 4 == 0){
        setSpaceGridAndLabel();
    }
}

// Delete game object(sprite)
void CollisionTestLayer::deleteObject(CCNode *obj){
    if(gameObjects->containsObject(obj)){
        
        gameObjects->removeObject(obj);
        
        CCFadeOut *fade = CCFadeOut::create(0.2f);
        CCCallFuncND *func = CCCallFuncND::create(obj, callfuncND_selector(CCNode::removeFromParent), NULL);
        CCSequence *seq = CCSequence::create(fade, func, NULL);
        obj->runAction(seq);
    }
}

// Draw collision space grid and label
void CollisionTestLayer::setSpaceGridAndLabel(){
    
    CCSize winSize = collisionDetaction->getSpaceRect().size;
    labelBMFontBatch->removeAllTexts();
    
    if(!gridTexture){
        gridTexture = CCRenderTexture::create(winSize.width, winSize.height);
        gridTexture->setPosition(ccp(winSize.width/2, winSize.height/2));
        gridTexture->begin();
    }
    
    // Loop space level count
    for(register int i = 0; i<collisionDetaction->getUiLevel()+1; i++){
        
        // Get spaceCount of this level
        int spaceCount = collisionDetaction->getSpaceNumBySpaceLevel(i);
            
        for(register int x = 0; x<sqrt(spaceCount); x++){
            for(register int y = 0; y<sqrt(spaceCount); y++){
                
                // Get space Size
                int spaceWidth = winSize.width / sqrt(spaceCount);
                int spaceHeight = winSize.height / sqrt(spaceCount);
                
                // Draw space rect
                CCPoint startPos = ccp(collisionDetaction->getSpaceRect().origin.x + spaceWidth*x, + collisionDetaction->getSpaceRect().origin.y + spaceHeight*y);
                CCPoint endPos = ccp((collisionDetaction->getSpaceRect().origin.x + spaceWidth*x) + spaceWidth, collisionDetaction->getSpaceRect().origin.y + (spaceHeight*y) + spaceHeight);
                
                if(!getChildren()->containsObject(gridTexture)){
                    glLineWidth(3.0f);
                    ccDrawRect(startPos, endPos);
                }
                
                // Set Labels
                int spaceIndex = collisionDetaction->getMortonNumberFromPosition(ccp(startPos.x + spaceWidth/2, startPos.y + spaceHeight/2));
                CCArray *spaceCellArray = (CCArray*)collisionDetaction->getSpaceArray()->objectAtIndex(spaceIndex);
                labelBMFontBatch->addTextAt(CCString::createWithFormat("%d", spaceCellArray->count())->getCString(), ccp(startPos.x + spaceWidth/2, startPos.y + spaceHeight/2 - 20), 1.0f);
            }
        }
    }
    
    if(!getChildren()->containsObject(gridTexture)){
        addChild(gridTexture);
        gridTexture->end();
    }
}
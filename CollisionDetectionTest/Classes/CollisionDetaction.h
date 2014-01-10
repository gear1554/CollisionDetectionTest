//
//  CollisionDetaction.h
//  
//
//  CollisionDetaction
//
//  Created by gear1554 on 2012/10/18.
//

#pragma once

#include "cocos2d.h"


#define CLINER4TREEMANAGER_MAXLEVEL		9

USING_NS_CC;
using namespace std;

class CollisionPair{
private:
    CC_SYNTHESIZE(CCNode*, object1, Object1);
    CC_SYNTHESIZE(CCNode*, object2, Object2);
public:
    CollisionPair(CCNode* obj1, CCNode* obj2){
        object1 = obj1;
        object2 = obj2;
    };
    ~CollisionPair(){
        object1 = object2 = NULL;
    }
};

class CollisionDetactionDelegate
{
public:
    /**
     * Delegate to respond collision event
     *
     * @param collisionPair colliding things
     */
    virtual void onCollide(CollisionPair& collisionPair) = 0;
    
    /**
     * Please implement a method to detect a collision
     *
     * @param CollisionObject1 node that may collided
     * @param CollisionObject2 another node that may collided
     */
    virtual bool detectCollision(CCNode* collisionObject1, CCNode* collisionObject2) = 0;
};


class CollisionDetaction{

public:

    CollisionDetaction(CollisionDetactionDelegate* _collisionDetactionDelegate,
                       CCArray *_gameObjecrtArray,
                       unsigned int spaceLevel);
    ~CollisionDetaction();
    
    CC_SYNTHESIZE(CollisionDetactionDelegate*, collisionDetectionDelegate, CollisionDetactionDelegate);
    CC_SYNTHESIZE(unsigned int, checkHitCount, CheckHitCount);
    CC_SYNTHESIZE(unsigned int, checkTreeSpaceCount, CheckTreeSpaceCount);
    CC_SYNTHESIZE(int, dwCellNum, DwCellNum);
    CC_SYNTHESIZE(int, uiLevel, UiLevel);
    CC_SYNTHESIZE(float, fW, FW);
    CC_SYNTHESIZE(float, fH, FH);
    CC_SYNTHESIZE(float, fLeft, FLeft);
    CC_SYNTHESIZE(float, fTop, FTop);
    CC_SYNTHESIZE(float, fUnit_W, FUnit_W);
    CC_SYNTHESIZE(float, fUnit_H, FUnit_H);
    
    CC_SYNTHESIZE(CCRect, spaceRect, SpaceRect);
    
    CC_SYNTHESIZE(vector<CollisionPair>, hitObjectList, HitObjectList);
    CC_SYNTHESIZE(CCArray*, spaceArray, SpaceArray);
    
    bool Init(int Level, float left, float top, float right, float bottom);

    void update();
    
    int getMortonNumberFromNode(CCNode* sprite);
    
    int getMortonNumberFromPosition(CCPoint position);

    int getSpaceNumBySpaceLevel(unsigned int spaceLevel);
    
    bool isHavingChildSpace(int spaceIndex);
    
private:
    
    CCArray *gameObjectArray;
    
    unsigned int iPow[CLINER4TREEMANAGER_MAXLEVEL+1];                       
    
        
    int BitSeparate32(int n);
           
    int Get2DMortonNumber(int x, int y);
    
    int GetPointElem(float pos_x,  float pos_y);
    
    void updateSpaceStatus(CCNode* collisionObject);
    
    void refreshSpace();
    
    void scanCollisionDetection(int spaceIndex, CCArray* stackArray);
    
    void checkHit(CCNode* CollisionObject1, CCNode* collisionObject2);
    
    void checkHitSpaceCell(CCArray* array1, CCArray* array2);
};

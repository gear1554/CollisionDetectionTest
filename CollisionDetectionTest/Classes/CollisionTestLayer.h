#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

#include "CCPointer.h"
#include "CollisionDetaction.h"
#include "LabelBMFontBatch.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CollisionTestLayer :
public CCLayer,
public CCBSelectorResolver,
public CCBMemberVariableAssigner,
public CollisionDetactionDelegate
{
private:
    
    CC_SYNTHESIZE(CCPointer<CCLabelTTF>, m_titleLabel, M_titleLabel);
    CC_SYNTHESIZE(CCPointer<CCLabelBMFont>, m_debugLabel, M_debugLabel);

    CC_SYNTHESIZE(CCPointer<CCRenderTexture>, gridTexture, GridTexture);
    CC_SYNTHESIZE(CCPointer<LabelBMFontBatch>, labelBMFontBatch, LabelBMFontBatch);
    CC_SYNTHESIZE(CCPointer<CCSpriteBatchNode>, batchNode, BatchNode);
    CC_SYNTHESIZE(CollisionDetaction*, collisionDetaction, CollisionDetaction);
    CC_SYNTHESIZE(CCPointer<CCArray>, gameObjects, GameObjects);
    CC_SYNTHESIZE(CCPointer<CCArray>, spaceLabelArray, SpaceLabelArray);
    
    unsigned int counter;
    
    CollisionTestLayer();    
    ~CollisionTestLayer();    
    
public:
    
    virtual bool init();
    virtual void onEnter();
    virtual void update(float dt);
    virtual void draw();
    
    virtual void onCollide(CollisionPair& collisionPair);
    virtual bool detectCollision(CCNode* collisionObject1, CCNode* collisionObject2);
    
    void deleteObject( CCNode* obj );
    void setSpaceGridAndLabel();
    
    CREATE_FUNC(CollisionTestLayer);
    
    bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
    {
        //doc_root_var
	    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "titleLabel", CCLabelTTF *, this->m_titleLabel);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "debugLabel", CCLabelBMFont *, this->m_debugLabel);
	    return false;
    };
    SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName) {
        //cc_menu
        return NULL;
    };
    SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName) {
        //cc_control
        return NULL;
    };
    
};


class CollisionTestLayerLoader : public extension::CCLayerLoader {
public:    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CollisionTestLayerLoader, loader);
protected: CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CollisionTestLayer);
};

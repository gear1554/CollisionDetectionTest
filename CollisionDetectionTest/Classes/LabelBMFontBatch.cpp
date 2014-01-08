#include "LabelBMFontBatch.h"
 
LabelBMFontBatch::LabelBMFontBatch(const char *fntFile) : CCSpriteBatchNode() {
    _fntFile = fntFile;
    _lastChildTag = 0;
}
 
LabelBMFontBatch::~LabelBMFontBatch() {
    _fntFile = NULL;
    this->removeAllChildren();
}
 
LabelBMFontBatch *LabelBMFontBatch::create(const char *fileImage, const char *fntFile, unsigned int capacity) {
 
    LabelBMFontBatch *batchNode = new LabelBMFontBatch(fntFile);
    batchNode->initWithFile(fileImage, capacity);
    batchNode->autorelease();
 
    return batchNode;
}
 
int LabelBMFontBatch::addTextAt(const char *text, CCPoint position, float scale) {
 
    _lastChildTag += 100;
 
    CCLabelBMFont *bmpFont = CCLabelBMFont::create(text, _fntFile);
    CCSize textWidth = bmpFont->getContentSize();
 
    // center text ...
    position.x -= textWidth.width * 0.5f * scale;
 
    for(int i = 0; i < bmpFont->getChildrenCount(); i++)
    {
        CCObject *child = bmpFont->getChildren()->objectAtIndex(i);
        CCSprite *pNode = (CCSprite*)child;
        CCPoint pNodePosition = pNode->getPosition();
 
        pNode->retain();
 
        bmpFont->removeChild(pNode, false);
        this->addChild(pNode);
 
        pNode->setScale(scale);
        pNode->setPosition(ccp(position.x + pNodePosition.x * scale, position.y + pNodePosition.y * scale));
        pNode->setTag(_lastChildTag);
        pNode->release();
 
        --i;
    }
 
    return _lastChildTag;
}
 
void LabelBMFontBatch::removeTextByID(int textID)
{
    CCNode *child = this->getChildByTag(textID);
 
    while(child != NULL)
    {
        this->removeChild(child, true);
        child = this->getChildByTag(textID);
    }
}
 
void LabelBMFontBatch::removeAllTexts() {
    this->removeAllChildrenWithCleanup(true);
}
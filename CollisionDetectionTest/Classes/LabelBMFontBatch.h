#include "cocos2d.h"
 
using namespace cocos2d;
 
class LabelBMFontBatch : public cocos2d::CCSpriteBatchNode
{
 
private:
    const char *_fntFile;
    int _lastChildTag;
 
public:
 
    LabelBMFontBatch(const char *fntFile);
    ~LabelBMFontBatch();
 
    static LabelBMFontBatch *create(const char *fileImage, const char *fntFile, unsigned int capacity);
 
    /* returns a text id. used to identify the text in the batch. use the id with removeTextByID  */
    int addTextAt(const char *text, CCPoint position, float scale);
    void removeTextByID(int textID);
    void removeAllTexts();
};
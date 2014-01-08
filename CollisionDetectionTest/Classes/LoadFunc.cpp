// ##### 【注意】このファイルは自動生成ファイルですので、変更しないでください ######
// ##### 更新時は、LoaderMaker/LoadMaker.rb のrubyスクリプトを実行してください #####

#include "LoadFunc.h"




    //-----------------------------------
    //../CollisionDetectionTest/CocosBuilder/Resources/CollisionTestLayer.ccb
    #ifdef __CollisionDetectionTest__CollisionTestLayer__
    bool CollisionTestLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
    {
      //doc_root_var 
	    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "debugLabel", CCLabelBMFont *, this->m_debugLabel);
	    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "titleLabel", CCLabelTTF *, this->m_titleLabel);
	    return false;
    }

    SEL_MenuHandler CollisionTestLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName) {
      //cc_menu 
      return NULL;
    };
    SEL_CCControlHandler CollisionTestLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName) {
      //cc_control 
      return NULL;
    };
    #endif


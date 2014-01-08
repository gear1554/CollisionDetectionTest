// ##### 【注意】このファイルは自動生成ファイルですので、変更しないでください ######
// ##### 更新時は、LoaderMaker/LoadMaker.rb のrubyスクリプトを実行してください #####
#ifndef __CollisionDetectionTest__LoadFunc__
#define __CollisionDetectionTest__LoadFunc__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;



#define CCB_CUSTOMPROPERTY_GLUE(TARGET, MEMBERVARIABLENAME, PROPVALUE) if (0 == strcmp(pMemberVariableName, ( #MEMBERVARIABLENAME ))) {   TARGET->set ## MEMBERVARIABLENAME (PROPVALUE);   return true; }





// include section ------------ 
  #include "CollisionTestLayer.h"




// Loader define section ------------ 
      //-----------------------------------
    //../CollisionDetectionTest/CocosBuilder/Resources/CollisionTestLayer.ccb
      #ifdef __CollisionDetectionTest__CollisionTestLayer__
      class CollisionTestLayerLoader : public extension::CCLayerLoader {
	      public:    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CollisionTestLayerLoader, loader);
    	  protected: CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CollisionTestLayer);
      };
      #endif




// loader function section ------------ 
      class LoadFunc{
        public: static void registerLoader(){
          CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
        //#ifdef __CollisionDetectionTest__CollisionTestLayer__
          ccNodeLoaderLibrary->registerCCNodeLoader("CollisionTestLayer", CollisionTestLayerLoader::loader());
        //#endif
        }
      };
#endif //__CollisionDetectionTest__LoadFunc__)
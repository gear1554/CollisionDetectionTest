CollisionDetectionTest
======================

cocos2d-x上での当り判定走査の効率的に行う  
CollisionDetectionクラスの動作確認、デモ用のプロジェクト  


###CollisionDetectionクラスの使い方
1. CollisionDetection.hとCollisionDetection.cppを使用したいプロジェクトへ追加
2. ヘッダーへの定義、初期化を行う
  - コンストラクタの第1引数に判定を行いたい対象の配列を指定してください
  - コンストラクタの第2引数に0～9の数値(空間の分割レベル)を指定してください(2～4がおすすめ?)
***
 CollisionTestLayer.h
  ```C++
    CC_SYNTHESIZE(CollisionDetaction*, collisionDetaction, CollisionDetaction);
    CC_SYNTHESIZE(CCPointer<CCArray>, gameObjects, GameObjects);
  ``` 
***
  CollisionTestLayer.cpp
  ```C++
    gameObjects = CCArray::create();
    
    // Create collisionDetaction
    collisionDetaction = new CollisionDetaction(gameObjects, 3);
  ```
***
3. 毎フレーム処理を行う箇所でcollisionDetaction->update();を呼んでやる  
  CollisionTestLayer.cpp
  ```C++
    // Inter-frame operation
    void CollisionTestLayer::update(float dt){
      /**
          省略
      */
      
      // Collision detection
      collisionDetaction->update(); // ←ここで呼んでいる
      
      /**
          省略
      */
    }
  ```
4. 当ったと判定されたオブジェクトのペアの取得  
  CollisionTestLayer.cpp
  ```C++
    // Inter-frame operation
    void CollisionTestLayer::update(float dt){
      /**
          省略
      */
      
      // Collision detection
      collisionDetaction->update();

      // Collision Handling
      for(int i = 0; i<collisionDetaction->getHitObjectList().size(); i++){
        // 当ったオブジェクトのペアの取得
        CCSprite *gameObject1 = (CCSprite*)collisionDetaction->getHitObjectList()[i].getObject1();
        CCSprite *gameObject2 = (CCSprite*)collisionDetaction->getHitObjectList()[i].getObject2();
        // ここでは当ったオブジェクトの色を赤と青に変更し、消す処理をしている
        gameObject1->setColor(ccRED);
        gameObject2->setColor(ccBLUE);
        deleteObject(gameObject1);
        deleteObject(gameObject2);
      }
      
      /**
          省略
      */
    }
  ```

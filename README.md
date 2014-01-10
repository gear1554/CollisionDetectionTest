CollisionDetectionTest
======================

cocos2d-x上での当り判定走査を効率的に行う(判定回数を減らす)ための  
CollisionDetectionクラスの動作確認、デモ用のプロジェクト  

※cocos2d-xのバージョンは2.1.4前提です

アルゴリズム、実装は下記記事を参考に、しています。  
[その８ 4分木空間分割を最適化する！（理屈編）](http://marupeke296.com/COL_2D_No8_QuadTree.html)


###CollisionDetectionクラスの使い方
CCTableViewのような感じで利用できます。  

1. CollisionDetection.hとCollisionDetection.cppを使用したいプロジェクトへ追加
2. ヘッダーへの定義、初期化を行う
  - 画面クラスにはCollisionDetactionDelegateクラスを継承させてください
  - コンストラクタの第1引数に判定を行いたい画面(CCLayer*)を指定してください
  - コンストラクタの第2引数に判定を行いたい対象の配列を指定してください
  - コンストラクタの第3引数に0～9の数値(空間の分割レベル)を指定してください(2～4推奨?)
***
 CollisionTestLayer.h
  ```C++

     class CollisionTestLayer :
        public CCLayer,
        public CCBSelectorResolver,
        public CCBMemberVariableAssigner,
        public CollisionDetactionDelegate // これを継承してください
        {
          private:
          /**
            省略
          */
  
          CC_SYNTHESIZE(CollisionDetaction*, collisionDetaction, CollisionDetaction); // こんな感じで宣言
          CC_SYNTHESIZE(CCPointer<CCArray>, gameObjects, GameObjects);                // 当り判定チェックを行うオブジェクト格納用
  ``` 
***
  CollisionTestLayer.cpp
  ```C++
    gameObjects = CCArray::create();
    
    // Create collisionDetaction
    collisionDetaction = new CollisionDetaction(this, gameObjects, 3);
  ```
***
3. 毎フレーム処理を行う箇所でcollisionDetaction->update();を呼んでください
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
4. 仮想関数を実装してください(onCollide detectCollision)
***
  CollisionTestLayer.h
  ```C++
    virtual void onCollide(CollisionPair& collisionPair); // 当った際の処理
    virtual bool detectCollision(CCNode* collisionObject1, CCNode* collisionObject2); // 当っているかを判定
  ```
***
  CollisionTestLayer.cpp
  ```C++
    // Callback
    void CollisionTestLayer::onCollide(CollisionPair& collisionPair){ // 当った際の処理
      // ここでは当ったオブジェクトの色を赤と青に変更し、消す処理をしている
      CCSprite *gameObject1 = (CCSprite*)collisionPair.getObject1();
      CCSprite *gameObject2 = (CCSprite*)collisionPair.getObject2();
      gameObject1->setColor(ccRED);
      gameObject2->setColor(ccBLUE);
      deleteObject(gameObject1);
      deleteObject(gameObject2);
    }
 
    // Detect collision by bounding box
    bool CollisionTestLayer::detectCollision(CCNode* collisionObject1, CCNode* collisionObject2){ // 当っているかを判定
      return collisionObject1->boundingBox().intersectsRect(collisionObject2->boundingBox()); // 矩形が重なっていた場合は、当っているとする
    }
  ```
***

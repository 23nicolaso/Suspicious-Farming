#include "LevelA.h"

LevelA::LevelA()                                      : Scene { {0.0f}, nullptr   } {}
LevelA::LevelA(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

LevelA::~LevelA() { shutdown(); }

void LevelA::initialise()
{
   mGameState.nextSceneID = 0;

   mGameState.bgm = LoadMusicStream("assets/game/04 - Silent Forest.wav");
   SetMusicVolume(mGameState.bgm, 0.33f);
   // PlayMusicStream(gState.bgm);

   mGameState.jumpSound = LoadSound("assets/game/Dirt Jump.wav");

   /*
      ----------- MAP -----------
   */
   mGameState.map = new Map(
      LEVEL_WIDTH, LEVEL_HEIGHT,          // map grid cols & rows
      (unsigned int *) mLevelData,        // grid data
      "assets/game/basic_tileset.png",    // texture filepath
      TILE_DIMENSION,                     // tile size
      5, 1,                               // texture cols & rows
      mOrigin                             // in-game origin
   );

   /*
      ----------- PROTAGONIST -----------
   */
   
   // Assets from me!
   mGameState.xochitl = new Player(
      {mOrigin.x - 300.0f, mOrigin.y - 200.0f}, // position
      {100.0f, 100.0f},                         // scale
      "assets/game/walk.png",                   // texture file address
      ATLAS,                                    // single image or atlas?
      { 8, 8 },                                 // atlas dimensions
      PLAYER                                    // entity type
   );

   mGameState.xochitl->setColliderDimensions({
      mGameState.xochitl->getScale().x,
      mGameState.xochitl->getScale().y
   });
   mGameState.xochitl->setFrameSpeed(5);

   /*
      ----------- CROSSHAIR ----------
   */
  mGameState.crosshair = new Crosshair(
   {mOrigin.x, mOrigin.y},
   {0, 0},
   {50.0f, 50.0f},
   "assets/game/crosshair.png"
  );

  mGameState.crosshair->activate();

  /*
      ----------- MANAGERS ----------
  */
   mGameState.bulletManager = new BulletManager();
   mGameState.monsterManager =  new MonsterManager();

   /*
      ----------- CAMERA -----------
   */
   mGameState.camera = { 0 };                                    // zero initialize
   mGameState.camera.target = mGameState.xochitl->getPosition(); // camera follows player
   mGameState.camera.offset = mOrigin;                           // camera offset to center of screen
   mGameState.camera.rotation = 0.0f;                            // no rotation
   mGameState.camera.zoom = 1.0f;                                // default zoom
}

void LevelA::update(float deltaTime)
{
   UpdateMusicStream(mGameState.bgm);

   mGameState.xochitl->update(
      deltaTime,      // delta time / fixed timestep
      nullptr,        // player
      nullptr,        // map
      nullptr,        // collidable entities
      0               // col. entity count
   );

   Vector2 currentPlayerPosition = { mGameState.xochitl->getPosition().x, mGameState.xochitl->getPosition().y };

   mGameState.bulletManager -> update(deltaTime);
   mGameState.monsterManager -> update(
      deltaTime, 
      mGameState.xochitl, 
      mGameState.map
   );

   panCamera(&mGameState.camera, &currentPlayerPosition);
}

void LevelA::render()
{
   ClearBackground(ColorFromHex(mBGColourHexCode));

   mGameState.map->render();
   mGameState.xochitl->updateAtlas();
   mGameState.xochitl->render();
   mGameState.crosshair->render();
   mGameState.bulletManager->render();
   mGameState.monsterManager->render();
}

void LevelA::shutdown()
{
   delete mGameState.xochitl;
   delete mGameState.map;
   delete mGameState.monsterManager;
   delete mGameState.bulletManager;

   UnloadMusicStream(mGameState.bgm);
   UnloadSound(mGameState.jumpSound);
}
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
      LEVEL_WIDTH, LEVEL_HEIGHT,   // map grid cols & rows
      (unsigned int *) mLevelData, // grid data
      "assets/game/tileset.png",   // texture filepath
      TILE_DIMENSION,              // tile size
      4, 1,                        // texture cols & rows
      mOrigin                      // in-game origin
   );

   /*
      ----------- PROTAGONIST -----------
   */
   std::map<AnimState, std::vector<int>> xochitlAnimationAtlas = {
      {RIGHT_SLASH,  { 25, 26, 27, 28, 29 }},
      {LEFT_SLASH,   { 30, 31, 32, 33, 34 }},
      {DOWN,         { 1,  0,  1,  2  }},
      {LEFT,         { 10, 9,  10, 11 }},
      {UP,           { 4,  3,  4,  5  }},
      {RIGHT,        { 7,  6,  7,  8  }},
      {UP_HOLDING,   { 12, 13, 14, 13 }},
      {LEFT_HOLDING, { 18, 19, 20, 19 }},
      {RIGHT_HOLDING,{ 15, 16, 17, 16 }},
      {DOWN_HOLDING, { 40, 39, 40, 41 }},
      {DOWN_SLASH,   { 21, 22, 23, 24 }},
      {UP_SLASH,     { 35, 36, 37, 38 }},
      {DOWN_GUN,     { 42, 43, 44, 43 }},
      {RIGHT_GUN,    { 45, 46, 47, 46 }},
      {UP_GUN,       { 51, 52, 53, 52 }},
      {LEFT_GUN,     { 48, 49, 50, 49 }},
      {LEFT_SHOOT,   { 49, 55, 49 }},
      {RIGHT_SHOOT,  { 46, 54, 46 }},
      {UP_SHOOT,     { 52, 57, 52 }},
      {DOWN_SHOOT,   { 43, 56, 43 }},
   };

   // Assets from me!
   mGameState.xochitl = new Entity(
      {mOrigin.x - 300.0f, mOrigin.y - 200.0f}, // position
      {100.0f, 100.0f},                         // scale
      "assets/game/walk.png",                   // texture file address
      ATLAS,                                    // single image or atlas?
      { 8, 8 },                                 // atlas dimensions
      xochitlAnimationAtlas,                    // actual atlas
      PLAYER                                    // entity type
   );

   mGameState.xochitl->setColliderDimensions({
      mGameState.xochitl->getScale().x,
      mGameState.xochitl->getScale().y
   });
   mGameState.xochitl->setFrameSpeed(3);

   /*
      ----------- CROSSHAIR ----------
   */
  mGameState.crosshair = new Crosshair(
   {mOrigin.x, mOrigin.y},
   {50.0f, 50.0f},
   "assets/game/crosshair.png"
  );

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
      mGameState.map, // map
      nullptr,        // collidable entities
      0               // col. entity count
   );

   Vector2 currentPlayerPosition = { mGameState.xochitl->getPosition().x, mGameState.xochitl->getPosition().y };

   panCamera(&mGameState.camera, &currentPlayerPosition);
}

void LevelA::render()
{
   ClearBackground(ColorFromHex(mBGColourHexCode));

   mGameState.map->render();
   mGameState.xochitl->render();
   mGameState.crosshair->render();
}

void LevelA::shutdown()
{
   delete mGameState.xochitl;
   delete mGameState.map;

   UnloadMusicStream(mGameState.bgm);
   UnloadSound(mGameState.jumpSound);
}
#include "House.h"

House::House()                                      : Scene { {0.0f}, nullptr   } {}
House::House(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

House::~House() { shutdown(); }

void House::initialise()
{
   mGameState.nextSceneID = 0;

   mGameState.bgm = LoadMusicStream("assets/audio/groovin.mp3");
   SetMusicVolume(mGameState.bgm, 0.3f);
   PlayMusicStream(mGameState.bgm);

   /*
      ----------- MAPS -----------
   */
   mGameState.map = new Map(
      LEVEL_WIDTH, LEVEL_HEIGHT,          // map grid cols & rows
      (unsigned int *) mLevelData,        // grid data
      "assets/game/tileset_room.png",     // texture filepath
      TILE_DIMENSION,                     // tile size
      17, 1,                              // texture cols & rows
      mOrigin                             // in-game origin
   );

   mGameState.plantMap = new Map(
      LEVEL_WIDTH, LEVEL_HEIGHT,
      (unsigned int *) mLevelPlantData,
      "assets/game/interior.png",
      TILE_DIMENSION,
      16, 1,
      mOrigin
   );

   /*
      --------- MANAGERS ---------
   */
   mGameState.npcManager     =  new NPCManager();
   mGameState.npcManager->setOrigin(mOrigin);

   mGameState.npcManager->spawnNPC(0);


   /*
      ----------- PROTAGONIST -----------
   */
   
   // Assets from me!
   mGameState.xochitl = new Player(
      {mOrigin.x - 300.0f, mOrigin.y + 100.0f}, // position
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
   mGameState.xochitl->setFrameSpeed(4);
   mGameState.xochitl->setSpeed(200.0f);

   /*
      ----------- CROSSHAIR ----------
   */
    const std::map<int, std::vector<int>> anim_atlas = {{0,{0}},{1,{1}},{2,{2}},{3,{3}},{4,{4}}};

    mGameState.crosshair = new Crosshair(
    {mOrigin.x, mOrigin.y},
    {50.0f, 50.0f},
    "assets/game/crosshair.png",
    ATLAS,
    {1, 5},
    anim_atlas,
    CROSSHAIR
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

void House::update(float deltaTime)
{
   UpdateMusicStream(mGameState.bgm);

   mGameState.xochitl->update(
      deltaTime,                  // delta time / fixed timestep
      nullptr,                    // player
      mGameState.plantMap,        // map
      nullptr,                    // collidable entities
      0                           // col. entity count
   );

   Vector2 currentPlayerPosition = { mGameState.xochitl->getPosition().x, mGameState.xochitl->getPosition().y };
   if (currentPlayerPosition.y > END_GAME_THRESHOLD){
      mGameState.nextSceneID = 3;
   }

   mGameState.bulletManager -> update(deltaTime, mGameState.monsterManager);

   mGameState.npcManager->update(deltaTime, mGameState.plantMap);
   
   mGameState.crosshair->updateCrosshair(mGameState.plantMap, mGameState.npcManager->getNPCs());   

   panCamera(&mGameState.camera, &currentPlayerPosition);
}

void House::render()
{
   ClearBackground(ColorFromHex(mBGColourHexCode));

   mGameState.map->render();
   mGameState.plantMap->render();
   mGameState.xochitl->updateAtlas();
   mGameState.xochitl->render();
   mGameState.bulletManager->render();
   mGameState.npcManager->render();
   mGameState.crosshair->render();
}

void House::shutdown()
{
   delete mGameState.xochitl;
   delete mGameState.plantMap;
   delete mGameState.map;
   delete mGameState.monsterManager;
   delete mGameState.npcManager;
   delete mGameState.bulletManager;

   UnloadMusicStream(mGameState.bgm);
}
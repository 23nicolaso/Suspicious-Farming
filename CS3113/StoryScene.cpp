#include "StoryScene.h"

StoryScene::StoryScene()                                      : Scene { {0.0f}, nullptr   } {}
StoryScene::StoryScene(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

StoryScene::~StoryScene() { shutdown(); }

void StoryScene::initialise()
{
    mLineTracker = 0;
    mBGTexture = LoadTexture("assets/game/grandmabesleepin.png");
    mSecondBGTexture = LoadTexture("assets/game/dish_to_please_the_gods.png");
    mGameState.nextSceneID = 0;

    mGameState.bgm = LoadMusicStream("assets/audio/grandmabesleepin.mp3");
    SetMusicVolume(mGameState.bgm, 0.33f);
    PlayMusicStream(mGameState.bgm);
}

void StoryScene::update(float deltaTime)
{
   UpdateMusicStream(mGameState.bgm);
}

void StoryScene::render()
{
    ClearBackground(ColorFromHex(mBGColourHexCode));

    // Whole texture (UV coordinates)
    Rectangle textureArea = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(mBGTexture.width),
        static_cast<float>(mBGTexture.height)
    };

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea = {
        0,
        0,
        static_cast<float>(GetScreenWidth()),
        static_cast<float>(GetScreenHeight())
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 originOffset = {
        0,
        0
    };

    // Render the texture on screen
    if (mLineTracker > 3){
        DrawTexturePro(
            mSecondBGTexture, 
            textureArea, destinationArea, originOffset,
            0, WHITE
        );
    }
    else {
        DrawTexturePro(
            mBGTexture, 
            textureArea, destinationArea, originOffset,
            0, WHITE
        );
    }
}

void StoryScene::shutdown()
{
    UnloadTexture(mBGTexture);
    UnloadTexture(mSecondBGTexture);
    UnloadMusicStream(mGameState.bgm);
}
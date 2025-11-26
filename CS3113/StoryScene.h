#ifndef STORY_H
#define STORY_H

#include "Scene.h"

class StoryScene : public Scene {
private:
    Texture2D mBGTexture;
    Texture2D mSecondBGTexture;
    int mLineTracker = 0;
public:
    StoryScene();
    StoryScene(Vector2 origin, const char *bgHexCode);
    ~StoryScene();
    
    void initialise() override;
    void update(float deltaTime) override;
    void render() override;
    void shutdown() override;
    void updateDialogNumber(int newLine) { mLineTracker = newLine; if (mLineTracker > 5){ mGameState.nextSceneID = 2; }}
};

#endif
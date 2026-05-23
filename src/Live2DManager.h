#ifndef LIVE2DMANAGER_H
#define LIVE2DMANAGER_H

class Live2DManager {
public:
    Live2DManager();
    ~Live2DManager();

    void init();
    void render();
    void update();
    void loadModel(const char* modelPath);
};

#endif // LIVE2DMANAGER_H

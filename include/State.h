#ifndef STATE_H
#define STATE_H

class State {
protected:
    bool popRequested;
    bool quitRequested;
    bool started;
    std::vector<std::shared_ptr<GameObject >> objectArray;

    void StartArray();
    virtual void UpdateArray(float dt);
    virtual void RenderArray();

public:
    State();
    virtual ~State();
    virtual void LoadAssets(float dt, std::string img_file, std::string music_file) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual std::weak_ptr<GameObject> AddObject(GameObject* go);
    virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
    bool PopRequested();
    bool QuitRequested();

};

#endif // STATE_H

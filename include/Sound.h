#ifndef SOUND_H
#define SOUND_H

class Sound : public Component{
private:
    Mix_Chunk* chunk;
    int channel;

public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, std::string file);
    ~Sound();
    void Open(std::string file);
    bool IsOpen();
    void Play(int times=1);
    bool Playing();
    void Stop();
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) const override;
    void Start() override;
    void NotifyCollision(GameObject& other) override;
    
};

#endif // SOUND_H

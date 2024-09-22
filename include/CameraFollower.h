#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

class CameraFollower : public Component{
private:
    Vec2 pos;
public:
    CameraFollower(GameObject& associated, int x=0, int y=0);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) const override;
    void Start() override;
    void NotifyCollision(GameObject& other) override;

};

#endif // CAMERAFOLLOWER_H
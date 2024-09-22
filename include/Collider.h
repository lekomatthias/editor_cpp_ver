#ifndef COLLIDER_H
#define COLLIDER_H

class Collider : public Component{
private:
    Vec2 scale;
    Vec2 offset;

public:
    Rect box;
    Collider(GameObject& associated, Vec2 scale=Vec2(1, 1), Vec2 offset=Vec2(0, 0));
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) const override;
    void Start() override;
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
    static bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB);
    void NotifyCollision(GameObject& other) override;

};

#endif // COLLIDER_H
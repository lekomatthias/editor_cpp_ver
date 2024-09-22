#ifndef CAMERA_H
#define CAMERA_H

class Camera {
private:
    static GameObject* focus;

public:
    static Vec2 pos;
    static Vec2 speed;

    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Zero();
    static void Update(float dt);

};

#endif // CAMERA_H

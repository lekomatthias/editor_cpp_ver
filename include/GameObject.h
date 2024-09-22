#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class Component;

class GameObject{
private:
    std::vector <Component*> components;
    bool isDeath;
    float dt;

public:
    Rect box;
    double angleDeg;
    bool started;
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render();
    bool IsDeath();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);
    void Start();
    void NotifyCollision(GameObject& other);
    
};

#endif // GAMEOBJECT_H

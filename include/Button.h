#ifndef BUTTON_H
#define BUTTON_H

class Button : public Component{
private:
    SDL_Texture* texture;
    Rect rect;
    SDL_Color color;
    std::string label;
    std::function<void()> funct;

public:
    Button(GameObject& associated, Rect rect, SDL_Color color, std::string label);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type)const override;
    void Start() override;
    void NotifyCollision(GameObject& other) override;
    
    void SetRect(Rect rect){ this->rect = rect;}
    void SetColor(SDL_Color color){ this->color = color;}
    void SetFunct(const std::function<void()>& function){ funct = function;}
    void SetLabel(std::string label){ this->label = label;}
    std::string GetLabel(){ return label;}
    void Press();

};

#endif // BUTTON_H
#ifndef TEXT_H
#define TEXT_H


enum class TextStyle {SOLID, SHADED, BLENDED};

class Text : public Component{
private:
    using IntFunct = std::function<int()>;

    TTF_Font* font;
    SDL_Texture* texture;
    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;
    int opacity;
    Timer timer;
    int tickTime;
    IntFunct followFunction;

    void RemakeTexture();

public:
    Text(GameObject& associated, std::string fontFile,
        int fontSize, TextStyle style, std::string text, SDL_Color color, int tickTime=0);
    ~Text();
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string) const override;
    void Start() override;
    void NotifyCollision(GameObject& other) override;
    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int size);
    void SetOpacity(int opacity);
    void SetFollowFunction(IntFunct function);

};

#endif // TEXT_H
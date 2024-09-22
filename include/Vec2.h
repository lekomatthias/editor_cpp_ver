#ifndef VEC2_H
#define VEC2_H

class Vec2{
public:
    float x, y;
    Vec2() : x(0.0f), y(0.0f){}
    Vec2(float x, float y) : x(x), y(y){}
    ~Vec2(){}

    inline float GetMagnitude(){ return sqrt(x*x + y*y);}
    inline Vec2 GetRotated(float angle){ return Vec2(x*cos(angle)-y*sin(angle), x*sin(angle)+y*cos(angle));}
    inline Vec2 GetNorm(){ return Vec2(x/this->GetMagnitude(), y/this->GetMagnitude());}
    inline Vec2 operator+(const Vec2& other){ return Vec2(x+other.x, y+other.y);}
    inline Vec2 operator-(const Vec2& other){ return Vec2(x-other.x, y-other.y);}
    inline Vec2 operator*(float n){ return Vec2(x*n, y*n);}
    inline float operator^(const Vec2& other){return x*other.x + y*other.y;}
    float GetAngle(){
        if (x >= 0) return asin(y/GetMagnitude());
        else return Config::name["PI"]/2 + (Config::name["PI"]/2 - asin(y/GetMagnitude()));
    }

};

#endif // VEC2_H
#include "Game_include.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset)
    : Component(associated){
        SetScale(scale);
        SetOffset(offset);
    }

void Collider::Update(float dt){ box = associated.box;}
// void Collider::Render(){}
bool Collider::Is(std::string type) const{ return ( type == COLLIDER);}
void Collider::Start(){}
void Collider::SetScale(Vec2 scale){ this->scale = scale;}
void Collider::SetOffset(Vec2 offset){ this->offset = offset;}
void Collider::NotifyCollision(GameObject& other){}

bool Collider::IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
    Vec2 A[] = { Vec2( a.x, a.y + a.h ),
                    Vec2( a.x + a.w, a.y + a.h ),
                    Vec2( a.x + a.w, a.y ),
                    Vec2( a.x, a.y )
                };
    Vec2 B[] = { Vec2( b.x, b.y + b.h ),
                    Vec2( b.x + b.w, b.y + b.h ),
                    Vec2( b.x + b.w, b.y ),
                    Vec2( b.x, b.y )
                };

    for (auto& v : A) {
        v = (v - a.GetCenter()).GetRotated(angleOfA) + a.GetCenter();
    }

    for (auto& v : B) {
        v = (v - b.GetCenter()).GetRotated(angleOfB) + b.GetCenter();
    }

    Vec2 axes[] = { (A[0] - A[1]).GetNorm(), (A[1] - A[2]).GetNorm(), (B[0] - B[1]).GetNorm(), (B[1] - B[2]).GetNorm() };

    for (auto& axis : axes) {
        float P[4];

        for (int i = 0; i < 4; ++i) P[i] = A[i] ^ axis;

        float minA = *std::min_element(P, P + 4);
        float maxA = *std::max_element(P, P + 4);

        for (int i = 0; i < 4; ++i) P[i] = B[i] ^ axis;

        float minB = *std::min_element(P, P + 4);
        float maxB = *std::max_element(P, P + 4);

        if (maxA < minB || minA > maxB)
            return false;
    }

    return true;
}

// Copie o conteúdo dessa função para dentro da sua e adapte o nome das funções para as suas.
// Funções usadas:
// Rect::GetCenter()				- Retorna um Vec2 no centro do Rect
// Vec2::operator-( const Vec2& )	- Subtrai dois Vec2
// Vec2::Rotate( float rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado
void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated( associated.angleDeg )
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).GetRotated( associated.angleDeg )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( associated.angleDeg )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).GetRotated( associated.angleDeg )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

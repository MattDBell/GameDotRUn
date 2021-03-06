#include <Box2D/Common/b2Math.h>
#include <SFML\System\Vector2.hpp>

#ifndef GDR_VECTOR2
#define GDR_VECTOR2
//Needs to be expanded to handle operators from both types... Yay
class GDR_Vector2
{
	b2Vec2 b2v;
public:
	GDR_Vector2() : b2v(0, 0) {};
	GDR_Vector2(float x, float y): b2v(x, y){};
	float GetX() {return b2v.x;}
	float GetY() {return b2v.y;}
	void SetX(float to) {b2v.x = to;}
	void SetY(float to) {b2v.y = to; }
	void Set(float xTo, float yTo) {SetX(xTo); SetY(yTo);}
	b2Vec2& AsBox() {return b2v;}
	sf::Vector2<float> AsSFML() const {return sf::Vector2<float>(b2v.x, b2v.y);} //This should only be called a la "DelayDest(sf::Vector2<float>) mine = gdr_vec2.AsSFML(); to avoid copying

};
#endif//GDR_VECTOR2
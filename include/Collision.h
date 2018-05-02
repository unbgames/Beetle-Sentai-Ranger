#include "Rect.h"
#include "Vec2.h"

#include <algorithm>
#include <cmath>

class Collision {

	public:
		// Observação: IsColliding espera ângulos em radianos!
		// Para usar graus, forneça a sua própria implementação de Rotate,
		// ou transforme os ângulos no corpo de IsColliding.
		static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {

			//SDL_Log("I: %f J: %f", angleOfA, angleOfB);
			//SDL_Log("I: x.%f y.%f w.%f h.%f", a.x, a.y, a.w, a.h);
			//SDL_Log("J: x.%f y.%f w.%f h.%f", b.x, b.y, b.w, b.h);

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
			/*for (auto& v : A) {
				v = v - a.GetCenter();
				v = v.Rotate(angleOfA);
				v = v + a.GetCenter();
			}

			for (auto& v : B) {
				v = v - b.GetCenter();
				v = v.Rotate(angleOfB);
				v = v + b.GetCenter();
			}*/

			Vec2 axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

			for (auto& axis : axes) {
				float P[4];

				for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

				float minA = *std::min_element(P, P + 4);
				float maxA = *std::max_element(P, P + 4);

				for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

				float minB = *std::min_element(P, P + 4);
				float maxB = *std::max_element(P, P + 4);

				if (maxA < minB || minA > maxB){
					//SDL_Log("false");
					return false;
				}
			}
			//SDL_Log("true");
			return true;
		}

		static inline bool IsColliding2(Rect& a, Rect& b, float angleOfA, float angleOfB) {

			SDL_Log("I: %f J: %f", angleOfA, angleOfB);
			SDL_Log("I: x.%f y.%f w.%f h.%f", a.x, a.y, a.w, a.h);
			SDL_Log("J: x.%f y.%f w.%f h.%f", b.x, b.y, b.w, b.h);

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

			/*for (int i = 0; i < 4; ++i) {
				A[i] = A[i] - a.GetCenter();
				A[i] = A[i].Rotate(angleOfA) + a.GetCenter();
			}

			for (int i = 0; i < 4; ++i) {
				B[i] = B[i] - b.GetCenter();
				B[i] = B[i].Rotate(angleOfB) + b.GetCenter();
			}*/
					
			for(int i = 0; i < 4; ++i){
				for (int j = 0; j < 4; ++j){
					int index1 = i;
					int index2 = (j+1)%4;
					
					if(IsIntersecting(A[index1], A[index2], B[index1], B[index2])){
						return(true);
					}
					//SDL_Log("%d %d", index1, index2);
				}		
			}	
			return(false);
		}

	private:

		static bool SegmentCollision(Vec2 a1, Vec2 a2, Vec2 b1, Vec2 b2){
			/*float x1 = p1.x;
			float x2 = p2.x;
			float x3 = p3.x;
			float x4 = p4.x;
			float y1 = p1.y;
			float y2 = p2.y;
			float y3 = p3.y;
			float y4 = p4.y;*/
			 
			float d = (a1.x - a2.x) * (b1.y - b2.y) - (a1.y - a2.y) * (b1.x - b2.x);
			// If d is zero, there is no intersection
			if(d == 0){
				//SDL_Log("chegou false");
				return(false);
			}
			//SDL_Log("chegou true");
			return(true);
		}

		static bool IsIntersecting(Vec2 a, Vec2 b, Vec2 c, Vec2 d){

		    float denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));
		    float numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
		    float numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

		    // Detect coincident lines (has a problem, read below)
		    if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

		    float r = numerator1 / denominator;
		    float s = numerator2 / denominator;

		    return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
		}

		static inline float Mag(const Vec2& p) {
			return std::sqrt(p.x * p.x + p.y * p.y);
		}

		static inline Vec2 Norm(const Vec2& p) {
			return p * (1.f / Mag(p));
		}

		static inline float Dot(const Vec2& a, const Vec2& b) {
			return a.x * b.x + a.y * b.y;
		}

		static inline Vec2 Rotate(const Vec2& p, float angle) {
			float cs = std::cos(angle), sn = std::sin(angle);
			return Vec2 ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
		}
};

// Aqui estão três operadores que sua classe Vec2 deve precisar, se já não tiver. 
// Se sua classe tiver métodos para Mag, Norm, Dot e/ou Rotate, você pode substituir
// os usos desses métodos por usos dos seus, mas garanta que deem resultados corretos.

// Vec2 operator+(const Vec2& rhs) const {
//    return Vec2(x + rhs.x, y + rhs.y);
// }

// Vec2 operator-(const Vec2& rhs) const {
//    return Vec2(x - rhs.x, y - rhs.y);
// }

// Vec2 operator*(const float rhs) const {
//    return Vec2(x * rhs, y * rhs);
// }

#ifndef __RT_ISICG_COOK_TORRANCE__
#define __RT_ISICG_COOK_TORRANCE__

#include "defines.hpp"

namespace RT_ISICG
{
	class CookTorrance
	{
	  public:
		CookTorrance( const Vec3f & p_kd, const Vec3f & p_F0, float p_Sigma )
			: _kd( p_kd ), F0( p_F0 ), Sigma( p_Sigma ) {};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & Wi, const Vec3f & Wo, const Vec3f & n ) const
		{
			///------------D-----------------//
			float Alpha		 = Sigma * Sigma;
			Vec3f h = glm::normalize( Wo + Wi );
			float Alpha2 = Alpha * Alpha;
			float nh		 = glm::dot( n, h );
			float x=(nh*nh * (Alpha2 - 1.f) + 1.f);
			float x2		 = glm::pow( x, 2 );
			float D			 = Alpha2 / ( PIf * x2 );
			///--------------K---------//
			float a = (Sigma +1);
			float a2 = glm::pow( a, 2 );
			float K	 = a2 / 8;
			///-------------G-----------------//
			float xo = glm::dot( n, Wo );
			float xi = glm::dot( n, Wi );
			float G1i = xi / (xi  * ( 1 - K ) + K );
			float G1o = xo / ( xo * ( 1 - K ) + K );
			float G	  = G1i * G1o;
			///------------F-------------------//
			float hwo = glm::dot(h,Wo);
			float InvHwo = 1 - hwo;
			float InvHwo5 = glm::pow( InvHwo ,5);

			Vec3f F = F0 + ( Vec3f( 1.0f, 1.0f, 1.0f ) - F0 ) * InvHwo5;
			//////Res/////////
			float Won = glm::dot( Wo, n );
			float Win = glm::dot( Wi, n );
			
			return ( D * F * G ) / ( 4 * Won * Win );
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		float Sigma;
		Vec3f _kd = WHITE;
		Vec3f F0 = Vec3f(0.0f,0.0f,0.0f);
	};
	} // namespace RT_ISICG
#endif //__RT_ISICG_COOK_TORRANCE__
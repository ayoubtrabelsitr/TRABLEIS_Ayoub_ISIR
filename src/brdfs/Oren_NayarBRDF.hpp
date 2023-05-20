#ifndef __RT_ISICG_BRDF_ORENNAYAR__
#define __RT_ISICG_BRDF_ORENNAYAR__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd, float p_Segma ) : _kd( p_kd ), _Segma( p_Segma ) {};

		
		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & p_wo, const Vec3f & p_wi, const Vec3f & p_n ) const
		{
			const float cosThetaO = glm::dot( p_n, p_wo );
			const float cosThetaI = glm::dot( p_n, p_wi );

			const float thetaO = glm::acos( cosThetaO );
			const float thetaI = glm::acos( cosThetaI );

			const float alpha = glm::max( thetaO, thetaI );
			const float beta  = glm::min( thetaO, thetaI );
			const Vec3f woPhi = glm::normalize( p_wo - p_n * cosThetaO );
			const Vec3f wiPhi = glm::normalize( p_wi - p_n * cosThetaI );

			const float cosPhiIO = glm::dot( woPhi, wiPhi );
			const float gamma	 = glm::max( 0.f, cosPhiIO );
			float		segma2	 = _Segma * _Segma;
			float		_A		 = 1.f - 0.5f * ( segma2 / ( segma2 + 0.33f ) );
			float		_B		 = 0.45f * ( segma2 / ( segma2 + 0.09f ) );
			return _kd * INV_PIf * ( _A + ( _B * gamma * glm::sin( alpha ) * glm::tan( beta ) ) );
		}
		inline const Vec3f & getKd() const{ return _kd; }

	  private:
		float _Segma;
		Vec3f _kd = WHITE;
	};

} // namespace RT_ISICG
#endif //__RT_ISICG_BRDF_ORENNAYAR__
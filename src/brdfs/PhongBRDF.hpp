#ifndef __RT_ISICG_BRDF_PHONGBRDF__
#define __RT_ISICG_BRDF_PHONGBRDF__

#include "defines.hpp"

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & p_kd, const Vec3f & p_ks, float p_s ) : _kd( p_kd ), _ks( p_ks ), s( p_s ) {};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( const Vec3f & Wi, const Vec3f & Wo, const Vec3f & n ) const
		{ 
			Vec3f Wr		= glm::reflect( Wi, n );
			float Cos_alpha = glm::dot( Wo, Wr );
			float Cos_puissance = glm::pow( Cos_alpha,s);
					
			return _ks * Cos_puissance;
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		float s;
		Vec3f _kd = WHITE;
		Vec3f _ks ;
	};

} // namespace RT_ISICG
#endif //__RT_ISICG_BRDF_PHONGBRDF__
#ifndef __RT_ISICG_REAL_MATERIAL__
#define __RT_ISICG_REAL_MATERIAL__

#include "base_material.hpp"
#include "brdfs/Cook_Torrance.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "defines.hpp"
namespace RT_ISICG
{
	class RealMaterial : public BaseMaterial
	{
	  public:
		RealMaterial( const std::string & p_name,
					  const Vec3f &		  p_diffuse,
					  const Vec3f &		  p_Specular,
					  const Vec3f		  F0,
					  const float		  p_metalness,
					  const float		  p_rugosité )
			: BaseMaterial( p_name ), LambertBRDF( p_diffuse ), CookBRDF( p_Specular, F0, p_rugosité ),
			  _metalness( p_metalness )
		{
		}
		virtual ~RealMaterial() = default;
		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			Vec3f diffuse  = LambertBRDF.evaluate(); 
				Vec3f specular = CookBRDF.evaluate( -p_ray.getDirection(), p_lightSample._direction,p_hitRecord._normal);
			return ( 1.0f - _metalness ) * diffuse + _metalness * specular;
		}

		inline const Vec3f & getFlatColor() const override { return LambertBRDF.getKd() + CookBRDF.getKd(); }

	  protected:
		LambertBRDF	 LambertBRDF;
		CookTorrance CookBRDF;
		float		 _metalness=0.0f;
	};
} // namespace RT_ISICG
#endif // __RT_ISICG_REAL_MATERIAL__
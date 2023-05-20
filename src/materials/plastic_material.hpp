#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/lambert_brdf.hpp"
#include "brdfs/PhongBRDF.hpp"
#include "defines.hpp"
namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_nameconst,
						 const Vec3f &			  p_kd,
						 const float & p_Specular,
						 const Vec3f &		 p_ks,
						 const float &		 p_s )
			: BaseMaterial( p_nameconst ), _Specular( p_Specular ), _BRDFLambert( p_kd ), _BRDFPhong( p_kd, p_ks, p_s )
			  
		{
		}

		  virtual ~PlasticMaterial() = default;
		Vec3f	  shade( const Ray &		 p_ray,
						 const HitRecord &	 p_hitRecord,
						 const LightSample & p_lightSample ) const override
		  {
			Vec3f Lambert= _BRDFLambert.evaluate();
			Vec3f Phong	= _BRDFPhong.evaluate(p_ray.getDirection(),p_lightSample._direction,p_hitRecord._normal);
			Lambert		 = ( 1.0f - _Specular ) * Lambert;
			Phong		 = _Specular * Phong;
			return Lambert+Phong;
		}
		  inline const Vec3f & getFlatColor() const override { return _BRDFPhong.getKd(); }
		  
	  protected:
		  LambertBRDF _BRDFLambert;
		  PhongBRDF	_BRDFPhong;
		  float		  _Specular;
		
		
	};

} // namespace RT_ISICG
#endif // __RT_ISICG_PLASTIC_MATERIAL__
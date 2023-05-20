#ifndef __RT_ISICG_PLANE__
#define __RT_ISICG_PLANE__

#include "base_object.hpp"
#include "geometry/PlaneGeometry.hpp"
namespace RT_ISICG
{
	class Plane : public BaseObject
	{

	  public:
		Plane()		  = delete;
		virtual ~Plane() = default;
		Plane( const std::string & p_name, const Vec3f & p_point, const Vec3f & p_normal )
			: BaseObject( p_name ), _geometry( p_point, p_normal ) {};
		virtual bool intersect( const Ray & p_ray,
								const float p_tMin,
								const float p_tMax,
								HitRecord & p_hitRecord ) const override;
		virtual bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;
		private:
		PlaneGeometry _geometry;

	};
}
#endif // __RT_ISICG_PLANE__
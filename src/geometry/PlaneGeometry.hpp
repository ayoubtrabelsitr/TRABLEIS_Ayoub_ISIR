#ifndef __RT_ISICG_PLANE_GEOMETRY__
#define __RT_ISICG_PLANE_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{

	class PlaneGeometry : public BaseGeometry
	{
		public :
		PlaneGeometry() = delete;
		virtual ~PlaneGeometry() = default;
		PlaneGeometry( const Vec3f & p_point, const Vec3f & p_normale ) : _point( p_point), _normal( p_normale ) {}
		inline const Vec3f & get_Point() const { return _point; }
		inline const Vec3f & get_Normal() const { return _normal; }
		bool				 intersect( const Ray & p_ray, float & p_t ) const;
	  private:
		Vec3f _point = { 0, 0, 0 };
		Vec3f _normal = { 0, 0, 0 };
	};
} // namespace RT_ISICG
#endif // __RT_ISICG_PLANE_GEOMETRY__
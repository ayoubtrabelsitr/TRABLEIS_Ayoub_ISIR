#include "implicit_surface.hpp"

namespace RT_ISICG
{
	bool ImplicitSurface::intersect( const Ray & p_ray,
									 const float p_tMin,
									 const float p_tMax,
									 HitRecord & p_hitRecord ) const
	{
		for ( float i = p_tMin; i < p_tMax;) //profondeur minimale ---> profondeur maximale
		{
			Vec3f point_i   = p_ray.pointAtT( i );//point sur le rayon à la profondeur i
			float distance = _sdf( point_i );	  // distance entre le point et la surface implicite
			i += distance;
			if ( distance < _minDistance ) //une intersection avec la surface implicite à point_i
			{	// Intersection found, fill p_hitRecord.
				p_hitRecord._point	= p_ray.pointAtT( i );
				p_hitRecord._normal = _evaluateNormal( p_hitRecord._point );
				p_hitRecord.faceNormal( p_ray.getDirection() );
				p_hitRecord._distance = i;
				p_hitRecord._object	  = this;
				return true;
			}
		}
		return false;
	}

	bool ImplicitSurface::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		for ( float i = p_tMin; i < p_tMax; ) // profondeur minimale ---> profondeur maximale
		{
			Vec3f point_i  = p_ray.pointAtT( i ); // point sur le rayon à la profondeur i
			float distance = _sdf( point_i );	  // distance entre le point et la surface implicite
			i += distance;
			if ( distance < _minDistance ) // une intersection avec la surface implicite à point_i
			{ // Intersection found, fill p_hitRecord.
				return true;
			}
		}
		return false;
	}
} // namespace RT_ISICG

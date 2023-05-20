#include "sphere_geometry.hpp"

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		/// TODO !
		
		Vec3f oc = p_ray.getOrigin() - getCenter();
		float b	 = 2.0f * dot( oc, p_ray.getDirection() );
		float c	 = dot( oc, oc ) - _radius * _radius;

		float Delta = b * b - 4 * c;

		if ( Delta < 0 ) 
		{
			return false; 
		}
		else
		{
			float t1 = ( -b - sqrt( Delta ) ) /2.0f;
			float t2 = ( -b + sqrt( Delta ) ) /2.0f;

			if ( t1 < t2 )
			{
				p_t1 = t1;
				p_t2 = t2;
			}
			else
			{
				p_t1 = t2;
				p_t2 = t1;
			}

			return true;
		}
	}

} // namespace RT_ISICG

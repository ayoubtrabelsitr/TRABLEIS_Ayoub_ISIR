#include "aabb.hpp"
using namespace std;
namespace RT_ISICG
{
	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		Vec3f origine = p_ray.getOrigin();
		Vec3f direction = p_ray.getDirection();
		float tx_min	= ( _min.x - origine.x ) / direction.x;
		float tx_max    = ( _max.x - origine.x ) / direction.x;
		float ty_min	= ( _min.y - origine.y ) / direction.y;
		float ty_max	= ( _max.y - origine.y ) / direction.y;
		float tz_min	= ( _min.z - origine.z ) / direction.z;
		float tz_max	= ( _max.z - origine.z ) / direction.z;
		
		float tmin = max( max( min( tx_min, tx_max ), min( ty_min, ty_max ) ), min( tz_min, tz_max ) );
		float tmax = min( min( max( tx_min, tx_max ), max( ty_min, ty_max ) ), max( tz_min, tz_max ) );

		if ( tmax < 0 )
		{
			return false;
		}
		if ( tmin > tmax )
		{
			return false;
		}
		return true;
		
	}
} // namespace RT_ISICG

#include "PlaneGeometry.hpp"
namespace RT_ISICG
{
	


	bool PlaneGeometry::intersect(const Ray& p_ray, float& p_t)const { 
		float den = glm::dot( p_ray.getDirection(), _normal );
		Vec3f po  = _point - p_ray.getOrigin();
		p_t		  = glm::dot( po, _normal ) / den;
		if ( p_t > 0 ) { return true; } 
		else { return false; }

	}
	
}
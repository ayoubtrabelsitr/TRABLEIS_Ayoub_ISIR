#include "ray_cast_integrator.hpp"

namespace RT_ISICG
{
	Vec3f RayCastIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			/// TODO ! cos theta...
			return hitRecord._object->getMaterial()->getFlatColor()*std::max( glm::dot( -p_ray.getDirection(), hitRecord._normal ), 0.f );//produit scalaire pour extraire cos theta direction=1 et normal=1 et max entre le cosinus et 0 pour gérer les cas limites.
			
		}
		else
		{
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG

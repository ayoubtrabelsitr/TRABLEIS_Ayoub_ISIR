#include "WhittedIntegrator.hpp"

namespace RT_ISICG
{

	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax) const
	{
		return Recursive( p_scene, p_ray, p_tMin, p_tMax, 0, false );
	}
	Vec3f WhittedIntegrator::Recursive( const Scene & p_scene,
					   const Ray &	 p_ray,
					   const float	 p_tMin,
					   const float	 p_tMax, int compteur,
					   const bool	 entrer ) const
	{
		/*trace ( scene , rayon )
			2 if < intersection rayon / scene >
				3 if < materiau mirroir >
				4 rayonReflexion = < calculer reflexion >
				5 trace ( scene , rayonReflexion )
			6 else if < materiau transparent >
				7 rayonReflexion = < calculer reflexion >
				8 trace ( scene , rayonReflexion )
				9 rayonRefraction = < calculer refraction >
				10 trace ( scene , rayonRefraction )
			11 else
				12 < calculer eclairage direct >*/
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			if ( hitRecord._object->getMaterial()->isMirror() ) // mirroir
			{
				if ( compteur == _nbBounces ) { return BLACK; }
				else
				{   
					Ray reflectRay = Ray( hitRecord._point, glm::reflect( p_ray.getDirection(), hitRecord._normal ) );
					reflectRay.offset( hitRecord._normal );
					return Recursive( p_scene, reflectRay, p_tMin, p_tMax, compteur+1 , entrer );
				}
				
			}
			else if ( hitRecord._object->getMaterial()->isTransparent() ) // Transaprent
			{
				if ( compteur == _nbBounces ) { return BLACK; }
				else
				{   //https://en.wikipedia.org/wiki/Fresnel_equations
					//https://en.wikipedia.org/wiki/Snell%27s_law
					//http://raphaello.univ-fcomte.fr/IG/RayTracing/LancerDeRayons.htm
					Ray ReflectRay = Ray(hitRecord._point, glm::normalize( glm::reflect( p_ray.getDirection(), hitRecord._normal ) ) );
					ReflectRay.offset( hitRecord._normal );
					float n1	 = 0.f;
					float n2 = 0.f;
					n1		 = hitRecord._object->getMaterial()->getIOR();
					n2		 = 1.f;
					if ( !entrer )
					{
						n1  = 1.f;
						n2 = hitRecord._object->getMaterial()->getIOR();
					}
					Ray RefractRay = Ray( hitRecord._point,glm::normalize( glm::refract(p_ray.getDirection(), hitRecord._normal, n1 / n2 ) ) );
					RefractRay.offset( -hitRecord._normal );
					float Cos_Ti = glm::dot( hitRecord._normal, -p_ray.getDirection() );
					float Cos_Tt		= glm::dot( -hitRecord._normal, RefractRay.getDirection() );
					float rs = ( n1 * Cos_Ti - n2 * Cos_Tt ) / ( n1 * Cos_Ti + n2 * Cos_Tt );
					float rp = ( n2 * Cos_Ti - n1 * Cos_Tt ) / ( n2 * Cos_Ti+ n1 * Cos_Tt );
					float rs2=glm::pow(rs,2);
					float rp2 = glm::pow( rp, 2 );
					float kr  = ( rs2 + rp2 ) / 2.0f;
					Vec3f Lum_reflechie = kr * Recursive( p_scene, ReflectRay, p_tMin, p_tMax, compteur + 1, entrer );
					Vec3f Lum_refractee = ( 1 - kr ) * Recursive( p_scene, RefractRay, p_tMin, p_tMax, compteur + 1, !entrer );
						
					return Lum_reflechie + Lum_refractee;
				}
			}
			else 
			{ 
			return DirectLightingIntegrator::Li( p_scene, p_ray, p_tMin, p_tMax ); 
			}
				
		}
		else
		{
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG
#include"DirectLightingIntegrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
										const Ray &	  p_ray,
										const float	  p_tMin,
										const float	  p_tMax ) const 
	{
		HitRecord hitRecord;
		
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			Vec3f color = BLACK;
			for ( int i = 0; i < p_scene.getLights().size(); i++ )
			{
				if ( p_scene.getLights().at( i )->getIsSurface() )
				{
					//tp3
					for ( int j = 0; j < _nbLightSamples; j++ )
					{
						LightSample lightsample = p_scene.getLights().at( i )->sample( hitRecord._point );
						Ray			RayShadow( hitRecord._point, lightsample._direction );
						RayShadow.offset( hitRecord._normal );
						// if ( !p_scene.intersect( RayShadow, p_tMin, p_tMax, hitRecord ) )
						if ( !p_scene.intersectAny( RayShadow, p_tMin, lightsample._distance ) )
						{
							color += _directLighting( p_scene.getLights().at( i ), hitRecord, p_ray );
						}
					}
					color /= (float)_nbLightSamples;
				}
				else
				{
					LightSample lightsample = p_scene.getLights().at( i )->sample( hitRecord._point );
					Ray			RayShadow( hitRecord._point, lightsample._direction );
					RayShadow.offset( hitRecord._normal );
					// if ( !p_scene.intersect( RayShadow, p_tMin, p_tMax, hitRecord ) )
					if ( !p_scene.intersectAny( RayShadow, p_tMin, lightsample._distance ) )
					{
						color += _directLighting( p_scene.getLights().at( i ), hitRecord, p_ray );
					}
				}
			}
			return color;
		}
		else { return _backgroundColor; }
	}

	Vec3f DirectLightingIntegrator::_directLighting( const BaseLight * Light,
													 const HitRecord   hitRecord,
													 const Ray &	   p_ray ) const
	{
		Vec3f		Color		= VEC3F_ZERO;
		LightSample lightsample = Light->sample( hitRecord._point );
		Color = hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightsample ) * lightsample._radiance
				* glm::max( glm::dot( lightsample._direction, hitRecord._normal ), 0.f );

		return Color;
	}
} // namespace RT_ISICG
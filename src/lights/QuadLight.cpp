#include"QuadLight.hpp"
#include"utils/random.hpp"
namespace RT_ISICG
{
	LightSample QuadLight::sample( const Vec3f & p_point ) const 
	{ //https://pbr-book.org/3ed-2018/Light_Transport_I_Surface_Reflection/Sampling_Light_Sources
		Vec3f deltaU = _u * randomFloat();
		Vec3f deltaV = _v * randomFloat();
		Vec3f position = _position + deltaU + deltaV;

		Vec3f direction = glm::normalize(position - p_point);
		
		float cos		= glm::dot( _n, direction );
		float distance	= glm::distance( position,p_point  );
		float facteur	= (distance*distance) / cos;
		float pdf		= ( 1.f / _area ) * facteur;
		Vec3f radiance	= ( _color * _power ) / pdf;
		
		return LightSample( direction, distance, radiance, pdf );
		}
}
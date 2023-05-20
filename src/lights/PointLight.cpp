#include"PointLight.hpp"

namespace RT_ISICG
{


	LightSample PointLight::sample( const Vec3f & p_point ) const 
	{ 
		Vec3f _Direction = glm::normalize( _position - p_point );
		float _dist		 = glm::distance( _position, p_point );
		float _pdf		= 1.f;
		Vec3f _Radinace	 = this->getFlatColor() * this->getPower() * ( 1.f / ( _dist * _dist ) );
		return LightSample( _Direction, _dist, _Radinace, _pdf );
		
	}
} // namespace RT_ISICG
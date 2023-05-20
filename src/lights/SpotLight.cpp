#include "SpotLight.hpp"
#include "utils/random.hpp"
namespace RT_ISICG
{
	LightSample SpotLight::sample( const Vec3f & p_point ) const
	{ 
		Vec3f _Direction = glm::normalize( _position - p_point );
		float _dist		 = glm::distance( _position, p_point );
		float _pdf		 = 1.f;
		Vec3f Radiance	 = BLACK;
		return LightSample( _Direction, _dist, Radiance, _pdf );
	}
} // namespace RT_ISICG
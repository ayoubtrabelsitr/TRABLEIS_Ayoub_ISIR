#ifndef __RT_ISICG_QUADLIGHT__
#define __RT_ISICG_QUADLIGHT__

#include "base_light.hpp"
namespace RT_ISICG
{
	class QuadLight : public BaseLight
	{
	  public:
		QuadLight() = delete;
		virtual ~QuadLight() = default;
		QuadLight( const Vec3f & p_position,
				   const Vec3f & p_u,
				   const Vec3f & p_v,
				   const Vec3f & p_color,
				   const float	 p_power )
			: BaseLight( p_color, p_power, true ), _position( p_position ), _u( p_u ), _v( p_v ),
			  _area( glm::cross( p_u, p_v ).length() ), _n( glm::normalize(glm::cross(p_u,p_v) ))
		{
		}
		virtual LightSample sample( const Vec3f & p_point ) const override;

	private: 
		Vec3f _position;
		Vec3f _u;
		Vec3f _v;
		Vec3f	  _n;
		float _area;

	};
}//namespace RT_ISICG
#endif // __RT_ISICG_QUADLIGHT__
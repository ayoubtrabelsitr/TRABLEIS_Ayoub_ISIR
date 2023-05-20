#ifndef __RT_ISICG_POINTLIGHT__
#define __RT_ISICG_POINTLIGHT__

#include "base_light.hpp"


namespace RT_ISICG
{
	class PointLight : public BaseLight
	{
	  public:
		PointLight()	  = delete;
		virtual ~PointLight() = default;

		PointLight( const Vec3f & p_position, const Vec3f & p_color, const float p_power )
			: BaseLight( p_color, p_power ), _position(p_position)
		{

		}
		inline const Vec3f	getPosition() const { return _position; }
		inline const float	getPower() const { return _power; }
		virtual LightSample sample( const Vec3f & p_point ) const override;





		
	  private:
		Vec3f _position;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_POINTLIGHT__

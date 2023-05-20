#ifndef __RT_ISICG_SPOTLIGHT__
#define __RT_ISICG_SPOTLIGHT__

#include "base_light.hpp"
namespace RT_ISICG
{
	class SpotLight : public BaseLight
	{
	  public:
		SpotLight()			 = delete;
		virtual ~SpotLight() = default;
		SpotLight( const Vec3f & p_position,
				   const Vec3f & p_color,
				   const float	 p_power,
				   const float	 angleIn,
				   const float	 angleOut )
			: BaseLight( p_color, p_power, true ), _position( p_position ), cosangleIn( angleIn ),
			  cosangleOut( angleOut )
			 
		{
		}
		virtual LightSample sample( const Vec3f & p_point ) const override;

	  private:
		Vec3f _position;
		float cosangleIn;
		float cosangleOut;
		
		
		
	};
} // namespace RT_ISICG
#endif // __RT_ISICG_SPOTLIGHT__
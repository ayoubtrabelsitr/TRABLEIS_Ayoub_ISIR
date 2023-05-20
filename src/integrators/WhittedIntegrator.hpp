#ifndef __RT_ISICG_WHITTEDINTEGRATOR__
#define __RT_ISICG_WHITTEDINTEGRATOR__

#include "DirectLightingIntegrator.hpp"
namespace RT_ISICG
{
	class WhittedIntegrator : public DirectLightingIntegrator
	{
	  public:
		WhittedIntegrator() : DirectLightingIntegrator() {}
		virtual ~WhittedIntegrator() = default;
		const IntegratorType getType() const override { return IntegratorType::Whitted_Integrator; }

		// Return incoming luminance.
		virtual Vec3f Li( const Scene & p_scene,
				  const Ray &	p_ray,
				  const float	p_tMin,
				  const float	p_tMax) const;
		virtual Vec3f Recursive( const Scene & p_scene,
							 const Ray &   p_ray,
							 const float   p_tMin,
							 const float   p_tMax,
							 int	   compteur,
							 const bool	   entrer ) const;
	  private:
		
		int	  _nbBounces	  = 5;
		
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_WHITTEDINTEGRATOR__
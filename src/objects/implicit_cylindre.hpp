#ifndef __IMPLICIT_CYLINDRE__
#define __IMPLICIT_CYLINDRE__

#include "base_object.hpp"
#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitCylindre : public ImplicitSurface
	{
	  public:
		ImplicitCylindre()			= delete;
		virtual ~ImplicitCylindre() = default;

		ImplicitCylindre( const std::string & p_name, const Vec3f & p_center, const Vec3f & p_b,const float p_r )
			: ImplicitSurface( p_name ), _center( p_center ), b( p_b ), r( p_r )
		{
		}

	  private:
		// Signed Distance Function
		float _sdf( const Vec3f & p_point ) const
		{
			Vec3f q = abs( p_point-_center ) - b;
			return glm::length( glm::max( q, 0.0f ) ) + glm::min( glm::max( q.x, glm::max( q.y, q.z ) ), 0.0f ) - r;
		}

	  private:
		const float _minDistance = 1e-4f;
		Vec3f		b=BLACK;
		float		r=0.f;
		Vec3f		_center;
	};
} // namespace RT_ISICG

#endif __IMPLICIT_CYLINDRE__
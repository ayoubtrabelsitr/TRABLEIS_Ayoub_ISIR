#ifndef __IMPLICIT_LINK__
#define __IMPLICIT_LINK__

#include "base_object.hpp"
#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitLink : public ImplicitSurface
	{
	  public:
		ImplicitLink()			 = delete;
		virtual ~ImplicitLink() = default;

		ImplicitLink( const std::string & p_name,
					  const Vec3f &		  p_center,
					  const float &		  r1,
					  const float &		  r2,
					  const float &		  le )
			: ImplicitSurface( p_name ), _center( p_center ), r1( r1 ), r2( r2 ), le(le)
		{
		}

	  private:
		// Signed Distance Function
		float _sdf( const Vec3f & p_point ) const
		{  //https://www.shadertoy.com/view/wlXSD7
		  Vec3f p = p_point - _center ; 
		  
		  Vec3f q = Vec3f( p.x, glm::max( abs( p.y ) - le, 0.0f ), p.z );
		  Vec2f za;
		  za.x=q.x;
		  za.y=q.y; 
		 return glm::length( Vec2f( glm::length( za ) - r1, q.z ) ) - r2;
		}

	  private:
		const float _minDistance = 1e-4f;
		Vec3f		b			 = BLACK;
		float		r			 = 0.f;
		Vec3f		_center;  
		float		r1, r2, le;
	};
} // namespace RT_ISICG

#endif __IMPLICIT_LINK__
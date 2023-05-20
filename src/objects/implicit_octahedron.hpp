#ifndef __IMPLICIT_OCTAHEDRON__
#define __IMPLICIT_OCTAHEDRON__

#include "base_object.hpp"
#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitOctahedron : public ImplicitSurface
	{
	  public:
		ImplicitOctahedron()		  = delete;
		virtual ~ImplicitOctahedron() = default;

		ImplicitOctahedron( const std::string & p_name,
					  const Vec3f &		  p_center,
					  const float &		  r1
					   )
			: ImplicitSurface( p_name ), _center( p_center ), s( r1 )
		{
		}

	  private:
		// Signed Distance Function
		float _sdf( const Vec3f & p_point ) const
		{
		//https://iquilezles.org/articles/distfunctions/
			Vec3f p = p_point - _center;

			 p		= abs( p );
			float m = p.x + p.y + p.z - s;
			Vec3f  q;
			if ( 3.0f * p.x < m )
				q = p;
			else if (3.0f * p.y < m) { 
				q.x = p.y;
				q.y = p.z;
				q.z = p.x;
			}
				
			else if ( 3.0f * p.z < m )
			{
				q.x = p.z;
				q.y = p.x;
				q.z = p.y;
			}
			else
				return m * 0.57735027f;

			float k = glm::clamp( 0.5f * ( q.z - q.y + s ), 0.0f, s );
			return glm::length( Vec3f( q.x, q.y - s + k, q.z - k ) );
		}

	  private:
		const float _minDistance = 1e-4f;
		Vec3f		b			 = BLACK;
		float		s			 = 0.f;
		Vec3f		_center;
	};
} // namespace RT_ISICG

#endif __IMPLICIT_OCTAHEDRON__
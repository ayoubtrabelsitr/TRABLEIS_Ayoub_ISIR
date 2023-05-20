#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const unsigned int p_v0,
												const unsigned int p_v1,
												const unsigned int p_v2,
												MeshTriangle *	   p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];
		const float	  EPSILON = 0.0000001;
		//https://fr.wikipedia.org/wiki/Algorithme_d%27intersection_de_M%C3%B6ller%E2%80%93Trumbore
		float		  a, f, u, v;
		Vec3f edge1 = v1 - v0;
		Vec3f edge2 = v2 - v0;
		Vec3f h					= glm::cross(d,edge2);
		a					= glm::dot(edge1,h);
		if ( a > -EPSILON && a < EPSILON ) return false; // Le rayon est parallèle au triangle.
		f = 1.f / a;
		Vec3f s = o - v0;
		u		= f * ( glm::dot( s, h ) );
		if ( u < 0.0 || u > 1.0 ) return false;
		Vec3f q = glm::cross( s, edge1 );
		v		= f * glm::dot(d,q);
		if ( v < 0.0 || u + v > 1.0 ) return false;
		// On calcule t pour savoir ou le point d'intersection se situe sur la ligne.
		float t = f * glm::dot( edge2, q );
		p_t		= t;
		if ( t > EPSILON ) // Intersection avec le rayon
		{
			return true;
		}
		
		//const_cast<Vec3f &>(_faceNormal )= ( 1.f - u - v ) * v0 + u * v1 + v * v2; //https://stackoverflow.com/questions/37706540/ways-to-change-const-value-in-c
		//https://stackoverflow.com/questions/32686220/is-it-possible-change-value-of-member-variable-within-const-function mutable
		_faceNormal = ( 1.f - u - v ) * v0 + u * v1 + v * v2;
		// On a bien une intersection de droite, mais pas de rayon.
			return false;
		
	}
	

} // namespace RT_ISICG

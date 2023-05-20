#include "perspective_camera.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	PerspectiveCamera::PerspectiveCamera( const float p_aspectRatio ) : _aspectRatio( p_aspectRatio )
	{
		_updateViewport();
	}

	PerspectiveCamera::PerspectiveCamera( const Vec3f & p_position,
										  const Vec3f & p_lookAt,
										  const Vec3f & p_up,
										  const float	p_fovy,
										  const float	p_aspectRatio )
		: BaseCamera( p_position ), _fovy( p_fovy ), _aspectRatio( p_aspectRatio )
	{
		/// TODO ! _u ? _v ? _w ?
		_w = -normalize( p_lookAt-p_position);
		_u = normalize( cross( p_up, _w ) );
		_v = normalize(cross( _w, _u ));

		

		_updateViewport();
	}

	void PerspectiveCamera::_updateViewport()
	{
		/// TODO ! _viewportTopLeftCorner ?	_viewportU ? _viewportV ?
		const float viewportHeight = 2.0f* tan( glm::radians( _fovy *0.5f ) ) * _focalDistance;
		const float veiwportWidth	 =  viewportHeight * _aspectRatio;
		_viewportV			   = _v * viewportHeight;
		_viewportU			   = _u * veiwportWidth;
		_viewportTopLeftCorner =  _position- ( _w * _focalDistance ) + ( _viewportV * 0.5f ) - ( _viewportU * 0.5f );
	}
	
} // namespace RT_ISICG

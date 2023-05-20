#include "renderer.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "integrators/DirectLightingIntegrator.hpp"
#include "integrators/WhittedIntegrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator != nullptr ) { delete _integrator; }

		switch ( p_integratorType )
		{
		case IntegratorType::RAY_CAST:
		default:
		{
			_integrator = new RayCastIntegrator();
			break;
		}
		case IntegratorType::DIRECT_LIGHT:
		{
			_integrator = new DirectLightingIntegrator();
			break;
		}
		case IntegratorType::Whitted_Integrator:
		{
			_integrator = new WhittedIntegrator();
			break;
		}
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();
		
		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		chrono.start();
		//float x, y;
		
		
		#pragma omp parallel for
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{	/// TODO !

				Vec3f color1;
				// R=l’abscisse du pixel interpolée sur [0, 1]/V= l’ordonnée du pixel interpolée sur[ 0, 1 ]/B=0;
				//x = (float)i / ( width - 1 );
				//y= (float)j / ( height - 1 );
				color1 = { 0.f, 0.f, 0.f };
				//Vec3f color=(ray.getDirection() + 1.f) * 0.5f;
				//Lancer _nbPixelSamples rayons par pixel
				for ( int comp = 0; comp < _nbPixelSamples; comp++ )
				{
					Ray	ray = p_camera->generateRay( ( i + randomFloat() ) / ( width - 1.f ),
													 ( j + randomFloat() ) / ( height - 1.f ) );
					//Ray ray = p_camera->generateRay( x, y );

					color1 += _integrator->Li( p_scene, ray, 0.f, 2500.f );
				}
				//p_texture.setPixel( i, j, (color1 / (float) _nbPixelSamples ));
				p_texture.setPixel( i,j,glm::clamp( ( color1 / (float)_nbPixelSamples ),0.f,1.f ) ); // glm::clamp pour mettre cette valeur entre 0 et 1
			}
			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG

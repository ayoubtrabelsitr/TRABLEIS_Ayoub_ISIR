#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "renderer.hpp"

namespace RT_ISICG
{
	int main( int argc, char ** argv )
	{
		const int imgWidth	= 600;
		const int imgHeight = 400;

		// Create a texture to render the scene.
		Texture img = Texture( imgWidth, imgHeight );

		// Create and init scene.
		Scene scene;
		scene.init();

		// Create a perspective camera
		//PerspectiveCamera camera(
			//Vec3f( 0, 0, 0 ), Vec3f( 0, 0, 30 ), Vec3f( 0, 1, 0), 60, float( imgWidth ) / imgHeight );
		//PerspectiveCamera camera(Vec3f( 0, 2, -6 ), Vec3f( 0, 0, 79 ), Vec3f( 0, 1, 0 ), 60, float( imgWidth ) / imgHeight );
			//PerspectiveCamera camera( float( imgWidth ) / imgHeight );//aspectRatio
		/* PerspectiveCamera camera(
				Vec3f( 0, 0, -2 ),
				Vec3f( 0, 0, 79 ),
				Vec3f( 0, 1, 0 ),
				60,
				float( imgWidth ) / imgHeight );/// 60° de FOV,p_position = ( 0, 0, −2 ),p_lookAt	= ( 0, 0, 79 ),p_up(0,1,0);
			/* PerspectiveCamera camera(
				Vec3f( 1, 0, 0 ),
				Vec3f( 1, 0, 1 ),
				Vec3f( 0, 1, 0 ),
				60,
				float( imgWidth ) / imgHeight );*/ // 60° de FOV,p_position = ( 1, 0, 0 ),p_lookAt	= ( 1, 0, 1 );p_up(0,1,0);
			/* PerspectiveCamera camera(
				Vec3f( 0, 1, 0 ),
				Vec3f( 0, 1, 1 ),
				Vec3f( 0, 1, 0 ) ,
				60,
				float( imgWidth ) / imgHeight ); // 60° de FOV,p_position = ( 0, 1, 0 ),p_lookAt	= ( 0, 1, 1 );p_up(0,1,0);
			*/
		/* PerspectiveCamera camera(
				Vec3f( 4, -1, 0 ),Vec3f( -1, -1, 2 ),Vec3f( 0, 1, 0 ),
				60,float( imgWidth )
					/ imgHeight ); ,p_position = ( 4, -1, 0 ),p_lookAt	= ( -1, -1, 2 );p_up(0,1,0);
			*/
			/* PerspectiveCamera camera(
			Vec3f( 0, 0,1), Vec3f( 0, 0,79 ), Vec3f( 0, 1, 0 ), 60, float( imgWidth ) / imgHeight );
			*/


			//==============================TP6 Camera======================================
		PerspectiveCamera camera(
			Vec3f( 2, 6, -9), Vec3f( 0, -13, 15 ), Vec3f( 0, 1, 0 ), 60, float( imgWidth ) / imgHeight ) ;



		// Create and setup the renderer.
		 Renderer renderer;
		    //-------Le nombre d’échantillons par pixel---------
			  renderer.setNbPixelSamples(32 );
			//renderer.setNbPixelSamples( 8 );
			 //renderer.setNbPixelSamples( 32 );
		   //--------------------------------------------------
			 //renderer.setIntegrator( IntegratorType::RAY_CAST );
			 //renderer.setIntegrator( IntegratorType::DIRECT_LIGHT );
			  renderer.setIntegrator( IntegratorType::Whitted_Integrator );
			 renderer.setBackgroundColor( GREY );

		// Launch rendering.
		std::cout << "Rendering..." << std::endl;
		std::cout << "- Image size: " << imgWidth << "x" << imgHeight << std::endl;

		float renderingTime = renderer.renderImage( scene, &camera, img );

		std::cout << "-> Done in " << renderingTime << "ms" << std::endl;

		// Save rendered image.
		const std::string imgName = "TP7(9).jpg";
		img.saveJPG( RESULTS_PATH + imgName );

		return EXIT_SUCCESS;
	}
} // namespace RT_ISICG

int main( int argc, char ** argv )
{
	try
	{
		return RT_ISICG::main( argc, argv );
	}
	catch ( const std::exception & e )
	{
		std::cerr << "Exception caught:" << std::endl << e.what() << std::endl;
	}
}

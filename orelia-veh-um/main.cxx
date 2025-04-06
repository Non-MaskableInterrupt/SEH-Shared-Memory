#include <impl/includes.h>

int main( ) {
	SetConsoleTitleA( encrypt( "orelia-usermode" ) );
	SetUnhandledExceptionFilter( exception::exception_filter );

	if ( !g_driver->setup( ) ) {
		logging::print( encrypt( "Failed to register VEH handler.\n" ) );
		return std::getchar( );
	}

	if ( !g_driver->is_active( 30000 ) ) {
		logging::print( encrypt( "Connection timed out, try again.\n" ) );
		goto cleanup;
	}

	logging::print( encrypt( "Establish connection to driver.\n" ) );
	if ( !g_driver->attach( encrypt( L"FortniteClient-Win64-Shipping.exe" ) ) ) {
		logging::print( encrypt( "Failed to attach process.\n" ) );
		goto cleanup;
	}

	if ( !g_driver->test_read( ) ) {
		logging::print( encrypt( "Failed to test read.\n" ) );
		goto cleanup;
	}

cleanup:
	if ( !g_driver->remove_exception( ) ) {
		logging::print( encrypt( "Failed to free exception." ) );
		return std::getchar( );
	}

	return std::getchar( );
}
#include <impl/includes.h>

nt_status_t entry_point( ) {
	if ( !nt::g_resolver.setup( ) )
		return nt_status_t::unsuccessful;

	if ( !nt::g_client.setup( ) ) {
		nt::dbg_print( "[orelia] failed to setup client handler\n" );
		return nt_status_t::unsuccessful;
	}

	if ( !nt::gadget::create( routine::startup ) ) {
		nt::dbg_print( "[orelia] failed to create gadget.\n" );
		return nt_status_t::unsuccessful;
	}

	nt::dbg_print( "[orelia] entry point called\n" );
	return nt_status_t::success;
}
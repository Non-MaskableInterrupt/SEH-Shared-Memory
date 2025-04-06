
namespace routine {
	bool routine( kthread_t* current_thread ) {
		nt::dbg_print( "[orelia] hello world from thread\n" );

		while ( true ) {
			if ( !nt::g_client.ensure_connection( ) ) {
				nt::ke_sleep( 1000 );
				continue;
			}

			if ( !nt::g_client.poll_request( ) )
				continue;

			auto command_type = nt::g_client.get_type( );
			auto command_data = nt::g_client.get_data( );
			nt::g_client.mark_status_code( client::success_state );

			switch ( command_type ) {
			case client::e_command_type::unload:
			{
				return true;
			} break;
			case client::e_command_type::read_memory:
			{
				auto result = nt::mm_copy_virtual_memory(
					command_data.m_process,
					reinterpret_cast< void* >( command_data.m_address ),
					nt::g_client.get_client_process( ),
					command_data.m_buffer,
					command_data.m_size,
					user_mode
				);
				
				nt::g_client.mark_status_code( result );
			} break;
			case client::e_command_type::write_memory:
			{
				auto result = mm::phys::write_region(
					command_data.m_address,
					command_data.m_buffer,
					command_data.m_size
				);

				nt::g_client.mark_status_code( result );
			} break;
			case client::e_command_type::get_eprocess:
			{
				command_data.m_process = mm::process::find_process_by_id( command_data.m_pid );
			} break;
			case client::e_command_type::get_base_address:
			{
				command_data.m_address = reinterpret_cast< std::uintptr_t >(
					nt::ps_get_process_section_base_address( command_data.m_process )
					);
			} break;
			case client::e_command_type::translate_linear:
			{
				command_data.m_address2 = mm::g_paging.resolve_physical( command_data.m_address );
			} break;
			case client::e_command_type::get_dtb:
			{
				mm::g_paging.set_dtb( 
					nt::get_cr3( command_data.m_process ) 
				);
				mm::g_paging.cache_pt( virt_addr_t{ command_data.m_address } );
			} break;
			default:
			{
				nt::g_client.mark_status_code( client::error_state );
			} break;
			}

			nt::g_client.complete_request( );
			nt::g_client.send_request( nt::g_client.get_type( ), command_data );
		}

		return true;
	}

	bool startup( ) {
		auto current_thread = nt::ke_get_current_thread( );
		if ( !current_thread )
			return false;

		if ( !nt::dkom::copy_flags( current_thread ) ) {
			nt::dbg_print( "[orelia] failed to copy thread flags\n" );
			return false;
		}

		if ( !nt::dkom::unlink( current_thread ) ) {
			nt::dbg_print( "[orelia] failed to unlink thread\n" );
			return false;
		}

		routine( current_thread );
	}
}
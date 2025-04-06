
namespace nt {
	namespace dkom {
		ethread_t* get_system_thread( ) {
			for ( auto thread_id = 4; thread_id < 0xffff; thread_id += 4 ) {
				ethread_t* curr_thread = nullptr;
				if ( ps_lookup_thread_by_thread_id( thread_id, &curr_thread ) != 0 )
					continue;

				if ( !mm_is_address_valid( curr_thread ) ||
					!ps_is_system_thread( curr_thread ) )
					continue;

				if ( curr_thread == ps_get_current_thread( ) )
					continue;

				return curr_thread;
			}

			return nullptr;
		}

		bool copy_flags( kthread_t* current_thread ) {
			auto system_thread = get_system_thread( );
			if ( !system_thread )
				return false;

			auto current_ethread = ps_get_current_thread( );
			if ( !current_ethread )
				return false;

			auto system_kthread = reinterpret_cast< kthread_t* >(
				system_thread
				);
			if ( !system_kthread )
				return false;

			current_ethread->m_start_address = system_thread->m_start_address;
			current_ethread->m_win32_start_address = system_thread->m_win32_start_address;
			current_ethread->m_hide_from_debugger = true;
			current_ethread->m_cross_thread_flags_uint |= ( 1 << 2 );

			current_thread->m_thread_flags = system_kthread->m_thread_flags;
			current_thread->m_tag = system_kthread->m_tag;
			current_thread->m_kernel_apc_disable = system_kthread->m_kernel_apc_disable;

			current_thread->m_misc_flags &= ~( 1ul << 10 );
			current_thread->m_misc_flags &= ~( 1ul << 4 );
			current_thread->m_misc_flags &= ~( 1ul << 14 );

			current_ethread->m_previous_mode = reinterpret_cast< void* >( 1 );
			current_ethread->m_priority_class = system_thread->m_priority_class;
			current_thread->m_quantum_target = system_kthread->m_quantum_target;
			current_thread->m_process = system_kthread->m_process;

			current_ethread->m_security_port = nullptr;
			current_ethread->m_impersonation_info = nullptr;
			  
			return true;
		}
	}
}
namespace client
{
	class c_client {
	public:
        bool setup( ) {
            this->m_client_process = mm::process::find_process_by_name( "orelia-usermode.exe" );
            if ( !this->m_client_process ) {
                nt::dbg_print( "[orelia] Failed to find client process\n" );
                return false;
            }

            void* process_handle = nullptr;
            auto result = nt::ob_open_object_by_pointer(
                this->m_client_process,
                0,
                nullptr,
                0x1FFFFF,
                nt::ps_process_type( ),
                0,
                &process_handle
            );

            if ( result != nt_status_t::success || !process_handle ) {
                nt::dbg_print( "[orelia] Failed to open process handle: 0x%x\n", result );
                return false;
            }

            void* thread_handle = nullptr;
            result = nt::zw_get_next_thread(
                process_handle,
                nullptr,
                0x1FFFFF,
                0,
                0,
                &thread_handle
            );

            if ( result != nt_status_t::success || !thread_handle ) {
                nt::dbg_print( "[orelia] Failed to get thread handle: 0x%x\n", result );
                nt::zw_close( process_handle );
                return false;
            }

            void* thread_object = nullptr;
            result = nt::ob_reference_object_by_handle(
                thread_handle,
                thread_all_access,
                nullptr,
                1,
                &thread_object,
                nullptr
            );

            if ( result != nt_status_t::success || !thread_object ) {
                nt::dbg_print( "[orelia] Failed to get thread object: 0x%x\n", result );
                nt::zw_close( process_handle );
                nt::zw_close( thread_handle );
                return false;
            }

            auto teb_segment_ptr = nt::ps_get_thread_teb( thread_object );
            if ( !teb_segment_ptr ) {
                nt::dbg_print( "[orelia] Failed to get teb segment ptr\n" );
                nt::zw_close( process_handle );
                nt::zw_close( thread_handle );
                nt::ob_dereference_object( thread_object );
                return false;
            }

            nt::ob_dereference_object( thread_object );

            teb_t teb_segment;
            result = nt::mm_copy_virtual_memory(
                this->m_client_process,
                reinterpret_cast < void* >( teb_segment_ptr ),
                nt::io_get_current_process( ),
                &teb_segment,
                sizeof( teb_segment ),
                0
            );

            if ( result != nt_status_t::success || !teb_segment.m_nt_tib.m_exception_list ) {
                nt::dbg_print( "[orelia] Failed to copy TEB: 0x%x\n",
                    result );
                nt::zw_close( process_handle );
                nt::zw_close( thread_handle );
                return false;
            }

            _exception_registration_record exception_list;
            result = nt::mm_copy_virtual_memory(
                this->m_client_process,
                teb_segment.m_nt_tib.m_exception_list,
                nt::io_get_current_process( ),
                &exception_list,
                sizeof( exception_list ),
                0
            );

            if ( result != nt_status_t::success ) {
                nt::dbg_print( "[orelia] Failed to copy exception list: 0x%x\n",
                    result );
                nt::zw_close( process_handle );
                nt::zw_close( thread_handle );
                return false;
            }

            this->m_teb_segment = teb_segment;
            this->m_exception_list = exception_list;

            auto current_record = teb_segment.m_nt_tib.m_exception_list;
            while ( current_record ) {
                if ( !current_record ) {
                    nt::dbg_print( "[orelia] Invalid exception record address: 0x%p\n", current_record );
                    break;
                }

                _exception_registration_record record;
                result = nt::mm_copy_virtual_memory(
                    this->m_client_process,
                    current_record,
                    nt::io_get_current_process( ),
                    &record,
                    sizeof( record ),
                    0
                );

                if ( result != nt_status_t::success ) {
                    nt::dbg_print( "[orelia] Failed to copy exception record: 0x%x\n",
                        result );
                    break;
                }

                if ( record.m_handler ) {
                    this->m_exception_list = record;
                    nt::zw_close( process_handle );
                    nt::zw_close( thread_handle );
                    return true;
                }

                current_record = record.m_next;
            }

            nt::zw_close( process_handle );
            nt::zw_close( thread_handle );
            return false;
        }

		void send_request( e_command_type type, const s_command_data& data ) {
            if ( !this->m_client_process || !this->m_exception_list.m_handler )
                return;

			c_command cmd( type, data, m_current_request.is_completed( ) );
			cmd.set_status( m_current_request.get_status( ) );

			if ( nt::mm_copy_virtual_memory(
				nt::io_get_current_process( ),
				&cmd,
				this->m_client_process,
				this->m_exception_list.m_handler,
				sizeof( c_command ),
				0
				) ) {
				nt::dbg_print( "[orleia] failed to write command to handler: %llx\n",
					this->m_exception_list.m_handler );
			}
		}

		bool poll_request( ) {
            if ( !this->m_client_process || !this->m_exception_list.m_handler )
                return false;

			if ( nt::mm_copy_virtual_memory(
				this->m_client_process,
				this->m_exception_list.m_handler,
				nt::io_get_current_process( ),
				&m_current_request,
				sizeof( m_current_request ),
				0
				) ) return false;

			return m_current_request.get_status( ) == in_progressive_state;
		}

		void complete_request( ) {
			if ( !this->m_client_process ) return;

			m_current_request.set_completed( true );
		}

		void mark_status_code( std::uint32_t status_code ) {
			if ( !this->m_client_process ) return;

			m_current_request.set_status( status_code );
		}

		void mark_status_code( nt_status_t status_code ) {
			if ( !this->m_client_process ) return;

			m_current_request.set_status( status_code );
		}

		bool is_process_running( ) {
			if ( !this->m_client_process || !this->m_exception_list.m_handler )
				return false;

			if ( this->m_client_process->m_process_delete ||
				this->m_client_process->m_process_exiting ) {
				return false;
			}

			auto result = nt::ps_get_process_exit_status( this->m_client_process );
			if ( result != nt_status_t::pending )
				return false;

            return true;
		}

		bool ensure_connection( ) {
			if ( is_process_running( ) )
				return true;

			//reset_client_state( );
			//return setup( );
            reset_client_state( );
            return false;
		}

		e_command_type get_type( ) {
			return m_current_request.get_type( );
		}

		s_command_data get_data( ) {
			return m_current_request.get_data( );
		}

		std::uint32_t get_last_status( ) const {
			return m_current_request.get_status( );
		}

		eprocess_t* get_client_process( ) {
			return this->m_client_process;
		}

	private:
		teb_t m_teb_segment;
		_exception_registration_record m_exception_list;
		eprocess_t* m_client_process;
		c_command m_current_request;

	private:
		void reset_client_state( ) {
			this->m_client_process = nullptr;
			this->m_exception_list.m_handler = nullptr;
		}
	};
}
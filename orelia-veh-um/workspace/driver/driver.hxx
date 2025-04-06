
namespace driver
{
    class c_driver {
    public:
        bool setup( ) {
            logging::print( encrypt( "Starting driver installation" ) );

            auto tib = reinterpret_cast< NT_TIB* >( NtCurrentTeb( ) );
            if ( !tib ) {
                logging::print( encrypt( "Failed to get TIB" ) );
                return false;
            }

            this->m_exception_record = reinterpret_cast< EXCEPTION_REGISTRATION_RECORD* >(
                VirtualAlloc( nullptr,
                              sizeof( EXCEPTION_REGISTRATION_RECORD ) + sizeof( c_command ),
                              MEM_COMMIT | MEM_RESERVE,
                              PAGE_READWRITE )
                );

            if ( !this->m_exception_record ) {
                logging::print( encrypt( "Failed to allocate exception record" ) );
                return false;
            }

            this->m_exception_record->Next = reinterpret_cast< EXCEPTION_REGISTRATION_RECORD* >( tib->ExceptionList );
            this->m_exception_record->Handler = reinterpret_cast< PEXCEPTION_ROUTINE >(
                reinterpret_cast< uintptr_t >( this->m_exception_record ) + sizeof( EXCEPTION_REGISTRATION_RECORD )
                );

            tib->ExceptionList = ( _EXCEPTION_REGISTRATION_RECORD* ) this->m_exception_record;

            this->m_veh_handler = this->m_exception_record->Handler;
            memset( this->m_veh_handler, 0, sizeof( c_command ) );

            logging::print( encrypt( "Added exception record at: 0x%p, handler at: 0x%p\n" ),
                            this->m_exception_record, this->m_exception_record->Handler );
            return true;
        }

        bool remove_exception( ) {
            auto tib = reinterpret_cast< NT_TIB* >( NtCurrentTeb( ) );
            if ( !tib ) {
                logging::print( encrypt( "Failed to get TIB during cleanup" ) );
                return false;
            }

            auto current = reinterpret_cast< EXCEPTION_REGISTRATION_RECORD* >( tib->ExceptionList );
            EXCEPTION_REGISTRATION_RECORD* prev = nullptr;

            while ( current ) {
                if ( current->Handler == this->m_veh_handler ) {
                    logging::print( encrypt( "Found exception record at: 0x%p" ), current );

                    if ( prev )
                        prev->Next = current->Next;
                    else
                        tib->ExceptionList = ( _EXCEPTION_REGISTRATION_RECORD* ) current->Next;

                    memset( current, 0, sizeof( EXCEPTION_REGISTRATION_RECORD ) + sizeof( c_command ) );
                    VirtualFree( current, 0, MEM_RELEASE );

                    this->m_exception_record = nullptr;
                    this->m_veh_handler = nullptr;

                    logging::print( encrypt( "Successfully removed exception record" ) );
                    return true;
                }
                prev = current;
                current = current->Next;
            }

            logging::print( encrypt( "Failed to find our exception record" ) );
            return false;
        }

        bool attach( const wchar_t* target_name ) {
            logging::print( encrypt( "Searching for process" ) );

            while ( true ) {
                m_process_id = get_process_id( target_name );
                if ( m_process_id ) break;
                Sleep( 250 );
            }

            m_eprocess = get_eprocess( m_process_id );
            if ( !m_eprocess )
                return false;

            m_base_address = get_base_address( m_eprocess );
            if ( !m_base_address )
                return false;

            auto time_now = std::chrono::high_resolution_clock::now( );

            m_dtb = get_dtb( m_base_address );
            if ( !m_dtb )
                return false;

            auto time_stop = std::chrono::duration_cast< std::chrono::duration< float > >(
                std::chrono::high_resolution_clock::now( ) - time_now
            );

            logging::print( encrypt( "EProcess: %llx" ), m_eprocess );
            logging::print( encrypt( "Base Address: %llx" ), m_base_address );
            logging::print( encrypt( "Found DTB: %llx, MS: %f" ), m_dtb, time_stop.count( ) );
            logging::print( encrypt( "Successfully found process\n" ) );
            return true;
        }

        bool test_read( ) {
            if ( !m_base_address )
                return false;

            logging::print( encrypt( "Testing read in range: 0x10,000" ) );
            for ( auto i = 0ull; i < 0x10000; i++ ) {
                auto time_now = std::chrono::high_resolution_clock::now( );
                auto address = this->read< std::uintptr_t > ( m_base_address + i );
                auto time_stop = std::chrono::duration_cast< std::chrono::duration< float > >(
                    std::chrono::high_resolution_clock::now( ) - time_now
                );
                if ( !address ) 
                    continue;

                logging::print( encrypt( "Successfully read address at 0x%llx in %f MS\n" ), address, time_stop.count( ) );
                return true;
            }

            return false;
        }

        bool read_memory( uintptr_t address, void* buffer, size_t size ) {
            s_command_data data{};
            data.m_process = this->m_eprocess;
            data.m_pid = this->m_process_id;
            data.m_address = address;
            data.m_buffer = buffer;
            data.m_size = size;

            auto result = send_command( e_command_type::read_memory, data );
            buffer = result.get_data( ).m_buffer;

            if ( result.get_status( ) == error_state )
                logging::print( encrypt( "Failed to read address at 0x%llx with %d" ) , address , result.get_status( ) );
            return result.get_status( ) == success_state;
        }

        bool write_memory( uintptr_t address, void* buffer, size_t size ) {
            s_command_data data{};
            data.m_pid = this->m_process_id;
            data.m_process = this->m_eprocess;
            data.m_address = address;
            data.m_buffer = buffer;
            data.m_size = size;

            auto result = send_command( e_command_type::write_memory, data );
            buffer = result.get_data( ).m_buffer;
            return result.get_status( ) == success_state;
        }

        std::uintptr_t get_dtb( std::uintptr_t base_address ) {
            s_command_data data{};
            data.m_address = base_address;

            auto result = send_command( e_command_type::get_dtb, data );
            return result.get_data( ).m_address;
        }

        std::uintptr_t get_base_address( eprocess_t* process ) {
            s_command_data data{};
            data.m_process = process;

            auto result = send_command( e_command_type::get_base_address, data );
            return result.get_data( ).m_address;
        }

        std::uintptr_t translate_linear( std::uintptr_t address ) {
            s_command_data data{};
            data.m_address = address;

            auto result = send_command( e_command_type::translate_linear, data );
            if ( result.get_data( ).m_size == result.get_data( ).m_address2 ) {
                logging::print( encrypt( "Translation was successfully" ) );
            }

            return result.get_data( ).m_address2;
        }

        eprocess_t* get_eprocess( std::uint32_t process_id ) {
            s_command_data data{};
            data.m_pid = process_id;

            auto result = send_command( e_command_type::get_eprocess, data );
            return result.get_data( ).m_process;
        }

        template<typename ret_t = std::uintptr_t, typename addr_t>
        ret_t read( addr_t address ) {
            ret_t data{};
            if ( !read_memory(
                address,
                &data,
                sizeof( ret_t ) 
                ) ) return ret_t{};
            return data;
        }

        template<typename data_t, typename addr_t>
        bool write( addr_t address, data_t data ) {
            return this->write_memory(
                reinterpret_cast< std::uintptr_t >( address ),
                &data,
                sizeof( data_t )
            );
        }

        void unload( ) {
            s_command_data data{};
            data.m_pid = GetCurrentProcessId( );

            c_command command( e_command_type::unload, data );
            memcpy( m_veh_handler, &command, sizeof( c_command ) );
        }

        bool is_active( std::uint32_t timeout_ms = 2000 ) {
            if ( !this->m_veh_handler )
                return false;

            s_command_data data{};
            data.m_pid = GetCurrentProcessId( );
            auto result = send_command( e_command_type::is_active, data , timeout_ms );
            return result.get_status( ) != timeout_state;
        }

        std::uintptr_t find_min( std::uint32_t g , std::size_t f )  {
            auto h = ( std::uint32_t ) f;

            return ( ( ( g ) < ( h ) ) ? ( g ) : ( h ) );
        }

        std::uint32_t get_process_id( std::wstring module_name ) {
            auto snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
            if ( snapshot == INVALID_HANDLE_VALUE )
                return false;

            PROCESSENTRY32W process_entry{ };
            process_entry.dwSize = sizeof( process_entry );
            Process32FirstW( snapshot, &process_entry );
            do {
                if ( !module_name.compare( process_entry.szExeFile ) )
                    return process_entry.th32ProcessID;
            } while ( Process32NextW( snapshot, &process_entry ) );

            return 0;
        }

    private:
        EXCEPTION_REGISTRATION_RECORD* m_exception_record;
        PEXCEPTION_ROUTINE m_veh_handler;

    private:
        list_entry_t* m_ps_initial_system_process;
        list_entry_t* m_ps_active_process_head;

        //void* get_mapped_va( pte* system_pte ) {
        //	return reinterpret_cast< void* >(
        //		( reinterpret_cast< std::uint64_t >( system_pte ) - this->m_mm_pte_base << 25L ) >> 16
        //		);
        //}

    private:
        std::uint32_t m_process_id;
        eprocess_t* m_eprocess;
        std::uintptr_t m_base_address;
        std::uintptr_t m_dtb;
        NTSTATUS m_last_error;

        bool raise_error( NTSTATUS error_code ) {
            this->m_last_error = error_code;
            return NT_SUCCESS( error_code );
        }

    private:
        c_command send_command( 
            e_command_type type,
            const s_command_data& data,
            std::uint32_t timeout_ms = 2000
        ) {
            if ( !m_veh_handler ) {
                logging::print( encrypt( "Cannot send command: buffer not mapped" ) );
                return { };
            }

            c_command command( type, data );
            command.set_status( in_progressive_state );
            memcpy( this->m_veh_handler, &command, sizeof( c_command ) );

            const auto start_time = std::chrono::steady_clock::now( );
            while ( true ) {
                const auto current_time = std::chrono::steady_clock::now( );
                const auto elapsed = std::chrono::duration_cast< std::chrono::milliseconds >(
                    current_time - start_time
                ).count( );

                if ( elapsed > timeout_ms ) {
                    logging::print( encrypt( "Cannot get response: response timed out after %d ms" ), timeout_ms );
                    command.set_status( timeout_state );
                    return command;
                }

                memcpy( &command, this->m_veh_handler, sizeof( c_command ) );
                if ( command.is_completed( ) &&
                     command.get_status( ) != in_progressive_state ) {
                    return command;
                }

                std::this_thread::sleep_for(
                    std::chrono::milliseconds(
                        30
                    ) );
            }
        }
    };
}
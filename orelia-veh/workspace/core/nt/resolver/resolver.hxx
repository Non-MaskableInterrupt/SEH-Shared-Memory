
namespace nt {
    class c_resolver {
    public:
        bool setup( ) {
            this->m_nt_base = reinterpret_cast< std::addr_t >(
                get_nt_base( )
                );

            if ( !this->m_nt_base )
                return false;
            return true;
        }

        std::uintptr_t find( std::uintptr_t base, std::size_t size, const char* pat, const char* msk ) {
            for ( auto i = 0ull; i < size - crt::strlen( msk ); ++i )
                if ( check( base + i, pat, msk ) )
                    return base + i;
            return 0;
        }

        bool next_exec_section( std::uint64_t* exec_base, std::uint64_t* exec_size ) const {
            auto dos_header{ reinterpret_cast< dos_header_t* > ( m_nt_base ) };
            auto nt_headers{ reinterpret_cast< nt_headers_t* > ( m_nt_base + dos_header->m_lfanew ) };
            if ( !dos_header->is_valid( )
                || !nt_headers->is_valid( ) )
                return false;

            auto section_header = reinterpret_cast< section_header_t* >(
                reinterpret_cast< std::uintptr_t >( nt_headers ) +
                nt_headers->m_size_of_optional_header + 0x18 );

            for ( int i = 0; i < nt_headers->m_number_of_sections; i++ ) {
                auto current_section_base = reinterpret_cast< std::uint64_t >( dos_header ) + section_header[ i ].m_virtual_address;
                if ( section_header[ i ].m_characteristics & 0x20000000 /*IMAGE_SCN_MEM_EXECUTE*/ ) {
                    *exec_base = current_section_base;
                    *exec_size = section_header[ i ].m_size_of_raw_data;
                    break;
                }
            }

            return *exec_base && *exec_size;
        }

        std::addr_t get_system_routine( const char* export_name ) const {
            auto dos_header{ reinterpret_cast< dos_header_t* > ( m_nt_base ) };
            auto nt_headers{ reinterpret_cast< nt_headers_t* > ( m_nt_base + dos_header->m_lfanew ) };
            if ( !dos_header->is_valid( )
                || !nt_headers->is_valid( ) )
                return {};

            auto exp_dir{ nt_headers->m_export_table.as_rva< export_directory_t* >( m_nt_base ) };
            if ( !exp_dir->m_address_of_functions
                || !exp_dir->m_address_of_names
                || !exp_dir->m_address_of_names_ordinals )
                return {};

            auto name{ reinterpret_cast< std::int32_t* > ( m_nt_base + exp_dir->m_address_of_names ) };
            auto func{ reinterpret_cast< std::int32_t* > ( m_nt_base + exp_dir->m_address_of_functions ) };
            auto ords{ reinterpret_cast< std::int16_t* > ( m_nt_base + exp_dir->m_address_of_names_ordinals ) };

            for ( std::int32_t i{}; i < exp_dir->m_number_of_names; i++ ) {
                auto cur_name{ m_nt_base + name[ i ] };
                auto cur_func{ m_nt_base + func[ ords[ i ] ] };
                if ( !cur_name
                    || !cur_func )
                    continue;

                if ( crt::strcmp( export_name, reinterpret_cast< char* > ( cur_name ) ) == 0 )
                    return reinterpret_cast< std::addr_t > ( cur_func );
            }
            return {};
        }

    private:
        std::addr_t m_nt_base = 0;

        bool check( std::uintptr_t ptr, const char* pat, const char* msk ) {
            for ( ; *msk; ++ptr, ++pat, ++msk )
                if ( *msk == 'x' && *reinterpret_cast< const char* >( ptr ) != *pat )
                    return false;
            return true;
        }
    };
}
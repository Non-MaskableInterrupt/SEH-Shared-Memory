
namespace interrupts
{
    static void* g_nmi_handle = nullptr;

    bool nmi_handler( void* context, bool handled ) {
        auto kpcr = reinterpret_cast< kpcr_t* >( __readmsr( ia32_gs_base ) );
        if ( !kpcr || !nt::mm_is_address_valid( kpcr ) )
            return true;

        auto ist_ptr = reinterpret_cast< std::uint64_t >(
            kpcr->m_ist[ 1 ]
            );
        if ( !ist_ptr || !nt::mm_is_address_valid( ( void* ) ist_ptr ) )
            return true;

        auto nmi_frame = reinterpret_cast< machine_frame_t* >(
            ist_ptr - sizeof( machine_frame_t )
            );
        if ( !nmi_frame || !nt::mm_is_address_valid( nmi_frame ) )
            return true;

        __try {
            nt::dbg_print( "[orelia] KPCR base: %llx\n", kpcr );
            nt::dbg_print( "[orelia] RIP: %llx\n", nmi_frame->m_rip );
            nt::dbg_print( "[orelia] CS: %llx\n", nmi_frame->m_cs );
            nt::dbg_print( "[orelia] EFLAGS: %llx\n", nmi_frame->m_eflags );
            nt::dbg_print( "[orelia] RSP: %llx\n", nmi_frame->m_rsp );
            nt::dbg_print( "[orelia] SS: %llx\n", nmi_frame->m_ss );
        }
        __except ( 1 ) {
            nt::dbg_print( "[orelia] exception accessing nmi frame at: %llx\n", nmi_frame );
            return true;
        }

        return true;
    }

    bool cleanup_nmi( ) {
        if ( g_nmi_handle ) {
            if ( !nt::ke_deregister_nmi_callback( g_nmi_handle ) )
                return false;
            g_nmi_handle = nullptr;
        }
        return true;
    }

    bool init_nmi( ) {
        auto ke_active_processors = nt::get_ke_active_processors( );
        nt::dbg_print("[orelia] Active processors mask: %llx\n", ke_active_processors);

        g_nmi_handle = nt::ke_register_nmi_callback(
            reinterpret_cast< p_nmi_callback >( nmi_handler ),
            nullptr
        );
        if ( !g_nmi_handle ) {
            nt::dbg_print( "failed to register nmi.\n" );
            return false;
        }

        auto current_prcb = reinterpret_cast< kprcb_t* >( __readgsqword( 0x20 ) );
        if ( !current_prcb ) {
            nt::dbg_print( "failed to copy prcb.\n" );
            return false;
        }

        char affinity[ 0x1000 ]{};
        auto result = nt::ke_copy_affinity_ex(
            reinterpret_cast< std::uint64_t >( &affinity ),
            ke_active_processors
        );
        if ( !result ) {
            nt::dbg_print( "failed to copy processor affinity.\n" );
            return false;
        }

        result = nt::ke_remove_processor_affinity_ex(
            reinterpret_cast< std::uint64_t >( &affinity ),
            current_prcb->m_number
        );
        if ( !result ) {
            nt::dbg_print( "failed to remove processor affinity.\n" );
            return false;
        }

        return !nt::hal_send_nmi( reinterpret_cast< std::uint64_t* >( &affinity ) );
    }
}
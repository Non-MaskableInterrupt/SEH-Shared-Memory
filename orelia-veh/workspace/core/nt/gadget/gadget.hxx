
namespace nt
{
	namespace gadget {
		bool create( void* function ) {
			std::uint64_t exec_base = 0;
			std::uint64_t exec_size = 0;
			if ( !g_resolver.next_exec_section( &exec_base, &exec_size ) )
				return false;

			auto jmp_rcx_addr = g_resolver.find( exec_base, exec_size, "\xFF\xE1", "xx" );
			if ( !jmp_rcx_addr )
				return false;

			auto result = ps_create_system_thread(
				&g_thread_handle,
				0x10000000L,
				nullptr,
				nullptr,
				nullptr,
				reinterpret_cast< void* >( jmp_rcx_addr ),
				function
			);

			zw_close( g_thread_handle );
			return result == nt_status_t::success;
		}
	}
}
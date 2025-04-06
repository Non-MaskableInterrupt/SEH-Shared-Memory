
namespace nt {
	namespace dkom {
		bool remove_apcs( kthread_t* current_thread ) {
			auto& apc_state = current_thread->m_apc_state;
			for ( auto apc_list_entry = apc_state.m_apc_list_head[ 0 ].m_flink;
				apc_list_entry != &apc_state.m_apc_list_head[ 0 ]; ) {
				auto next_entry = apc_list_entry->m_flink;

				auto current_apc = reinterpret_cast< kapc_t* >(
					reinterpret_cast< std::uint8_t* >( apc_list_entry ) - offsetof( kapc_t, apc_list_entry )
					);

				auto routine_address = current_apc->kernel_routine;
				current_thread->m_apc_queueable = 0;

				apc_list_entry->m_blink->m_flink = apc_list_entry->m_flink;
				apc_list_entry->m_flink->m_blink = apc_list_entry->m_blink;
				apc_list_entry = next_entry;
			}

			return true;
		}
	}
}
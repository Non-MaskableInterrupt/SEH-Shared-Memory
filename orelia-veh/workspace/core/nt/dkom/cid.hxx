
namespace nt {
	namespace dkom {
		bool unlink( kthread_t* current_thread ) {
			auto psp_cid_table = get_psp_cid_table( );
			if ( !psp_cid_table )
				return false;

			auto curr_ethread = reinterpret_cast< ethread_t* >( current_thread );
			if ( !curr_ethread )
				return false;

			auto thread_id = ps_get_thread_id( curr_ethread );
			if ( !thread_id )
				return false;

			auto cid_entry = exp_lookup_handle_table_entry(
				reinterpret_cast< std::uint64_t* >( psp_cid_table ),
				reinterpret_cast< long long >( thread_id )
			);
			if ( !cid_entry )
				return false;

			ex_destory_handle( psp_cid_table, thread_id, cid_entry );
			return cid_entry->m_object_pointer == 0;
		}
	}
}
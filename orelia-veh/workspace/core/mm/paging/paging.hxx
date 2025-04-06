
namespace mm {
	namespace paging {
		constexpr auto page_4kb_size = 0x1000ull;
		constexpr auto page_2mb_size = 0x200000ull;
		constexpr auto page_1gb_size = 0x40000000ull;

		constexpr auto page_shift = 12ull;
		constexpr auto page_2mb_shift = 21ull;
		constexpr auto page_1gb_shift = 30ull;

		constexpr auto page_4kb_mask = 0xFFFull;
		constexpr auto page_2mb_mask = 0x1FFFFFull;
		constexpr auto page_1gb_mask = 0x3FFFFFFFull;

		class c_paging {
			cr3 m_dtb;
			c_vector< pml4e, 512 > m_pml4_table;
			c_vector< pdpte, 512 > m_pdpt_table;
			c_vector< physical_memory_range_t, 512 > m_memory_ranges;

		public:
			bool cache_pt( virt_addr_t va ) {
				// hello sir
				return true;
			}

			std::uint64_t resolve_physical( std::uint64_t virtual_address, std::uint32_t* out_page_size = nullptr ) {
				// hello sir
				return 0;
			}

			void set_dtb( std::uintptr_t dtb ) {
				this->m_dtb.flags = dtb;
			}

			bool is_valid_physical_virtual_address( std::uint64_t virtual_address, std::size_t size ) {
				for ( const auto& range : m_memory_ranges ) {
					if ( !range.m_base_page || !range.m_page_count )
						continue;

					std::uint64_t base = range.m_base_page * page_4kb_size;
					std::uint64_t length = range.m_page_count * page_4kb_size;
					std::uint64_t end = base + length;

					if ( virtual_address >= base && ( virtual_address + size ) <= end )
						return true;
				}
				return false;
			}
		};
	}
}

namespace driver
{
	// status code
	const std::uint16_t in_progressive_state = 1;
	const std::uint16_t error_state = 2;
	const std::uint16_t success_state = 3;
	const std::uint16_t timeout_state = 4;

	enum class e_command_type : std::uint32_t {
		unload,
		is_active,
		read_memory,
		write_memory,
		get_eprocess,
		get_base_address,
		translate_linear,
		get_dtb
	};

	struct s_command_data {
		std::uint32_t m_pid{};
		std::uintptr_t m_address{};
		std::uintptr_t m_address2{};
		eprocess_t* m_process{};
		std::size_t m_size{};
		void* m_buffer{};
	};

	class c_command {
	public:
		c_command( ) = default;
		c_command(
			e_command_type type,
			s_command_data data,
			bool completed = false )
			: m_type( type ), m_data( data ), m_completed( completed ) {
		}

		bool is_completed( ) const { return m_completed; }
		void set_completed( bool state ) { m_completed = state; }

		std::uint32_t get_status( ) const { return m_status_code; }
		void set_status( std::uint32_t status_code ) { m_status_code = status_code; }

		e_command_type get_type( ) const { return m_type; }
		const s_command_data& get_data( ) const { return m_data; }

	private:
		e_command_type m_type;
		s_command_data m_data;
		bool m_completed;
		std::uint32_t m_status_code;
		std::uint64_t m_timestamp;
	};

	class c_event_log {
	public:
		c_event_log( ) = default;

	private:

	};
}

namespace nt {
    void rtl_init_unicode_string(
        unicode_string_t* destination_string,
        const wchar_t* source_string
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "RtlInitUnicodeString" );
            if ( !function_address ) return;
        }

        using function_t = void( * )(
            unicode_string_t* destination_string,
            const wchar_t* source_string
            );

        reinterpret_cast< function_t >( function_address )(
            destination_string,
            source_string
            );
    }

    nt_status_t ob_reference_object_by_name(
        unicode_string_t* object_name,
        std::uint32_t attributes,
        void* parsed_object,
        std::uint32_t access_mode,
        void* object_type,
        std::uint32_t access_mode2,
        void* context,
        void** object
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ObReferenceObjectByName" );
            if ( !function_address ) return {};
        }

        using function_t = nt_status_t( * )(
            unicode_string_t* object_name,
            std::uint32_t attributes,
            void* parsed_object,
            std::uint32_t access_mode,
            void* object_type,
            std::uint32_t access_mode2,
            void* context,
            void** object
            );

        return reinterpret_cast< function_t >( function_address )(
            object_name,
            attributes,
            parsed_object,
            access_mode,
            object_type,
            access_mode2,
            context,
            object
            );
    }

    nt_status_t ke_query_system_information(
        std::uint32_t information_class,
        void* system_information,
        std::uint32_t length,
        std::uint32_t* return_length
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeQuerySystemInformation" );
            if ( !function_address ) return {};
        }

        using function_t = nt_status_t( * )(
            std::uint32_t information_class,
            void* system_information,
            std::uint32_t length,
            std::uint32_t* return_length
            );

        return reinterpret_cast< function_t >( function_address )(
            information_class,
            system_information,
            length,
            return_length
            );
    }

    void rtl_copy_memory(
        void* dest,
        const void* src,
        size_t length
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "RtlCopyMemory" );
            if ( !function_address ) return;
        }

        using function_t = void( * )(
            void* dest,
            const void* src,
            size_t length
            );

        reinterpret_cast< function_t >( function_address )(
            dest,
            src,
            length
            );
    }

    void probe_for_read(
        void* address,
        std::size_t length,
        std::uint8_t alignment
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ProbeForRead" );
            if ( !function_address ) return;
        }

        using function_t = void( * )(
            void*,
            std::size_t,
            std::uint8_t
            );

        return reinterpret_cast< function_t >( function_address )(
            address,
            length,
            alignment
            );
    }

    eprocess_t* zw_current_process( ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ZwCurrentProcess" );
            if ( !function_address ) return nullptr;
        }

        using function_t = eprocess_t * ( * )( );

        return reinterpret_cast< function_t >( function_address )( );
    }

    void ke_initialize_spin_lock( kspin_lock_t* lock ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeInitializeSpinLock" );
            if ( !function_address ) return;
        }

        using function_t = void ( * )( kspin_lock_t* );
        reinterpret_cast< function_t >( function_address )( lock );
    }

    void ke_acquire_spin_lock( kspin_lock_t* lock, kirql_t* old_irql ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeAcquireSpinLock" );
            if ( !function_address ) return;
        }

        using function_t = void ( * )( kspin_lock_t*, kirql_t* );
        reinterpret_cast< function_t >( function_address )( lock, old_irql );
    }

    void ke_release_spin_lock( kspin_lock_t* lock, kirql_t old_irql ) {
        if ( !lock ) return;

        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeReleaseSpinLock" );
            if ( !function_address ) return;
        }

        using function_t = void ( * )( kspin_lock_t*, kirql_t );
        reinterpret_cast< function_t >( function_address )( lock, old_irql );
    }

    void rtl_zero_memory( void* dest, size_t length ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "RtlZeroMemory" );
            if ( !function_address ) return;
        }

        using function_t = void ( * )( void*, size_t );
        reinterpret_cast< function_t >( function_address )( dest, length );
    }

    void rtl_move_memory( void* dest, const void* src, size_t length ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "RtlMoveMemory" );
            if ( !function_address ) return;
        }

        using function_t = void ( * )( void*, const void*, size_t );
        reinterpret_cast< function_t >( function_address )( dest, src, length );
    }

    nt_status_t zw_map_view_of_section(
        void* section_handle,
        void* process_handle,
        void** base_address,
        std::uint64_t zero_bits,
        std::size_t commit_size,
        large_integer_t* section_offset,
        std::size_t* view_size,
        std::uint32_t inherit_disposition,
        std::uint64_t allocation_type,
        std::uint32_t win32_protect
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ZwMapViewOfSection" );
            if ( !function_address ) return nt_status_t::unsuccessful;
        }

        using function_t = nt_status_t( * )(
            void*,
            void*,
            void**,
            std::uint64_t,
            std::size_t,
            large_integer_t*,
            std::size_t*,
            std::uint32_t,
            std::uint64_t,
            std::uint32_t
            );

        return reinterpret_cast< function_t >( function_address )(
            section_handle,
            process_handle,
            base_address,
            zero_bits,
            commit_size,
            section_offset,
            view_size,
            inherit_disposition,
            allocation_type,
            win32_protect
            );
    }

    std::uintptr_t ps_get_thread_teb(
        void* thread
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsGetThreadTeb" );
            if ( !function_address ) return 0;
        }

        using function_t = std::uintptr_t( * )(
            void*
            );

        return reinterpret_cast< function_t >( function_address )( thread );
    }

    object_type_t* ps_process_type( ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsProcessType" );
            if ( !function_address ) return nullptr;
        }

        return *reinterpret_cast< object_type_t** >( function_address );
    }

    nt_status_t zw_get_next_thread(
        void* process_handle,
        void* thread_handle,
        std::uint32_t desired_access,
        std::uint32_t handle_attributes,
        std::uint32_t flags,
        void** new_thread_handle
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ZwGetNextThread" );
            if ( !function_address ) return { };
        }

        using function_t = nt_status_t( * )(
            void*,
            void*,
            std::uint32_t,
            std::uint32_t,
            std::uint32_t,
            void**
            );

        return reinterpret_cast< function_t >( function_address )(
            process_handle,
            thread_handle,
            desired_access,
            handle_attributes,
            flags,
            new_thread_handle
            );
    }

    nt_status_t ob_open_object_by_pointer(
        void* object,
        std::uint32_t handle_attributes,
        void* access_state,
        std::uint32_t desired_access,
        void* object_type,
        std::uint32_t access_mode,
        void** handle
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ObOpenObjectByPointer" );
            if ( !function_address ) return {};
        }

        using function_t = nt_status_t( * )(
            void*,              // Object
            std::uint32_t,      // HandleAttributes
            void*,              // PassedAccessState
            std::uint32_t,      // DesiredAccess
            void*,              // ObjectType
            std::uint32_t,      // AccessMode
            void**              // Handle
            );

        return reinterpret_cast< function_t >( function_address )(
            object,
            handle_attributes,
            access_state,
            desired_access,
            object_type,
            access_mode,
            handle
            );
    }

    nt_status_t ob_reference_object_by_handle(
        void* handle,
        std::uint32_t desired_access,
        void* object_type,
        std::uint8_t access_mode,
        void** object,
        void* handle_information
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ObReferenceObjectByHandle" );
            if ( !function_address ) return nt_status_t::unsuccessful;
        }

        using function_t = nt_status_t( * )(
            void*,
            std::uint32_t,
            void*,
            std::uint8_t,
            void**,
            void*
            );

        return reinterpret_cast< function_t >( function_address )(
            handle,
            desired_access,
            object_type,
            access_mode,
            object,
            handle_information
            );
    }

    void ob_dereference_object(
        void* object
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ObDereferenceObject" );
            if ( !function_address ) return;
        }

        using function_t = void( * )(
            void*
            );

        reinterpret_cast< function_t >( function_address )( object );
    }

    nt_status_t zw_create_section(
        void** section_handle,
        std::uint32_t desired_access,
        object_attributes_t* object_attributes,
        large_integer_t* maximum_size,
        std::uint32_t page_protection,
        std::uint32_t allocation_attributes,
        void* file_handle
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ZwCreateSection" );
            if ( !function_address ) return nt_status_t::unsuccessful;
        }

        using function_t = nt_status_t( * )(
            void**,
            std::uint32_t,
            object_attributes_t*,
            large_integer_t*,
            std::uint32_t,
            std::uint32_t,
            void*
            );

        return reinterpret_cast< function_t >( function_address )(
            section_handle,
            desired_access,
            object_attributes,
            maximum_size,
            page_protection,
            allocation_attributes,
            file_handle
            );
    }

    nt_status_t zw_create_user_process(
        void** process_handle,
        void** thread_handle,
        std::uint32_t process_access,
        std::uint32_t thread_access,
        object_attributes_t* process_attributes,
        object_attributes_t* thread_attributes,
        std::uint32_t process_flags,
        std::uint32_t thread_flags,
        void* process_parameters,
        ps_create_info_t* create_info,
        ps_attribute_list_t* attribute_list
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ZwCreateUserProcess" );
            if ( !function_address ) return nt_status_t::unsuccessful;
        }

        using function_t = nt_status_t( * )(
            void**,
            void**,
            std::uint32_t,
            std::uint32_t,
            object_attributes_t*,
            object_attributes_t*,
            std::uint32_t,
            std::uint32_t,
            void*,
            ps_create_info_t*,
            ps_attribute_list_t*
            );

        return reinterpret_cast< function_t >( function_address )(
            process_handle,
            thread_handle,
            process_access,
            thread_access,
            process_attributes,
            thread_attributes,
            process_flags,
            thread_flags,
            process_parameters,
            create_info,
            attribute_list
            );
    }

    nt_status_t zw_close(
        void* handle
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ZwClose" );
            if ( !function_address ) return nt_status_t::unsuccessful;
        }

        using function_t = nt_status_t( * )( void* );
        return reinterpret_cast< function_t >( function_address )( handle );
    }

    std::uint16_t* get_ke_active_processors( ) {
        static std::uint16_t* ke_active_processors = nullptr;
        if ( !ke_active_processors ) {
            std::addr_t function_address = g_resolver.get_system_routine( "KeQueryGroupAffinity" );
            while ( function_address[ 0x0 ] != 0x66 ||
                function_address[ 0x1 ] != 0x3B ||
                function_address[ 0x2 ] != 0x0D )
                function_address++;

            ke_active_processors = reinterpret_cast< std::uint16_t* >(
                &function_address[ 0x7 ] + *reinterpret_cast< std::int32_t* >( &function_address[ 0x3 ] ) );
        }

        return ke_active_processors;
    }

    std::uint64_t hal_send_nmi(
        std::uint64_t* affinity
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "HalSendNMI" );
            if ( !function_address ) return {};
        }

        using function_t = std::uint64_t(
            std::uint64_t* affinity
        );

        return reinterpret_cast< function_t* >( function_address )( affinity );
    }

    std::int16_t ke_remove_processor_affinity_ex(
        std::uint64_t affinity,
        std::uint32_t number
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeRemoveProcessorAffinityEx" );
            if ( !function_address ) return {};
        }

        using function_t = std::int16_t(
            std::uint64_t affinity,
            std::uint32_t number
        );

        return reinterpret_cast< function_t* >( function_address )( affinity, number );
    }

    std::int16_t ke_copy_affinity_ex(
        std::uint64_t affinity,
        std::uint16_t* processors
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeCopyAffinityEx" );
            if ( !function_address ) return {};
        }

        using function_t = std::int16_t(
            std::uint64_t affinity,
            std::uint16_t* processors
        );

        return reinterpret_cast< function_t* >( function_address )( affinity, processors );
    }

    void* ke_register_nmi_callback(
        p_nmi_callback callback_routine,
        void* context
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeRegisterNmiCallback" );
            if ( !function_address ) return {};
        }

        using function_t = void* (
            p_nmi_callback,
            void*
            );

        return reinterpret_cast< function_t* >( function_address )( callback_routine, context );
    }

    bool ke_deregister_nmi_callback( void* handle ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeDeregisterNmiCallback" );
            if ( !function_address ) return false;
        }

        using function_t = bool( void* Handle );
        return reinterpret_cast< function_t* >( function_address )( handle );
    }

    void probe_for_write(
        void* address,
        std::size_t length,
        std::uint8_t alignment
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ProbeForWrite" );
            if ( !function_address ) return;
        }

        using function_t = void(
            void* address,
            std::size_t length,
            std::uint8_t alignment
            );

        reinterpret_cast< function_t* >( function_address )(
            address,
            length,
            alignment
            );
    }

    void mm_unmap_io_space(
        void* base_address,
        std::size_t number_of_bytes
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "MmUnmapIoSpace" );
            if ( !function_address ) return;
        }

        using function_t = void(
            void* base_address,
            std::size_t number_of_bytes
            );

        reinterpret_cast< function_t* >( function_address ) (
            base_address,
            number_of_bytes );
    }

    void* map_io_space_ex(
        physical_address_t physical_address,
        std::size_t number_of_bytes,
        std::uint32_t protect
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "MmMapIoSpaceEx" );
            if ( !function_address ) return { };
        }

        using function_t = void* (
            physical_address_t physical_address,
            std::size_t number_of_bytes,
            std::uint32_t protect
            );

        return reinterpret_cast< function_t* >( function_address ) (
            physical_address,
            number_of_bytes,
            protect );
    }

    nt_status_t mm_copy_memory(
        void* target_address,
        mm_copy_address_t source_address,
        std::size_t number_of_bytes,
        std::uint32_t flags,
        std::size_t* number_of_bytes_transferred
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "MmCopyMemory" );
            if ( !function_address ) return { };
        }

        using function_t = nt_status_t(
            void* target_address,
            mm_copy_address_t source_address,
            std::size_t number_of_bytes,
            std::uint32_t flags,
            std::size_t* number_of_bytes_transferred
        );

        return reinterpret_cast< function_t* >( function_address )(
            target_address,
            source_address,
            number_of_bytes,
            flags,
            number_of_bytes_transferred
            );
    }

    mmpfn_t* get_mm_pfn_database( ) {
        static mmpfn_t* mm_pfn_database = nullptr;
        if ( !mm_pfn_database ) {
            static std::addr_t function_address = nullptr;
            if ( !function_address ) {
                function_address = g_resolver.get_system_routine( "KeCapturePersistentThreadState" );
                if ( !function_address ) return { };
            }

            while ( function_address[ 0x0 ] != 0x48
                || function_address[ 0x1 ] != 0x8B
                || function_address[ 0x2 ] != 0x05 )
                function_address++;

            mm_pfn_database = *reinterpret_cast< mmpfn_t** >(
                &function_address[ 0x7 ] + *reinterpret_cast< std::int32_t* >( &function_address[ 0x3 ] ) );
        }

        return mm_pfn_database;
    }

    std::uint8_t ke_raise_irql(
        std::uint8_t new_irql
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeRaiseIrql" );
            if ( !function_address ) return {};
        }

        using function_t = void( * )(
            std::uint8_t new_irql,
            std::uint8_t* old_irql
            );

        std::uint8_t old_irql;
        reinterpret_cast< function_t >( function_address )(
            new_irql,
            &old_irql
            );

        return old_irql;
    }

    void ke_lower_irql(
        std::uint8_t new_irql
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeLowerIrql" );
            if ( !function_address ) return;
        }

        using function_t = void( * )(
            std::uint8_t new_irql
            );

        reinterpret_cast< function_t >( function_address )(
            new_irql
            );
    }

    void ke_sleep(
        std::int64_t ms
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeDelayExecutionThread" );
            if ( !function_address ) return;
        }

        using function_t = void( * )(
            std::uint8_t wait_mode,
            std::uint8_t alertable,
            std::int64_t* interval
            );

        std::int64_t interval = -10000LL * ms;
        reinterpret_cast< function_t >( function_address )(
            0,              // KernelMode
            false,          // Non-alertable
            &interval
            );
    }

    nt_status_t zw_free_virtual_memory(
        void* process_handle,
        void** base_address,
        std::size_t* region_size,
        std::uint32_t free_type
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ZwFreeVirtualMemory" );
            if ( !function_address ) return {};
        }

        using function_t = nt_status_t( * )(
            void* process_handle,
            void** base_address,
            std::size_t* region_size,
            std::uint32_t free_type
            );

        return reinterpret_cast< function_t >( function_address )(
            process_handle,
            base_address,
            region_size,
            free_type
            );
    }

    physical_memory_range_t* mm_get_physical_memory_ranges( ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "MmGetPhysicalMemoryRanges" );
            if ( !function_address ) return { };
        }

        using function_t = physical_memory_range_t * ( void );

        return reinterpret_cast< function_t* >( function_address )( );
    }

    nt_status_t zw_query_information_process(
        void* process_handle,
        std::uint32_t process_information_class,
        void* process_information,
        std::uint32_t process_information_length,
        std::uint32_t* return_length
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ZwQueryInformationProcess" );
            if ( !function_address ) return {};
        }

        using fn_t = nt_status_t( * )( void*, std::uint32_t, void*, std::uint32_t, std::uint32_t* );
        return reinterpret_cast< fn_t >( function_address )(
            process_handle,
            process_information_class,
            process_information,
            process_information_length,
            return_length
            );
    }

    nt_status_t ps_query_full_process_image_name(
        void* process,
        unicode_string_t** image_name
    ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsQueryFullProcessImageName" );
            if ( !function_address ) return { };
        }

        using function_t = nt_status_t( * )(
            void*,
            unicode_string_t**
            );

        return reinterpret_cast< function_t >( function_address )(
            process,
            image_name
            );
    }

    std::uintptr_t ps_initial_system_process( ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsInitialSystemProcess" );
            if ( !function_address ) return {};
        }

        return *reinterpret_cast< std::uintptr_t* >( function_address );
    }

    std::uint32_t ps_get_process_id(
        eprocess_t* process
    ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsGetProcessId" );
            if ( !function_address ) return {};
        }

        using function_t = void* (
            eprocess_t* Process
            );

        return reinterpret_cast< std::uint32_t >(
            reinterpret_cast< function_t* >( function_address )( process )
            );
    }

    list_entry_t* ps_active_process_head( ) {
        static list_entry_t* ps_active_process_head = nullptr;
        if ( !ps_active_process_head ) {
            static std::addr_t function_address = 0;
            if ( !function_address ) {
                function_address = g_resolver.get_system_routine( "KeCapturePersistentThreadState" );
                if ( !function_address ) return {};
            }

            while ( function_address[ 0x0 ] != 0x20
                || function_address[ 0x1 ] != 0x48
                || function_address[ 0x2 ] != 0x8d )
                function_address++;

            ps_active_process_head = *reinterpret_cast< list_entry_t** >
                ( &function_address[ 0x8 ] + *reinterpret_cast< std::int32_t* >( &function_address[ 0x4 ] ) );
        }

        return ps_active_process_head;
    }

    std::uintptr_t get_cr3( eprocess_t* process ) {
        if ( !process ) return 0;

        auto directory_table_base = *reinterpret_cast< std::uintptr_t* >(
            reinterpret_cast< std::uintptr_t >( process ) + 0xB8
            );

        return *reinterpret_cast< std::uintptr_t* >( directory_table_base + 0x28 ) & 0xFFFFFFFFFFFFF000;
    }

    void memcpy( void* destination, const void* source, size_t length ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "RtlCopyMemory" );
        }
        if ( !function_address ) return;

        using function_t = void( void* destination, const void* source, size_t length );
        reinterpret_cast< function_t* >( function_address )( destination, source, length );
    }

    void ex_free_pool( void* base_address ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ExFreePool" );
        }
        if ( !function_address ) return;

        using function_t = void( void* );
        reinterpret_cast< function_t* >( function_address )( base_address );
    }

    void* ex_allocate_pool( std::size_t number_of_bytes, pool_type used_pool_type = pool_type::nonpaged_pool ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "ExAllocatePool" );
        }
        if ( !function_address ) return nullptr;

        using function_t = void* ( pool_type, std::size_t );
        return reinterpret_cast< function_t* >( function_address )( used_pool_type, number_of_bytes );
    }

    nt_status_t ps_get_process_exit_status( eprocess_t* process ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsGetProcessExitStatus" );
        }
        if ( !function_address ) return {};

        using function_t = nt_status_t( eprocess_t* );
        return reinterpret_cast< function_t* >( function_address )( process );
    }

    nt_status_t mm_copy_virtual_memory(
        eprocess_t* source_process,
        void* source_address,
        eprocess_t* target_process,
        void* target_address,
        std::size_t buffer_size,
        std::int8_t previous_mode
    ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "MmCopyVirtualMemory" );
        }
        if ( !function_address ) return {};

        std::size_t bytes_read = 0;
        using function_t = nt_status_t( eprocess_t*, void*, eprocess_t*, void*, std::size_t, std::int8_t, std::size_t* );
        return reinterpret_cast< function_t* >( function_address )( source_process, source_address, target_process, target_address, buffer_size, previous_mode, &bytes_read );
    }

    eprocess_t* io_get_current_process( ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "IoGetCurrentProcess" );
        }
        if ( !function_address ) return nullptr;

        using function_t = eprocess_t * ( );
        return reinterpret_cast< function_t* >( function_address )( );
    }

    eprocess_t* ps_get_current_process( ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsGetCurrentProcess" );
        }
        if ( !function_address ) return nullptr;

        using function_t = eprocess_t * ( );
        return reinterpret_cast< function_t* >( function_address )( );
    }

    void* ps_get_thread_teb( ethread_t* Thread ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsGetThreadTeb" );
        }
        if ( !function_address ) return nullptr;

        using function_t = void* ( ethread_t* );
        return reinterpret_cast< function_t* >( function_address )( Thread );
    }

    void* ps_get_process_section_base_address( eprocess_t* Process ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsGetProcessSectionBaseAddress" );
        }
        if ( !function_address ) return nullptr;

        using function_t = void* (
            eprocess_t* Process
            );

        return reinterpret_cast< function_t* >( function_address )( Process );
    }

    eprocess_t* ps_lookup_process_by_process_id( std::uint32_t process_id ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsLookupProcessByProcessId" );
        }
        if ( !function_address ) return nullptr;

        eprocess_t* process;
        using function_t = nt_status_t( void*, eprocess_t** );
        auto result = reinterpret_cast< function_t* >( function_address )(
            reinterpret_cast< void* >( process_id ),
            &process );
        if ( result == 0 )
            return process;

        return nullptr;
    }

    ethread_t* ps_get_next_process_thread( eprocess_t* Process, ethread_t* Thread ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsGetNextProcessThread" );
        }
        if ( !function_address ) return nullptr;

        using function_t = ethread_t * ( eprocess_t*, ethread_t* );
        return reinterpret_cast< function_t* >( function_address )(
            Process, Thread );
    }

    nt_status_t zw_terminate_thread( void* ThreadHandle, nt_status_t ExitStatus ) {
        auto function_address = g_resolver.get_system_routine( "ZwTerminateThread" );
        if ( !function_address ) {
            return {};
        }

        using function_t = nt_status_t( void*, nt_status_t );
        return reinterpret_cast< function_t* >( function_address )(
            ThreadHandle,
            ExitStatus
            );
    }

    nt_status_t ex_destory_handle(
        handle_table_t* table,
        void* handle,
        handle_table_entry_t* handle_table_entry
    ) {
        static std::addr_t ex_destory_handle = 0;
        if ( !ex_destory_handle ) {
            static auto function_address = g_resolver.get_system_routine( "RtlEmptyAtomTable" );
            if ( !function_address )
                return {};

            while ( function_address[ 0x0 ] != 0x48 ||
                function_address[ 0x1 ] != 0x83 ||
                function_address[ 0x2 ] != 0x23 ||
                function_address[ 0x3 ] != 0x00 ||
                function_address[ 0x4 ] != 0xE8 )
                function_address++;

            auto relative_offset = *reinterpret_cast< std::int32_t* >( &function_address[ 0x5 ] );
            auto rtlp_free_handle_for_atom = reinterpret_cast< std::addr_t >( function_address + 9 + relative_offset );
            if ( !rtlp_free_handle_for_atom )
                return {};

            while ( rtlp_free_handle_for_atom[ 0x0 ] != 0x4C ||
                rtlp_free_handle_for_atom[ 0x1 ] != 0x8B ||
                rtlp_free_handle_for_atom[ 0x2 ] != 0xC0 ||
                rtlp_free_handle_for_atom[ 0x3 ] != 0x48 ||
                rtlp_free_handle_for_atom[ 0x4 ] != 0x8B ||
                rtlp_free_handle_for_atom[ 0x5 ] != 0x4B ||
                rtlp_free_handle_for_atom[ 0x6 ] != 0x10 ||
                rtlp_free_handle_for_atom[ 0x7 ] != 0xE8 )
                rtlp_free_handle_for_atom++;

            relative_offset = *reinterpret_cast< std::int32_t* >( &rtlp_free_handle_for_atom[ 0x8 ] );
            ex_destory_handle = rtlp_free_handle_for_atom + 0xC + relative_offset;
        }

        using function_t = nt_status_t( handle_table_t* table,
            void* handle,
            handle_table_entry_t* handle_table_entry );

        return reinterpret_cast< function_t* >( ex_destory_handle )( table, handle, handle_table_entry );
    }

    handle_table_entry_t* exp_lookup_handle_table_entry( std::uint64_t* handle_table, long long handle ) {
        std::uint64_t v2; // rdx
        long long v3; // r8

        v2 = handle & 0xFFFFFFFFFFFFFFFC;
        if ( v2 >= *handle_table )
            return 0;
        v3 = *( handle_table + 1 );
        if ( ( v3 & 3 ) == 1 )
            return reinterpret_cast< handle_table_entry_t* >( *reinterpret_cast< std::uint64_t* >( v3 + 8 * ( v2 >> 10 ) - 1 ) + 4 * ( v2 & 0x3FF ) );
        if ( ( v3 & 3 ) != 0 )
            return reinterpret_cast< handle_table_entry_t* >( *reinterpret_cast< std::uint64_t* >( *reinterpret_cast< std::uint64_t* >( v3 + 8 * ( v2 >> 19 ) - 2 ) + 8 * ( ( v2 >> 10 ) & 0x1FF ) ) + 4 * ( v2 & 0x3FF ) );
        return reinterpret_cast< handle_table_entry_t* >( v3 + 4 * v2 );
    }

    handle_table_t* get_psp_cid_table( ) {
        static handle_table_t* psp_cid_table = nullptr;
        if ( !psp_cid_table ) {
            auto function_address = g_resolver.get_system_routine( "PsLookupThreadByThreadId" );
            if ( !function_address )
                return {};

            while ( function_address[ 0x0 ] != 0xB2 ||
                function_address[ 0x1 ] != 0x06 ||
                function_address[ 0x2 ] != 0xE8 )
                function_address++;

            auto relative_offset = *reinterpret_cast< std::int32_t* >( &function_address[ 0x3 ] );
            auto psp_reference_cid_table_entry = function_address + 7 + relative_offset;
            if ( !psp_reference_cid_table_entry )
                return {};

            while ( psp_reference_cid_table_entry[ 0x0 ] != 0x48 ||
                psp_reference_cid_table_entry[ 0x1 ] != 0x8B ||
                psp_reference_cid_table_entry[ 0x2 ] != 0x05 )
                psp_reference_cid_table_entry++;

            auto psp_cid_table_ptr = reinterpret_cast< handle_table_t** >(
                psp_reference_cid_table_entry + 7 +
                *reinterpret_cast< std::int32_t* >( &psp_reference_cid_table_entry[ 0x3 ] ) );

            psp_cid_table = *psp_cid_table_ptr;
        }

        return psp_cid_table;
    }

    void* ps_get_thread_id( ethread_t* Thread ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsGetThreadId" );
            if ( !function_address ) return {};
        }

        using function_t = void* (
            ethread_t* Thread
            );

        return reinterpret_cast< function_t* >( function_address )( Thread );
    }

    ethread_t* ps_get_current_thread( ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsGetCurrentThread" );
            if ( !function_address ) return {};
        }

        using function_t = ethread_t * ( );

        return reinterpret_cast< function_t* >( function_address )( );
    }

    bool ps_is_system_thread( ethread_t* Thread ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsIsSystemThread" );
            if ( !function_address ) return {};
        }

        using function_t = bool(
            ethread_t* Thread
            );

        return reinterpret_cast< function_t* >( function_address )( Thread );
    }

    nt_status_t ps_lookup_thread_by_thread_id( std::uint32_t ThreadId, ethread_t** Thread ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsLookupThreadByThreadId" );
            if ( !function_address ) return {};
        }

        using function_t = nt_status_t(
            void* ThreadId,
            ethread_t** Thread
        );

        return reinterpret_cast< function_t* >( function_address )(
            reinterpret_cast< void* >( ThreadId ),
            Thread
            );
    }

    bool mm_is_address_valid( void* VirtualAddress ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "MmIsAddressValid" );
            if ( !function_address ) return {};
        }

        using function_t = bool(
            void* VirtualAddress
            );

        return reinterpret_cast< function_t* >( function_address )( VirtualAddress );
    }

    kthread_t* ke_get_current_thread( void ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "KeGetCurrentThread" );
            if ( !function_address ) return {};
        }

        using function_t = kthread_t * ( void );
        return reinterpret_cast< function_t* >( function_address )( );
    }

    nt_status_t ps_create_system_thread(
        void** thread_handle,
        std::uint32_t desired_access,
        void* object_attributes,
        void* process_handle,
        void* client_id,
        void* start_routine,
        void* start_context ) {
        static std::addr_t function_address = nullptr;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "PsCreateSystemThread" );
            if ( !function_address ) return {};
        }

        using function_t = nt_status_t(
            void** thread_handle,
            std::uint32_t desired_access,
            void* object_attributes,
            void* process_handle,
            void* client_id,
            void* start_routine,
            void* start_context
        );

        return reinterpret_cast< function_t* >( function_address )(
            thread_handle,
            desired_access,
            object_attributes,
            process_handle,
            client_id,
            start_routine,
            start_context
            );
    }

    template<class... args_t>
    std::int8_t dbg_print( const char* format, args_t... va_args ) {
        static std::addr_t function_address = 0;
        if ( !function_address ) {
            function_address = g_resolver.get_system_routine( "DbgPrintEx" );
        }
        if ( !function_address ) return 0;

        using function_t = std::int32_t( std::uint32_t flag, std::uint32_t level,
            const char* format, args_t... va_args );
        return reinterpret_cast< function_t* >( function_address )( 0, 0, format, va_args... ) ==
            nt_status_t::success;
    }
}
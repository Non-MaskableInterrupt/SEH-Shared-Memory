
namespace crt
{
    [[ nodiscard ]]
    const char* str_str( 
        const char* haystack,
        const char* needle
    ) {
        if ( !haystack || !needle )
            return nullptr;

        if ( !*needle )
            return haystack;

        const char* p1 = haystack;
        while ( *p1 ) {
            const char* p1_begin = p1;
            const char* p2 = needle;

            while ( *p1 && *p2 && ( *p1 == *p2 ) ) {
                p1++;
                p2++;
            }

            if ( !*p2 )
                return p1_begin;

            p1 = p1_begin + 1;
        }

        return nullptr;
    }

    [[ nodiscard ]] 
    void* memcpy ( 
        void* dest ,
        const void* src , 
        size_t len 
    ) {
        char* d = ( char* ) dest;
        const char* s = ( const char* ) src;
        while ( len-- )
            *d++ = *s++;
        return dest;
    }

    [[ nodiscard ]]
    int wcscmp (
        const wchar_t* s1 ,
        const wchar_t* s2
    ) {
        while ( *s1 == *s2++ )
            if ( *s1++ == '\0' )
                return ( 0 );

        return ( *( const unsigned int* ) s1 - *( const unsigned int* )--s2 );
    }

    [[ nodiscard ]]
    std::int32_t strcmp (
        const char* string,
        const char* string_cmp
    ) {
        while ( *string != '\0' )
        {
            if ( *string != *string_cmp )
                break;
            string++;
            string_cmp++;
        }
        return *string - *string_cmp;
    }

    [[ nodiscard ]] 
    std::size_t strlen (
        const char* str 
    ) {
        const char* s;
        for ( s = str; *s; ++s );
        return ( s - str );
    }
}
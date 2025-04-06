#include <impl/std/std.h>
#include <impl/ia32/ia32.h>
#include <impl/crt/crt.hxx>
extern "C" std::uintptr_t get_nt_base( );

#define kernel_mode 0
#define user_mode 1

#include <workspace/core/nt/nt.h>
#include <workspace/core/mm/mm.h>

#include <workspace/core/user/request/request.h>
#include <workspace/core/user/user.hxx>
namespace nt {
	client::c_client g_client;
}

#include <workspace/callbacks/interrupts/interrupts.hxx>
#include <workspace/core/user/handler/handler.hxx>
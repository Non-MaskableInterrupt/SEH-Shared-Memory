#include <workspace/core/nt/resolver/resolver.hxx>

namespace nt {
	c_resolver g_resolver;
	void* g_thread_handle = nullptr;
}

#include <workspace/core/nt/symbols/symbols.hxx>
#include <workspace/core/nt/custom/vector.hxx>
#include <workspace/core/nt/gadget/gadget.hxx>
#include <workspace/core/nt/dkom/thread.hxx>
#include <workspace/core/nt/dkom/cid.hxx>
#include <workspace/core/nt/dkom/apc.hxx>
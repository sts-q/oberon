#include <assert.h>
#include "config.h"
#include "dialog.h"
#include "heap.h"
#include "o3.h"
#include "skl_vmsvc.h"

namespace skl {

    typedef struct vmsvc_early_hwdtrap_desc_t : vmsvc_desc_t {
        /* Kernel.VMServiceHwdTrapDesc */
        md::uint32 ip;
        md::uint32 sfp;
        md::uint32 trap;
        md::uint32 cr2;
    } vmsvc_early_hwdtrap_desc_t;


    void
    vmsvc_early_hwdtrap(md::OADDR adr)
    {
        md::HADDR                   ptr   = heap::host_address(adr);
        vmsvc_early_hwdtrap_desc_t *vmsvc = reinterpret_cast<vmsvc_early_hwdtrap_desc_t *>(ptr);
        O3::decode_pc_t             decoded_pc;

        fflush(stdout); // Ensure all stdout appears before terminating.

        O3::decode_pc(vmsvc->ip, decoded_pc);
        dialog::print("Kernel.HwdTrap invoked before bootstrap complete.\n");
        dialog::print("  Data: %xH  (%p)\n", adr, ptr);
        dialog::print("   TRAP: %xH\n", vmsvc->trap);
        dialog::print("   IP  : %s\n", decoded_pc);
        dialog::print("   CR2 : %xH\n", vmsvc->cr2);
        dialog::print("   SFP : %xH\n", vmsvc->sfp);

        dialog::fatal(__func__);
    }
}

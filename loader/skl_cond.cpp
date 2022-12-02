/* Copyright (c) 2021, 2022 Logic Magicians Software */

#include "config.h"
#include "dialog.h"
#include "md.h"
#include "skl_flags.h"
#include "skl_cond.h"

namespace skl {
    typedef enum opc_t {
#define OPC(_t) OPC_##_t,
#include "skl_cond_opc.h"
#undef OPC
        N_OPCODES
    } opc_t;

    static const char *mne[N_OPCODES] = {
#define OPC(_t) #_t,
#include "skl_cond_opc.h"
#undef OPC
    };


    struct skl_conditional_set_t : skl::instruction_t {
        int Rd;
        int R0;

        skl_conditional_set_t(md::OADDR    pc_,
                              md::OINST    inst_,
                              const char **mne_) :
            skl::instruction_t(pc_, inst_, mne_),
            Rd(field(inst, 25, 21)),
            R0(field(inst, 20, 16))
        {
        }


        void epilog(skl::cpu_t *cpu, bool value, md::uint32 R0v)
        {
            write_integer_register(cpu, Rd, value);
            increment_pc(cpu, 1);
            dialog::trace("%xH: %s  R%u, R%u  [%xH, %u]\n",
                          cpu->pc, mne, R0, Rd, R0v, value);
        }
    };


    struct skl_seq_t : skl::skl_conditional_set_t {
        skl_seq_t(md::OADDR pc_, md::OINST inst_, const char **mne_) :
            skl::skl_conditional_set_t(pc_, inst_, mne_)
        {
        }


        virtual void interpret(skl::cpu_t *cpu)
        {
            md::uint32 R0v   = read_integer_register(cpu, R0);
            bool       value = relation_eq(R0v);

            epilog(cpu, value, R0v);
        }
    };


    struct skl_sge_t : skl::skl_conditional_set_t {
        skl_sge_t(md::OADDR pc_, md::OINST inst_, const char **mne_) :
            skl::skl_conditional_set_t(pc_, inst_, mne_)
        {
        }


        virtual void interpret(skl::cpu_t *cpu)
        {
            md::uint32 R0v   = read_integer_register(cpu, R0);
            bool       value = relation_ge(R0v);

            epilog(cpu, value, R0v);
        }
    };


    struct skl_sgeu_t : skl::skl_conditional_set_t {
        skl_sgeu_t(md::OADDR pc_, md::OINST inst_, const char **mne_) :
            skl::skl_conditional_set_t(pc_, inst_, mne_)
        {
        }


        virtual void interpret(skl::cpu_t *cpu)
        {
            md::uint32 R0v   = read_integer_register(cpu, R0);
            bool       value = relation_geu(R0v);

            epilog(cpu, value, R0v);
        }
    };


    struct skl_sgt_t : skl::skl_conditional_set_t {
        skl_sgt_t(md::OADDR pc_, md::OINST inst_, const char **mne_) :
            skl::skl_conditional_set_t(pc_, inst_, mne_)
        {
        }


        virtual void interpret(skl::cpu_t *cpu)
        {
            md::uint32 R0v   = read_integer_register(cpu, R0);
            bool       value = relation_gt(R0v);

            epilog(cpu, value, R0v);
        }
    };


    struct skl_sgtu_t : skl::skl_conditional_set_t {
        skl_sgtu_t(md::OADDR pc_, md::OINST inst_, const char **mne_) :
            skl::skl_conditional_set_t(pc_, inst_, mne_)
        {
        }


        virtual void interpret(skl::cpu_t *cpu)
        {
            md::uint32 R0v   = read_integer_register(cpu, R0);
            bool       value = relation_gtu(R0v);

            epilog(cpu, value, R0v);
        }
    };


    struct skl_sle_t : skl::skl_conditional_set_t {
        skl_sle_t(md::OADDR pc_, md::OINST inst_, const char **mne_) :
            skl::skl_conditional_set_t(pc_, inst_, mne_)
        {
        }


        virtual void interpret(skl::cpu_t *cpu)
        {
            md::uint32 R0v   = read_integer_register(cpu, R0);
            bool       value = relation_le(R0v);

            epilog(cpu, value, R0v);
        }
    };


    struct skl_sleu_t : skl::skl_conditional_set_t {
        skl_sleu_t(md::OADDR pc_, md::OINST inst_, const char **mne_) :
            skl::skl_conditional_set_t(pc_, inst_, mne_)
        {
        }


        virtual void interpret(skl::cpu_t *cpu)
        {
            md::uint32 R0v   = read_integer_register(cpu, R0);
            bool       value = relation_leu(R0v);

            epilog(cpu, value, R0v);
        }
    };


    struct skl_slt_t : skl::skl_conditional_set_t {
        skl_slt_t(md::OADDR pc_, md::OINST inst_, const char **mne_) :
            skl::skl_conditional_set_t(pc_, inst_, mne_)
        {
        }


        virtual void interpret(skl::cpu_t *cpu)
        {
            md::uint32 R0v   = read_integer_register(cpu, R0);
            bool       value = relation_lt(R0v);

            epilog(cpu, value, R0v);
        }
    };


    struct skl_sltu_t : skl::skl_conditional_set_t {
        skl_sltu_t(md::OADDR pc_, md::OINST inst_, const char **mne_) :
            skl::skl_conditional_set_t(pc_, inst_, mne_)
        {
        }


        virtual void interpret(skl::cpu_t *cpu)
        {
            md::uint32 R0v   = read_integer_register(cpu, R0);
            bool       value = relation_ltu(R0v);

            epilog(cpu, value, R0v);
        }
    };


    struct skl_sne_t : skl::skl_conditional_set_t {
        skl_sne_t(md::OADDR pc_, md::OINST inst_, const char **mne_) :
            skl::skl_conditional_set_t(pc_, inst_, mne_)
        {
        }


        virtual void interpret(skl::cpu_t *cpu)
        {
            md::uint32 R0v   = read_integer_register(cpu, R0);
            bool       value = relation_ne(R0v);

            epilog(cpu, value, R0v);
        }
    };


    skl::instruction_t *
    op_conditional_set(cpu_t *cpu, md::OINST inst)
    {

        opc_t opc = static_cast<opc_t>(field(inst, 4, 0));

        switch (opc) {
        case OPC_SEQ:  return new skl_seq_t(cpu->pc, inst, mne);
        case OPC_SGE:  return new skl_sge_t(cpu->pc, inst, mne);
        case OPC_SGEU: return new skl_sgeu_t(cpu->pc, inst, mne);
        case OPC_SGT:  return new skl_sgt_t(cpu->pc, inst, mne);
        case OPC_SGTU: return new skl_sgtu_t(cpu->pc, inst, mne);
        case OPC_SLE:  return new skl_sle_t(cpu->pc, inst, mne);
        case OPC_SLEU: return new skl_sleu_t(cpu->pc, inst, mne);
        case OPC_SLT:  return new skl_slt_t(cpu->pc, inst, mne);
        case OPC_SLTU: return new skl_sltu_t(cpu->pc, inst, mne);
        case OPC_SNE:  return new skl_sne_t(cpu->pc, inst, mne);
        default:       dialog::internal_error("%s: improper opcode", __func__);
        }
    }
}

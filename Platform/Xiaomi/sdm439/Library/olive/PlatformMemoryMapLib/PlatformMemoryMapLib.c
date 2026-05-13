#include <Library/BaseLib.h>
#include <Library/PlatformMemoryMapLib.h>

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
    /* Name               Address     Length      HobOption        ResourceAttribute    ArmAttributes
                                                          ResourceType          MemoryType */

    /* DDR Regions - Total 3GB (0xC0000000) */
    {"RAM Partition",     0x80000000, 0x00200000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    {"HLOS 1",            0x80200000, 0x05E00000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"Hypervisor",        0x86000000, 0x00600000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, NS_DEVICE},
    {"SMEM",              0x86600000, 0x00200000, AddMem, MEM_RES, WRITE_COMBINEABLE, Reserv, UNCACHED_UNBUFFERED},
    {"TZ",                0x86800000, 0x00B00000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, NS_DEVICE},
    {"TZApps",            0x87300000, 0x00E00000, NoHob,  SYS_MEM, SYS_MEM_CAP, Reserv, NS_DEVICE},
    {"MPSS_EFS",          0x88100000, 0x00200000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"PIL_REGION",        0x8AB00000, 0x04000000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"Display Reserved",  0x90000000, 0x01400000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_THROUGH_XN},
    {"Runtime Data",      0x91400000, 0x00080000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, WRITE_BACK_XN},
    {"Runtime Code",      0x91480000, 0x00080000, AddMem, SYS_MEM, SYS_MEM_CAP, RtCode, WRITE_BACK_XN},
    {"HLOS 2",            0x91500000, 0x0D800000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    {"DBI Dump",          0x9ED00000, 0x000D0000, NoHob,  MMAP_IO, INITIALIZED, Reserv, UNCACHED_UNBUFFERED_XN},
    {"FV Region",         0x9F800000, 0x00800000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"CPU Vectors",       0x9FF80000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"MMU PageTables",    0x9FF81000, 0x0000F000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"UEFI Stack",        0x9FF90000, 0x00040000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"SEC Heap",          0x9FFD0000, 0x00020000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"HLOS 3",            0xA0000000, 0xA0000000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    {"HLOS 4",            0x9FC00000, 0x00200000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},

    // Note: Runtime memory has to be on an alignment of 0x10000
    {"RSRV1",             0x9FFB0000, 0x00010000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"TPMControl",        0x9FFC0000, 0x00003000, AddMem, MEM_RES, WRITE_COMBINEABLE, Reserv, UNCACHED_UNBUFFERED_XN},
    {"Reset Data",        0x9FFC3000, 0x00004000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"RSRV3",             0x9FFC7000, 0x00009000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Capsule Header",    0x9FFD0000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"RSRV2",             0x9FFD1000, 0x00014000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Log Buffer",        0x9FFF7000, 0x00008000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Info Blk",          0x9FFFF000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},

    {"DXE Heap",          0xA0000000, 0x1E000000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    {"UEFI FD",           0x80200000, 0x00800000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"IMEM Base",         0x08600000, 0x00001000, NoHob,  MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"IMEM Cookie Base",  0x08601000, 0x00001000, AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"QDSS_STM",          0x01600000, 0x00100000, AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},

    /* Register regions - Endereços Reais SDM439 */
    {"BOOT_CONFIG",       0x00070000, 0x00010000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"GCC CLK CTL",       0x01800000, 0x00080000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"RPM MSG RAM",       0x00060000, 0x00008000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"SECURITY CONTROL",  0x00780000, 0x00007000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"PRNG_CFG_PRNG",     0x000E3000, 0x00001000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"MPM2_SLP_CNTR",     0x004A3000, 0x00001000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"MPM2_TSENS0",       0x004A8000, 0x00001000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"MPM2_PSHOLD",       0x004AB000, 0x00001000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"A1_NOC",            0x00500000, 0x00010000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"CRYPTO0 CRYPTO",    0x00700000, 0x00040000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"TCSR_TCSR_REGS",    0x01937000, 0x00008000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"USB30_PRIM",        0x07000000, 0x00200000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"SDCC1_ICE",         0x07808000, 0x00008000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"SDCC1_SDCC",        0x07800000, 0x00008000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"SDCC2_SDCC",        0x07840000, 0x00008000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"TLMM",              0x01000000, 0x00300000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"GIC_DIST",          0x0B000000, 0x00001000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"TLMM CSR",          0x01000000, 0x00300000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"GPMU_DRAM",         0x05026000, 0x00002000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"GPMU_BLOCK0",       0x0502A000, 0x00002000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"GPU_ISENSE",        0x05030000, 0x00002000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"GPUCC",             0x05065000, 0x00009000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"QDSS_QDSS",         0x01600000, 0x00100000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"PMIC ARB SPMI",     0x02000000, 0x01000000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"USB30_PRIM",        0x07000000, 0x00200000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"PERIPH_SS",         0x0B000000, 0x00200000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"MMSS",              0x01A00000, 0x00800000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"APCS_CC",           0x0B011000, 0x00010000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"QTIMER",            0x0B120000, 0x00010000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"GIC_DIST",          0x0B000000, 0x00001000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"GIC_CPU",           0x0B002000, 0x00002000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"GCC CLK CTL",       0x01800000, 0x00080000,  AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},

    /* Terminator for MMU */
    {"Terminator", 0, 0, 0, 0, 0, 0, 0}};

ARM_MEMORY_REGION_DESCRIPTOR_EX *GetPlatformMemoryMap()
{
  return gDeviceMemoryDescriptorEx;
}

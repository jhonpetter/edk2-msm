#include <Library/BaseLib.h>
#include <Library/PlatformMemoryMapLib.h>

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
    /* Name               Address     Length      HobOption        ResourceAttribute    ArmAttributes
                                                          ResourceType          MemoryType */

    /* --- DDR Bank 1 (1GB): 0x40000000 - 0x80000000 --- */
    {"RAM Bank 1",        0x40000000, 0x40000000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},

    /* --- DDR Bank 2 (2GB): 0x80000000 - 0x100000000 --- */
    {"RAM Partition",     0x80000000, 0x04A00000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},

    /* Reserved firmware regions (from DTS other_ext_region: 0x84A00000, size 0x1D00000) */
    {"Other Ext Region",  0x84A00000, 0x01900000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, NS_DEVICE},
    {"SMEM",              0x86300000, 0x00100000, AddMem, MEM_RES, WRITE_COMBINEABLE, Reserv, UNCACHED_UNBUFFERED},
    {"Other Ext Region 2",0x86400000, 0x00300000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, NS_DEVICE},

    /* UEFI Runtime (in 1MB gap between Other Ext end and Modem, per IOMAN) */
    {"Runtime Data",      0x86700000, 0x00080000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, WRITE_BACK_XN},
    {"Runtime Code",      0x86780000, 0x00080000, AddMem, SYS_MEM, SYS_MEM_CAP, RtCode, WRITE_BACK_XN},

    /* Subsystem firmware regions (from DTS reserved-memory) */
    {"Modem Region",      0x86800000, 0x05500000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, NS_DEVICE},
    {"ADSP FW Region",    0x8BD00000, 0x01800000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, NS_DEVICE},
    {"WCNSS FW Region",   0x8D500000, 0x00700000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, NS_DEVICE},

    /* Free RAM between WCNSS end and Splash */
    {"RAM Partition 2",   0x8DC00000, 0x02400000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},

    /* Display / splash framebuffer (from DTS splash_region) */
    {"Splash Region",     0x90000000, 0x01400000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_THROUGH_XN},

    /* HLOS free memory */
    {"HLOS Region",       0x91400000, 0x0E380000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},

    /* UEFI boot structures (placed before FV Region) */
    {"CPU Vectors",       0x9F780000, 0x00010000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"MMU PageTables",    0x9F790000, 0x00030000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"UEFI Stack",        0x9F7C0000, 0x00040000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},

    /* UEFI FD (BootShim target: must be WRITE_BACK to allow code execution) */
    {"UEFI FD",           0x9F800000, 0x00700000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},

    /* SEC Heap (early PrePi allocation area, follows SDM845 pattern) */
    {"SEC Heap",          0x9FF00000, 0x000D0000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},

    /* UEFI internal structures */
    {"RSRV1",             0x9FFD0000, 0x0000A000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"TPMControl",        0x9FFDA000, 0x00003000, AddMem, MEM_RES, WRITE_COMBINEABLE, Reserv, UNCACHED_UNBUFFERED_XN},
    {"Reset Data",        0x9FFDD000, 0x00004000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"RSRV3",             0x9FFE1000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Capsule Header",    0x9FFE2000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"RSRV2",             0x9FFE3000, 0x00014000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Log Buffer",        0x9FFF7000, 0x00008000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Info Blk",          0x9FFFF000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},

    /* DXE Heap */
    {"DXE Heap",          0xA0000000, 0x2E000000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},

    /* Remaining Bank 2 RAM */
    {"RAM Partition 3",   0xCE000000, 0x32000000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},

    /* MMIO regions */
    {"IMEM Base",         0x08600000, 0x00001000, NoHob,  MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"IMEM Cookie Base",  0x08601000, 0x00001000, AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"QDSS_STM",          0x06000000, 0x01000000, AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},

    /* Register regions - SDM439 Olive IO Devices */
    {"RPM MSG RAM",       0x00060000, 0x00008000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SECURITY CONTROL",  0x000A0000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"PRNG_CFG_PRNG",     0x000E3000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_SLP_CNTR",     0x004A3000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_TSENS0",       0x004A8000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_TSENS0_TM",    0x004A9000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_PSHOLD",       0x004AB000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    /* Disabled: not needed for basic display boot */
    /* {"A1_NOC",            0x00500000, 0x00100000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE}, */
    /* Disabled: not needed for basic display boot */
    /* {"CRYPTO0 CRYPTO",    0x00700000, 0x00040000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE}, */
    {"TCSR_TCSR_REGS",    0x01930000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"TLMM_PINCTRL",      0x01000000, 0x00300000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"GCC_CLK_CTL",       0x01800000, 0x00080000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MDSS_MDP",          0x01A00000, 0x00090000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MDSS_DSI_CTRL0",    0x01A94000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MDSS_DSI_CTRL1",    0x01A96000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MDSS_VBIF",         0x01AB0000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    /* Disabled: camera/GPU/video/IOMMU not needed for basic display boot */
    /* {"CAMSS",             0x01B00000, 0x000A0000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE}, */
    /* {"GPU_KGSL3D0",       0x01C00000, 0x00040000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE}, */
    /* {"GPU_SMMU",          0x01C40000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE}, */
    /* {"VENUS",             0x01DE0000, 0x00004000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE}, */
    /* {"APPS_IOMMU",        0x01E00000, 0x00040000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE}, */
    {"SPMI_CORE",         0x0200F000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SPMI_CHNL",         0x02400000, 0x00800000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SPMI_OBSRVR",       0x02C00000, 0x00800000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SPMI_INTR",         0x03800000, 0x00200000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    /* Disabled: BAM DMA not needed for basic display boot */
    /* {"BAM_DMUX",          0x04044000, 0x00019000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE}, */
    /* Disabled: eMMC ICE not needed for basic display boot */
    /* {"SDCC1_ICE",         0x07803000, 0x00008000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE}, */
    {"SDHC1_eMMC",        0x07824000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SDHC2_SDCARD",      0x07864000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"UART_CONSOLE",      0x078B0000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    /* Disabled: USB not needed for basic display boot */
    /* {"USB2_BAM",          0x078C4000, 0x00017000, AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE}, */
    /* {"USB2_HSUSB_CORE",   0x078DB000, 0x00001000, AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE}, */
    {"QGIC2_GICD",        0x0B000000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"QGIC2_GICC",        0x0B002000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"APCS_C1_RCG",       0x0B011000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"APCS_C0_RCG",       0x0B111000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"APSS_WDT",          0x0B017000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"QTIMER",            0x0B120000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    /* Terminator for MMU */
    {"Terminator", 0, 0, 0, 0, 0, 0, 0}};

ARM_MEMORY_REGION_DESCRIPTOR_EX *GetPlatformMemoryMap()
{
  return gDeviceMemoryDescriptorEx;
}

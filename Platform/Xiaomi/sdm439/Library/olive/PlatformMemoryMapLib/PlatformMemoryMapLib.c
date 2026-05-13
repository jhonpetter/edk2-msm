#include <Library/BaseLib.h>
#include <Library/PlatformMemoryMapLib.h>

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
    /* Name               Address     Length      HobOption        ResourceAttribute    ArmAttributes
                                                          ResourceType          MemoryType */

   /* --- DDR Espaço 1 (1GB) --- */
    {"RAM Bank 1",        0x40000000, 0x40000000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},

    /* --- DDR Espaço 2 (2GB) --- */
    /* Parte inicial da RAM livre */
    {"RAM Partition",     0x80000000, 0x04A00000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    
    /* Regiões de Hardware Separadas (Conforme DTS) */
    {"Other Ext Region",  0x84A00000, 0x01D00000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, NS_DEVICE},
    
    /* UEFI Runtime (Ajustado para o espaço vago em 0x86700000) */
    {"Runtime Data",      0x86700000, 0x00080000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, WRITE_BACK_XN},
    {"Runtime Code",      0x86780000, 0x00080000, AddMem, SYS_MEM, SYS_MEM_CAP, RtCode, WRITE_BACK_XN},
    
    /* Divisão Fiel do Subsistema de Processadores (PIL Separado) */
    {"Modem Region",      0x86800000, 0x05500000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, NS_DEVICE},
    {"ADSP FW Region",    0x8BD00000, 0x01800000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, NS_DEVICE},
    {"WCNSS FW Region",   0x8D500000, 0x00700000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, NS_DEVICE},
    
    /* Memória de Vídeo / Display */
    {"Splash Region",     0x90000000, 0x01400000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_THROUGH_XN},
    
    /* HLOS / Memória Livre do Sistema */
    {"HLOS Region",       0x91400000, 0x0E400000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    
    /* UEFI Firmware & Debug */
    {"FV Region",         0x9F800000, 0x00400000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"DBI Dump",          0x9FC00000, 0x00300000, NoHob,  MMAP_IO, INITIALIZED, Reserv, UNCACHED_UNBUFFERED_XN},
    
    /* Região PStore (Extraído do DTS) */
    {"PStore Region",     0x9FF00000, 0x00100000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, NS_DEVICE},
    
    /* Estruturas Críticas do Processador */
    {"CPU Vectors",       0x9FFC0000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"MMU PageTables",    0x9FFC1000, 0x0000F000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    {"UEFI Stack",        0x9FFD0000, 0x00030000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK_XN},
    // 
    {"RSRV1",             0x9FFD0000, 0x0000A000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"TPMControl",        0x9FFDA000, 0x00003000, AddMem, MEM_RES, WRITE_COMBINEABLE, Reserv, UNCACHED_UNBUFFERED_XN},
    {"Reset Data",        0x9FFDD000, 0x00004000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"RSRV3",             0x9FFE1000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Capsule Header",    0x9FFE2000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, UNCACHED_UNBUFFERED_XN},
    {"RSRV2",             0x9FFE3000, 0x00014000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Log Buffer",        0x9FFF7000, 0x00008000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"Info Blk",          0x9FFFF000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK_XN},
    {"DXE Heap",          0xA0000000, 0x2E000000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK_XN},
    {"UEFI FD",           0xCE000000, 0x02000000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"IMEM Base",         0x08600000, 0x00040000, NoHob,  MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"IMEM Cookie Base",  0x0863F000, 0x00001000, AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    {"QDSS_STM",          0x06000000, 0x01000000, AddDev, MMAP_IO, INITIALIZED, Conv,   NS_DEVICE},
    /* Register regions - SDM439 Olive IO Devices */
    {"BOOT_CONFIG",       0x00060000, 0x00010000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"RPM MSG RAM",       0x00060000, 0x00010000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SECURITY CONTROL",  0x000A0000, 0x00010000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"PRNG_CFG_PRNG",     0x000E3000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_SLP_CNTR",     0x004A3000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_TSENS0",       0x004A8000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_TSENS0_TM",    0x004A9000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MPM2_PSHOLD",       0x004AB000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"A1_NOC",            0x00500000, 0x00100000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"CRYPTO0 CRYPTO",    0x00700000, 0x00040000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"TCSR_TCSR_REGS",    0x01930000, 0x00010000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"TLMM_PINCTRL",      0x01000000, 0x00300000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"GCC_CLK_CTL",       0x01800000, 0x00080000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MDSS_MDP",          0x01A00000, 0x00090000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MDSS_DSI_CTRL0",    0x01A94000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MDSS_DSI_CTRL1",    0x01A96000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"MDSS_VBIF",         0x01AB0000, 0x00010000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"CAMSS",             0x01B00000, 0x000A0000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"GPU_KGSL3D0",       0x01C00000, 0x00040000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"GPU_SMMU",          0x01C40000, 0x00010000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"VENUS",             0x01DE0000, 0x00004000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"APPS_IOMMU",        0x01E00000, 0x00040000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SPMI_CORE",         0x0200F000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SPMI_CHNL",         0x02400000, 0x00800000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SPMI_OBSRVR",       0x02C00000, 0x00800000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SPMI_INTR",         0x03800000, 0x00200000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"BAM_DMUX",          0x04044000, 0x00019000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SDCC1_ICE",         0x07803000, 0x00008000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SDHC1_eMMC",        0x07824000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"SDHC2_SDCARD",      0x07864000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"UART_CONSOLE",      0x078B0000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"USB2_BAM",          0x078C4000, 0x00017000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"USB2_HSUSB_CORE",   0x078DB000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"IMEM Base",         0x08600000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"IMEM Cookie",       0x08601000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"QGIC2_GICD",        0x0B000000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"QGIC2_GICC",        0x0B002000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"APCS_C1_RCG",       0x0B011000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"APCS_C0_RCG",       0x0B111000, 0x00001000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    {"QTIMER",            0x0B120000, 0x00010000,  AddDev, MMAP_IO, UNCACHEABLE, MmIO,   NS_DEVICE},
    /* Terminator for MMU */
    {"Terminator", 0, 0, 0, 0, 0, 0, 0}};

ARM_MEMORY_REGION_DESCRIPTOR_EX *GetPlatformMemoryMap()
{
  return gDeviceMemoryDescriptorEx;
}

## @file
#
#  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.
#  Copyright (c) 2018 - 2019, Bingxing Wang. All rights reserved.
#  Copyright (c) 2022, Xilin Wu. All rights reserved.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################

[Defines]
  SOC_PLATFORM            = SDM439
  USE_PHYSICAL_TIMER      = TRUE

!include Silicon/Qualcomm/QcomPkg/QcomCommonDsc.inc

[PcdsFixedAtBuild.common]
  # A RAM física do SDM439 (Olive) começa em 0x40000000
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x40000000         
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x80000000         # Define o limite inicial (ex: 2GB), expansível via Partitions

  # Vetores e Stack realocados para evitar a zona de memória protegida/pstore
  gArmTokenSpaceGuid.PcdCpuVectorBaseAddress|0x9F88C000     
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|19200000
  gArmTokenSpaceGuid.PcdArmArchTimerSecIntrNum|17
  gArmTokenSpaceGuid.PcdArmArchTimerIntrNum|18
  gArmTokenSpaceGuid.PcdGicDistributorBase|0x17a00000
  gArmTokenSpaceGuid.PcdGicRedistributorsBase|0x17b00000

  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultOemRevision|0x00000439
  gEmbeddedTokenSpaceGuid.PcdPrePiStackBase|0x9F890000      # UEFI Stack alinhada com o Memory Map
  gEmbeddedTokenSpaceGuid.PcdPrePiStackSize|0x00040000      # 256K stack
  gEmbeddedTokenSpaceGuid.PcdPrePiCpuIoSize|44

  # Heap do DXE e Endereço do Framebuffer (Olive utiliza 0x9D400000 para o splash)
  gQcomTokenSpaceGuid.PcdUefiMemPoolBase|0xA0000000         
  gQcomTokenSpaceGuid.PcdUefiMemPoolSize|0x2E000000         
  gQcomTokenSpaceGuid.PcdMipiFrameBufferAddress|0x9D400000

  gArmPlatformTokenSpaceGuid.PcdCoreCount|8
  gArmPlatformTokenSpaceGuid.PcdClusterCount|2

  # SimpleInit
  gSimpleInitTokenSpaceGuid.PcdDeviceTreeStore|0x83300000
  gSimpleInitTokenSpaceGuid.PcdLoggerdUseConsole|FALSE

[LibraryClasses.common]

  # Ported from SurfaceDuoPkg
  PlatformMemoryMapLib|Platform/$(VENDOR_NAME)/sdm439/Library/$(PLATFORM_NAME)/PlatformMemoryMapLib/PlatformMemoryMapLib.inf
  
  PlatformPeiLib|Silicon/Qualcomm/sdm439/Library/PlatformPeiLib/PlatformPeiLib.inf
  PlatformPrePiLib|Silicon/Qualcomm/sdm439/Library/PlatformPrePiLib/PlatformPrePiLib.inf
  AslUpdateLib|Silicon/Qualcomm/QcomPkg/Library/DxeAslUpdateLib/DxeAslUpdateLib.inf
  MsPlatformDevicesLib|Silicon/Qualcomm/sdm439/Library/MsPlatformDevicesLib/MsPlatformDevicesLib.inf
  SOCSmbiosInfoLib|Silicon/Qualcomm/sdm439/Library/SOCSmbiosInfoLib/SOCSmbiosInfoLib.inf

[Components.common]
  Platform/EFI_Binaries/Applications/LinuxSimpleMassStorage/LinuxSimpleMassStorage.inf

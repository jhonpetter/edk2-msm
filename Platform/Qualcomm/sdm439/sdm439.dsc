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
  # Physical RAM base and size (Bank 2: 2GB)
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x80000000

  # GIC addresses (from DTS interrupt-controller@b000000)
  gArmTokenSpaceGuid.PcdGicDistributorBase|0x0b000000
  gArmTokenSpaceGuid.PcdGicInterruptInterfaceBase|0x0b002000
  gArmTokenSpaceGuid.PcdCpuVectorBaseAddress|0x9FF8C000
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|19200000
  gArmTokenSpaceGuid.PcdArmArchTimerSecIntrNum|17
  gArmTokenSpaceGuid.PcdArmArchTimerIntrNum|18
  gArmTokenSpaceGuid.PcdGicRedistributorsBase|0x0b002000

  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultOemRevision|0x00000439
  gEmbeddedTokenSpaceGuid.PcdPrePiStackBase|0x9FF90000
  gEmbeddedTokenSpaceGuid.PcdPrePiStackSize|0x00040000
  gEmbeddedTokenSpaceGuid.PcdPrePiCpuIoSize|44

  # DXE Heap and Framebuffer
  gQcomTokenSpaceGuid.PcdUefiMemPoolBase|0xA0000000
  gQcomTokenSpaceGuid.PcdUefiMemPoolSize|0x2E000000
  gQcomTokenSpaceGuid.PcdMipiFrameBufferAddress|0x90000000

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

#function platform_build_bootimg(){
#	abootimg \
#		--create "${OUTDIR}/boot-${DEVICE}${EXT}.img" \
#		-k "${WORKSPACE}/uefi-${DEVICE}-kernel" -r ramdisk \
#		||return "$?"
#}
function platform_build_bootimg(){
		mkbootimg \
		--kernel "${WORKSPACE}/uefi-${DEVICE}-kernel" \
		--ramdisk ramdisk \
		--base 0x80000000 \
		--pagesize 2048 \
		--kernel_offset 0x00000000 \
		--ramdisk_offset 0x01000000 \
		--tags_offset 0x00000100 \
		--os_version "${BOOTIMG_OS_VERSION}" \
		--os_patch_level "${BOOTIMG_OS_PATCH_LEVEL}" \
		--header_version "${BOOTIMG_HEADER_VERSION}" \
		-o "${OUTDIR}/boot-${DEVICE}${EXT}.img" \
		||return "$?"
}
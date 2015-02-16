
/*++

Copyright (c) Rocket Division Software 2001-2008. All rights reserved.

Module Name:

    StarBurn.h

Abstract:

    CD/DVD/Blu-Ray/HD-DVD Burning, Grabbing and Mastering Toolkit main user header.

Author:

    Anton A. Kolomyeytsev

    Alexey Popov

	Trubetskoy Andrey

Environment:

    Windows 95/98/ME/NT/2K/XP/2003/Vista/Longhorn UserMode only

Notes:

Known bugs/Illegal behavior:

ToDo:

Revision/Development History:

    2002-01-14 : * Project restarted "from the scratch".

    2003-07-14 : * StarBurn_UDF_Destory() changed to StarBurn_UDF_Destroy().

    2003-07-15 : * StarBurn_UDF_Create() now accepts extra parameter for AUDIO_TS root.

    2003-07-28 : * StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromFile() and StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFile() added.
               :
               : * EN_NOT_IMPLEMENTED added.

    2003-07-31 : * Level2 support added for names generation.

    2003-08-01 : * DEVICES_PER_BUS increased from 15 to 63 to support badly written virtual CD/DVD/Blu-Ray/HD-DVD devices.

    2003-09-15 : * DAO_DISC_LAYOUT_ENTRY and DAO_DISC_LAYOUT added.

    2003-09-21 : * DAO_DISC_LAYOUT_ENTRY extended with m__LONG__TrackStartingLBA member.

    2003-09-29 : * StarBurn_UDF_Create(...) extended to accept volume label.

    2003-10-27 : * CN_BUFFER_UNDERRUN added.

    2003-11-04 : * Added call-back notification CN_FILE_TREE_PROGRESS_NAME_COLLISION.
               :
               : * Added enumeration NAME_COLLISION_SOLUTION.
               :
               : * Added structure NAME_COLLISION_INFO.

    2003-11-26 : * DAO_DISC_LAYOUT entry extended with m__BOOLEAN__IsRawTrack member.

	2004-02-28 : * Rocket Division Software port.

	2004-03-01 : * StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromFile() updated to support sub-channel repair.

	2004-08-25 : * StarBurn API extended with some node information gettinf routines.

	2004-09-01 : * Added function StarBurn_CdvdBurnerGrabber_SetCDTextItem(...).
	           :
	           : * Added function StarBurn_ISO9660JolietFileTree_GetFullPath.
	           :
	           : * Added enumeration ISO9660_KIDTYPE.

	2004-09-10 : * StarBurn_CdvdBurnerGrabber_TestUnitReadyEx() added.

	2004-10-07 : * StarBurn_CdvdBurnerGrabber_Read10() added.

	2004-10-17 : * StarBurn_GetDVDPadding() and StarBurn_SetDVDPadding() added.

	2004-10-29 : * Updated BUILD_DATE to match new release date.

	2004-10-30 : * Extended logging constants added.

	2004-11-07 : * StarBurn_CdvdBurnerGrabber_ReadATIP(...) added.

	2004-11-14 : * ASPI_SAFE_BUFFER_SIZE_IN_UCHARS and DVD_ECC_BLOCK_SIZE_IN_UCHARS and DVD_ECC_BLOCK_SIZE_IN_LBS added or moved to public 
			   : header from private headers.

	2004-11-16 : * CACHE_SIZE_IN_MBS changed from 64 to 160. B/s of the different caching strategies for CD and DVD devices only CD devices 
			   : would use full caching size. DVD devices would use only half of the allocated cache.
			   :
			   : * StarBurn_CdvdBurnerGrabber_DiscBasicInformation_Create(...) and StarBurn_CdvdBurnerGrabber_DiscBasicInformation_Destroy(...)
		       : disc basic information management functions added.

	2004-11-20 : * StarBurn_Memory_Allocate(...) and StarBurn_Memory_Free(...) added.

	2004-11-22 : * New error codes were added.

	2004-11-23 : * New error codes were added.

	2004-11-24 : * READ_FLAG_XXX constants added.

    2004-11-25 : * EN_UNRECOGNIZED_MEDIA error code was added.

	2004-11-27 : * DISC_TYPE_NO_MEDIA media type added.

	2004-12-01 : * DISC_TYPE_DVDPLUSR_DL media type added.

	2004-12-05 : * READ_FLAG_REPAIR_BROKEN_SUB_CHANNEL added.

	2004-12-06 : * Additional medium error codes represented.

	2004-12-15 : * StarBurn_CdvdBurnerGrabber_CreateEx(...) added.

	2004-12-19 : * READ_FLAG_NEED_TRUE_COOKED, READ_FLAG_NEED_TRUE_RAW, READ_FLAG_NEED_TRUE_RAW_PQ and READ_FLAG_NEED_TRUE_RAW_RAW_PW added.

	2004-12-20 : * StarBurn_CdvdBurnerGrabber_ReadCD(...) and StarBurn_CdvdBurnerGrabber_Read(...) prototypes changed.

	2004-12-22 : * EN_UNSUPPORTED_READ_MODE added.

	2004-12-29 : * READ_FLAG_DO_NOT_RECOVER added.

	2005-01-10 : * TYPE_CODE_XXX definitions added.
		   	   :
		   	   : * StarBurn_CdvdBurnerGrabber_GetRPC(...) added.

	2005-01-21 : * EN_FULL_ERASE_REQUIRED exception number added.

	2005-01-27 : * Added enumeration NAME_COLLISION_SOLUTION.

	2005-01-28 : * CN_CDVD_READ_CANCEL_QUERY added.

	2005-02-01 : * StarBurn_CdvdBurnerGrabber_VideoCDExEx(...) and StarBurn_CdvdBurnerGrabber_SuperVideoCDExEx(...) added. 
	           :
			   : * Added new parameter p__PPVOID__ISO9660JolietFileTreeNode__NewChild to functions StarBurn_ISO9660JolietFileTree_AddMemory(...)
			   : and StarBurn_ISO9660JolietFileTree_Add(...).

	2005-02-02 : * Added new parameter p__UCHAR__SectorsToLoad to the function StarBurn_ISO9660JolietFileTree_SetBootImage(...). Default value 
			   : should be one.

	2005-02-09 : * Added new parameter p__BOOLEAN__HideNode to StarBurn_ISO9660JolietFileTree_SetBootImage(...).

	2005-02-10 : * CN_DVDRW_QUICK_FORMAT_BEGIN and CN_DVDRW_QUICK_FORMAT_END added.

	2005-02-16 : * TRACK_INFORMATION structure updated. Now we show fixed packet size in LBs (logical blocks) and not in UCHARs as it was.

	2005-02-17 : * DVD single and dual layer default capacity sizes in logical blocks added.
			   :
			   : * DVD_SPEED_IN_KBPS_XXX constants added.	

	2005-02-18 : * Added functions: StarBurn_UDF_Add, StarBurn_UDF_GetNodeObject, StarBurn_UDF_DestroyNodeAndKids.

	2005-02-19 : * Changed structure UDF_TREE_ITEM:
			   :
	           : - m__UCHAR__FileIdentifierDescriptor
			   : - m__UCHAR__FileIdentifierDescriptorParent
			   :
			   : + m__PUCHAR__FileIdentifierDescriptor
			   : + m__ULONG__FileIdentifierDescriptorSizeInUCHARs

	2005-02-21 : * Removed some parameters from StarBurn_UDF_Create(...).

	2005-02-22 : * Version change to 5.2.22.

	2005-03-02 : * StarBurn_CdvdBurnerGrabber_CreateExEx(...) added.

	2005-03-04 : * StarBurn_CdvdBurnerGrabber_CreateExEx(...) updated. Now we accept pointer to wide chars of device name and not single
			   : char of drive letter and do accept additional BOOLEAN parameter for exclusive or shared access flag.
			   :
			   : * StarBurn_CdvdBurnerGrabber_Read(...), StarBurn_CdvdBurnerGrabber_ReadCD(...) and StarBurn_CdvdBurnerGrabber_Read10(...) got
			   : extra paramete - pointer to execution time.
			   :
			   : * All profiling-related floating point math removed and replaced with 64-bit integers math.

	2005-04-17 : * Some of the undocumented function prototypes and secret flags removed from this public header to secret one.

	2005-04-18 : * StarBurn_CdvdBurnerGrabber_GetLastTrack(...) API call added.

	2005-04-22 : * CN_CDVD_DPM_XXX callbacks added.

	2005-05-17 : * StarBurn_GetAudioFileStreamSizeInUCHARs(...) API call added.
			   :
			   : * Version change to 5.5.17.

	2005-05-26 : * Version change to 5.5.26.

	2005-05-27 : * StarBurn_CdvdBurnerGrabber_Verify(...) API call added.
			   :
			   : * CN_CDVD_VERIFY_PROGRESS callback added.
			   :
			   : * EN_VERIFY_FAILED status code added.

	2005-05-29 : * StarBurn_CdvdBurnerGrabber_Verify(...) renamed to StarBurn_CdvdBurnerGrabber_VerifyTree(...).
			   :
			   : * StarBurn_CdvdBurnerGrabber_VerifyFile(...) API call added.
			   :
			   : * StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipeEx(...) API call added.
			   :
			   : * StarBurn_ISO9660FileTree_AddEx(...) API call added.	

	2005-05-31 : * StarBurn_CdvdBurnerGrabber_TrackAtOnceFromMemory(...) API call added.

	2005-06-04 : * StarBurn_CdvdBurnerGrabber_ExecuteGeneric(...) API call added.

	2005-06-05 : * EN_DPM_FAILED added.

	2005-06-07 : * StarBurn_SetEjectAfterFail(...) and StarBurn_GetEjectAfterFail(...) API calls added.
			   :
			   : * StarBurn_SetBufferUnderrunTimeOutInMs(...) and StarBurn_GetBufferUnderrunTimeOutInMs(...) added.

	2005-06-20 : * CN_SAO_TRACK_WRITE_BEGIN and CN_SAO_TRACK_WRITE_END callbacks added.

	2005-06-26 : * StarBurn_GetDVDPLUSRDLCompatibleMode(...) and StarBurn_SetDVDPLUSRDLCompatibleMode(...) declared.

	2005-08-01 : * EN_DEVICE_SHARING_VIOLATION added.
			   :	 
	           : * StarBurn_CdvdBurnerGrabber_TestUnitReadyExEx(...) added.

	2005-08-12 : * StarBurn_CdvdBurnerGrabber_GetMediaTrayStatus(...) added.

	2005-08-24 : * StarBurn_CdvdBurnerGrabber_StopPlayScan(...) added.

	2005-10-02 : * StarBurn_GetDeviceTimeOutByDeviceAddress(...) and StarBurn_SetDeviceTimeOutByDeviceAddress(...) API calls added.

	2005-10-13 : * DAO_DISC_LAYOUT_ENTRY extended with m__BOOLEAN__IsAudioExTrack member. Data structure size changed. 

	2005-10-21 : * StarBurn_SetFastReadTOC(...) and StarBurn_GetFastReadTOC(...) API calls added. Now users can select from
			   : "fast" and "accurate" TOC formatting.

	2005-10-25 : * StarBurn_CdvdBurnerGrabber_SetReadSpeed(...) API call added. Now we do work with broken devices incapable
			   : of ignoring write speed and ending number of logical blocks to process for DVD passed.

	2005-11-01 : * StarBurn_UDF_Create(...) extended with new parameters and renamed to StarBurn_UDF_CreateEx(...).
			   :
			   : * StarBurn_GetId(...) implemented.
			   :
			   : * DISC_TYPE_XXX constants renamed to STARBURN_DISC_TYPE_XXX not to confuse the users with enum DISC_TYPE members.	
			                                                                                                       
	2005-11-18 : * StarBurn_CdvdBurnerGrabber_VerifyTreeEx(...) API call and DEFAULT_NUMBER_OF_VERIFY_READ_RETRIES define added.

	2005-11-22 : * StarBurn_DVDVideo_Create(...), StarBurn_DVDVideo_Destroy(...), StarBurn_DVDVideo_SeekToBegin(...), StarBurn_DVDVideo_Read(...)
			   : and StarBurn_DVDVideo_GetSizeInUCHARs(...) API calls added. Now DVD-Video compilation process should be automated.

	2005-11-23 : * StarBurn_UDF_PatchXxx API calls removed from public header as they seems to be a source of problems with improper use.
			   :
			   : * StarBurn_DVDVideo_GetTreePointer(...) API call added.	

	2005-11-28 : * StarBurn_ISO9660JolietFileTree_GetNamesEx(...) API call added. Now we can get file system dependent names.

	2005-12-30 : * StarBurn_SetIsCollisionDetectionDisabled(...) and StarBurn_GetIsCollisionDetectionDisabled(...) API calls added.

	2005-12-02 : * Version change to 5.12.2.

	2005-12-18 : * StarBurn_CorrectISO9660Name(...) and StarBurn_CorrectJolietName(...) moved here from samples.

	2005-12-19 : * StarWave API calls and types overwrapped here. Now there's no need in StarWave.h header and some of it's
			   : COM-related and StarWave initialization/deinitalization calls.
			   :
			   : * DISC_BASIC_INFORMATION management API calls moved from here to private header.
			   :
			   : * All of the new and existing code gets documented.		

	2006-01-18 : * StarBurn_GetIsSafeGrabbingEnabled(...) and StarBurn_SetIsSafeGrabbingEnabled(...) API calls added.

	2006-01-20 : * CN_DVD_MEDIA_PADDING_WRITE_PROGRESS callback value added.

	2006-01-24 : * Finally all of the StarBurn_DVDVideo_Xxx API calls were documented.

	2006-01-27 : * CD+G API calls and types moved from here to "secret" header.
			   :
			   : * Changed DISC_INFORMATION to STARBURN_DISC_INFORMATION as we had collisions with scsi.h DDK header.
			   :
			   : * Changed TRACK_INFORMATION to STARBURN_TRACK_INFORMATION as we had collisions with scsi.h DDK header.

	2006-01-28 : * All of the public API set is fully documented now.

	2006-02-06 : * Version change to 6.2.24.

	2006-02-10 : * Added new and separated CD and DVD speed constants.
			   :
			   : * StarBurn_StarPort_Xxx API and all of the related data types represented.

	2006-05-11 : * StarBurn_StarPort_DeviceAdd(...) renamed to StarBurn_StarPort_DeviceAddLocal(...) and now it deals with local device types only.
			   :
			   : * StarBurn_StarPort_DeviceAddRemote(...) added so now all StarPort and StarWind integration is done.
			   :
			   : * Version change to 6.4.20 applied.

	2006-05-14 : * StarBurn_GetVolumeIDs(...) API call added.
			   :
			   : * StarBurn_CdvdBurnerGrabber_GetNumberOfSystemDescriptors(...) API call added.

	2006-06-01 : * StarBurn_StarPort_GetDeviceLetter(...) API call added.

	2006-06-14 : * StarBurn_StarPort_GetVersion(...) API call added.

	2006-06-20 : * Corrected StarBurn_CdvdBurnerGrabber_DiscBasicInformation_Create(..) to set right last session status (was always COMPLETED) and right leadout LBA.

   	2006-06-24 : * StarBurn_StarPort_GetDeviceInformation(...) API call added.

	2006-06-30 : * Version change to 6.6.30 applied.

	2006-07-19 : * StarBurn_CdvdBurnerGrabber_LoadEx(...) API call added.

	2006-07-21 : * StarBurn_ISO9660JolietFileTree_GetNodeStartingLBA(...) API call added.

	2006-08-01 : * CN_CDVD_WRITE_BEGIN,	CN_CDVD_WRITE_END, CN_CDVD_VERIFY_BEGIN, CN_CDVD_VERIFY_END	callbacks added.

	2006-08-15 : * EN_INVALID_FIELD_IN_CDB exception number added.

	2006-08-26 : * StarBurn_StarPort_GetDeviceSCSIAddress(...) API call added.

	2006-08-29 : * Fixed crash with multisession CDs because of TOC having more raw tracks than tracks array size.

	2006-09-10 : * Version change to 6.10.10 applied.

	2006-10-23 : * Version change to 6.10.30 applied.
			   :
			   : * All version-related stuff removed to the separate StarBurnVersion.h header.
			   :
			   : * DVD-R DL and Blu-Ray constants added to the DISC_TYPE enum.

	2006-10-28 : * StarBurn_CdvdBurnerGrabber_GetMechanicalOptions(...) API call added.
			   :
			   : * STARBURN_LOADING_MECHANISM_TYPE_XXX definitions added.

	2006-11-04 : * Callback parameters documented by Andrew and Anton.

	2006-11-10 : * StarBurn_CdvdBurnerGrabber_ReadLB(...) API call added.

	2006-11-14 : * HD-DVD constants added to DISC_TYPE enum.

	2006-11-15 : * StarBurn_CdvdBurnerGrabber_GetAdvancedSupportedMediaFormats(...) API call added.

    2007-01-22 : * StarBurn_CdvdBurnerGrabber_GetDiscFileSystem(...) API call added.

	2007-02-07 : * StarBurn_CdvdBurnerGrabber_GetNumberOfSystemDescriptors(...) fixed to return LONG instead of EXCEPTION_NUMBER.

	2007-02-07 : * StarBurn_CorrectISO9660Name_Default(...) API call added.

	2007-02-08 : * StarBurn_CorrectJolietName_Default(...) API call added.

	2007-02-17 : * Definitions related to SCSI_OPCODE_READ_CD moved here from StarBurn_Base.hpp file as now they are public.

	2007-02-18 : * StarBurn_CdvdBurnerGrabber_ReadCooked(...) and StarBurn_CdvdBurnerGrabber_ReadRaw(...) API calls added.

	2007-03-05 : * StarBurn_CdvdBurnerGrabber_CreateExEx(...) documented.
			   :
			   : * Some minor declarations and code samples fixes.

	2007-04-03 : * Version change to 7.6.30 applied.

	2007-04-16 : * StarBurn_ISO9660JolietFileTree_SetBootImageEx(...) API call added. 

	2007-04-17 : * HARD_DISK_LB_SIZE_IN_UCHARS definition added.

	2007-05-11 : * StarBurn_CdvdBurnerGrabber_GetDiscFreeSpace(...) API call added. Added by Trubetskoy Andrey.

	2007-05-14 : * StarBurn_CdvdBurnerGrabber_IsDiscBlank(...) API call added. Added by Trubetskoy Andrey.

	2007-05-28 : * StarBurn_StarWave2_EncodeMP3OGGFromWAV(...) API call added. Added by Trubetskoy Andrey.

	2007-07-23 : * Version change to 9 applied.

	2007-10-20 : * StarBurn_CreatePipe(...), StarBurn_DestroyPipe(...) and STARBURN_PIPE_SIZE_IN_UCHARS API calls and definition added.

	2007-10-21 : * STARBURN_ISO9660_FILE_MAX_SIZE_IN_UCHARS definition added.

	2007-10-29 : * STARBURN_BDRE_FORMAT_XXX definitions, structures and StarBurn_CdvdBurnerGrabber_BluRayXxx(...) API calls added.

	2007-11-04 : * StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFileEx(...) implemented to support variable AudioCD track-to-track pause length.

	2007-11-11 : * StarBurn_CdvdBurnerGrabber_TrackAtOnceFromMemoryEx(...) implemented to support variable AudioCD track-to-track pause length.

	2007-12-09 : * STARBURN_DVD_VIDEO_MAX_NUMBER_OF_TITLES definition added.

	2008-02-11 : * StarBurn_GetIs64KBIO(...) and StarBurn_SetIs64KBIO(...) API calls added.

	2008-02-20 : * UDF2 API wrappers and all related definitions and types added.

	2008-03-03 : * STARBURN_UDF_OS_CLASS_XXX definitions added.

	2008-04-03 : * STARBURN_TRACK_INFORMATION_EX definition and StarBurn_CdvdBurnerGrabber_GetTrackInformationEx API call added.	

	2008-06-30 : * StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFileAudioUnicode(...) API call added.

	2008-07-13 : * StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFileAudioUnicode(...) API call added. 
			   :
			   : * DAO_DISC_LAYOUT and DAO_DISC_LAYOUT_ENTRY structures changed to allow Unicode names for the tracks.

--*/


//
// Define this file __STARBURN_H__ (begin)
//

#ifndef __STARBURN_H__

#define __STARBURN_H__ // Define StarBurn.h to avoid including it more then once


//
// Own includes (begin)
//
    

#include <time.h> 	// Time handling routines from C runtime library

#include <stdio.h>	// Generic I/O


//
// Own includes (end)
//


//
// Have to put exported function bodies in this block to avoid possible C++ name mangling
//

#ifdef __cplusplus

extern "C" {

#endif


//
// Own definitions and macros (begin)
//


#define STARBURN_IMPEX_API


#ifdef STARBURN_DYNAMIC


#undef STARBURN_IMPEX_API

#define STARBURN_IMPEX_API __declspec( dllimport )


#endif // STARBURN_DYNAMIC


#ifdef STARBURN_DYNLINK


#undef STARBURN_IMPEX_API

#define STARBURN_IMPEX_API __declspec( dllexport )


#endif // STARBURN_DYNAMIC


//
// Default cache size for I/O operations
//

#define STARBURN_CACHE_SIZE_READ_ONLY 				1

#define STARBURN_CACHE_SIZE_READ_WRITE 				0


//
// Default pipe size in UCHAR(s)
//

#define STARBURN_PIPE_SIZE_IN_UCHARS				( 60 * 64 * 1024 )	// 60, 64 or 32 KB I/O packets


//
// ISO9660/Joliet largest supported file size in UCHAR(s)
//

#define STARBURN_ISO9660_FILE_MAX_SIZE_IN_UCHARS	( LONGLONG )( 0xFFFFFFFF ) // ( 4GB - 1 )


//
// Loading mechanism type constants 
//

#define STARBURN_LOADING_MECHANISM_TYPE_CADDY		0x00	

#define STARBURN_LOADING_MECHANISM_TYPE_TRAY		0x01

#define STARBURN_LOADING_MECHANISM_TYPE_POP_UP		0x02

#define STARBURN_LOADING_MECHANISM_TYPE_RESERVED1	0x03

#define STARBURN_LOADING_MECHANISM_TYPE_CHANGER		0x04

#define STARBURN_LOADING_MECHANISM_TYPE_CARTRIDGE	0x05

#define STARBURN_LOADING_MECHANISM_TYPE_RESERVED2	0x06

#define STARBURN_LOADING_MECHANISM_TYPE_RESERVED3	0x07


//
// Expected LB type for SCSI_OPCODE_READ_CD
//

#define EXPECTED_LB_TYPE_ANY                        0x00    // Accept all LBs

#define EXPECTED_LB_TYPE_CDDA                       0x01    // Accept only CDDA (CD digital audio) LBs

#define EXPECTED_LB_TYPE_MODE1                      0x02    // Accept only MODE1 LBs

#define EXPECTED_LB_TYPE_MODE2                      0x03    // Accept only MODE2 LBs (both Form1 and Form2)

#define EXPECTED_LB_TYPE_MODE2_FORM1                0x04    // Accept only MODE2 Form1 LBs

#define EXPECTED_LB_TYPE_MODE2_FORM2                0x05    // Accept only MODE2 Form2 LBs


//
// Header codes for SCSI_OPCODE_READ_CD
//

#define HEADER_CODE_NONE                            0x00    // No header

#define HEADER_CODE_HEADER_ONLY                     0x01    // 4-byte header

#define HEADER_CODE_SUBHEADER_ONLY                  0x02    // MODE2 Form1 or Form2 subheader

#define HEADER_CODE_ALL_HEADERS                     0x03    // Both header and subheader


//
// Error field for SCSI_OPCODE_READ_CD
//

#define ERROR_FIELD_NO_ERROR                        0x00    // No error information

#define ERROR_FIELD_C2_ERROR                        0x01    // C2 error information

#define ERROR_FIELD_C2_AND_BLOCK_ERROR              0x02    // C2 and block error information

#define ERROR_FIELD_RESERVED                        0x03    // Reserved


//
// Sub-channel selection for SCSI_OPCODE_READ_CD
//

#define SUBCHANNEL_NO                               0x00    // No sub-channel

#define SUBCHANNEL_RAW_PW                           0x01    // RAW P-W sub-channel

#define SUBCHANNEL_PQ                               0x02    // PQ sub-channel

#define SUBCHANNEL_RESERVED                         0x03    // Reserved

#define SUBCHANNEL_RW                               0x04    // R-W sub-channel


//
// StarPort device name size in UCHARs
//

#define STARPORT_DEVICE_NAME_SIZE_IN_UCHARS			1024


//
// Default number of read retries during verification process
//

#define DEFAULT_NUMBER_OF_VERIFY_READ_RETRIES		10


//
// Small page size in UCHARs on x86 machines (default allocatable storage)
//

#define PAGE_SIZE_IN_UCHARS                         4096


//
// ASPI safe buffer size in UCHARs. ASPI is assumed to support at least 64KB large transfer per time. 64KB - PAGE_SIZE_IN_UCHARS
// was old default value. Now we'll use DVD_ECC_BLOCK_SIZE_IN_UCHARS as it's smaller and produce better results when dealing with DVD media
//

#define ASPI_SAFE_BUFFER_SIZE_IN_UCHARS             65536


//
// StarWave recommended I/O buffer size in UCHARs. It's *STRONGLY* recommended to use either it or multiplications of
// STARWAVE_IO_BUFFER_SIZE_IN_UCHARS as internal calculations and indexations are integer rather then float based 
//

#define STARBURN_STARWAVE_IO_BUFFER_SIZE_IN_UCHARS	( 44100 * 2 * 2 )


//
// DVD ECC block size in UCHARs. This is true "hardware" logical block size on DVD. It's recommended to have transfers of
// this size and this size aligned
//

#define DVD_ECC_BLOCK_SIZE_IN_UCHARS				32768


//
// DVD ECC block size in logical blocks (2048 UCHARs each)
//

#define DVD_ECC_BLOCK_SIZE_IN_LBS					16


//
// StarBurn smallest split file size in megabytes
//

#define STARBURN_SMALLEST_SPLIT_FILE_SIZE_IN_MBS	200


//
// Default cache size in MBs that toolkit will allocate to buffer I/O operations
//

#define CACHE_SIZE_IN_MBS                           160 // 64


//
// Top number of SCSI devices per logical SCSI bus (was 15 originally)
//

#define DEVICES_PER_BUS                             63


//
// SCSI disk device
//

#define SCSI_DEVICE_DIRECT_ACCESS                   0x00


//
// SCSI tape device
//

#define SCSI_DEVICE_SEQUENTIAL_ACCESS               0x01


//
// SCSI printer device
//

#define SCSI_DEVICE_PRINTER                         0x02


//
// SCSI processor device
//

#define SCSI_DEVICE_PROCESSOR                       0x03


//
// SCSI WORM (Write-Once-Read-Multiple) device
//

#define SCSI_DEVICE_WORM                            0x04


//
// SCSI CD/DVD/Blu-Ray/HD-DVD device
//

#define SCSI_DEVICE_RO_DIRECT_ACCESS                0x05


//
// SCSI scanner device
//

#define SCSI_DEVICE_SCANNER                         0x06


//
// SCSI MO (Magneto-Optical) disk device
//

#define SCSI_DEVICE_MAGNETO_OPTICAL                 0x07


//
// SCSI jukebox (disc changer) device
//

#define SCSI_DEVICE_MEDIUM_CHANGER                  0x08


//
// SCSI network device
//

#define SCSI_DEVICE_NETWORK                         0x09


//
// SCSI device... Is gone!
//

#define SCSI_DEVICE_UNPRESENT                       0x7F


//
// SCSI device any (wildcard for StarBurn_FindDevice() function)
//

#define SCSI_DEVICE_WILDCARD                        0xFF


//
// Number of sub-channels
//

#define NUMBER_OF_SUBCHANNELS                       8       // sub-channels from P to W


//
// Subchannel size in UCHARs
//

#define SUBCHANNEL_SIZE_IN_UCHARS                   12      // Sub-channel size in UCHARs

#define SUBCHANNEL_PQ_SIZE_IN_UCHARS                16      // PQ sub-channel size in UCHARs

#define SUBCHANNEL_RAW_PW_SIZE_IN_UCHARS            96      // Raw P-W sub-channel size in UCHARs


//
// Hard disk LB (logical block) size in UCHARs
//

#define HARD_DISK_LB_SIZE_IN_UCHARS					512

//
// MODE1 LB (logical block) size in UCHARs
//

#define MODE1_LB_SIZE_IN_UCHARS                     2048


//
// MODE2 Formless LB (logical block) size in UCHARS
//

#define MODE2_FORMLESS_LB_SIZE_IN_UCHARS            2336


//
// MODE2 Form1 LB (logical block) size in UCHARs
//

#define MODE2_FORM1_LB_SIZE_IN_UCHARS               2048


//
// MODE2 Form2 LB (logical block) size in UCHARs
//

#define MODE2_FORM2_LB_SIZE_IN_UCHARS               2324


//
// MODE2 Form2 + 8 UCHARs of subheader LB (logical block) size in UCHARs
//

#define MODE2_FORM2_SUB_LB_SIZE_IN_UCHARS           2332


//
// Audio LB (logical block) size in UCHARs
//

#define AUDIO_LB_SIZE_IN_UCHARS                     2352


//
// RAW LB (logical block) size in UCHARs
//

#define RAW_LB_SIZE_IN_UCHARS                       2352


//
// RAW LB (logical block) with PQ sub-channel size in UCHARs
//

#define RAW_LB_PQ_SUB_SIZE_IN_UCHARS                2368


//
// RAW LB (logical block) with RAW P-W sub-channel size in UCHARs
//

#define RAW_LB_RAW_PW_SUB_SIZE_IN_UCHARS            2448


//
// Short (w/o sync and header) RAW LB (logical block) size in UCHARs
//

#define SHORT_RAW_LB_SIZE_IN_UCHARS                 2336


//
// ISO9660 top supported file tree level
//

#define ISO9660_TREE_LEVEL                          8


//
// 1X CD speed constant
//

#define CD_SPEED_IN_KBPS_1X                       	176


//
// 2X CD speed constant
//

#define CD_SPEED_IN_KBPS_2X                       	353


//
// 2.2X CD speed constant
//

#define CD_SPEED_IN_KBPS_2P2X                     	387


//
// 3X CD speed constant
//

#define CD_SPEED_IN_KBPS_3X                       	528


//
// 4X CD speed constant
//

#define CD_SPEED_IN_KBPS_4X                       	706


//
// 6X CD speed constant
//

#define CD_SPEED_IN_KBPS_6X                       	1056


//
// 8X CD speed constant
//

#define CD_SPEED_IN_KBPS_8X                       	1400


//
// 10X CD speed constant
//

#define CD_SPEED_IN_KBPS_10X                      	1760


//
// 12X CD speed constant
//

#define CD_SPEED_IN_KBPS_12X                      	2112


//
// 16X CD speed constant
//

#define CD_SPEED_IN_KBPS_16X                      	2800


//
// 20X CD speed constant
//

#define CD_SPEED_IN_KBPS_20X                      	3250


//
// 24X CD speed constant
//

#define CD_SPEED_IN_KBPS_24X                      	4224


//
// 32X CD speed constant
//

#define CD_SPEED_IN_KBPS_32X                      	5632


//
// 36X CD speed constant
//

#define CD_SPEED_IN_KBPS_36X                      	6336


//
// 40X CD speed constant
//

#define CD_SPEED_IN_KBPS_40X                      	7040


//
// 44X CD speed constant
//

#define CD_SPEED_IN_KBPS_44X                      	7744


//
// 48X CD speed constant
//

#define CD_SPEED_IN_KBPS_48X                      	8448


//
// 52X CD speed constant
//

#define CD_SPEED_IN_KBPS_52X                      	9152


//
// Other CD speeds are just multiplier of ( CD_SPEED_IN_KBPS_1X * N ) where N is drive speed
//


//
// 1X DVD speed constant (DVD-R, DVD-RW and DVD-RAM)
//

#define DVD_SPEED_IN_KBPS_1X						1385


//
// 2X DVD speed constant (DVD-R, DVD-RW and DVD-RAM)
//

#define DVD_SPEED_IN_KBPS_2X						2770


//
// 2.4X DVD speed constant (DVD+R, DVD+R DL and DVD+RW)
//

#define DVD_SPEED_IN_KBPS_2DOT4X					3324


//
// 3X DVD speed constant (DVD-RAM)
//

#define DVD_SPEED_IN_KBPS_3X						4155


//
// 4X DVD speed constant (DVD-R, DVD-R DL, DVD-RW, DVD+R, DVD+R DL, DVD+RW and DVD-RAM)
//

#define DVD_SPEED_IN_KBPS_4X						5540


//
// 5X DVD speed constant (DVD-RAM)
//

#define DVD_SPEED_IN_KBPS_5X						6925


//
// 6X DVD speed constant (DVD-RW)
//

#define DVD_SPEED_IN_KBPS_6X						8310


//
// 8X DVD speed constant (DVD-R, DVD-R DL, DVD+R, DVD+R DL and DVD+RW)
//

#define DVD_SPEED_IN_KBPS_8X						11080


//
// 12X DVD speed constant (DVD-R, DVD+R)
//

#define DVD_SPEED_IN_KBPS_12X						16620


//
// 16X DVD speed constant (DVD+R and DVD-R)
//

#define DVD_SPEED_IN_KBPS_16X						22160


//
// 18X DVD speed constant (DVD+R and DVD-R)
//

#define DVD_SPEED_IN_KBPS_18X						24930


//
// 20X DVD speed constant (DVD+R and DVD-R)
//

#define DVD_SPEED_IN_KBPS_20X						27700


//
// Other DVD speeds are just multiplier of ( DVD_SPEED_IN_KBPS_1X * N ) where N is drive speed
//


//
// 1X Blu-Ray speed constant (BD-R and BD-RE)
//

#define BLURAY_SPEED_IN_KBPS_1X						4495	// Actually 4495.5


//
// 2X Blu-Ray speed constant (BD-R and BD-RE)
//

#define BLURAY_SPEED_IN_KBPS_2X						8991


//
// Other Blu-Ray speeds are just multiplier of ( BLURAY_SPEED_IN_KBPS_1X * N ) where N is drive speed
//


//
// Top supported CD/DVD/Blu-Ray/HD-DVD speed constant (wildcard)
//

#define CDVD_SPEED_IS_KBPS_MAXIMUM                  0xFFFF


//
// Special "invisible" track number
//

#define TRACK_NUMBER_INVISIBLE                      0xFF


//
// Top number of tracks (or border-in/border-out zones) on CD/DVD/Blu-Ray/HD-DVD disc
//

#define NUMBER_OF_TRACKS                            100


//
// Top number of raw tracks (including maintenance tracks) on CD/DVD/Blu-Ray/HD-DVD disc.
//
// This is calculated based on the worst CD case when all tracks will be in
// a separate sessions. We need this approximate value to avoid allocating
// TOC_INFORMATION structure dynamically.
//

#define NUMBER_OF_RAW_TRACKS                        ( NUMBER_OF_TRACKS * 4 + 1 )

//
// Disc is empty
//

#define DISC_STATUS_EMPTY                           0x00


//
// Disc is incomplete
//

#define DISC_STATUS_INCOMPLETE                      0x01


//
// Disc is complete
//

#define DISC_STATUS_COMPLETE                        0x02


//
// Last session is empty
//

#define LAST_SESSION_EMPTY                          0x00


//
// Last session is incomplete
//

#define LAST_SESSION_INCOMPLETE                     0x01


//
// Last session is complete
//

#define LAST_SESSION_COMPLETE                       0x03


//
// Disc type is CDDA (CD-ROM or Digital Audio)
//

#define STARBURN_DISC_TYPE_CDDA						0x01


//
// Disc type is CDI
//

#define STARBURN_DISC_TYPE_CDI						0x10


//
// Disc type is CD-ROM XA
//

#define STARBURN_DISC_TYPE_XA						0x20


//
// Disc type is undefined
//

#define STARBURN_DISC_TYPE_UNDEFINED				0xFF


//
// Default write report delay in seconds
//

#define WRITE_REPORT_DELAY_IN_SECONDS               1


//
// Default read report delay in seconds
//

#define READ_REPORT_DELAY_IN_SECONDS                1


//
// Default buffer status report delay in seconds
//

#define BUFFER_STATUS_REPORT_DELAY_IN_SECONDS       5


//
// Default number of retries on read operations (if bad block was possibly hit, was 2 originally)
//

#define NUMBER_OF_READ_RETRIES                      1


//
// WAVE file RIFF signature
//

#define WAVE_FILE_RIFF_SIGNATURE                    ( ULONG )( 'FFIR' )


//
// WAVE file WAVE signature
//

#define WAVE_FILE_WAVE_SIGNATURE                    ( ULONG )( 'EVAW' )


//
// WAVE file TAG signature
//

#define WAVE_FILE_TAG_SIGNATURE                     ( ULONG )( ' tmf' )


//
// WAVE file DATA signature
//

#define WAVE_FILE_DATA_SIGNATURE                    ( ULONG )( 'atad' )


//
// WAVE file number of channels
//

#define WAVE_FILE_CHANNELS                          2


//
// WAVE file bits per sample
//

#define WAVE_FILE_BITS_PER_SAMPLE                   16


//
// WAVE file samples per second
//

#define WAVE_FILE_SAMPLES_PER_SECOND                44100


//
// WAVE file WAVE format
//

#define WAVE_FILE_WAVE_FORMAT                       1


//
// WAVE file data alignment (4 UCHARs, 1 ULONG)
//

#define WAVE_FILE_ALIGNMENT                         4


//
// DVD protection systems (begin)
//


//
// DVD w/o any protection system
//

#define DVD_PROTECTION_NONE                         0x00


//
// DVD with CSS (Content Scrambling System) protection
//

#define DVD_PROTECTION_CSS                          0x01


//
// DVD with CPRM (Copy-Protected Removable Media) protection
//

#define DVD_PROTECTION_CPRM                         0x02


//
// DVD protection systems (end)
//


//
// Type codes for KEY_FORMAT_RPC
//

#define TYPE_CODE_NONE								0x00	// No Logical Unit region setting

#define TYPE_CODE_SET 								0x01	// Logical Unit region is set

#define TYPE_CODE_LAST_CHANCE						0x02	// Logical Unit region is set. Additional restrictions required to make a change

#define TYPE_CODE_PERM								0x03	// Logical Unit region has been set permanently, but may be reset by vendor if necessery


//
// ISO9660 volume descriptor system and volume ID size in UCHARs
//

#define ISO9660_SYSTEM_VOLUME_ID_SIZE_IN_UCHARS     32


//
// ISO9660 name size in UCHARs
//

#define ISO9660_NAME_SIZE_IN_UCHARS                 128


//
// ISO9660 file size in UCHARs
//

#define ISO9660_FILE_SIZE_IN_UCHARS                 37


//
// ISO9660 date size in UCHARs
//

#define ISO9660_DATE_SIZE_IN_UCHARS                 17


//
// UDF constants (begin)
//


//
// UDF logical block size in UCHARs
//

#define UDF_LOGICAL_BLOCK_SIZE_IN_UCHARS            2048


//
// UDF longest name size in UCHARs
//

#define UDF_NAME_SIZE_IN_UCHARS                     255


//
// UDF OS class 
//

#define STARBURN_UDF_OS_CLASS_UNDEFINED				0x00

#define STARBURN_UDF_OS_CLASS_DOS					0x01

#define STARBURN_UDF_OS_CLASS_OS_2					0x02

#define STARBURN_UDF_OS_CLASS_MACINTOSH_OS			0x03

#define STARBURN_UDF_OS_CLASS_UNIX					0x04

#define STARBURN_UDF_OS_CLASS_WINDOWS_9X			0x05

#define STARBURN_UDF_OS_CLASS_WINDOWS_NT			0x06

#define STARBURN_UDF_OS_CLASS_OS_400				0x07

#define STARBURN_UDF_OS_CLASS_BE_OS					0x08

#define STARBURN_UDF_OS_CLASS_WINDOWS_CE			0x09


//
// UDF/ISO9660 bridge file system structures size in logical blocks (was 5 originally)
//

#define UDF_ISO9660_FILE_SYSTEM_SIZE_IN_LBS         5


//
// UDF file set descriptor logical block address
//

#define UDF_FILE_SET_DESCRIPTOR_LBA                 ( 257 + UDF_ISO9660_FILE_SYSTEM_SIZE_IN_LBS )


//
// UDF file set descriptor terminator logical block address
//

#define UDF_FILE_SET_DESCRIPTOR_TERMINATOR_LBA		( 1 + UDF_FILE_SET_DESCRIPTOR_LBA )

//
// UDF head size in logical blocks
//

#define UDF_HEAD_SIZE_IN_LOGICAL_BLOCKS             ( UDF_FILE_SET_DESCRIPTOR_TERMINATOR_LBA + 1 )


//
// UDF tail size in logical blocks
//

#define UDF_TAIL_SIZE_IN_LOGICAL_BLOCKS             256


//
// UDF constants (end)
//


//
// El Torito constants (begin)
//


//
// Non-bootable disc ID
//

#define ELTORITO_NON_BOOTABLE                  		0x00


//
// Bootable disc ID
//

#define ELTORITO_BOOTABLE                           0x88


//
// Bootable specification signature
//

#define ELTORITO_BOOTSYSTEM_ID                      "EL TORITO SPECIFICATION"


//
// x86 platform identifier
//

#define ELTORITO_PLATFORM_80X86                     0x00


//
// PowerPC platform identifier
//

#define ELTORITO_PLATFORM_POWERPC                   0x01


//
// MAC platform identifier
//

#define ELTORITO_PLATFORM_MAC                       0x02


//
// Custom bootable media emulation
//

#define ELTORITO_MEDIA_CUSTOM                       0x00


//
// 1.2 MB floppy bootable media emulation
//

#define ELTORITO_MEDIA_FLOPPY120                    0x01


//
// 1.44 MB floppy bootable media emulation
//

#define ELTORITO_MEDIA_FLOPPY144                    0x02


//
// 2.88 MB floppy bootable media emulation
//

#define ELTORITO_MEDIA_FLOPPY288                    0x03


//
// Hard disk bootable media emulation
//

#define ELTORITO_MEDIA_HARDDISK                     0x04


//
// Real mode code load segment
//

#define ELTORITO_DEF_LOAD_SEGMENT                   0x07C0


//
// El Torito constants (end)
//


//
// Default DVD capacity in logical blocks (for single layer DVD and dual layer DVD)
//

#define SINGLE_LAYER_DVD_CAPACITY_SIZE_IN_LBS		2298495	// Number of logical blocks on single layer DVD

#define DUAL_LAYER_DVD_CAPACITY_SIZE_IN_LBS			( SINGLE_LAYER_DVD_CAPACITY_SIZE_IN_LBS * 2 ) // Doubled...


//
// BD-RE format types
//

#define STARBURN_BDRE_FORMAT_DEFAULT				0x00

#define STARBURN_BDRE_FORMAT_SPARE_AREA_EXPANSION	0x01

#define STARBURN_BDRE_FORMAT_WITH_SPARE_AREA		0x30

#define STARBURN_BDRE_FORMAT_WITHOUT_SPARE_AREA		0x31


//
// BD-RE format certification types
//

#define STARBURN_BDRE_FORMAT_CERTIFICATION_NO		0x00

#define STARBURN_BDRE_FORMAT_CERTIFICATION_FULL		0x01

#define STARBURN_BDRE_FORMAT_CERTIFICATION_QUICK	0x02

#define STARBURN_BDRE_FORMAT_CERTIFICATION_RESERVED	0x03


//
// DVD-Video maximum number of titles
//

#define STARBURN_DVD_VIDEO_MAX_NUMBER_OF_TITLES		99


//
// Own definitions and macros (end)
//


//
// Own data types, global function bodies, classes and methods (begin)
//


//
// Keep original structure packing and enable single UCHAR packing
//

#pragma pack( push, 1 )


//
// Structure that represents format profile for BD-RE media 
//
// <TABLE>
// Member                               				Definition
// ----------                           				---------------
// LONG m__LONG__FormatProfileNumber					Format profile number
// UCHAR m__ULONG__NumberOfBlocksOrUserAreaDataSize		Number of logical block(s) or user area data size
// UCHAR m__UCHAR__CertificationType					Certification type
// UCHAR m__UCHAR__FormatType							Format type 
// UCHAR m__ULONG__SpareAreaSizeInClustersOrBlockLength Spare area size in cluster(s) or block length 
// </TABLE>
//

typedef struct _STARBURN_BDRE_FORMAT_PROFILE
{
	LONG m__LONG__FormatProfileNumber;

    ULONG m__ULONG__NumberOfBlocksOrUserAreaDataSize;

    UCHAR m__UCHAR__CertificationType : 2;

    UCHAR m__UCHAR__FormatType : 6;

    ULONG m__ULONG__SpareAreaSizeInClustersOrBlockLength;

} **PPSTARBURN_BDRE_FORMAT_PROFILE, *PSTARBURN_BDRE_FORMAT_PROFILE, STARBURN_BDRE_FORMAT_PROFILE;


//
// Structure that represents advanced supported media formats
//
// <TABLE>
// Member                               	Definition
// ----------                           	---------------
// ULONG m__ULONG__SizeInUCHARs 			This structure size in UCHARs
// BOOLEAN m__BOOLEAN__IsCDROMRead			Is CD-ROM read capable
// BOOLEAN m__BOOLEAN__IsCDRRead			Is CD-R read capable
// BOOLEAN m__BOOLEAN__IsCDRWrite  			Is CD-R write capable
// BOOLEAN m__BOOLEAN__IsCDRWRead			Is CD-RW read capable
// BOOLEAN m__BOOLEAN__IsCDRWWrite			Is CD-RW write capable
// BOOLEAN m__BOOLEAN__IsDVDROMRead			Is DVD-ROM read capable
// BOOLEAN m__BOOLEAN__IsDVDRRead			Is DVD-R read capable
// BOOLEAN m__BOOLEAN__IsDVDRWrite			Is DVD-R write capable
// BOOLEAN m__BOOLEAN__IsDVDRDLRead			Is DVD-R DL read capable
// BOOLEAN m__BOOLEAN__IsDVDRDLWrite		Is DVD-R DL write capable
// BOOLEAN m__BOOLEAN__IsDVDRWRead			Is DVD-RW read capable
// BOOLEAN m__BOOLEAN__IsDVDRWWrite			Is DVD-RW write capable
// BOOLEAN m__BOOLEAN__IsDVDRWDLRead		Is DVD-RW DL read capable
// BOOLEAN m__BOOLEAN__IsDVDRWDLWrite		Is DVD-RW DL write capable
// BOOLEAN m__BOOLEAN__IsDVDRAMRead			Is DVD-RAM read capable
// BOOLEAN m__BOOLEAN__IsDVDRAMWrite		Is DVD-RAM write capable
// BOOLEAN m__BOOLEAN__IsDVDPLUSRWRead		Is DVD+RW read capable
// BOOLEAN m__BOOLEAN__IsDVDPLUSRWWrite		Is DVD+RW write capable
// BOOLEAN m__BOOLEAN__IsDVDPLUSRWDLRead	Is DVD+RW DL read capable
// BOOLEAN m__BOOLEAN__IsDVDPLUSRWDLWrite	Is DVD+RW DL write capable
// BOOLEAN m__BOOLEAN__IsDVDPLUSRRead		Is DVD+R read capable
// BOOLEAN m__BOOLEAN__IsDVDPLUSRWrite		Is DVD+R write capable
// BOOLEAN m__BOOLEAN__IsDVDPLUSRDLRead		Is DVD+R DL read capable
// BOOLEAN m__BOOLEAN__IsDVDPLUSRDLWrite	Is DVD+R DL write capable
// BOOLEAN m__BOOLEAN__IsBDROMRead			Is BD-ROM read capable
// BOOLEAN m__BOOLEAN__IsBDRRead			Is BD-R read capable
// BOOLEAN m__BOOLEAN__IsBDRWrite			Is BD-R write capable
// BOOLEAN m__BOOLEAN__IsBDRDLRead			Is BD-R DL read capable
// BOOLEAN m__BOOLEAN__IsBDRDLWrite			Is BD-R DL write capable
// BOOLEAN m__BOOLEAN__IsBDRERead			Is BD-RE read capable
// BOOLEAN m__BOOLEAN__IsBDREWrite			Is BD-RE write capable
// BOOLEAN m__BOOLEAN__IsBDREDLRead			Is BD-RE DL read capable
// BOOLEAN m__BOOLEAN__IsBDREDLWrite		Is BD-RE DL write capable
// BOOLEAN m__BOOLEAN__IsHDDVDROMMRead		Is HD-DVD-ROM read capable
// BOOLEAN m__BOOLEAN__IsHDDVDRRead			Is HD-DVD-R read capable
// BOOLEAN m__BOOLEAN__IsHDDVDRWrite		Is HD-DVD-R write capable
// BOOLEAN m__BOOLEAN__IsHDDVDRDLRead		Is HD-DVD-R DL read capable
// BOOLEAN m__BOOLEAN__IsHDDVDRDLWrite		Is HD-DVD-R DL write capable
// BOOLEAN m__BOOLEAN__IsHDDVDRWRead		Is HD-DVD-RW read capable
// BOOLEAN m__BOOLEAN__IsHDDVDRWWrite		Is HD-DVD-RW write capable
// BOOLEAN m__BOOLEAN__IsHDDVDRWDLRead		Is HD-DVD-RW DL read capable
// BOOLEAN m__BOOLEAN__IsHDDVDRWDLWrite		Is HD-DVD-RW DL write capable
// </TABLE>

typedef struct _STARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS
{
	ULONG m__ULONG__SizeInUCHARs; 			// This structure size in UCHARs

	BOOLEAN m__BOOLEAN__IsCDROMRead;		// Is CD-ROM read capable

	BOOLEAN m__BOOLEAN__IsCDRRead;			// Is CD-R read capable

	BOOLEAN m__BOOLEAN__IsCDRWrite;  		// Is CD-R write capable

	BOOLEAN m__BOOLEAN__IsCDRWRead;			// Is CD-RW read capable

	BOOLEAN m__BOOLEAN__IsCDRWWrite;		// Is CD-RW write capable

	BOOLEAN m__BOOLEAN__IsDVDROMRead;		// Is DVD-ROM read capable

	BOOLEAN m__BOOLEAN__IsDVDRRead;			// Is DVD-R read capable

	BOOLEAN m__BOOLEAN__IsDVDRWrite;		// Is DVD-R write capable

	BOOLEAN m__BOOLEAN__IsDVDRDLRead;		// Is DVD-R DL read capable

	BOOLEAN m__BOOLEAN__IsDVDRDLWrite;		// Is DVD-R DL write capable

	BOOLEAN m__BOOLEAN__IsDVDRWRead;		// Is DVD-RW read capable

	BOOLEAN m__BOOLEAN__IsDVDRWWrite;		// Is DVD-RW write capable

	BOOLEAN m__BOOLEAN__IsDVDRWDLRead;		// Is DVD-RW DL read capable

	BOOLEAN m__BOOLEAN__IsDVDRWDLWrite;		// Is DVD-RW DL write capable

	BOOLEAN m__BOOLEAN__IsDVDRAMRead;		// Is DVD-RAM read capable

	BOOLEAN m__BOOLEAN__IsDVDRAMWrite;		// Is DVD-RAM write capable

	BOOLEAN m__BOOLEAN__IsDVDPLUSRWRead;	// Is DVD+RW read capable

	BOOLEAN m__BOOLEAN__IsDVDPLUSRWWrite;	// Is DVD+RW write capable

	BOOLEAN m__BOOLEAN__IsDVDPLUSRWDLRead;	// Is DVD+RW DL read capable

	BOOLEAN m__BOOLEAN__IsDVDPLUSRWDLWrite;	// Is DVD+RW DL write capable
	
	BOOLEAN m__BOOLEAN__IsDVDPLUSRRead;		// Is DVD+R read capable

	BOOLEAN m__BOOLEAN__IsDVDPLUSRWrite;	// Is DVD+R write capable

	BOOLEAN m__BOOLEAN__IsDVDPLUSRDLRead;	// Is DVD+R DL read capable

	BOOLEAN m__BOOLEAN__IsDVDPLUSRDLWrite;	// Is DVD+R DL write capable

	BOOLEAN m__BOOLEAN__IsBDROMRead;		// Is BD-ROM read capable

	BOOLEAN m__BOOLEAN__IsBDRRead;			// Is BD-R read capable

	BOOLEAN m__BOOLEAN__IsBDRWrite;			// Is BD-R write capable

	BOOLEAN m__BOOLEAN__IsBDRDLRead;		// Is BD-R DL read capable

	BOOLEAN m__BOOLEAN__IsBDRDLWrite;		// Is BD-R DL write capable

	BOOLEAN m__BOOLEAN__IsBDRERead;			// Is BD-RE read capable

	BOOLEAN m__BOOLEAN__IsBDREWrite;		// Is BD-RE write capable

	BOOLEAN m__BOOLEAN__IsBDREDLRead;		// Is BD-RE DL read capable

	BOOLEAN m__BOOLEAN__IsBDREDLWrite;		// Is BD-RE DL write capable

	BOOLEAN m__BOOLEAN__IsHDDVDROMRead;		// Is HD-DVD-ROM read capable

	BOOLEAN m__BOOLEAN__IsHDDVDRRead;		// Is HD-DVD-R read capable

	BOOLEAN m__BOOLEAN__IsHDDVDRWrite;		// Is HD-DVD-R write capable

	BOOLEAN m__BOOLEAN__IsHDDVDRDLRead;		// Is HD-DVD-R DL read capable

	BOOLEAN m__BOOLEAN__IsHDDVDRDLWrite;	// Is HD-DVD-R DL write capable

	BOOLEAN m__BOOLEAN__IsHDDVDRWRead;		// Is HD-DVD-RW read capable

	BOOLEAN m__BOOLEAN__IsHDDVDRWWrite;		// Is HD-DVD-RW write capable

	BOOLEAN m__BOOLEAN__IsHDDVDRWDLRead;	// Is HD-DVD-RW DL read capable

	BOOLEAN m__BOOLEAN__IsHDDVDRWDLWrite;	// Is HD-DVD-RW DL write capable

} *PSTARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS, STARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS;


//
// Structure that represents formatted PQ sub-channel
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__UCHAR__ADR 						Track ADR
// m__UCHAR__CONTROL 					Track CONTROL
// m__UCHAR__TrackNumber				Track Number
// m__UCHAR__IndexNumber				Index Number
// m__UCHAR__Min						Min (from the beginning of the track)
// m__UCHAR__Sec						Sec (from the beginning of the track)
// m__UCHAR__Frame						Frame (from the beginning of the track)
// m__UCHAR__ZERO						MBZ
// m__UCHAR__AMIN						Min (from the beginning of the disc)
// m__UCHAR__ASEC						Sec (from the beginning of the disc)
// m__UCHAR__AFRAME						Frame (from the beginning of the disc)
// m__UCHAR__CRC1_Reserved1				CRC1 or MBZ
// m__UCHAR__CRC2_Reserved2				CRC2 or MBZ
// m__UCHAR__Reserved3[ 3 ]				MBZ
// m__UCHAR__Reserved4 					MBZ
// m__UCHAR__PSubChannel 				P sub-channel bit
// </TABLE>

typedef struct _PQ_SUBCHANNEL
{
    UCHAR m__UCHAR__ADR : 4;     		// Track ADR

    UCHAR m__UCHAR__CONTROL : 4;        // Track CONTROL

    UCHAR m__UCHAR__TrackNumber;		// Track Number

    UCHAR m__UCHAR__IndexNumber;		// Index Number

    UCHAR m__UCHAR__Min;				// Min (from the beginning of the track)

    UCHAR m__UCHAR__Sec;                // Sec (from the beginning of the track)

    UCHAR m__UCHAR__Frame;              // Frame (from the beginning of the track)

    UCHAR m__UCHAR__ZERO;				// MBZ

    UCHAR m__UCHAR__AMIN;               // Min (from the beginning of the disc)

    UCHAR m__UCHAR__ASEC;               // Sec (from the beginning of the disc)

    UCHAR m__UCHAR__AFRAME;            	// Frame (from the beginning of the disc)
	
    UCHAR m__UCHAR__CRC1_Reserved1;		// CRC1 or MBZ

    UCHAR m__UCHAR__CRC2_Reserved2;		// CRC2 or MBZ

    UCHAR m__UCHAR__Reserved3[ 3 ];		// MBZ
	
    UCHAR m__UCHAR__Reserved4 : 7;		// MBZ		

    UCHAR m__UCHAR__PSubChannel : 1;	// P sub-channel bit

} *PPQ_SUBCHANNEL, PQ_SUBCHANNEL;


//
// Structure that represents UDF file handle
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__HANDLE							Win32 file handle
// </TABLE>

typedef struct _UDF_FILE_HANDLE
{
    HANDLE m__HANDLE;					// Win32 file handle

} *PUDF_FILE_HANDLE, UDF_FILE_HANDLE;


//
// Structure that represents UDF control block
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__PVOID__Head						Pointer to the head of the linked list
// m__PVOID__SystemStructures			Pointer to the allocated and formatted UDF system structures
// m__PVOID__Tail						Pointer to the tail of the linked list
// m__PVOID__Body						Pointer to block body itself
// </TABLE>

typedef struct _UDF_CONTROL_BLOCK
{
    void *m__PVOID__Head;				// Pointer to the head of the linked list

    void *m__PVOID__SystemStructures;	// Pointer to the allocated and formatted UDF system structures

    void *m__PVOID__Tail;				// Pointer to the tail of the linked list

    void *m__PVOID__Body;				// Pointer to block body itself

} *PUDF_CONTROL_BLOCK, UDF_CONTROL_BLOCK;


//
// Structure that represents ISO9660 date and time
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__UCHAR__Year						Year
// m__UCHAR__Month						Month
// M__UCHAR__Day						Day
// m__UCHAR__Hour						Hour
// m__UCHAR__Minute						Minute
// m__UCHAR__Second						Second
// m__UCHAR__GMTOffset					Offset from GMT in hours
// </TABLE>

typedef struct _ISO9660_DATE_TIME
{
    UCHAR m__UCHAR__Year;				// Year

    UCHAR m__UCHAR__Month;				// Month

    UCHAR m__UCHAR__Day;				// Day

    UCHAR m__UCHAR__Hour;				// Hour

    UCHAR m__UCHAR__Minute;				// Minute

    UCHAR m__UCHAR__Second;				// Second

    UCHAR m__UCHAR__GMTOffset;			// Offset from GMT in hours

} *PISO9660_DATE_TIME, ISO9660_DATE_TIME;


//
// Structure that represents UDF tree item
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__ULONG__FileEntryRBA				File entry relative block address
// m__ULONG__FileIdentifierRBA			File identifier relative block address
// m__ULONG__FileIdentifier...			File identifier parent or content relative block address
// m__ULONG__LastTouchedRBA				Last touched relative block address (last occupied)
// m__ULONG__GUID						Globally unique identifier
// m__UCHAR__IsDirectory				Is this directory (0x01) or file (0x00)
// m__UCHAR__IsCached					Is this entry content cached (located in memory) or not cached (located on the disk)
// m__USHORT_NumberOfKidsAsParents		Number of kids that have their own kids
// m__CHAR__Name						Name of this node
// m__UDF_FILE_HANDLE					UDF file handle of this node
// m__PUCHAR__File						Pointer to file content (for cached files)
// m__ULONGLONG__SizeInUCHARs			Node content size in UCHARs
// m__ULONG__SizeInLogicalBlocks		Node content size in logical blocks
// m__PUDF_TREE_ITEM__Next				Pointer to the next UDF tree item in the linked list
// m__PUDF_TREE_ITEM__Prev				Pointer to the previous UDF tree item in the linked list
// m__PUDF_TREE_ITEM__Kids				Pointer to the kids liked list
// m__PUDF_TREE_ITEM__Parent			Pointer to the parent of the current UDF tree item
// m__UCHAR__FileEntryDescriptor		Array if UCHARs holding UDF file entry descriptor for current UDF tree item
// m__UCHAR__FileIdentifier...			Array of UCHARs holding UDF file identifier descriptor for current UDF tree item
// m__UCHAR__FileIdentifier...			Array of UCHARs holding UDF file identifier descriptor for parent of the current UDF tree item
// m__UCHAR__FileContent				Array of UCHARs holding file content (alternative cached data)
// m__PVOID__Context					Pointer to context value
// m__ISO9660_DATE_TIME					ISO9660 date and time
// </TABLE>

typedef struct _UDF_TREE_ITEM
{
    unsigned long m__ULONG__FileEntryRBA;						// File entry relative block address

    unsigned long m__ULONG__FileIdentifierRBA;                  // File identifier relative block address

    unsigned long m__ULONG__FileIdentifierParentOrContentRBA; 	// File identifier parent or content relative block address

    unsigned long m__ULONG__LastTouchedRBA;                  	// Last touched relative block address (last occupied)

    unsigned long m__ULONG__GUID;                               // Globally unique identifier

    unsigned char m__UCHAR__IsDirectory;                       	// Is this directory (0x01) or file (0x00)

    unsigned char m__UCHAR__IsCached;                       	// Is this entry content cached (located in memory) or not cached (located on the disk)

    unsigned short m__USHORT__NumberOfKidsAsParents;         	// Number of kids that have their own kids

    char m__CHAR__Name[ UDF_NAME_SIZE_IN_UCHARS ];         		// Name of this node

    UDF_FILE_HANDLE m__UDF_FILE_HANDLE;							// UDF file handle of this node

    unsigned char *m__PUCHAR__File;                         	// Pointer for file content (for cached files)

    unsigned __int64 m__ULONGLONG__SizeInUCHARs;				// Node content size in UCHARs

    unsigned long m__ULONG__SizeInLogicalBlocks;             	// Node content size in logical blocks

    struct _UDF_TREE_ITEM *m__PUDF_TREE_ITEM__Next;             // Pointer to the next UDF tree item in the linked list

    struct _UDF_TREE_ITEM *m__PUDF_TREE_ITEM__Prev;             // Pointer to the previous UDF tree item in the linked list

    struct _UDF_TREE_ITEM *m__PUDF_TREE_ITEM__Kids;				// Pointer to the kids linked list

    struct _UDF_TREE_ITEM *m__PUDF_TREE_ITEM__Parent;           // Pointer to the parent of the current UDF tree item

    unsigned char m__UCHAR__FileEntryDescriptor[ UDF_LOGICAL_BLOCK_SIZE_IN_UCHARS ];			// Array of UCHARs holding UDF file entry descriptor for current UDF tree item

    unsigned char * m__PUCHAR__FileIdentifierDescriptor;		// Pointer to allocated file identifier

	unsigned long m__ULONG__FileIdentifierDescriptorSizeInUCHARs; // Size of allocated FID in bytes

    unsigned char m__UCHAR__FileContent[ UDF_LOGICAL_BLOCK_SIZE_IN_UCHARS ];					// Array of UCHARs holding file content (alternative cached data)

    void *m__PVOID__Context;									// Pointer to context value

    ISO9660_DATE_TIME m__ISO9660_DATE_TIME;    					// ISO9660 date and time

} *PUDF_TREE_ITEM, UDF_TREE_ITEM;


//
// Restore original structure packing
//

#pragma pack( pop )


// 
// Structure that represents UDF2 file date and time
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// Year									Year
// Month								Month
// Day									Day
// Hour									Hour
// Minute								Minute
// Second								Second
// Millisecnd							Millisecond
// Offset								UTC offset in minutes
// </TABLE>

typedef struct _STARBURN_UDF2_FILE_DATE_TIME
{
	unsigned short Year;

	unsigned char Month;

	unsigned char Day;

	unsigned char Hour;

	unsigned char Minute;

	unsigned char Second;

	unsigned char Millisecond;

	short Offset; // UTC offset in minutes

} STARBURN_UDF2_FILE_DATE_TIME;


//
// Enum that represents StarPort device type
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// STARPORT_DEVICE_TYPE_UNKNOWN			Unknown device type
// STARPORT_DEVICE_TYPE_RAM				RAM disk
// STARPORT_DEVICE_TYPE_HDD				Virtual hard disk
// STARPORT_DEVICE_TYPE_DVD				Virtual DVD
// STARPORT_DEVICE_TYPE_AOE				AoE (ATA-over-Ethernet)
// STARPORT_DEVICE_TYPE_ISCSI			iSCSI (SCSI-over-IP)
// </TABLE>

typedef enum _STARPORT_DEVICE_TYPE
{
	STARPORT_DEVICE_TYPE_UNKNOWN = 0,	// Unknown device type

	STARPORT_DEVICE_TYPE_RAM,			// RAM disk

	STARPORT_DEVICE_TYPE_HDD,			// Virtual hard disk

	STARPORT_DEVICE_TYPE_DVD,			// Virtual DVD

	STARPORT_DEVICE_TYPE_AOE,			// AoE (ATA-over-Ethernet)

	STARPORT_DEVICE_TYPE_ISCSI			// iSCSI (SCSI-over-IP)

} **PPSTARPORT_DEVICE_TYPE, *PSTARPORT_DEVICE_TYPE, STARPORT_DEVICE_TYPE;


//
// Enum that represents exception number
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// EN_SUCCESS                           Nothing really happened, operation completed successfully
// EN_FAILURE                           Undefined error happened, something goes really wrong
// EN_INVALID_INPUT_PARAMETER           User input parameter is not valid
// EN_INVALID_STATE                     The state of the object is not valid for current operation
// EN_MEMORY_ALLOCATION_FAILED          Memory allocation failed
// EN_SYSTEM_CALL_FAILED                System call failed, check SystemError pointer to system error value
// EN_SCSI_TRANSPORT_FAILED             SCSI transport internal error
// EN_SCSI_DEVICE_BUSY                  SCSI device is busy for a while
// EN_SCSI_CDB_FAILED                   SCSI CDB delivery failed, check CDB_FAILURE_INFORMATION for details
// EN_SCSI_DEVICE_INVALID_TYPE          SCSI device of this type is not supported
// EN_INVALID_RESPONSE                  Something really unsupported returned
// EN_BUFFER_UNDERRUN                   Buffer underrun happened
// EN_INVALID_EXCEPTION                 Exception was not allocated
// EN_ACCESS_TO_FEATURE_DENIED          Access to feature denied b/s of the wrong version
// EN_USER_EXCEPTION                    This is not a real exception just the result of user interaction
// EN_PATH_TOO_LONG                     File path is too long
// EN_UNDER_CONSTRUCTION                This feature is still under construction
// EN_NOT_FOUND                         Operation could not be performed b/s either device or requested parameter not found
// EN_FILE_TOO_BIG                      File is too big for requested operation
// EN_NOT_IMPLEMENTED                   Feature is not implemented yet
// EN_RANGE                             Passed range is not valid
// EN_REGISTRATION_FAILED               Registration procedure completed with errors
// EN_UNSUPPORTED_AUDIO                 Unsupported audio format used as either input or output
// EN_BUFFER_TOO_SMALL                  Buffer size supplied by caller is not sufficient
// EN_SYSTEM_CALL_FAILED_EX             Middle-layer error happened, check SystemError pointer for specific error value
// EN_ERROR_RECOVERY_FAILED             Error recovery failed
// EN_UNRECOGNIZED_MEDIA                Current media type is not recognized
// EN_GENERAL_SEEK_ERROR				General seek error on CD/DVD/Blu-Ray/HD-DVD media
// EN_GENERAL_READ_ERROR				General read error on CD/DVD/Blu-Ray/HD-DVD media
// EN_ILLEGAL_OPERATION_FOR_TRACK		Illegal operation for track
// EN_UNSUPPORTED_READ_MODE				Currently selected read mode is not supported by device
// EN_REQUEST_TOO_LARGE                 Request size is too large to be handled
// EN_FULL_ERASE_REQUIRED				Full erase required before recording to inserted media
// EN_VERIFY_FAILED						Verify operation found different memory buffers
// EN_DPM_FAILED						DPM associated call failed
// EN_DEVICE_SHARING_VIOLATION			Device failed to open b/s of sharing violation
// EN_CALL_IS_OBSOLETE					Function is obsolete
// EN_WRONG_OS_VERSION					OS version is not supported  
// EN_INVALID_FIELD_IN_CDB				Invalid field in CDB
// </TABLE>

typedef enum _EXCEPTION_NUMBER
{
    EN_SUCCESS = 0,                     // Nothing really happened, operation completed successfully

    EN_FAILURE,                         // Undefined error happened, something goes really wrong

    EN_INVALID_INPUT_PARAMETER,         // User input parameter is not valid

    EN_INVALID_STATE,                   // The state of the object is not valid for current operation

    EN_MEMORY_ALLOCATION_FAILED,        // Memory allocation failed

    EN_SYSTEM_CALL_FAILED,              // System call failed, check SystemError pointer to system error value

    EN_SCSI_TRANSPORT_FAILED,           // SCSI transport internal error

    EN_SCSI_DEVICE_BUSY,                // SCSI device is busy for a while

    EN_SCSI_CDB_FAILED,                 // SCSI CDB delivery failed, check CDB_FAILURE_INFORMATION for details

    EN_SCSI_DEVICE_INVALID_TYPE,        // SCSI device of this type is not supported

    EN_INVALID_RESPONSE,                // Something really unsupported returned

    EN_BUFFER_UNDERRUN,                 // Buffer underrun happened

    EN_INVALID_EXCEPTION,               // Exception was not allocated

    EN_ACCESS_TO_FEATURE_DENIED,        // Access to feature denied b/s of the wrong version

    EN_USER_EXCEPTION,                  // This is not a real exception just the result of user interaction

    EN_PATH_TOO_LONG,                   // File path is too long

    EN_UNDER_CONSTRUCTION,              // This feature is still under construction

    EN_NOT_FOUND,                       // Operation could not be performed b/s either device or requested parameter not found

    EN_FILE_TOO_BIG,                    // File is too big for the requested operation

    EN_NOT_IMPLEMENTED,                 // Feature is not implemented yet

    EN_RANGE,                           // Passed range is not valid

    EN_REGISTRATION_FAILED,             // Registration procedure completed with errors

    EN_UNSUPPORTED_AUDIO,               // Unsupported audio format used as either input or output

    EN_BUFFER_TOO_SMALL,                // Buffer size supplied by caller is not sufficient

    EN_SYSTEM_CALL_FAILED_EX,           // Middle-layer error happened, check SystemError pointer for specific error value

    EN_ERROR_RECOVERY_FAILED,           // Error recovery failed

    EN_UNRECOGNIZED_MEDIA,              // Current media type is not recognized

	EN_GENERAL_SEEK_ERROR,				// General seek error on CD/DVD/Blu-Ray/HD-DVD media

	EN_GENERAL_READ_ERROR,				// General read error on CD/DVD/Blu-Ray/HD-DVD media

	EN_ILLEGAL_OPERATION_FOR_TRACK,		// Illegal operation for track

	EN_UNSUPPORTED_READ_MODE,			// Currently selected read mode is not supported by device

    EN_REQUEST_TOO_LARGE,               // Request size is too large to be handled

	EN_FULL_ERASE_REQUIRED,				// Full erase required before recording to inserted media

	EN_VERIFY_FAILED,					// Verify operation found different memory buffers

	EN_DPM_FAILED,						// DPM associated call failed

	EN_DEVICE_SHARING_VIOLATION,		// Device failed to open b/s of sharing violation

	EN_CALL_IS_OBSOLETE,				// Function is obsolete

	EN_WRONG_OS_VERSION,				// OS version is not supported

	EN_INVALID_FIELD_IN_CDB				// Invalid field in CDB

} *PEXCEPTION_NUMBER, EXCEPTION_NUMBER;

//
// Enum that represents CD modes type
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// CD_MODE_UNKNOWN                      Unknown CD mode
// CD_MODE_AUDIO						Audio CD mode
// CD_MODE_VIDEO						Video CD mode
// CD_MODE_DATA							Data CD mode
// CD_MODE_RESERVED  					Reserved
// </TABLE>

typedef enum _STARBURN_CD_MODE
{
	CD_MODE_UNKNOWN = 0,	// Unknown CD mode

	CD_MODE_AUDIO,			// Audio CD mode 

	CD_MODE_VIDEO,			// Video CD mode

	CD_MODE_DATA,			// Data CD mode

	CD_MODE_RESERVED  		// Reserved

} *PSTARBURN_CD_MODE, STARBURN_CD_MODE;

//
// Enum that represent type of ISO9660 tree node
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// KIDTYPE_UNKNOWN						Unknown kid type
// KIDTYPE_IMPORTED                     Node was imported from previous track
// KIDTYPE_FROMDISK						Node was added from the disk
// KIDTYPE_VIRTUAL						Node was created as memory file or virtual directory
// </TABLE>

typedef enum _ISO9660_KIDTYPE
{
	KIDTYPE_UNKNOWN,					// Unknown kid type

	KIDTYPE_IMPORTED,					// Node was imported from previous track

	KIDTYPE_FROMDISK,					// Node was added from the disk

	KIDTYPE_VIRTUAL                     // Node was created as memory file or virtual directory

} *PISO9660_KIDTYPE, ISO9660_KIDTYPE;


//
// Enum that represents file time that will be included in the ISO9660/Joliet image
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// FILE_TIME_CREATION                   Original creation file time will be included into the file system image
// FILE_TIME_LAST_ACCESS                Last access time will be included into the file system image
// FILE_TIME_LAST_WRITE                 Last write tile will be included into the file system image
// </TABLE>

typedef enum _FILE_TIME
{
    FILE_TIME_CREATION = 0,             // Original creation file time will be included into the file system image

    FILE_TIME_LAST_ACCESS,              // Last access time will be included into the file system image

    FILE_TIME_LAST_WRITE                // Last write tile will be included into the file system image

} *PFILE_TIME, FILE_TIME;


//
// Enum that represents the solutions of name collisions
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// NAME_COLLISION_SKIP_NEW              Remove new node and leave old node
// NAME_COLLISION_REPLACE_OLD           Remove old node and insert new node
// NAME_COLLISION_RENAME_NEW            Leave old node and insert new node with the new name
// NAME_COLLISION_MERGE_FOLDERS			Add files from new folder into an old folder
// </TABLE>

typedef enum _NAME_COLLISION_SOLUTION
{
    NAME_COLLISION_SKIP_NEW = 0,   		// Remove new node and leave old node

    NAME_COLLISION_REPLACE_OLD = 1,		// Remove old node and insert new node

    NAME_COLLISION_RENAME_NEW = 2,		// Leave old node and insert new node with the new name

	NAME_COLLISION_MERGE_FOLDERS = 3    // Add files from new folder into an old folder

} *PNAME_COLLISION_SOLUTION, NAME_COLLISION_SOLUTION;


//
// Enum that represents callback number
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// CN_FILE_TREE_PROGRESS_ADD            Item was add to the file tree
// CN_FILE_TREE_PROGRESS_REMOVE         Item was removed from the file tree
// CN_FILE_TREE_PROGRESS_IGNORE         Item was ignored during processing file tree
// CN_FILE_TREE_PROGRESS_NAME...		There are two nodes which have the same name
// CN_TARGET_FILE_ANALYZE_BEGIN         File internal structure (size, type etc) analyze started
// CN_TARGET_FILE_ANALYZE_END           File structure analyze completed
// CN_WAIT_CACHE_FULL_BEGIN             Toolkit started to wait for cache to become full
// CN_WAIT_CACHE_FULL_END               Toolkit finished to wait for cache fullness
// CN_SYNCHRONIZE_CACHE_BEGIN           Cache flushing to the media started
// CN_SYNCHRONIZE_CACHE_END             Cache flushing to the media completed
// CN_FIND_DEVICE                       Find device operation completed
// CD_CDVD_READ_PROGRESS                CD/DVD/Blu-Ray/HD-DVD read operation progress
// CN_CDVD_WRITE_PROGRESS               CD/DVD/Blu-Ray/HD-DVD write operation progress
// CN_CDVD_BUFFER_STATUS                CD/DVD/Blu-Ray/HD-DVD buffer status information queried
// CN_CDVD_TRACK_BEGIN                  CD/DVD/Blu-Ray/HD-DVD track processing started
// CN_CDVD_TRACK_END                    CD/DVD/Blu-Ray/HD-DVD track processing completed
// CN_CDVD_SPLIT_BEGIN                  CD/DVD/Blu-Ray/HD-DVD split section processing started
// CN_CDVD_SPLIT_END                    CD/DVD/Blu-Ray/HD-DVD split section processing completed
// CN_CDVD_READ_BAD_BLOCK_HIT           CD/DVD/Blu-Ray/HD-DVD read operation had hit a bad (unrecoverable) block
// CN_CDVD_READ_ECCEDC_BAD_BLOCK_HIT    CD/DVD/Blu-Ray/HD-DVD read operation had hit a ECC/EDC bad (recoverable) block
// CN_CDVD_READ_RETRY                   CD/DVD/Blu-Ray/HD-DVD read operation was retried
// CN_DVDPLUSRW_FORMAT_BEGIN            DVD+RW format operation started
// CN_DVDPLUSRW_FORMAT_EDN              DVD+RW format operation completed
// CN_DVDRAM_FORMAT_BEGIN               DVD-RAM format operation started
// CN_DVDRAM_FORMAT_EDN                 DVD-RAM format operation completed
// CN_BUFFER_UNDERRUN                   Buffer underrun condition happened
// CN_DVD_MEDIA_PADDING_SIZE			DVD media would be padded to 1GB size, additional info passed
// CN_DVD_MEDIA_PADDING_BEGIN			DVD media padding burn process started
// CN_DVD_MEDIA_PADDING_END				DVD media padding burn process completed
// CN_CDVD_READ_CANCEL_QUERY			CD/DVD/Blu-Ray/HD-DVD media processing plug-in queries cancel status
// CN_DVDRW_QUICK_FORMAT_BEGIN          DVD-RW quick format operation started
// CN_DVDRW_QUICK_FORMAT_END            DVD-RW quick format operation completed
// CN_DVD_TEST_WRITE_DISABLED			Test write is disabled (for DVD+R/RW, DVD-RAM or multisession DVD-RW)
// CN_CDVD_DPM_BEGIN                  	CD/DVD/Blu-Ray/HD-DVD DPM processing started
// CN_CDVD_DPM_END                    	CD/DVD/Blu-Ray/HD-DVD DPM processing completed
// CD_CDVD_DPM_PROGRESS                	CD/DVD/Blu-Ray/HD-DVD DPM operation progress
// CN_CDVD_VERIFY_PROGRESS              CD/DVD/Blu-Ray/HD-DVD verify operation completed
// CN_SAO_TRACK_WRITE_BEGIN				SAO track write started
// CN_SAO_TRACK_WRITE_END				SAO track write completed
// CN_DVD_MEDIA_PADDING_WRITE_PRO...	DVD media padding burn progress indication
// CN_CDVD_WRITE_BEGIN					CD/DVD/Blu-Ray/HD-DVD write operation started
// CN_CDVD_WRITE_END					CD/DVD/Blu-Ray/HD-DVD write operation completed
// CN_CDVD_VERIFY_BEGIN					CD/DVD/Blu-Ray/HD-DVD verify operation started
// CN_CDVD_VERIFY_END					CD/DVD/Blu-Ray/HD-DVD verify operation completed
// CN_BDRE_FORMAT_BEGIN            		BD-RE format operation started
// CN_BDRE_FORMAT_END              		BD-RE format operation completed
// </TABLE>

typedef enum _CALLBACK_NUMBER
{
    CN_FILE_TREE_PROGRESS_ADD = 0,      // Item was add to the file tree

    CN_FILE_TREE_PROGRESS_REMOVE,       // Item was removed from the file tree

    CN_FILE_TREE_PROGRESS_IGNORE,       // Item was ignored during processing file tree

    CN_FILE_TREE_PROGRESS_NAME_COLLISION,	// There are two nodes which have the same name

    CN_TARGET_FILE_ANALYZE_BEGIN,       // File internal structure (size, type etc) analyze started

    CN_TARGET_FILE_ANALYZE_END,         // File structure analyze completed

    CN_WAIT_CACHE_FULL_BEGIN,           // Toolkit started to wait for cache to become full

    CN_WAIT_CACHE_FULL_END,             // Toolkit finished to wait for cache fullness

    CN_SYNCHRONIZE_CACHE_BEGIN,         // Cache flushing to the media started

    CN_SYNCHRONIZE_CACHE_END,           // Cache flushing completed

    CN_FIND_DEVICE,                     // Find device operation completed

    CN_CDVD_READ_PROGRESS,              // CD/DVD/Blu-Ray/HD-DVD read operation progress

    CN_CDVD_WRITE_PROGRESS,             // CD/DVD/Blu-Ray/HD-DVD write operation progress

    CN_CDVD_BUFFER_STATUS,              // CD/DVD/Blu-Ray/HD-DVD buffer status information queried

    CN_CDVD_TRACK_BEGIN,                // CD/DVD/Blu-Ray/HD-DVD track processing started

    CN_CDVD_TRACK_END,                  // CD/DVD/Blu-Ray/HD-DVD track processing completed

    CN_CDVD_SPLIT_BEGIN,                // CD/DVD/Blu-Ray/HD-DVD split section processing started

    CN_CDVD_SPLIT_END,                  // CD/DVD/Blu-Ray/HD-DVD split section processing completed

    CN_CDVD_READ_BAD_BLOCK_HIT,         // CD/DVD/Blu-Ray/HD-DVD read operation had hit a bad (unrecoverable) block

    CN_CDVD_READ_ECCEDC_BAD_BLOCK_HIT,  // CD/DVD/Blu-Ray/HD-DVD read operation had hit a ECC/EDC bad (recoverable) block

    CN_CDVD_READ_RETRY,                 // CD/DVD/Blu-Ray/HD-DVD read operation was retried

    CN_DVDPLUSRW_FORMAT_BEGIN,          // DVD+RW format operation started

    CN_DVDPLUSRW_FORMAT_END,            // DVD+RW format operation completed

    CN_DVDRAM_FORMAT_BEGIN,             // DVD-RAM format operation started

    CN_DVDRAM_FORMAT_END,               // DVD-RAM format operation completed

    CN_BUFFER_UNDERRUN,                 // Buffer underrun condition happened

	CN_DVD_MEDIA_PADDING_SIZE,			// DVD media would be padded to 1GB size, additional info passed

	CN_DVD_MEDIA_PADDING_BEGIN,			// DVD media padding burn process started

	CN_DVD_MEDIA_PADDING_END,			// DVD media padding burn process completed

	CN_CDVD_READ_CANCEL_QUERY,			// CD/DVD/Blu-Ray/HD-DVD media processing plug-in queries cancel status

	CN_DVDRW_QUICK_FORMAT_BEGIN,		// DVD-RW quick format operation started

	CN_DVDRW_QUICK_FORMAT_END,			// DVD-RW quick format operation completed

	CN_DVD_TEST_WRITE_DISABLED,			// Test write is disabled (for DVD+R/RW, DVD-RAM or multisession DVD-RW)

	CN_CDVD_DPM_BEGIN,                  // CD/DVD/Blu-Ray/HD-DVD DPM processing started
	
	CN_CDVD_DPM_END,                   	// CD/DVD/Blu-Ray/HD-DVD DPM processing completed

	CN_CDVD_DPM_PROGRESS,              	// CD/DVD/Blu-Ray/HD-DVD DPM processing progress

	CN_CDVD_VERIFY_PROGRESS,            // CD/DVD/Blu-Ray/HD-DVD verify operation completed

	CN_SAO_TRACK_WRITE_BEGIN,			// SAO track write started

	CN_SAO_TRACK_WRITE_END,				// SAO track write completed

	CN_DVD_MEDIA_PADDING_WRITE_PROGRESS,	// DVD media padding burn progress indication

	CN_CDVD_WRITE_BEGIN,				// CD/DVD/Blu-Ray/HD-DVD write operation started

	CN_CDVD_WRITE_END,					// CD/DVD/Blu-Ray/HD-DVD write operation completed

	CN_CDVD_VERIFY_BEGIN,				// CD/DVD/Blu-Ray/HD-DVD verify operation started

	CN_CDVD_VERIFY_END,					// CD/DVD/Blu-Ray/HD-DVD verify operation completed

	CN_BDRE_FORMAT_BEGIN,    			// BD-RE format operation started

	CN_BDRE_FORMAT_END              	// BD-RE format operation completed

} *PCALLBACK_NUMBER, CALLBACK_NUMBER;


//
// Enum that represents raw read modes
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// READ_MODE_COOKED                     Cooked data
// READ_MODE_RAW                        Raw data
// READ_MODE_RAW_PQ                     Raw data + PQ sub-channel
// READ_MODE_RAW_RAW_PW                 Raw data + raw P-W sub-channel
// READ_MODE_PQ                         PQ sub-channel only (no main channel data)
// READ_MODE_RAW_PW                     Raw P-W sub-channel only (no main channel data)
// </TABLE>

typedef enum _READ_MODE
{
    READ_MODE_COOKED = 0,               // Cooked data

    READ_MODE_RAW,                      // Raw data

    READ_MODE_RAW_PQ,                   // Raw data + PQ sub-channel

    READ_MODE_RAW_RAW_PW,               // Raw data + raw P-W sub-channel

    READ_MODE_PQ,                       // PQ sub-channel only (no main channel data)

    READ_MODE_RAW_PW                    // Raw P-W sub-channel only (no main channel data)

} *PREAD_MODE, READ_MODE;


//
// Enum that represents write modes
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// WRITE_MODE_TRACK_AT_ONCE             Track-At-Once
// WRITE_MODE_SESSION_AT_ONCE           Session-At-Once
// WRITE_MODE_DISC_AT_ONCE_PQ           Disc-At-Once PQ
// WRITE_MODE_DISC_AT_ONCE_RAW_PW       Disc-At-Once raw P-W
// </TABLE>

typedef enum _WRITE_MODE
{
    WRITE_MODE_TRACK_AT_ONCE = 0,       // Track-At-Once

    WRITE_MODE_SESSION_AT_ONCE,         // Session-At-Once

    WRITE_MODE_DISC_AT_ONCE_PQ,         // Disc-At-Once PQ

    WRITE_MODE_DISC_AT_ONCE_RAW_PW      // Disc-At-Once raw P-W

} *PWRITE_MODE, WRITE_MODE;


//
// Enum that represents file tree
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// FILE_TREE_ISO9660                    ISO9660 file tree
// FILE_TREE_JOLIET                     ISO9660 file tree + Joliet extensions
// </TABLE>

typedef enum _FILE_TREE
{
    FILE_TREE_ISO9660 = 0,              // ISO9660 file tree

    FILE_TREE_JOLIET                    // ISO9660 file tree + Joliet extensions

} *PFILE_TREE, FILE_TREE;


//
// Enum that represents erase type
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// ERASE_TYPE_BLANK_DISC_FULL           Completely erase the rewritable disc
// ERASE_TYPE_BLANK_DISC_FAST           Erase only TOC, PMA and first track lead in on the rewritable disc
// ERASE_TYPE_BLANK_TRACK               Erase track only
// ERASE_TYPE_UNRESERVE_TRACK           Unreserve track that was reserved before
// ERASE_TYPE_BLANK_TRACK_TAIL          Erase track tail
// ERASE_TYPE_UNCLOSE_LAST_SESSION      Unclose last closed session
// ERASE_TYPE_BLANK_SESSION             Erase last session
// </TABLE>

typedef enum _ERASE_TYPE
{
    ERASE_TYPE_BLANK_DISC_FULL = 0,     // Completely erase the rewritable disc

    ERASE_TYPE_BLANK_DISC_FAST,         // Erase only TOC, PMA and first track lead in on the rewritable disc

    ERASE_TYPE_BLANK_TRACK,             // Erase track only

    ERASE_TYPE_UNRESERVE_TRACK,         // Unreserve track that was reserved before

    ERASE_TYPE_BLANK_TRACK_TAIL,        // Erase track tail

    ERASE_TYPE_UNCLOSE_LAST_SESSION,    // Unclose last closed session

    ERASE_TYPE_BLANK_SESSION            // Erase last session

} *PERASE_TYPE, ERASE_TYPE;


//
// Enum that represents inserted disc type
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// DISC_TYPE_UNKNOWN                    Unknown disc type
// DISC_TYPE_CDROM,                     CD-ROM
// DISC_TYPE_CDR,                       CD-R
// DISC_TYPE_CDRW,                      CD-RW
// DISC_TYPE_DVDROM,                    DVD-ROM
// DISC_TYPE_DVDR,                      DVD-R
// DISC_TYPE_DVDRAM,                    DVD-RAM
// DISC_TYPE_DVDRWRO,                   DVD-RW RO (Restricted Overwrite)
// DISC_TYPE_DVDRWSR,                   DVD-RW SR (Sequential Recording)
// DISC_TYPE_DVDPLUSRW,                 DVD+RW
// DISC_TYPE_DDCDROM,                   DD (Double Density) CD-ROM
// DISC_TYPE_DDCDR,                     DD (Double Density) CD-R
// DISC_TYPE_DDCRW                      DD (Double Density) CD-RW
// DISC_TYPE_DVDPLUSR                   DVD+R
// DISC_TYPE_NO_MEDIA					No media is inserted to the disc drive
// DISC_TYPE_DVDPLUSR_DL				DVD+R DL (Double Layer)
// DISC_TYPE_DVDR_DL					DVD-R DL (Dual Layer)
// DISC_TYPE_BDROM						BD-ROM (Blu-Ray ROM)
// DISC_TYPE_BDR						BD-R (Blu-Ray Disc Recordable)
// DISC_TYPE_BDRE						BD-RE (Blu-Ray Disc Recordable Erasable)
// DISC_TYPE_HDDVDROM					HD-DVD ROM
// DISC_TYPE_HDDVDR						HD-DVD Recordable
// DISC_TYPE_HDDVDRW					HD-DVD ReWritable
// </TABLE>

typedef enum _DISC_TYPE
{
    DISC_TYPE_UNKNOWN = 0,              // Unknown disc type

    DISC_TYPE_CDROM,                    // CD-ROM

    DISC_TYPE_CDR,                      // CD-R

    DISC_TYPE_CDRW,                     // CD-RW

    DISC_TYPE_DVDROM,                   // DVD-ROM

    DISC_TYPE_DVDR,                     // DVD-R

    DISC_TYPE_DVDRAM,                   // DVD-RAM

    DISC_TYPE_DVDRWRO,                  // DVD-RW RO (Restricted Overwrite)

    DISC_TYPE_DVDRWSR,                  // DVD-RW SR (Sequential Recording)

    DISC_TYPE_DVDPLUSRW,                // DVD+RW

    DISC_TYPE_DDCDROM,                  // DD (Double Density) CD-ROM

    DISC_TYPE_DDCDR,                    // DD (Double Density) CD-R

    DISC_TYPE_DDCDRW,                   // DD (Double Density) CD-RW

    DISC_TYPE_DVDPLUSR,                 // DVD+R

	DISC_TYPE_NO_MEDIA,					// No media is inserted to the disc drive

	DISC_TYPE_DVDPLUSR_DL,				// DVD+R DL (Double Layer)

	DISC_TYPE_DVDR_DL,					// DVD-R DL (Dual Layer)

	DISC_TYPE_BDROM,					// BD-ROM (Blu-Ray ROM)

	DISC_TYPE_BDR,						// BD-R (Blu-Ray Disc Recordable)

	DISC_TYPE_BDRE,						// BD-RE (Blu-Ray Disc Recordable Erasable)

	DISC_TYPE_HDDVDROM,					// HD-DVD ROM

	DISC_TYPE_HDDVDR,					// HD-DVD Recordable

	DISC_TYPE_HDDVDRW					// HD-DVD ReWritable

} *PDISC_TYPE, DISC_TYPE;


//
// StarWave callback reasons we'll be using
//
// <TABLE>
// Member                               				Definition
// ----------                           				---------------
// STARBURN_STARWAVE_CALLBACK_REASON_UNKNOWN			Unknown call reason 
// STARBURN_STARWAVE_CALLBACK_REASON_PROGRESS 			Progress indication reason 
// </TABLE>

typedef enum _STARBURN_STARWAVE_CALLBACK_REASON
{
	STARBURN_STARWAVE_CALLBACK_REASON_UNKNOWN = 0,		// Unknown call reason 

	STARBURN_STARWAVE_CALLBACK_REASON_PROGRESS 			// Progress indication reason 

} STARBURN_STARWAVE_CALLBACK_REASON, *PSTARBURN_STARWAVE_CALLBACK_REASON, **PPSTARBURN_STARWAVE_CALLBACK_REASON;


//
// Compression templates we'll be using, pointer to compression templates and pointer to pointer to compression templates,
// all of the compression templates are 44 kHz, stereo, 16-bit, CBR or VBR
//
// <TABLE>
// Member                               				Definition
// ----------                           				---------------
// STARBURN_STARWAVE_COMPRESSION_NONE 					Lossless PCM WAV uncompressed stream 
// STARBURN_STARWAVE_COMPRESSION_WMA_LOSS... 			Lossless WMA compressed stream, VBR at Quality 100 
// STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q10 			WMA compressed stream, VBR at Quality 10 
// STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q25 			WMA compressed stream, VBR at Quality 25 
// STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q50 			WMA compressed stream, VBR at Quality 50 
// STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q75 			WMA compressed stream, VBR at Quality 75 
// STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q90 			WMA compressed stream, VBR at Quality 90 
// STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q98 			WMA compressed stream, VBR at Quality 98 
// STARBURN_STARWAVE_COMPRESSION_WMA_CBR_32K 			WMA compressed stream, CBR at 32 Kbps 
// STARBURN_STARWAVE_COMPRESSION_WMA_CBR_48K 			WMA compressed stream, CBR at 48 Kbps 
// STARBURN_STARWAVE_COMPRESSION_WMA_CBR_64K 			WMA compressed stream, CBR at 64 Kbps 
// STARBURN_STARWAVE_COMPRESSION_WMA_CBR_80K 			WMA compressed stream, CBR at 80 Kbps 
// STARBURN_STARWAVE_COMPRESSION_WMA_CBR_96K 			WMA compressed stream, CBR at 96 Kbps 
// STARBURN_STARWAVE_COMPRESSION_WMA_CBR_128K 			WMA compressed stream, CBR at 128 Kbps 
// STARBURN_STARWAVE_COMPRESSION_WMA_CBR_160K 			WMA compressed stream, CBR at 160 Kbps 
// STARBURN_STARWAVE_COMPRESSION_WMA_CBR_192K 			WMA compressed stream, CBR at 192 Kbps 
// STARBURN_STARWAVE_COMPRESSION_WMA_CBR_256K 			WMA compressed stream, CBR at 256 Kbps 
// STARBURN_STARWAVE_COMPRESSION_WMA_CBR_320K 			WMA compressed stream, CBR at 320 Kbps 
// </TABLE>

typedef enum _STARBURN_STARWAVE_COMPRESSION 
{
	STARBURN_STARWAVE_COMPRESSION_NONE = 0,						// Lossless PCM WAV uncompressed stream 

	STARBURN_STARWAVE_COMPRESSION_WMA_LOSSLESS_VBR_Q100 = 1,	// Lossless WMA compressed stream, VBR at Quality 100 

	STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q10 = 10,				// WMA compressed stream, VBR at Quality 10 

	STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q25 = 25,				// WMA compressed stream, VBR at Quality 25 

	STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q50 = 50,				// WMA compressed stream, VBR at Quality 50 

	STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q75 = 75,				// WMA compressed stream, VBR at Quality 75 

	STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q90 = 90,				// WMA compressed stream, VBR at Quality 90 

	STARBURN_STARWAVE_COMPRESSION_WMA_VBR_Q98 = 98,				// WMA compressed stream, VBR at Quality 98 

	STARBURN_STARWAVE_COMPRESSION_WMA_CBR_32K = 32000, 			// WMA compressed stream, CBR at 32 Kbps 

	STARBURN_STARWAVE_COMPRESSION_WMA_CBR_48K = 48000,			// WMA compressed stream, CBR at 48 Kbps 

	STARBURN_STARWAVE_COMPRESSION_WMA_CBR_64K = 64000,			// WMA compressed stream, CBR at 64 Kbps 

	STARBURN_STARWAVE_COMPRESSION_WMA_CBR_80K = 80000, 			// WMA compressed stream, CBR at 80 Kbps 

	STARBURN_STARWAVE_COMPRESSION_WMA_CBR_96K = 96000,			// WMA compressed stream, CBR at 96 Kbps 

	STARBURN_STARWAVE_COMPRESSION_WMA_CBR_128K = 128000,		// WMA compressed stream, CBR at 128 Kbps 

	STARBURN_STARWAVE_COMPRESSION_WMA_CBR_160K = 160000,		// WMA compressed stream, CBR at 160 Kbps 

	STARBURN_STARWAVE_COMPRESSION_WMA_CBR_192K = 192000,		// WMA compressed stream, CBR at 192 Kbps 

	STARBURN_STARWAVE_COMPRESSION_WMA_CBR_256K = 256000,		// WMA compressed stream, CBR at 256 Kbps 

	STARBURN_STARWAVE_COMPRESSION_WMA_CBR_320K = 320000			// WMA compressed stream, CBR at 320 Kbps 

} STARBURN_STARWAVE_COMPRESSION, *PSTARBURN_STARWAVE_COMPRESSION, **PPSTARBURN_STARWAVE_COMPRESSION;


//
// Enum that represents MP3 quality for conversion
//
// <TABLE>
// Member                                    Definition
// ----------                                ---------------
// STARBURN_STARWAVE2_QM_FAST				 Fast mode
// STARBURN_STARWAVE2_QM_STANDARD			 Standard mode
// STARBURN_STARWAVE2_QM_HIGH				 High quality mode
// </TABLE>

typedef enum _STARBURN_STARWAVE2_QUALITY_MODE
{
	STARBURN_STARWAVE2_QM_FAST = 0, 

	STARBURN_STARWAVE2_QM_STANDARD, 

	STARBURN_STARWAVE2_QM_HIGH

} STARBURN_STARWAVE2_QUALITY_MODE, *PSTARBURN_STARWAVE2_QUALITY_MODE;


//
// Structure that represents conversion mode
//
// <TABLE>
// Member                     Definition
// ----------                 ---------------
// OGG_MODE0				  VBR, variable bit rate
// OGG_MODE1				  ABR, average bit rate
// OGG_MODE2				  CBR, constant bit rate
// OGG_MODE_MAX				  Now equal to OGG_MODE2
// MP3_MODE0			      CBR, constant bit rate	
// MP3_MODE1				  ABR, average bit rate
// MP3_MODE2                  VBR, variable bit rate
// MP3_MODE_MAX				  Now equal to MP3_MODE2
// </TABLE>

typedef enum _STARBURN_STARWAVE2_CONVERSION_MODE 
{
	STARBURN_STARWAVE2_OGG_MODE0, 

	STARBURN_STARWAVE2_OGG_MODE1, 

	STARBURN_STARWAVE2_OGG_MODE2, 

	STARBURN_STARWAVE2_OGG_MODE_MAX = STARBURN_STARWAVE2_OGG_MODE2,

	STARBURN_STARWAVE2_MP3_MODE0, 

	STARBURN_STARWAVE2_MP3_MODE1, 

	STARBURN_STARWAVE2_MP3_MODE2, 

	STARBURN_STARWAVE2_MP3_MODE_MAX = STARBURN_STARWAVE2_MP3_MODE2

} STARBURN_STARWAVE2_CONVERSION_MODE, *PSTARBURN_STARWAVE2_CONVERSION_MODE;

//
// Store original structure packing and enable 1 UCHAR packing
//

#pragma pack( push, 1 )

//
// Structure that represents initialization parameters for audio conversion
//
// <TABLE>
// Member									Definition
// ----------								---------------
// m__STARBURN_STARWAVE2_CONVERSION_MODE	Conversion mode 
// m__FLOAT__flQuality						Quality level from 0. (lo) to 1. (hi) (use for OGG_MODE0)
// m__LONG__nQuality						Quality level from 1 to 9 (use for MP3_MODE2)
// m__LONG__maxBitrate						Maximum bit rate (use for OGG_MODE1/OGG_MODE2)
// m__LONG__nominalBitrate					Nominal bit rate (use for OGG_MODE1/OGG_MODE2/MP3_MODE0/MP3_MODE1)
// m__LONG__minBitrate						Minimum bit rate (use for OGG_MODE1/OGG_MODE2)
// m__STARBURN_STARWAVE2_QUALITY_MODE		Quality mode (use for /MP3_MODE0/MP3_MODE1/MP3_MODE2)
// </TABLE>

typedef struct _STARBURN_STARWAVE2_INIT_PARAMS
{
	STARBURN_STARWAVE2_CONVERSION_MODE m__STARBURN_STARWAVE2_CONVERSION_MODE;		

	FLOAT m__FLOAT__flQuality;

	LONG m__LONG__nQuality;

	LONG m__LONG__maxBitrate;

	LONG m__LONG__nominalBitrate;

	LONG m_LONG__minBitrate;

	STARBURN_STARWAVE2_QUALITY_MODE m__STARBURN_STARWAVE2_QUALITY_MODE;

} STARBURN_STARWAVE2_INIT_PARAMS, *PSTARBURN_STARWAVE2_INIT_PARAMS;

//
// Restore original structure packing
//

#pragma pack( pop )


//
// Description
//
// Callback type (function of this type must be passed as callback)
//
// Parameters
//
// p__CALLBACK_NUMBER - Callback number
//
// p__PVOID__CallbackContext - Passed callback context
//
// p__PVOID__CallbackSpecial1 - Special parameter 1
//
// p__PVOID__CallbackSpecial2 - Special parameter 2
//
// Remarks
//
// <TABLE>
// Callback number                              		Special parameter 1											Special parameter 2
// ------------------------------------					-------------------------------------------					----------------------------------------
// CN_FILE_TREE_PROGRESS_ADD							(PCHAR) Adding item name									Not used
// CN_FILE_TREE_PROGRESS_REMOVE							(PCHAR) Removing item name									Not used
// CN_FILE_TREE_PROGRESS_IGNORE							(PCHAR) Ignoring item name									Not used
// CN_FILE_TREE_PROGRESS_NAME_COLLISION					(PCHAR) Collision item name									Not used
// CN_TARGET_FILE_ANALYZE_BEGIN 						Not used													Not used
// CN_TARGET_FILE_ANALYZE_END							(PLARGE_INTEGER) Target file size in UCHARs					(PLARGE_INTEGER) Target file size in LBs
// CN_WAIT_CACHE_FULL_BEGIN 							(PULONG) Wait time in milliseconds							Not used
// CN_WAIT_CACHE_FULL_END 								Not used													Not used
// CN_SYNCHRONIZE_CACHE_BEGIN							Not used													Not used 
// CN_SYNCHRONIZE_CACHE_END 							Not used													Not used
// CN_FIND_DEVICE										(PSCSI_DEVICE_ADDRESS) SCSI device address					Not used
// CN_CDVD_READ_PROGRESS								(PLARGE_INTEGER) Track size in LBs							(PLARGE_INTEGER) LBs readen
// CN_CDVD_WRITE_PROGRESS								(PLARGE_INTEGER) File size in LBs							(PLARGE_INTEGER) LBs written
// CN_CDVD_BUFFER_STATUS								(PULONG) Buffer size in UCHARs								(PULONG) Buffer free size in UCHARs
// CN_CDVD_TRACK_BEGIN									(PULONG) Started track number								(PULONG) Total number of tracks
// CN_CDVD_TRACK_END									(PULONG) Completed track number								(PULONG) Total number of track
// CN_CDVD_SPLIT_BEGIN									(PLONG) Started split section number						(PLONG) Total number of tracks
// CN_CDVD_SPLIT_END									(PLONG) Completed split section number						(PLONG) Total number of tracks
// CN_CDVD_READ_BAD_BLOCK_HIT							(PLONG)	LBA of bad blocks									(PULONG) Number of bad blocks
// CN_CDVD_READ_ECCEDC_BAD_BLOCK_HIT					(PLONG)	LBA of ECC/EDC bad blocks							(PULONG) Number of ECC/EDC bad blocks	
// CN_CDVD_READ_RETRY									(PLONG)	LBA of retry reading blocks							(PULONG) Number of retry reading LBs
// CN_DVDPLUSRW_FORMAT_BEGIN							Not used													Not used
// CN_DVDPLUSRW_FORMAT_END								Not used													Not used
// CN_DVDRAM_FORMAT_BEGIN								Not used													Not used
// CN_DVDRAM_FORMAT_END									Not used													Not used
// CN_BUFFER_UNDERRUN									Not used													Not used		
// CN_DVD_MEDIA_PADDING_SIZE							(PLARGE_INTEGER) Target file size in LBs					(PULONG) Track padding size in LBs
// CN_DVD_MEDIA_PADDING_BEGIN							Not used													Not used
// CN_DVD_MEDIA_PADDING_END								Not used													Not used
// CN_CDVD_READ_CANCEL_QUERY							Undocumented												Undocumented
// CN_DVDRW_QUICK_FORMAT_BEGIN							Not used													Not used
// CN_DVDRW_QUICK_FORMAT_END							Not used													Not used
// CN_DVD_TEST_WRITE_DISABLED							Not used													Not used
// CN_CDVD_DPM_BEGIN									Undocumented												Undocumented
// CN_CDVD_DPM_END					               		Undocumented												Undocumented
// CN_CDVD_DPM_PROGRESS									Undocumented												Undocumented
// CN_CDVD_VERIFY_PROGRESS								(PLONG) Processed LBs										(PLONG) Size in LBs
// CN_SAO_TRACK_WRITE_BEGIN								(PLONG) Track index											Not used
// CN_SAO_TRACK_WRITE_END								(PLONG) Track index											Not used
// CN_DVD_MEDIA_PADDING_WRITE_PROGRESS					(PULONG) Track padding size in LBs							(PLONG) Padding left in LBs
// CN_CDVD_WRITE_BEGIN									Not used													Not used
// CN_CDVD_WRITE_END									Not used													Not used
// CN_CDVD_VERIFY_BEGIN									Not used													Not used
// CN_CDVD_VERIFY_END									Not used													Not used
// </TABLE>

typedef
VOID
( __stdcall *PCALLBACK )(
    IN CALLBACK_NUMBER p__CALLBACK_NUMBER,
    IN PVOID p__PVOID__CallbackContext,
    OUT PVOID p__PVOID__CallbackSpecial1,
    OUT PVOID p__PVOID__CallbackSpecial2
    );


//
// Description
//
// StarWave callback passed to I/O functions. Return anything except zero from it to cancel I/O operation
//
// Parameters
//
// p__ULONG__Reason - Callback reason (see STARBURN_STARWAVE_CALLBACK_REASON enumeration)
//
// p__ULONG__Parameter - Callback parameter
//
// p__PVOID__Context - Passed callback context
//
// Remarks
//
// <TABLE>
// Callback reason                              		Callback parameter
// ------------------------------------------			-------------------------------------------
// STARBURN_STARWAVE_CALLBACK_REASON_PROGRESS			Completion percent
// </TABLE>

typedef 
ULONG 
( __stdcall *PSTARBURN_STARWAVE_CALLBACK )( 
	IN ULONG p__ULONG__Reason,
	IN ULONG p__ULONG__Parameter,
	IN PVOID p__PVOID__Context 
	);


//
// Description
//
// StarBurn UDF2 progress callback
//
// Parameters
//
// p__PCHAR__Name - Pointer to the file name added
//
// p__PCHAR__PathName - Pointer to the full path & name of the file added
//
// p__PVOID__Context - Passed callback context
//
// Remarks
//
// Check StarBurn_UDF2_DirectoryProcessEx(...) API call

typedef 
LONG 
( __stdcall *PSTARBURN_UDF2_PROGRESS_CALLBACK )( 
	PCHAR p__PCHAR__Name, 
	PCHAR p__PCHAR__PathName, 
	PVOID p__PVOID__Context 
	);


//
// Description
//
// StarBurn UDF2 UNICODE progress callback
//
// Parameters
//
// p__PUSHORT__UnicodeName - Pointer to the UNICODE file name added
//
// p__PUSHORT__UnicodePathName - Pointer to the UNICODE full path & name of the file added
//
// p__PVOID__Context - Passed callback context
//
// Remarks
//
// Check StarBurn_UDF2_DirectoryUnicodeProcessEx(...) API call

typedef 
LONG 
( __stdcall *PSTARBURN_UDF2_UNICODE_PROGRESS_CALLBACK )( 
	PUSHORT p__PUSHORT__UnicodeName, 
	PUSHORT p__PUSHORT__UnicodePathName, 
	PVOID p__PVOID__Context 
	);


//
// Store original structure packing and enable 1 UCHAR packing
//

#pragma pack( push, 1 )


//
// Structure that represents StarPort device list entry
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__LONG__Index						StarPort device index
// m__LONG__TargetId					StarPort device TargetId
// m__CHAR__Name						StarPort device name
// </TABLE>

typedef struct _STARPORT_DEVICE_LIST_ENTRY
{
	LONG m__LONG__Index;				// StarPort device index

	LONG m__LONG__TargetId;				// StarPort device TargetId

	CHAR m__CHAR__Name[ STARPORT_DEVICE_NAME_SIZE_IN_UCHARS ];	// StarPort device name

} **PPSTARPORT_DEVICE_LIST_ENTRY, *PSTARPORT_DEVICE_LIST_ENTRY, STARPORT_DEVICE_LIST_ENTRY;


//
// Structure that represents StarPort device list 
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__LONG__NumberOfEntries				Number of StarPort device list entries
// m__STARPORT_DEVICE_LIST_ENTRY		StarPort device list entries 
// </TABLE>

typedef struct _STARPORT_DEVICE_LIST
{
	LONG m__LONG__NumberOfEntries;		// Number of StarPort device list entries

	STARPORT_DEVICE_LIST_ENTRY m__STARPORT_DEVICE_LIST_ENTRY[ 1 ];	// StarPort device list entries

} **PPSTARPORT_DEVICE_LIST, *PSTARPORT_DEVICE_LIST, STARPORT_DEVICE_LIST;


//
// Structure that represents information about name collision
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__BOOLEAN__IsJolietName             Indicates the format of the m__UCHAR__Name
// m__UCHAR__Name                       The node name (CHAR for ISO9660 or USHORT for Joliet)
// m__PCHAR__OldAbsoluteName            Absolute file name of the old file node
// m__ULONG__OldFileAttributes			Old file attributes
// m__PCHAR__NewAbsoluteName            Absolute file name of the new file node
// m__ULONG__NewFileAttributes			New file attributes
// m__NAME_COLLISION_SOLUTION           The solution of the collision (what action has been performed)
// </TABLE>

typedef struct _NAME_COLLISION_INFO
{
    BOOLEAN m__BOOLEAN__IsJolietName;					// Indicates the format of the m__UCHAR__Name

    UCHAR m__UCHAR__Name[ MAX_PATH * 2 ];              	// The node name (CHAR for ISO9660 or USHORT for Joliet)

    PCHAR m__PCHAR__OldAbsoluteName;					// Absolute file name of the old file node

    ULONG m__ULONG__OldFileAttributes;					// Old file attributes

    PCHAR m__PCHAR__NewAbsoluteName;					// Absolute file name of the new file node

    ULONG m__ULONG__NewFileAttributes;					// New file attributes

    NAME_COLLISION_SOLUTION m__NAME_COLLISION_SOLUTION;	// The solution of the collision (what action has been performed)

} *PNAME_COLLISION_INFO, NAME_COLLISION_INFO;


//
// Structure that represents WAVE format chunk
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__USHORT__Format                    Format
// m__USHORT__Channels                  Number of channels
// m__ULONG__SamplesPerSecond           Number of samples per second
// m__ULONG__AverageSamplesPerSecond    Number of average samples per second
// m__USHORT__Alignment                 Alignment
// m__USHORT__BitsPerSample             Number of bits in single sample
// </TABLE>

typedef struct _WAVE_FORMAT_CHUNK
{
    USHORT m__USHORT__Format;  					// Format

    USHORT m__USHORT__Channels;					// Number of channels

    ULONG m__ULONG__SamplesPerSecond;			// Number of samples per second

    ULONG m__ULONG__AverageSamplesPerSecond;	// Number of average samples per second

    USHORT m__USHORT__Alignment;				// Alignment

    USHORT m__USHORT__BitsPerSample;			// Number of bits in single sample

} *PWAVE_FORMAT_CHUNK, WAVE_FORMAT_CHUNK;


//
// Structure that represents WAVE file header
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__ULONG__Riff                       Riff signature
// m__ULONG__Length                     Length of data section (w/o header) in UCHARs
// m__ULONG__Wave                       Wave signature
// m__ULONG__FormatTag                  Format tag
// m__ULONG__FormatLength               Format length (size of WAVE_FORMAT_CHUNK in UCHARs)
// m__WAVE_FORMAT_CHUNK                 WAVE format chunk (see WAVE_FORMAT_CHUNK for more details)
// m__ULONG__DataTag                    Data tag
// m__ULONG__DataLenght                 Data length in UCHARs
// </TABLE>

typedef struct _WAVE_FILE_HEADER
{
    ULONG m__ULONG__Riff;           		// Riff signature

    ULONG m__ULONG__Length;					// Length of data section (w/o header) in UCHARs

    ULONG m__ULONG__Wave;					// Wave signature

    ULONG m__ULONG__FormatTag;				// Format tag

    ULONG m__ULONG__FormatLength;			// Format length (size of WAVE_FORMAT_CHUNK in UCHARs)

    WAVE_FORMAT_CHUNK m__WAVE_FORMAT_CHUNK;	// WAVE format chunk (see WAVE_FORMAT_CHUNK for more details)

    ULONG m__ULONG__DataTag;				// Data tag

    ULONG m__ULONG__DataLength;				// Data length in UCHARs

} *PWAVE_FILE_HEADER, WAVE_FILE_HEADER;


//
// Structure that represents CDB failure information
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__BOOLEAN__IsValid                  Is this data valid (structure was really filled)
// m__UCHAR__CDBSizeInUCHARs            CDB size in UCHARs
// m__UCHAR__CDB[ 16 ]                  CDB dump
// m__UCHAR__SenseSizeInUCHARs          SCSI sense size in UCHARs
// m__UCHAR__Sense[ 32 ]                SCSI sense dump
// m__UCHAR__TransportStatus            SCSI transport status
// m__UCHAR__TargetStatus               SCSI target status
// m__UCHAR__HostAdapterStatus          SCSI host adapter status
// </TABLE>

typedef struct _CDB_FAILURE_INFORMATION
{
    BOOLEAN m__BOOLEAN__IsValid;        // Is this data valid (structure was really filled)

    UCHAR m__UCHAR__CDBSizeInUCHARs;    // CDB size in UCHARs

    UCHAR m__UCHAR__CDB[ 16 ];          // CDB dump

    UCHAR m__UCHAR__SenseSizeInUCHARs;  // SCSI sense size in UCHARs

    UCHAR m__UCHAR__Sense[ 32 ];        // SCSI sense dump

    UCHAR m__UCHAR__TransportStatus;    // SCSI transport status

    UCHAR m__UCHAR__TargetStatus;       // SCSI target status

    UCHAR m__UCHAR__HostAdapterStatus;  // SCSI host adapter status

} *PCDB_FAILURE_INFORMATION, CDB_FAILURE_INFORMATION;


//
// Structure that represents Track information
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__BOOLEAN__IsValid                  Is this data valid (structure was really filled)
// m__UCHAR__TrackNumber                Track number of this track  
// m__UCHAR__SessionNumber              Session number that contains this track
// m__UCHAR__TrackMode                  Track mode
// m__BOOLEAN__IsCopy                   Is this track second or higher generation copy
// m__BOOLEAN__IsDamage                 Is track damaged
// m__UCHAR__DataMode                   Data mode on the track
// m__BOOLEAN__IsFixedPacket            Is fixed packet used on this track
// m__BOOLEAN__IsPacket                 Is packet recording used on the track
// m__BOOLEAN__IsBlank                  Is track blank
// m__BOOLEAN__IsReserved               Is track reserved 
// m__BOOLEAN__IsNextWritable...        Is NWA (Next Writable Address) valid
// m__LONG__TrackStartAddress           Starting address (LBA or MSF) for this track
// m__LONG__NextWritableAddress         NWA (Next Writable Address)
// m__LONG__FreeLBs                     Free logical blocks on this track
// m__LONG__FixedPacketSize...          Fixed packet size in UCHARs
// </TABLE>

typedef struct _STARBURN_TRACK_INFORMATION 
{
    BOOLEAN m__BOOLEAN__IsValid;					// Is this data valid (structure was really filled)					

    UCHAR m__UCHAR__TrackNumber;                    // Track number of this track  

    UCHAR m__UCHAR__SessionNumber;                  // Session number that contains this track

    UCHAR m__UCHAR__TrackMode;                      // Track mode

    BOOLEAN m__BOOLEAN__IsCopy;                     // Is this track second or higher generation copy

    BOOLEAN m__BOOLEAN__IsDamage;                   // Is track damaged

    UCHAR m__UCHAR__DataMode;                       // Data mode on the track

    BOOLEAN m__BOOLEAN__IsFixedPacket;              // Is fixed packet used on this track

    BOOLEAN m__BOOLEAN__IsPacket;                   // Is packet recording used on the track

    BOOLEAN m__BOOLEAN__IsBlank;                    // Is track blank

    BOOLEAN m__BOOLEAN__IsReserved;                 // Is track reserved

    BOOLEAN m__BOOLEAN__IsNextWritableAddressValid;	// Is NWA (Next Writable Address) valid

    LONG m__LONG__TrackStartAddress;                // Starting address (LBA or MSF) for this track

    LONG m__LONG__NextWritableAddress;              // NWA (Next Writable Address)

    LONG m__LONG__FreeLBs;                          // Free logical blocks on this track

    LONG m__LONG__FixedPacketSizeInLBs;          	// Fixed packet size in LBs

} *PSTARBURN_TRACK_INFORMATION, STARBURN_TRACK_INFORMATION;

//
// Structure that represents Track information extended
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__BOOLEAN__IsValid                  Is this data valid (structure was really filled)
// m__UCHAR__TrackNumber                Track number of this track  
// m__UCHAR__SessionNumber              Session number that contains this track
// m__UCHAR__TrackMode                  Track mode
// m__BOOLEAN__IsCopy                   Is this track second or higher generation copy
// m__BOOLEAN__IsDamage                 Is track damaged
// m__UCHAR__DataMode                   Data mode on the track
// m__BOOLEAN__IsFixedPacket            Is fixed packet used on this track
// m__BOOLEAN__IsPacket                 Is packet recording used on the track
// m__BOOLEAN__IsBlank                  Is track blank
// m__BOOLEAN__IsReserved               Is track reserved 
// m__BOOLEAN__IsNextWritable...        Is NWA (Next Writable Address) valid
// m__LONG__TrackStartAddress           Starting address (LBA or MSF) for this track
// m__LONG__LastRecordedAddress         Last Recorded Address (LBA or MSF) for this track
// m__LONG__NextWritableAddress         NWA (Next Writable Address)
// m__LONG__FreeLBs                     Free logical blocks on this track
// m__LONG__FixedPacketSize...          Fixed packet size in UCHARs
// </TABLE>

typedef struct _STARBURN_TRACK_INFORMATION_EX 
{
	BOOLEAN m__BOOLEAN__IsValid;					// Is this data valid (structure was really filled)					

	UCHAR m__UCHAR__TrackNumber;                    // Track number of this track  

	UCHAR m__UCHAR__SessionNumber;                  // Session number that contains this track

	UCHAR m__UCHAR__TrackMode;                      // Track mode

	BOOLEAN m__BOOLEAN__IsCopy;                     // Is this track second or higher generation copy

	BOOLEAN m__BOOLEAN__IsDamage;                   // Is track damaged

	UCHAR m__UCHAR__DataMode;                       // Data mode on the track

	BOOLEAN m__BOOLEAN__IsFixedPacket;              // Is fixed packet used on this track

	BOOLEAN m__BOOLEAN__IsPacket;                   // Is packet recording used on the track

	BOOLEAN m__BOOLEAN__IsBlank;                    // Is track blank

	BOOLEAN m__BOOLEAN__IsReserved;                 // Is track reserved

	BOOLEAN m__BOOLEAN__IsNextWritableAddressValid;	// Is NWA (Next Writable Address) valid

	LONG m__LONG__TrackStartAddress;                // Starting address (LBA or MSF) for this track

	LONG m__LONG__LastRecordedAddress;				// Last Recorded Address (LBA or MSF) for this track

	LONG m__LONG__NextWritableAddress;              // NWA (Next Writable Address)

	LONG m__LONG__FreeLBs;                          // Free logical blocks on this track

	LONG m__LONG__FixedPacketSizeInLBs;          	// Fixed packet size in LBs

} *PSTARBURN_TRACK_INFORMATION_EX, STARBURN_TRACK_INFORMATION_EX;

//
// Structure that represents Disc information
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__BOOLEAN__IsValid                  Is this data valid (structure was really filled)
// m__UCHAR__DiscStatus                 Disc status (See DISC_STATUS_XXX constants)
// m__UCHAR__LastSessionStatus          Last session status (See LAST_SESSION_XXX constants)
// m__BOOLEAN__IsErasable               Is disc erasable (CD-RW or DVD-RW or DVD+RW or DVD-RAM)
// m__UCHAR__FirstTrackNumber           First track number on the disc
// m__UCHAR__NumberOfSessions           Number of sessions on the disc
// m__UCHAR__LastSessionFirstTrack      First track number of last complete session on the disc
// m__UCHAR__LastSessionLastTrack       Last track number of last complete session on the disc
// m__BOOLEAN__IsGEN                    Unrestricted use, when set to one - every application can write to the disc
// m__BOOLEAN__IsDBCValid               Is Disc Bar Code field valid
// m__BOOLEAN__IsDIDValid               Is Disc Identification field Valid
// m__UCHAR__DiscType                   Disc type (See DISC_TYPE_XXX constants)
// m__UCHAR__DiscIdentification         Disc identification number recorded in the PMA, see m__UCHAR__IsDIDValid 
// m__UCHAR__LastSessionLeadId          MSF of last session lead in start time
// m__UCHAR__LastPossibleStartTime      Last possible start time for lead out on this disc
// m__UCHAR__DiscBarCode                Disc bar code stored here if the device is capable of reading disc bar codes
// m__UCHAR__NumberOfOPCEntries         Number of optimum power calibration entries at the end of this structure
// </TABLE>

typedef struct _STARBURN_DISC_INFORMATION 
{
    BOOLEAN m__BOOLEAN__IsValid;  				// Is this data valid (structure was really filled)

    UCHAR m__UCHAR__DiscStatus;             	// Disc status (See DISC_STATUS_XXX constants)

    UCHAR m__UCHAR__LastSessionStatus;      	// Last session status (See LAST_SESSION_XXX constants)

    BOOLEAN m__BOOLEAN__IsErasable;         	// Is disc erasable (CD-RW or DVD-RW or DVD+RW or DVD-RAM)

    UCHAR m__UCHAR__FirstTrackNumber;       	// First track number on the disc

    UCHAR m__UCHAR__NumberOfSessions;       	// Number of sessions on the disc

    UCHAR m__UCHAR__LastSessionFirstTrack;  	// First track number of last complete session on the disc

    UCHAR m__UCHAR__LastSessionLastTrack;   	// Last track number of last complete session on the disc

    BOOLEAN m__BOOLEAN__IsGEN;              	// Unrestricted use, when set to one - every application can write to the disc

    BOOLEAN m__BOOLEAN__IsDBCValid;             // Is Disc Bar Code field valid

    BOOLEAN m__BOOLEAN__IsDIDValid;             // Is Disc Identification field Valid

    UCHAR m__UCHAR__DiscType;                   // Disc type (See DISC_TYPE_XXX constants)

    UCHAR m__UCHAR__DiscIdentification[ 4 ];    // Disc identification number recorded in the PMA, see m__UCHAR__IsDIDValid 

    UCHAR m__UCHAR__LastSessionLeadIn[ 4 ]; 	// MSF of last session lead in start time

    UCHAR m__UCHAR__LastPossibleStartTime[ 4 ];	// Last possible start time for lead out on this disc

    UCHAR m__UCHAR__DiscBarCode[ 8 ];           // Disc bar code stored here if the device is capable of reading disc bar codes

    UCHAR m__UCHAR__NumberOfOPCEntries;         // Number of optimum power calibration entries at the end of this structure

} *PSTARBURN_DISC_INFORMATION, STARBURN_DISC_INFORMATION;


//
// Structure that represents SCSI device address
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__BOOLEAN__IsValid                  Is this data valid (structure was really filled)
// m__UCHAR__PortID                     Port ID - Logical SCSI adapter ID if ASPI is used
// m__UCHAR__BusID                      Bus ID - 0 if ASPI is used
// m__UCHAR__TargetID                   Target ID
// m__UCHAR__LUN                        LUN (Logical Unit Number)
// </TABLE>

typedef struct _SCSI_DEVICE_ADDRESS
{
    BOOLEAN m__BOOLEAN__IsValid;		// Is this data valid (structure was really filled)

    UCHAR m__UCHAR__PortID;				// Port Id - Logical SCSI adapter ID if ASPI is used

    UCHAR m__UCHAR__BusID;				// Bus ID - 0 if ASPI is used

    UCHAR m__UCHAR__TargetID;			// Target Id

    UCHAR m__UCHAR__LUN;				// LUN (Logical Unit Number)

} *PSCSI_DEVICE_ADDRESS, SCSI_DEVICE_ADDRESS;


//
// Structure that represents TOC entry
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__BOOLEAN__IsValid                  Is this data valid (structure was really filled)
// m__UCHAR__TrackNumber                Track number
// m__UCHAR__SessionNumber              Session number that this track belongs to
// m__LONG__StartingLBA                 Starting LBA
// m__UCHAR__StartingMSF                Starting MSF
// m__LONG__EndingLBA                   Ending LBA
// m__UCHAR__EndingMSF                  Ending MSF
// m__BOOLEAN__IsMCNAvailable           Is Media Catalog Number available
// m__BOOLEAN__IsISRCAvailable          Is International Standard Recording Code available
// m__BOOLEAN__IsFourChannelsAudio		Is this four channels audio track
// m__BOOLEAN__IsPreEmphasisAudio		Is this pre-emphasis audio track
// m__BOOLEAN__IsData                   Is this data track
// m__BOOLEAN__IsAudio                  Is this audio track
// m__BOOLEAN__IsDigitalCopy...			Is digital copy prohibited for this track
// m__UCHAR__TrackMode                  Track mode (0 for audio track, 1 for MODE1 and 2 for MODE2)
// m__UCHAR__MODE2Form                  MODE2 Form (0 for Formless, 1 for Form1 and 2 for Form2)
// m__ULONG__LBSizeInUCHARs             LB (logical block) size in UCHARs on this track
// m__LONG__Index00						Index00 LBA (if present)
// </TABLE>

typedef struct _TOC_ENTRY 
{
    BOOLEAN m__BOOLEAN__IsValid;                  	// Is this data valid (structure was really filled)

    UCHAR m__UCHAR__TrackNumber;                   	// Track number

    UCHAR m__UCHAR__SessionNumber;					// Session number that this track belongs to

    LONG m__LONG__StartingLBA;						// Starting LBA
		
    UCHAR m__UCHAR__StartingMSF[ 3 ];				// Starting MSF

    LONG m__LONG__EndingLBA;						// Ending LBA

    UCHAR m__UCHAR__EndingMSF[ 3 ];					// Ending MSF

    BOOLEAN m__BOOLEAN__IsMCNAvailable; 			// Is Media Catalog Number available

    BOOLEAN m__BOOLEAN__IsISRCAvailable; 			// Is International Standard Recording Code available

    BOOLEAN m__BOOLEAN__IsFourChannelsAudio; 		// Is this four channels audio track
	
    BOOLEAN m__BOOLEAN__IsPreEmphasisAudio;			// Is this pre-emphasis audio track

    BOOLEAN m__BOOLEAN__IsData;						// Is this data track

    BOOLEAN m__BOOLEAN__IsAudio;					// Is this audio track

    BOOLEAN m__BOOLEAN__IsDigitalCopyProhibited;	// Is digital copy prohibited for this track					

    UCHAR m__UCHAR__TrackMode;						// Track mode (0 for audio track, 1 for MODE1 and 2 for MODE2)
			
    UCHAR m__UCHAR__MODE2Form;						// MODE2 Form (0 for Formless, 1 for Form1 and 2 for Form2)

    ULONG m__ULONG__LBSizeInUCHARs;					// LB (logical block) size in UCHARs on this track

	LONG m__LONG__Index00;							// Index00 LBA (if present)

} *PTOC_ENTRY, TOC_ENTRY;


//
// Structure that represents full TOC entry
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__UCHAR__SessionNumber              Session number
// m__UCHAR__CONTROL : 4                Control
// m__UCHAR__ADR : 4                    Address
// m__UCHAR__TNO                        Track number
// m__UCHAR__POINT                      Point
// m__UCHAR__Min                        Minute
// m__UCHAR__Sec                        Second
// m__UCHAR__Frame                      Frame
// m__UCHAR__Zero                       Zero (always 0)
// m__UCHAR__PMIN                       Starting minute (from MSF)
// m__UCHAR__PSEC                       Starting second (from MSF)
// m__UCHAR__PFRAME                     Starting frame (from MSF)
// </TABLE>

typedef struct _FULL_TOC_ENTRY_RAW
{
    UCHAR m__UCHAR__SessionNumber;		// Session number

    UCHAR m__UCHAR__CONTROL : 4;		// Control		

    UCHAR m__UCHAR__ADR : 4;			// Address

    UCHAR m__UCHAR__TNO;				// Track number

    UCHAR m__UCHAR__POINT;				// Point

    UCHAR m__UCHAR__Min;				// Minute

    UCHAR m__UCHAR__Sec;				// Second

    UCHAR m__UCHAR__Frame;				// Frame

    UCHAR m__UCHAR__Zero;				// Zero (always 0)

    UCHAR m__UCHAR__PMIN;				// Starting minute (from MSF)

    UCHAR m__UCHAR__PSEC;				// Starting second (from MSF)

    UCHAR m__UCHAR__PFRAME;				// Starting frame (from MSF)

} *PFULL_TOC_ENTRY_RAW, FULL_TOC_ENTRY_RAW;


//
// Structure that represents TOC information
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__BOOLEAN__IsValid                  Is this data valid (structure was really filled)
// m__BOOLEAN__IsDVD                    Is this DVD media or not
// m__USHORT__ProtectedDVDRegions       Number of protected DVD regions
// m__UCHAR__BusKeyForDiscKey			Bus key for disc key (CSS)
// m__UCHAR__NumberOfSessions           Number of sessions
// m__UCHAR__NumberOfTracks             Number of tracks
// m__UCHAR__NumberOfUnsortedEntries    Number of entries in unsorted raw TOC
// m__TOC_ENTRY                         TOC entries (decoded and extended)
// m__FULL_TOC_ENTRY_RAW                Full TOC raw entries sorted, each entry corresponds to m__TOC_ENTRY with the same TNO
// m__FULL_TOC_ENTRY_RAW__Unsorted      Full TOC raw entries unsorted
// </TABLE>

typedef struct _TOC_INFORMATION 
{
    BOOLEAN m__BOOLEAN__IsValid;											// Is this data valid (structure was really filled)

    BOOLEAN m__BOOLEAN__IsDVD;												// Is this DVD media or not 

    USHORT m__USHORT__ProtectedDVDRegions;									// Number of protected DVD regions

    UCHAR m__UCHAR__BusKeyForDiscKey[ 5 ];									// Bus key for disc key (CSS)
		
    UCHAR m__UCHAR__NumberOfSessions;										// Number of sessions

    UCHAR m__UCHAR__NumberOfTracks;											// Number of tracks

    UCHAR m__UCHAR__NumberOfUnsortedEntries;								// Number of entries in unsorted raw TOC

    TOC_ENTRY m__TOC_ENTRY[ NUMBER_OF_TRACKS ];								// TOC entries (decoded and extended)

    FULL_TOC_ENTRY_RAW m__FULL_TOC_ENTRY_RAW[ NUMBER_OF_TRACKS ];			// Full TOC raw entries sorted, each entry corresponds to m__TOC_ENTRY with the same TNO

    FULL_TOC_ENTRY_RAW m__FULL_TOC_ENTRY_RAW__Unsorted[ NUMBER_OF_RAW_TRACKS ];	// Full TOC raw entries unsorted

} *PTOC_INFORMATION, TOC_INFORMATION;


//
// Structure that represents disc layout entry (track)
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__BOOLEAN__IsAudio                  Is this audio track
// m__BOOLEAN__IsVideo                  Is this video track
// m__BOOLEAN__IsRawRawPW               Is this raw + raw P-W sub-channel track
// m__LONG__TrackSizeInLBs              Track size in LBs (logical blocks)
// m__LONG__PreGapSizeInLBs             PreGap size in LBs (logical blocks)
// m__LONG__PostGapSizeInLBs            PostGap size in LBs (logical blocks)
// m__CHAR__TrackName                   Track name (absolute path & name), can be zero array if next pointer is valid
// m__PVOID__File                       Pointer to internally created disk file object
// m__PVOID__Tree                       Pointer to object created with StarBurn_ISO9660JolietFileTree_Create(), can be NULL
// m__PVOID__BackSideTree               Pointer to undecorated ISO9660 file tree object
// </TABLE>

typedef struct _DISC_LAYOUT_ENTRY
{
    BOOLEAN m__BOOLEAN__IsAudio;    		// Is this audio track

    BOOLEAN m__BOOLEAN__IsVideo;			// Is this video track

    BOOLEAN m__BOOLEAN__IsRawRawPW;			// Is this raw + raw P-W sub-channel track

    LONG m__LONG__TrackSizeInLBs;			// Track size in LBs (logical blocks)

    LONG m__LONG__PreGapSizeInLBs;			// PreGap size in LBs (logical blocks)

    LONG m__LONG__PostGapSizeInLBs;			// PostGap size in LBs (logical blocks)

    CHAR m__CHAR__TrackName[ MAX_PATH ];	// Track name (absolute path & name), can be zero array if next pointer is valid

    PVOID m__PVOID__File;					// Pointer to internally created disk file object

    PVOID m__PVOID__Tree;   				// Pointer to object created with StarBurn_ISO9660JolietFileTree_Create(), can be NULL

    PVOID m__PVOID__BackSideTree;			// Pointer to undecorated ISO9660 file tree object

} *PDISC_LAYOUT_ENTRY, DISC_LAYOUT_ENTRY;


//
// Structure that represents disc layout
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__LONG__NumberOfEntries             Number of entries
// m__DISC_LAYOUT_ENTRY                 Disc layout entries
// m__LONG__NumberOfRawRawPWTracks      Number of raw + raw P-W sub-channel tracks
// m__LONG__RawRawPWTrackSize           Raw + raw P-W sub-channel track sizes
// </TABLE>

typedef struct _DISC_LAYOUT
{
    LONG m__LONG__NumberOfEntries;								// Number of entries

    DISC_LAYOUT_ENTRY m__DISC_LAYOUT_ENTRY[ NUMBER_OF_TRACKS ];	// Disc layout entries

    LONG m__LONG__NumberOfRawRawPWTracks;						// Number of raw + raw P-W sub-channel tracks

    LONG m__LONG__RawRawPWTrackSizeInLBs[ NUMBER_OF_TRACKS ];	// Raw + raw P-W sub-channel track sizes			

} *PDISC_LAYOUT, DISC_LAYOUT;


//
// Structure that represents DAO disc layout entry (track)
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__LONG__TrackSizeInLBs              Track size in LBs (logical blocks)
// m__LONG__TrackStartingLBA            Track starting LBA (logical block address)
// m__BOOLEAN__IsUnicode				Is name in Unicode format or not (see below)
// m__CHAR__TrackName					Track name (absolute path & name) in ANSI or Unicode format (see above)
// m__PVOID__File                       Pointer to internally created disk file object (NULL initially)
// m__BOOLEAN__IsDataTrack              Is this data track (audio otherwise)
// m__BOOLEAN__IsRawTrack				Is this raw track (MDF image)
// m__BOOLEAN__IsAudioExTrack			Is this extended audio track (2448 UCHARs/logical block)
// </TABLE>

typedef struct _DAO_DISC_LAYOUT_ENTRY
{
    LONG m__LONG__TrackSizeInLBs;					// Track size in LBs (logical blocks)

    LONG m__LONG__TrackStartingLBA;					// Track starting LBA (logical block address)

	BOOLEAN m__BOOLEAN__IsUnicode;					// Is name in Unicode format or not (see below)

    CHAR m__CHAR__TrackName[ ( MAX_PATH * 3 ) ];	// Track name (absolute path & name) in ANSI or Unicode format (see above)

    PVOID m__PVOID__File;							// Pointer to internally created disk file object (NULL initially)
		
    BOOLEAN m__BOOLEAN__IsDataTrack;				// Is this data track (audio otherwise)

	BOOLEAN m__BOOLEAN__IsRawTrack;					// Is this raw track (MDF image)

	BOOLEAN m__BOOLEAN__IsAudioExTrack;				// Is this extended audio track (2448 UCHARs/logical block)

} *PDAO_DISC_LAYOUT_ENTRY, DAO_DISC_LAYOUT_ENTRY;


//
// Structure that represents DAO disc layout 
//
// <TABLE>
// Member                               Definition
// ----------                           ---------------
// m__LONG__NumberOfEntries             Number of entries
// m__DAO_DISC_LAYOUT_ENTRY             DAO disc layout entries
// </TABLE>

typedef struct _DAO_DISC_LAYOUT
{
    LONG m__LONG__NumberOfEntries;										// Number of entries

    DAO_DISC_LAYOUT_ENTRY m__DAO_DISC_LAYOUT_ENTRY[ NUMBER_OF_TRACKS ];	// DAO disc layout entries

} *PDAO_DISC_LAYOUT, DAO_DISC_LAYOUT;


//
// Structure with disc file system flags
//
// <TABLE>
// Member                                Definition
// ----------                            ---------------
// m__BOOLEAN__UDFPresent                UDF file system is present
// m__BOOLEAN__ISO9660Present            ISO9660 file system is present
// m__BOOLEAN__JolietPresent      		 Joliet extension for ISO9660 file system is present
// m__BOOLEAN__ElToritoBootRecordPresent El Torito boot record is present
// </TABLE>

typedef struct _DISC_FILESYSTEM
{
	BOOLEAN m__BOOLEAN__UDFPresent;

	BOOLEAN m__BOOLEAN__JolietPresent;

	BOOLEAN m__BOOLEAN__ISO9660Present;

	BOOLEAN m__BOOLEAN__ElToritoBootRecordPresent; 

}* PDISC_FILESYSTEM, DISC_FILESYSTEM;


//
// Restore original structure packing
//

#pragma pack( pop )


//
// Static code (begin)
//


static
VOID
__stdcall
StarBurn_CorrectISO9660Name(
	IN OUT PCHAR p__PCHAR__Name
	)

/*++

Routine Description:

    This function generate next ISO9660 file name to make it unique

Arguments:

	Pointer to current name

Return Value:

    Nothing

--*/

{
    INT l__INT__Length = ( INT )( strlen( p__PCHAR__Name ) );

	CHAR l__CHAR__Name[ MAX_PATH ];

	CHAR l__CHAR__Extension[ 10 ];

	INT l__INT__ExtStart = 0;

	INT l__INT__k = 0;

    static INT l__INT__ISOIndex = 1;

    //
    // make the string to be not less then two chars
    //    
    while ( l__INT__Length < 2 )
    {
        p__PCHAR__Name[ ( l__INT__Length++ ) ] = '0';

        p__PCHAR__Name[ l__INT__Length ] = 0;
    }    

    //
    // Get index of extension
    //
    l__INT__ExtStart = ( p__PCHAR__Name[ ( l__INT__Length - 2 ) ] == ';' ) ? ( l__INT__Length - 2 ) : l__INT__Length;

    for ( l__INT__k = 0; l__INT__k < 5; l__INT__k++ )
    {
        if ( ( l__INT__ExtStart - l__INT__k ) < 0 )
		{
            break;
		}

        if ( p__PCHAR__Name[ ( l__INT__ExtStart - l__INT__k ) ] == '.' )
        {
            l__INT__ExtStart -= l__INT__k;

            break;
        }
    }

    //
    // Copy extension
    //
    strcpy(
		l__CHAR__Extension,
		&p__PCHAR__Name[ l__INT__ExtStart ] 
		);    

    //
    // Correct size of the name
    //
    if ( l__INT__ExtStart > 8 )
	{
    	l__INT__ExtStart = 7;    
	}

    //
    // Copy the name
    //
    strncpy(
		l__CHAR__Name,
		p__PCHAR__Name,
		l__INT__ExtStart
		);

    l__CHAR__Name[ l__INT__ExtStart ] = 0;

    //
    // Generate new file name
    //
    sprintf(
		p__PCHAR__Name,
		"%s%d%s",
		l__CHAR__Name,
		( l__INT__ISOIndex++ ),
		l__CHAR__Extension
		);
}


static
VOID 
__stdcall
StarBurn_CorrectJolietName(
	IN OUT PWCHAR p__PWCHAR__Name
	)

/*++

Routine Description:

    This function generate next Joliet file name to make it unique

Arguments:

	Pointer to current name

Return Value:

    Nothing

--*/

{
	INT l__INT__Length = ( INT )( wcslen( p__PWCHAR__Name ) );

    WCHAR l__WCHAR__Name[ MAX_PATH ];

    WCHAR l__WCHAR__Extension[ 10 ];

    INT l__INT__ExtStart = 0;

    INT l__INT__k = 0;

    time_t l__time_t;

    //
    // Make the string to be not less then two chars
    //    
    while ( l__INT__Length < 2 )
    {
        p__PWCHAR__Name[ ( l__INT__Length++ ) ] = '0';

        p__PWCHAR__Name[ l__INT__Length ] = 0;
    }    

    //
    // Get the start position of the extension
    //
    l__INT__ExtStart = ( p__PWCHAR__Name[ ( l__INT__Length - 2 ) ] == ';' ) ? ( l__INT__Length - 2 ) : l__INT__Length;

    for ( l__INT__k = 0; l__INT__k < 5; l__INT__k++ )
    {
        if ( ( l__INT__ExtStart - l__INT__k ) < 0 )
		{
            break;
		}

        if ( p__PWCHAR__Name[ ( l__INT__ExtStart - l__INT__k ) ] == '.' )
        {
            l__INT__ExtStart -= l__INT__k;

            break;
        }
    }

    //
    // Copy extension
    //
    wcscpy(
		l__WCHAR__Extension,
		&p__PWCHAR__Name[ l__INT__ExtStart ]
		);

    //
    // Copy only name
    //
    wcsncpy(
		l__WCHAR__Name,
		p__PWCHAR__Name,
		l__INT__ExtStart
		);

    l__WCHAR__Name[ l__INT__ExtStart ] = 0;

    //
    // Get current time and date
    //
    l__time_t = time( 0 );

    //
    // Generate new file name
    //
    swprintf(
		p__PWCHAR__Name,
		L"%s_%S%s",
		l__WCHAR__Name,
		ctime( &l__time_t ),
		l__WCHAR__Extension
		);

    l__INT__Length = ( INT )( wcslen( p__PWCHAR__Name ) - 1 );

    //
    // Remove spaces
    //
    while ( p__PWCHAR__Name[ l__INT__Length ] <= ' ' )
	{
    	p__PWCHAR__Name[ ( l__INT__Length-- ) ] = 0;    
	}

    //
    // Change spaces to the '_'
    //
    while (l__INT__Length > l__INT__ExtStart)
    {
        if (
			( p__PWCHAR__Name[ l__INT__Length ] <= ' ' ) ||
            ( p__PWCHAR__Name[ l__INT__Length ] == ':' )
        )
		{
        	p__PWCHAR__Name[ l__INT__Length ] ='_';
		}

        --l__INT__Length;
    }
}


static
VOID
__stdcall
StarBurn_DebugPrintf(
    IN const PCHAR p__PCHAR__Format,
    ...
    )

/*++

Routine Description:

    Dumps the string generated from the passed virtual arguments list to the system debug output facility       

Arguments:

    Virtual arguments list

Return Value:

    Nothing

--*/

{
    CHAR l__CHAR__Temp[ PAGE_SIZE_IN_UCHARS ];

    va_list l__va_list__Next;

    //
    // Start processing virtual arguments list
    //
    va_start(
        l__va_list__Next,
        p__PCHAR__Format
        );

    //
    // Format the string
    //

    RtlZeroMemory(
        &l__CHAR__Temp,
        sizeof( l__CHAR__Temp )
        );

    vsprintf(
        l__CHAR__Temp,
        p__PCHAR__Format,
        l__va_list__Next
        );

    //
    // Dump just generated string to the debug output
    //
    OutputDebugStringA( l__CHAR__Temp );

    //
    // Stop processing virtual arguments list
    //
    va_end( l__va_list__Next );
}


//
// Static code (end)
//


//
// This part of code will be visible only to external clients that does not include StarBurn_Core.hpp and only StarBurn.h header
//

#ifndef __STARBURN_CORE_HPP__


/*

This function returns a 32-bit unsigned long value that contains packed numbers that represent the year, the month and the date
of the toolkit build. So 10th of March, year of 1978 will look like 0x19780310.


Parameters

None.


Result

ULONG with the packed date. This function cannot fail. 


Remarks

Actually it's a good idea to check for supported toolkit version before performing any actions.


Example

This example checks for the toolkit version.

<code>

// Somewhere in the data region
ULONG l__ULONG__Version;

// Get toolkit version
l__ULONG__Version = 
StarBurn_GetVersion();

// Check for correct number
if ( l__ULONG__Version < SUPPORTED_VERSION_NUMBER )
{
// Handle error here...
}

</code>


See Also

Samples for more details about differences between newer and older toolkit versions. 

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_GetVersion(
    IN VOID
    );


/*

This function creates pipe for all of the StarBurn pipe operations and returns both "read" and "write" handles for it.


Parameters

p__PHANDLE__ReadPipe - pointer to the output "read" pipe handle.

p__PHANDLE__WritePipe -	pointer to the output "write" pipe handle.


Result

Win32 execution status.


Remarks

Used with all of the StarBurn pipe-related API calls.


Example

This example allocates both "read" and "write" handles for the same pipe, does some I/O and closes them both later.

<code>

// Somewhere in the data region
HANDLE l__HANDLE__ReadPipe = INVALID_HANDLE_VALUE;
HANDLE l__HANDLE__WritePipe = INVALID_HANDLE_VALUE;
ULONG l__ULONG__Status = ERROR_SUCCESS;

// Try to create pipe
l__ULONG__Status = 
StarBurn_CreatePipe(
	&l__HANDLE__ReadPipe,
	&l__HANDLE__WritePipe
	);

// Check for success
if ( l__ULONG__Status != ERROR_SUCCESS )
{
// Handle error here...
}

// Do something with the pipe handles here...

// Close both "read" and "write" pipe handles
StarBurn_DestroyPipe( 
	&l__HANDLE__ReadPipe,
	&l__HANDLE__WritePipe
	);

</code>


See Also

StarBurn_DestroyPipe, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipeEx

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_CreatePipe(
	OUT PHANDLE p__PHANDLE__ReadPipe,
	OUT PHANDLE p__PHANDLE__WritePipe
    );


/*

This function closes both "read" and "write" pipe handles.


Parameters

p__PHANDLE__ReadPipe - pointer to the input "read" pipe handle.

p__PHANDLE__WritePipe -	pointer to the input "write" pipe handle.


Result

Nothing.


Remarks

Used with all of the StarBurn pipe-related API calls.


Example

This example allocates both "read" and "write" handles for the same pipe, does some I/O and closes them both later.

<code>

// Somewhere in the data region
HANDLE l__HANDLE__ReadPipe = INVALID_HANDLE_VALUE;
HANDLE l__HANDLE__WritePipe = INVALID_HANDLE_VALUE;
ULONG l__ULONG__Status = ERROR_SUCCESS;

// Try to create pipe
l__ULONG__Status = 
StarBurn_CreatePipe(
	&l__HANDLE__ReadPipe,
	&l__HANDLE__WritePipe
	);

// Check for success
if ( l__ULONG__Status != ERROR_SUCCESS )
{
// Handle error here...
}

// Do something with the pipe handles here...

// Close both "read" and "write" pipe handles
StarBurn_DestroyPipe( 
	&l__HANDLE__ReadPipe,
	&l__HANDLE__WritePipe
	);

</code>


See Also

StarBurn_CreatePipe, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipeEx

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_DestroyPipe(
	IN PHANDLE p__PHANDLE__ReadPipe,
	IN PHANDLE p__PHANDLE__WritePipe
    );


/*

This function initializes burning toolkit. It's expected to be called as the very first function call before calling
any other StarBurn exported code. Some of StarBurn functions would work with not initialized core, some would fail
with EN_REGISTRATION_FAILED error. Starting from build 4.2.6 it's *REQUIRED* to call this function, it does not matter
what build (static Vs. dynamic) of StarBurn is used. License file StarBurn.key is assumed to be located near main
application executable. 

ATTENTION! This call is OBSOLTE. Use StarBurn_UpStartEx(...) instead of it.


Parameters

None.


Result

Execution status. EN_SUCCESS if initialization process completed successfully.


Remarks

See samples for details how and when call StarBurn_UpStart() function.


Example

This example checks for the toolkit version and initializes it.

<code>

// Somewhere in the data region
ULONG l__ULONG__Version;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER = EN_SUCCESS;

// Get toolkit version
l__ULONG__Version = 
StarBurn_GetVersion();

// Check for correct number
if ( l__ULONG__Version < SUPPORTED_VERSION_NUMBER )
{
// Handle error here...
}

// Try to initialize toolkit
l__EXCEPTION_NUMBER =
StarBurn_UpStart();

// Check for success
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

</code>


See Also

See samples for details how and when call StarBurn_UpStart() function.

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_UpStart(
    IN VOID
    );


/*

This function initializes burning toolkit. It's expected to be called as the very first function call before calling
any other StarBurn exported code. Some of StarBurn functions would work with not initialized core, some would fail
with EN_REGISTRATION_FAILED error. Starting from build 4.2.6 it's *REQUIRED* to call this function, it does not matter
what build (static Vs. dynamic) of StarBurn is used. The difference between this call and call to StarBurn_UpStart(...) is
that this particular call assumes StarBurn key is being embedded to the application binary and StarBurn_UpStart(...) always
looks for StarBurn.key near application executable.


Parameters

p__PVOID__RegistrationKey - Pointer to registration key.

p__ULONG__RegistrationKeySizeInUCHARs - Registration key size in UCHARs.



Result

Execution status. EN_SUCCESS if initialization process completed successfully.


Remarks

See samples for details how and when call StarBurn_UpStartEx() and StarBurn_UpStart() functions.


Example

This example checks for the toolkit version and initializes it.

<code>

// Somewhere in the data region
ULONG l__ULONG__Version;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER = EN_SUCCESS;
UCHAR l__UCHAR__RegistrationKey[ ] = { ... }; // Registration key goes here

// Get toolkit version
l__ULONG__Version = 
StarBurn_GetVersion();

// Check for correct number
if ( l__ULONG__Version < SUPPORTED_VERSION_NUMBER )
{
// Handle error here...
}

// Try to initialize toolkit
l__EXCEPTION_NUMBER =
StarBurn_UpStartEx(
	( PVOID )( &l__UCHAR__RegistrationKey ),
	sizeof( l__UCHAR__RegistrationKey )
	);

// Check for success
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

</code>


See Also

See samples for details how and when call StarBurn_UpStart() and StarBurn_UpStartEx() functions.

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_UpStartEx(
    IN PVOID p__PVOID__RegistrationKey,
	IN ULONG p__ULONG__RegistrationKeySizeInUCHARs
    );


/*

This function uninitialize burning toolkit. It's expected to be called after very last function call before 
exiting from StarBurn client application. It's a good idea to gather the trash before exiting. Starting from build 4.2.6 it's 
*REQUIRED* to call this function, it does not matter what build (static Vs. dynamic) of StarBurn is used.


Parameters

None.


Result

Execution status. EN_SUCCESS if uninitialization process completed successfully.


Remarks

See samples for details how and when call StarBurn_DownShut() function.


Example

This example just uninitialize toolkit.

<code>

// Somewhere in the data region
EXCEPTION_NUMBER l__EXCEPTION_NUMBER = EN_SUCCESS;

// Try to uninitialize toolkit
l__EXCEPTION_NUMBER =
StarBurn_DownShut();

// Check for success
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

</code>


See Also

See samples for details how and when call StarBurn_DownShut() function.

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_DownShut(
    IN VOID
    );


/*

This function frees allocated memory in the way of destroying the object that toolkit created internally. This is universal 
call, it frees all the objects and does not care about object type. 


Parameters

p__PPVOID__StarBurnObject - Pointer to pointer to the object that toolkit allocated before.


Returns

None. 


Remarks

This call does not check for passed parameter validness.  It's up to user to provide the toolkit with correct pointers to 
objects. After return from this call the object pointer will be NULL.


Example

This example allocates Joliet file tree and destroys it after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    TRUE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Perform actions with Joliet tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_CdvdBurnerGrabber_Create

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_Destroy(
    IN OUT PVOID *p__PPVOID__StarBurnObject
    );


/*

This function gets device name by device address.


Parameters

p__UCHAR__DevicePort - Device port.

p__UCHAR__DeviceBus - Device bus.

p__UCHAR__DeviceID - Device ID.

p__UCHAR__DeviceLUN - Device LUN.

p__PCHAR__DeviceName - Pointer to the buffer device name will be copied to.


Returns

Execution status. EN_SUCCESS if device name was located by device address.


Remarks

Good idea is to fill the device name with zeros before submitting it to this function. Buffer must be large enough to hold
all the device name.


Example

This example gets device name by device address.

<code>

// Somewhere in the data region
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
CHAR l__CHAR__DeviceName[ MAX_PATH ];

// Prepare device name
RtlZeroMemory(
    &l__CHAR__DeviceName,
    sizeof( l__CHAR__DeviceName )
    );

// Try to get device name by device address 0:0:1:0
l__EXCEPTION_NUMBER = 
StarBurn_GetDeviceNameByDeviceAddress(
    0,
    1,
    0,
    0,
    ( PCHAR )( &l__CHAR__DeviceName )
    );

// Check for correct reply
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Perform actions with device name here...

</code>


See Also

StarBurn_GetVersion, StarBurn_CdvdBurnerGrabber_Create

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_GetDeviceNameByDeviceAddress(
    IN UCHAR p__UCHAR__DevicePort,
    IN UCHAR p__UCHAR__DeviceBus,
    IN UCHAR p__UCHAR__DeviceID,
    IN UCHAR p__UCHAR__DeviceLUN,
    OUT PCHAR p__PCHAR__DeviceName
    );


/*

This function allocates in the memory and initializes ISO9660 or Joliet file tree. Later this file tree can be used to build 
"virtual" ISO96600 or Joliet file system image. Resulting "virtual" image can be either stored in the file on the disk or be 
recorder directly to the CD/DVD/Blu-Ray/HD-DVD media w/o any other intermediate buffering operations on the hard disk.


Parameters

p__PPVOID__ISO9660JolietFileTree - Pointer to pointer to the object that toolkit will set to the ISO9660 or Joliet file tree 
object it will allocate.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCALLBACK - Pointer to callback function that will be called from inside the toolkit to inform the user about the progress 
of this operation (See samples how to use this callback for progress indication and other useful things).

p__PVOID__CallbackContext - Pointer to arbitrary context value that will be passed as first PVOID parameter to the called 
callback function.

p__BOOLEAN__IsInvalidKidIgnore - TRUE to ignore bad kids (files or directories that cannot be accessed), FALSE to abort on 
every unsuccessful attempt to access such a files or directories.

p__BOOLEAN__IsLocked - TRUE of all files of the file tree will be locked, FALSE if they will not be locked (their file handles
will not be opened all the times - FALSE must be specified if running under Win9x OSes that have opened files limitation).

p__BOOLEAN__IsLevel2 - TRUE if Level2 ISO9660 names generation is used, FALSE if DOS 8.3 format for names generation is used.

p__FILE_TREE - Type of file tree to build, ISO9660 or Joliet (See FILE_TREE for details).


Returns

Execution status. EN_SUCCESS if the tree was allocated successfully, E_MEMORY_ALLOCATION_FAILED if there is not enough memory 
to allocate the tree. If the exception number will be EN_SYSTEM_CALL_FAILED, variable that SystemError points to will be 
filled with system error. If something other then EN_SUCCESS will be returned buffer that ExceptionText will point to will be 
filled with formatted exception message.


Remarks

Please see the BuildImage sample that will demonstrate how progress indication can be build and what parameters in general are 
passed into the callback function during the operations with file tree object.


Example

This example allocates Joliet file tree and destroys it after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    TRUE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Perform actions with Joliet tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, PCALLBACK, EXCEPTION_NUMBER, FILE_TREE, FILE_TIME, StarBurn_ISO9660JolietFileTree_Add

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_Create(
    OUT PVOID *p__PPVOID__ISO9660JolietFileTree,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN PCALLBACK p__PCALLBACK,
    IN PVOID p__PVOID__CallbackContext,
    IN BOOLEAN p__BOOLEAN__IsInvalidKidIgnore,
    IN BOOLEAN p__BOOLEAN__IsLocked,
    IN BOOLEAN p__BOOLEAN__IsLevel2,
    IN FILE_TREE p__FILE_TREE
    );


/*

This function adds the tree created from the directory to already created ISO9660 or Joliet file tree from passed directory. 
Later this tree can be used to build  "virtual" ISO96600 or Joliet file system image. Resulting "virtual" image can be either 
stored in the file on the disk or be burn directly to the CD/DVD/Blu-Ray/HD-DVD media w/o any other intermediate operations.


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCHAR__RootDirectoryAbsolutePathAndName - Pointer to directory name to build the ISO9660 or Joliet image from. This parameters
can be NULL (but in this case p__PCHAR__RootDirectoryNewName cannot!!!) if virtual (non-present on the disk) directory must
be added to the image.

p__PCHAR__RootDirectoryNewName - Pointer to directory name to be stored in the ISO9660 or Joliet image as root name,
NULL to include default name from the previous parameter.

p__FILE_TIME - File time that will be included in file system image (See FILE_TIME).

p__PPVOID__ISO9660JolietFileTreeNode__Parent - Pointer to pointer to the file tree node we'll use as parent. This is the result
of either tree walking with StarBurn_ISO9660JolietFileTree_GetFirstKid() or StarBurn_ISO9660JolietFileTree_GetNextKid() or the 
result of call to StarBurn_ISO9660JolietFileTree_GetRoot(). NULL can be passed instead of the result of 
StarBurn_ISO9660JolietFileTree_GetRoot().

p__PPVOID__ISO9660JolietFileTreeNode__NewChild - Pointer to pointer to the new created file tree node. 


Returns

Execution status. EN_SUCCESS if the tree was reallocated successfully, E_MEMORY_ALLOCATION_FAILED if there is not enough memory 
to reallocate the tree. If the exception number will be EN_SYSTEM_CALL_FAILED, variable that SystemError points to will be 
filled with system error. If something other then EN_SUCCESS will be returned buffer that ExceptionText will point to will be 
filled with formatted exception message.


Remarks

Please see the BuildImage sample that will demonstrate how progress indication can be build and what parameters in general are 
passed into the callback function during the operations with file tree object.


Example

This example allocates Joliet file tree and destroys it after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__Root;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get root here
l__PVOID__Root = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct reply
if ( l__PVOID__Root == NULL )
{
// Handle error here, keep in mind that root CAN be NULL if nothing was added to tree before...
}

// Try to add all from the root directory of the drive D: to already created Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Add(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    "D:\\",
    NULL,
    FILE_TIME_LAST_WRITE,
    &l__PVOID__Root,
    &l__PVOID__NewNode
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Perform actions with Joliet tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, PCALLBACK, EXCEPTION_NUMBER, FILE_TREE, FILE_TIME, StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_GetRoot,
StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_AddEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_Add(
    OUT PVOID p__PVOID__ISO9660JolietFileTree,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN PCHAR p__PCHAR__RootDirectoryAbsolutePathAndName,
    IN PCHAR p__PCHAR__RootDirectoryNewName,
    IN FILE_TIME p__FILE_TIME,
    IN PVOID *p__PPVOID__ISO9660JolietFileTreeNode__Parent,
    OUT PVOID *p__PPVOID__ISO9660JolietFileTreeNode__NewChild
    );


/*

This function adds the node created from the memory to already created ISO9660 or Joliet file tree from passed directory. 
Later this tree can be used to build  "virtual" ISO96600 or Joliet file system image. Resulting "virtual" image can be either 
stored in the file on the disk or be burn directly to the CD/DVD/Blu-Ray/HD-DVD media w/o any other intermediate operations.


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PUCHAR__MemoryRegion - Pointer to memory region to create node from.

p__LARGE_INTEGER__MemoryRegionSizeInUCHARs - Memory region size in UCHARs.

p__PCHAR__RootDirectoryNewName - Pointer to directory name to be stored in the ISO9660 or Joliet image as root name. Cannot be NULL in this case!

p__FILE_TIME - File time that will be included in file system image (See FILE_TIME).

p__PPVOID__ISO9660JolietFileTreeNode__Parent - Pointer to pointer to the file tree node we'll use as parent. This is the result
of either tree walking with StarBurn_ISO9660JolietFileTree_GetFirstKid() or StarBurn_ISO9660JolietFileTree_GetNextKid() or the 
result of call to StarBurn_ISO9660JolietFileTree_GetRoot(). NULL can be passed instead of the result of 
StarBurn_ISO9660JolietFileTree_GetRoot().

p__PPVOID__ISO9660JolietFileTreeNode__NewChild - Pointer to pointer to the new created file tree node. 


Returns

Execution status. EN_SUCCESS if the tree was reallocated successfully, E_MEMORY_ALLOCATION_FAILED if there is not enough memory 
to reallocate the tree. If the exception number will be EN_SYSTEM_CALL_FAILED, variable that SystemError points to will be 
filled with system error. If something other then EN_SUCCESS will be returned buffer that ExceptionText will point to will be 
filled with formatted exception message.


Remarks

Please see the BuildImage sample that will demonstrate how memory node can be added to already created ISO9660 or Joliet file tree, progress indication can be 
build and what parameters in general are passed into the callback function during the operations with file tree object.


Example

This example allocates Joliet file tree, adds memory node to it and destroys it after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__Root;
UCHAR l__UCHAR__MemoryNode[ 4096 ];
LARGE_INTEGER l__LARGE_INTEGER__MemoryNodeSizeInUCHARs;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get root here
l__PVOID__Root = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct reply
if ( l__PVOID__Root == NULL )
{
// Handle error here, keep in mind that root CAN be NULL if nothing was added to tree before...
}

// Try to add all from the root directory of the drive D: to already created Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Add(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    "D:\\",
    NULL,
    FILE_TIME_LAST_WRITE,
    &l__PVOID__Root,
    &l__PVOID__NewNode
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare memory node memory
RtlZeroMemory(
	&l__UCHAR__MemoryNode,
	sizeof( l__UCHAR__MemoryNode )
	);

// Format memory node here and store all required data into l__UCHAR__MemoryNode buffer

// Set size of memory node
l__LARGE_INTEGER__MemoryNodeSizeInUCHARs.QuadPart = sizeof( l__UCHAR__MemoryNode );

// Try to add memory node as "MemoryNodeName" to already created Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_AddMemory(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
	( PUCHAR )( &l__UCHAR__MemoryNode ),
	l__LARGE_INTEGER__MemoryNodeSizeInUCHARs,
	"MemoryNodeName",		
    FILE_TIME_LAST_WRITE,
    &l__PVOID__Root,
    &l__PVOID__NewNode
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Perform actions with Joliet tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, PCALLBACK, EXCEPTION_NUMBER, FILE_TREE, FILE_TIME, StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_GetRoot,
StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_ISO9660JolietFileTree_GetNextKid

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_AddMemory(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN PUCHAR p__PUCHAR__MemoryRegion,
    IN LARGE_INTEGER p__LARGE_INTEGER__MemoryRegionSizeInUCHARs,
    IN PCHAR p__PCHAR__Name,
    IN FILE_TIME p__FILE_TIME,
    IN PVOID *p__PPVOID__ISO9660JolietFileTreeNode__Parent,
    OUT PVOID *p__PPVOID__ISO9660JolietFileTreeNode__NewChild
    );


/*

This function returns ISO9660 or Joliet file tree level. The number of levels in the created tree.


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().


Returns

Tree level. This function cannot fail.


Remarks

The number of levels ISO9660 or Joliet can handle is limited to 8. Any values that exceed 8 is under your own risk.


Example

This example allocates Joliet file tree, checks tree level and destroys it (tree) after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
LONG l__LONG__TreeLevel;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get tree level here
l__LONG__TreeLevel = 
StarBurn_ISO9660JolietFileTree_GetLevel( l__PVOID__FileTree );

// Check for tree level here
if ( l__LONG__TreeLevel > 8 )
{
// Handle error here...
}

// Do something with Joliet file tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_Destroy 

*/

STARBURN_IMPEX_API
LONG
__stdcall
StarBurn_ISO9660JolietFileTree_GetLevel(
    IN PVOID p__PVOID__ISO9660JolietFileTree
    );


/*

This function returns ISO9660 or Joliet file tree root node pointer. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().


Returns

Pointer to root node. NULL if no root present.


Remarks

Root can be used to enumerate all the root node kids and walk down the tree. Attention! This function will return NULL if
nothing was added to the tree by StarBurn_ISO9660JolietFileTree_Add() before.


Example

This example allocates Joliet file tree, get root node and destroys it (tree) after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__RootNode;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get root node here
l__PVOID__RootNode = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct response
if ( l__PVOID__RootNode == NULL )
{
// Handle error here...
}

// Do something with Joliet file tree root node here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_Destroy 

*/

STARBURN_IMPEX_API
PVOID
__stdcall
StarBurn_ISO9660JolietFileTree_GetRoot(
    IN PVOID p__PVOID__ISO9660JolietFileTree
    );


/*

This function returns ISO9660 or Joliet file tree node first kid pointer. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PVOID__ISO9660JolietFileTreeNode - Pointer to the ISO9660 or Joliet file tree node object that is either result of previous
tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and StarBurn_ISO9660JolietFileTree_GetNextKid() 
or the result of call to StarBurn_ISO9660JolietFileTree_GetRoot().


Returns

Pointer to first kid node. NULL if no first kid node present.


Remarks

Kid node can be used to enumerate all the kids and walk down the tree.


Example

This example allocates Joliet file tree, get root node, gets first kid and destroys it (tree) after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__RootNode;
PVOID l__PVOID__FirstKidNode;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get root node here
l__PVOID__RootNode = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct response
if ( l__PVOID__RootNode == NULL )
{
// Handle error here...
}

// Get first kid node here
l__PVOID__FirstKidNode = 
StarBurn_ISO9660JolietFileTree_GetFirstKid( 
    l__PVOID__FileTree,
    l__PVOID__RootNode
    );

// Check for correct response
if ( l__PVOID__FirstKidNode == NULL )
{
// Handle error here...
}

// Do something with Joliet file tree root node here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_Destroy,
StarBurn_ISO9660JolietFileTree_GetNextKid

*/

STARBURN_IMPEX_API
PVOID
__stdcall
StarBurn_ISO9660JolietFileTree_GetFirstKid(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode
    );


/*

This function returns ISO9660 or Joliet file tree node parent pointer. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PVOID__ISO9660JolietFileTreeNode - Pointer to the ISO9660 or Joliet file tree node object that is either result of previous
tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and StarBurn_ISO9660JolietFileTree_GetNextKid() 
or the result of call to StarBurn_ISO9660JolietFileTree_GetRoot().


Returns

Pointer to parent node. NULL if no parent node present (this is root node).


Remarks

Parent node can be used to enumerate all the kids and walk down the tree.


Example

This example allocates Joliet file tree, get root node, gets parent and destroys it (tree) after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__RootNode;
PVOID l__PVOID__ParentNode;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get root node here
l__PVOID__RootNode = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct response
if ( l__PVOID__RootNode == NULL )
{
// Handle error here...
}

// Get parent node here
l__PVOID__ParentNode = 
StarBurn_ISO9660JolietFileTree_GetParent( 
    l__PVOID__FileTree,
    l__PVOID__RootNode
    );

// Check for correct response (MUST be NULL)
if ( l__PVOID__ParentNode == NULL )
{
// Handle error here...
}

// Do something with Joliet file tree root node here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_Destroy,
StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_GetFirstKid

*/

STARBURN_IMPEX_API
PVOID
__stdcall
StarBurn_ISO9660JolietFileTree_GetParent(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode
    );


/*

This function deletes ISO9660 or Joliet file tree node and all it's kids. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PPVOID__ISO9660JolietFileTreeNode - Pointer to pointer to the ISO9660 or Joliet file tree node object that is either result
of previous tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and 
StarBurn_ISO9660JolietFileTree_GetNextKid() or the result of call to StarBurn_ISO9660JolietFileTree_GetRoot().


Returns

TRUE if the node was destroyed, FALSE if node was not destroyed.


Remarks

You cannot delete root node - FALSE will be returned in this case.


Example

This example allocates Joliet file tree, get root node, gets first kid, deletes first node and destroys it (tree) after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__RootNode;
PVOID l__PVOID__FirstKidNode;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get root node here
l__PVOID__RootNode = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct response
if ( l__PVOID__RootNode == NULL )
{
// Handle error here...
}

// Get first kid node here
l__PVOID__FirstKidNode = 
StarBurn_ISO9660JolietFileTree_GetFirstKid( 
    l__PVOID__FileTree,
    l__PVOID__RootNode
    );

// Check for correct response
if ( l__PVOID__FirstKidNode == NULL )
{
// Handle error here...
}

// Try to delete first kid
if ( 
StarBurn_ISO9660JolietFileTree_Remove(
    l__PVOID__ISO9660JolietFileTree,
    &l__PVOID__FirstKidNode
    ) == FALSE 
)
{
// Handle error here...
}

// Do something with Joliet file tree root node here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_Destroy,
StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_Add

*/

STARBURN_IMPEX_API
BOOLEAN
__stdcall
StarBurn_ISO9660JolietFileTree_Remove(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN OUT PVOID *p__PPVOID__ISO9660JolietFileTreeNode
    );


/*

This function returns ISO9660 or Joliet file tree node attributes. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PVOID__ISO9660JolietFileTreeNode - Pointer to the ISO9660 or Joliet file tree node object that is either result of previous
tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and StarBurn_ISO9660JolietFileTree_GetNextKid() 
or the result of call to StarBurn_ISO9660JolietFileTree_GetRoot().


Returns

Attributes. This function cannot fail.

Combination of one or more of following attributes is valid (see file attributes values in Windows SDK):

FILE_ATTRIBUTE_ARCHIVE
FILE_ATTRIBUTE_COMPRESSED
FILE_ATTRIBUTE_DIRECTORY
FILE_ATTRIBUTE_NORMAL
FILE_ATTRIBUTE_HIDDEN
FILE_ATTRIBUTE_READONLY
FILE_ATTRIBUTE_SYSTEM
FILE_ATTRIBUTE_TEMPORARY


Remarks

Attributes can be used to build correct tree to visualize enumeration of all the kids and walk down the tree.


Example

This example allocates Joliet file tree, get root node, gets attributes and destroys it (tree) after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__RootNode;
ULONG l__ULONG__Attributes;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get root node here
l__PVOID__RootNode = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct response
if ( l__PVOID__RootNode == NULL )
{
// Handle error here...
}

// Get attributes node here
l__ULONG__Attributes = 
StarBurn_ISO9660JolietFileTree_GetAttributes( 
    l__PVOID__FileTree,
    l__PVOID__RootNode
    );

// Do something with Joliet file tree root node here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_Destroy,
StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_GetFirstKid

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_ISO9660JolietFileTree_GetAttributes(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode
    );

/*

This function sets ISO9660 or Joliet file tree node attributes. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PVOID__ISO9660JolietFileTreeNode - Pointer to the ISO9660 or Joliet file tree node object that is either result of previous
tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and StarBurn_ISO9660JolietFileTree_GetNextKid() 
or the result of call to StarBurn_ISO9660JolietFileTree_GetRoot().

p__ULONG__Attributes - New attributes


Returns

None. This function cannot fail.


Remarks

Attributes can be used to build correct tree to visualize enumeration of all the kids and walk down the tree.


Example

This example allocates Joliet file tree, get root node, gets attributes and destroys it (tree) after it's not needed any more.




See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_Destroy,
StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_GetFirstKid

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_ISO9660JolietFileTree_SetAttributes(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode,
	IN ULONG p__ULONG__Attributes
    );


/*

This function returns ISO9660 or Joliet file tree node power (file size) in UCHARs. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PVOID__ISO9660JolietFileTreeNode - Pointer to the ISO9660 or Joliet file tree node object that is either result of previous
tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and StarBurn_ISO9660JolietFileTree_GetNextKid() 
or the result of call to StarBurn_ISO9660JolietFileTree_GetRoot().

p__PLONG__HighPartSizeInUCHARs - Pointer to the variable to receive high part (32 bits) of the node power (file size) in UCHARs.


Returns

Low part (32 bits ) of the node power (file size ) in UCHARs. This function cannot fail.


Remarks

Node power (file size) in UCHARs can be used to build correct tree to visualize enumeration of all the kids and walk down 
the tree. This call is identical to the StarBurn_ISO9660JolietFileTree_GetFileSizeInUCHARs(...) except the semantics.


Example

This example allocates Joliet file tree, get root node, gets node power in UCHARs and destroys it (tree) after it's not needed 
any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__RootNode;
LARGE_INTEGER l__LARGE_INTEGER__NodePowerInUCHARs;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get root node here
l__PVOID__RootNode = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct response
if ( l__PVOID__RootNode == NULL )
{
// Handle error here...
}

// Get node power in UCHARs here
l__LARGE_INTEGER__NodePowerInUCHARs.LowPart =
StarBurn_ISO9660JolietFileTree_GetNodePowerInUCHARs( 
    l__PVOID__FileTree,
    l__PVOID__RootNode,
    ( PLONG )( &l__LARGE_INTEGER__NodePowerInUCHARs.HighPart )
    );

// Do something with Joliet file tree root node here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, 
StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_Destroy,
StarBurn_ISO9660JolietFileTree_GetFileSizeInUCHARs

*/

STARBURN_IMPEX_API
LONG
__stdcall
StarBurn_ISO9660JolietFileTree_GetNodePowerInUCHARs(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode,
    OUT PLONG p__PLONG__HighPartSizeInUCHARs
    );


/*

This function returns ISO9660 or Joliet file tree node names (long, short and absolute). 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PVOID__ISO9660JolietFileTreeNode - Pointer to the ISO9660 or Joliet file tree node object that is either result of previous
tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and StarBurn_ISO9660JolietFileTree_GetNextKid() 
or the result of call to StarBurn_ISO9660JolietFileTree_GetRoot().

p__PCHAR__AbsoluteName - Pointer to the array of CHARs MAX_PATH in size that will be filled with absolute name.

p__PCHAR__LongName - Pointer to the array of CHARs MAX_PATH in size that will be filled with long name.

p__PCHAR__ShortName - Pointer to the array of CHARs MAX_PATH in size that will be filled with short name.


Returns

Nothing. Passed buffers will be filled with the names. This function cannot fail.


Remarks

Names can be used to build correct tree to visualize enumeration of all the kids and walk down the tree.


Example

This example allocates Joliet file tree, get root node, gets names and destroys it (tree) after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__RootNode;
CHAR l__CHAR__AbsoluteName[ MAX_PATH ];
CHAR l__CHAR__LongName[ MAX_PATH ];
CHAR l__CHAR__ShortName[ MAX_PATH ];

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get root node here
l__PVOID__RootNode = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct response
if ( l__PVOID__RootNode == NULL )
{
// Handle error here...
}

// Get names here
StarBurn_ISO9660JolietFileTree_GetNames( 
    l__PVOID__FileTree,
    l__PVOID__RootNode,
    ( PCHAR )( &l__CHAR__AbsoluteName ),
    ( PCHAR )( &l__CHAR__LongName ),
    ( PCHAR )( &l__CHAR__ShortName )
    );

// Do something with Joliet file tree root node here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_Destroy,
StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_ISO9660JolietFileTree_GetAttributes,
StarBurn_ISO9660JolietFileTree_SetNames

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_ISO9660JolietFileTree_GetNames(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode,
    OUT PCHAR p__PCHAR__AbsoluteName,
    OUT PCHAR p__PCHAR__LongName,
    OUT PCHAR p__PCHAR__ShortName
    );

/*

StarBurn_ISO9660JolietFileTree_GetNamesW function is not documented
*/
STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_ISO9660JolietFileTree_GetNamesW(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode,
    OUT PWCHAR p__PWCHAR__AbsoluteName,
    OUT PWCHAR p__PWCHAR__LongName,
    OUT PWCHAR p__PWCHAR__ShortName
    );
/*

This function returns ISO9660 or Joliet file tree node names (long, short and absolute). Also it returns file system
dependent names in ANSI and Unicode.


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PVOID__ISO9660JolietFileTreeNode - Pointer to the ISO9660 or Joliet file tree node object that is either result of previous
tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and StarBurn_ISO9660JolietFileTree_GetNextKid() 
or the result of call to StarBurn_ISO9660JolietFileTree_GetRoot().

p__PCHAR__AbsoluteName - Pointer to the array of CHARs MAX_PATH in size that will be filled with absolute name.

p__PCHAR__LongName - Pointer to the array of CHARs MAX_PATH in size that will be filled with long name.

p__PCHAR__ShortName - Pointer to the array of CHARs MAX_PATH in size that will be filled with short name.

p__PCHAR__FileSystemName - Pointer to the array of CHARs MAX_PATH in size that will be filled with ISO9660 name.

p__PUSHORT__UnicodeFileSystemName - Pointer to the array of CHARs MAX_PATH in size that will be filled with Joliet name.


Returns

Nothing. Passed buffers will be filled with the names. This function cannot fail.


Remarks

Names can be used to build correct tree to visualize enumeration of all the kids and walk down the tree.


Example

This example allocates Joliet file tree, get root node, gets names and destroys it (tree) after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__RootNode;
CHAR l__CHAR__AbsoluteName[ MAX_PATH ];
CHAR l__CHAR__LongName[ MAX_PATH ];
CHAR l__CHAR__ShortName[ MAX_PATH ];
CHAR l__CHAR__FileSystemName[ MAX_PATH ];
WCHAR l__WCHAR__FileSystemName[ MAX_PATH ];

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get root node here
l__PVOID__RootNode = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct response
if ( l__PVOID__RootNode == NULL )
{
// Handle error here...
}

// Get names here
StarBurn_ISO9660JolietFileTree_GetNamesEx( 
    l__PVOID__FileTree,
    l__PVOID__RootNode,
    ( PCHAR )( &l__CHAR__AbsoluteName ),
    ( PCHAR )( &l__CHAR__LongName ),
    ( PCHAR )( &l__CHAR__ShortName ),
	( PCHAR )( &l__CHAR__FileSystemName ),
	( PUSHORT )( &l__WCHAR__FileSystemName )
    );

// Do something with Joliet file tree root node here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_Destroy,
StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_ISO9660JolietFileTree_GetAttributes,
StarBurn_ISO9660JolietFileTree_SetNames

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_ISO9660JolietFileTree_GetNamesEx(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode,
    OUT PCHAR p__PCHAR__AbsoluteName,
    OUT PCHAR p__PCHAR__LongName,
    OUT PCHAR p__PCHAR__ShortName,
	OUT PCHAR p__PCHAR__FileSystemName,
	OUT PUSHORT p__PUSHORT__UnicodeFileSystemName
    );


/*

This function sets ISO9660 or Joliet file tree node names (long, short and absolute). 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PVOID__ISO9660JolietFileTreeNode - Pointer to the ISO9660 or Joliet file tree node object that is either result of previous
tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and StarBurn_ISO9660JolietFileTree_GetNextKid() 
or the result of call to StarBurn_ISO9660JolietFileTree_GetRoot().

p__PCHAR__AbsoluteName - Pointer to the array of CHARs MAX_PATH in size that will be passed as absolute name.

p__PCHAR__LongName - Pointer to the array of CHARs MAX_PATH in size that will be passed as long name.

p__PCHAR__ShortName - Pointer to the array of CHARs MAX_PATH in size that will be passed as short name.


Returns

Nothing. Passed buffers will be copied to the internal file tree node. This function cannot fail. Attention! For now only
long file name can be changed (short and absolute file names will be ignored). 


Remarks

Names can be used to build correct tree to visualize enumeration of all the kids and walk down the tree. Changing the names
can allow to store the files or directories under different names.


Example

This example allocates Joliet file tree, get root node, gets names, sets new ones and destroys it (tree) after it's not needed
any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__RootNode;
CHAR l__CHAR__AbsoluteName[ MAX_PATH ];
CHAR l__CHAR__LongName[ MAX_PATH ];
CHAR l__CHAR__ShortName[ MAX_PATH ];
INT l__INT__NameSizeInUCHARs;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get root node here
l__PVOID__RootNode = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct response
if ( l__PVOID__RootNode == NULL )
{
// Handle error here...
}

// Get names here
StarBurn_ISO9660JolietFileTree_GetNames( 
    l__PVOID__FileTree,
    l__PVOID__RootNode,
    ( PCHAR )( &l__CHAR__AbsoluteName ),
    ( PCHAR )( &l__CHAR__LongName ),
    ( PCHAR )( &l__CHAR__ShortName )
    );

// Change long name

l__INT__NameSizeInUCHARs = strlen( l__CHAR__LongName );

RtlZeroMemory(
&l__CHAR__LongName,
sizeof( l__CHAR__LongName )
);

strncpy(
l__CHAR__LongName,
"New name",
l__INT__NameSizeInUCHARs
);

// Set names here
StarBurn_ISO9660JolietFileTree_SetNames(  
    l__PVOID__FileTree,
    l__PVOID__RootNode,
    ( PCHAR )( &l__CHAR__AbsoluteName ),
    ( PCHAR )( &l__CHAR__LongName ),
    ( PCHAR )( &l__CHAR__ShortName )
    );

// Do something with Joliet file tree root node here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_Destroy,
StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_ISO9660JolietFileTree_GetAttributes,
StarBurn_ISO9660JolietFileTree_GetNames

*/

STARBURN_IMPEX_API
BOOLEAN
__stdcall
StarBurn_ISO9660JolietFileTree_SetNames(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode,
    IN PCHAR p__PCHAR__AbsoluteName,
    IN PCHAR p__PCHAR__LongName,
    IN PCHAR p__PCHAR__ShortName
    );


/*

This function returns ISO9660 or Joliet file tree root node next kid pointer. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PVOID__ISO9660JolietFileTreeNode__Root - Pointer to the ISO9660 or Joliet file tree node object that is result of previous
tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and StarBurn_ISO9660JolietFileTree_GetNextKid().

p__PVOID__ISO9660JolietFileTreeNode__PreviousKid - the result of call to previous call to StarBurn_ISO9660JolietFileTreeNode__GetFirstKid()
or StarBurn_ISO9660JolietFileTree_GetNextKid().


Returns

Pointer to next kid node. NULL if no next kid node present.


Remarks

Kid node can be used to enumerate all the kids and walk down the tree.


Example

This example allocates Joliet file tree, get root node, gets first kid and next kid and destroys it (tree) after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__RootNode;
PVOID l__PVOID__FirstKidNode;
PVOID l__PVOID__NextKidNode;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get root node here
l__PVOID__RootNode = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct response
if ( l__PVOID__RootNode == NULL )
{
// Handle error here...
}

// Get first kid node node here
l__PVOID__FirstKidNode = 
StarBurn_ISO9660JolietFileTree_GetFirstKid( 
    l__PVOID__FileTree,
    l__PVOID__RootNode
    );

// Check for correct response
if ( l__PVOID__FirstKidNode == NULL )
{
// Handle error here...
}

// Get next kid node node here
l__PVOID__NextKidNode = 
StarBurn_ISO9660JolietFileTree_GetNextKid( 
    l__PVOID__FileTree,
    l__PVOID__RootNode,
    l__PVOID__FirstKidNode
    );

// Check for correct response
if ( l__PVOID__NextKidNode == NULL )
{
// Handle error here...
}

// Do something with Joliet file tree root node here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_Destroy,
StarBurn_ISO9660JolietFileTree_GetFirstKid

*/

STARBURN_IMPEX_API
PVOID
__stdcall
StarBurn_ISO9660JolietFileTree_GetNextKid(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode__Root,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode__PreviousKid
    );


/*

This function cancel ISO9660 or Joliet file tree creation process. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().


Returns

Nothing. This function cannot fail.


Remarks

Can cancel only the process initiated by call to StarBurn_ISO9660Joliet_Add, StarBurn_ISO9660JolietFileTree_BuildImage, 
StarBurn_ISO9660JolietFileTree_Read and StarBurn_ISO9660JolietFileTree_SeekToBegin time-expensive actions cannot be canceled with
this code. Also it must be noted that StarBurn_ISO9660JolietFileTree_Cancel is supposed to be executed from the different thread
that the one that calls StarBurn_ISO9660JolietFileTree_Add (original thread will be blocked processing it's call).


Example

This example allocates Joliet file tree, initiates tree creation, cancels it and destroys it (tree) after it's not needed any 
more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Cancel tree creation process. Keep in mind that this code must be called from the different thread
StarBurn_ISO9660JolietFileTree_Cancel( l__PVOID__FileTree );

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_Read, StarBurn_Destroy,
StarBurn_ISO9660JolietFileTree_SeekToBegin

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_ISO9660JolietFileTree_Cancel(
    IN PVOID p__PVOID__ISO9660JolietFileTree
    );


/*

This function builds ISO9660 or Joliet file system image from ISO9660 or Joliet file tree (assign all the logical block 
offsets and allocates and initializes all file system internal structures). Later this tree can be used to store the "virtual"
ISO9660 or Joliet image to the file on the disk or to burn this ISO9660 or Joliet image directly to the CD/DVD/Blu-Ray/HD-DVD media.


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call 
to StarBurn_ISO9660JolietFileTree_Create().

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__LONG__StartingLBA - Starting LBA to build the image from (it should be the next writable address of the track on the 
CD/DVD/Blu-Ray/HD-DVD media, 0 for empty disc).

p__LONG__TreeLevelToProcess - Top tree level to process, levels that exceed this value will be ignored and not included 
into the file system image. For now this parameter is ignored and whole tree will be put into the image.

p__BOOLEAN__IsXA - Is CDROM XA or CDROM data (do we need CDROM XA marker to be included to the the image).

p__PCHAR__VolumeSetName - Pointer to the volume set.

p__PCHAR__PublisherPreparerName - Pointer to the publisher and preparer name.

p__PCHAR__ApplictionName - Pointer to the application name.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message.


Remarks

Please see the BuildImage sample that will demonstrate how progress indication can be created and what parameters in general 
are passed into the callback function during the operations with file tree object. See ISO9660_XXX constants to verify correct 
string parameter lengths.


Example

This example allocates Joliet file tree from the directory, builds the image and destroys the file tree after it's not needed 
any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to build the image, start with LBA 0 and include up to 8 levels into the image 
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_BuildImage(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    0,
    8,
    FALSE,
    "Volume",
    "Publisher",
    "Application"
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Perform actions with Joliet tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_Destroy, PCALLBACK, EXCEPTION_NUMBER, StarBurn_ISO9660JolietFileTree_BuildImageEx 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_BuildImage(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN LONG p__LONG__StartingLBA,
    IN LONG p__LONG__TreeLevelToProcess,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN PCHAR p__PCHAR__VolumeSetName,
    IN PCHAR p__PCHAR__PublisherPreparerName,
    IN PCHAR p__PCHAR__ApplicationName
    );


/*

This function builds ISO9660 or Joliet file system image from ISO9660 or Joliet file tree (assign all the logical block 
offsets and allocates and initializes all file system internal structures). Later this tree can be used to store the "virtual"
ISO9660 or Joliet image to the file on the disk or to burn this ISO9660 or Joliet image directly to the CD/DVD/Blu-Ray/HD-DVD media.
It's identical to StarBurn_ISO9660JolietFileTree_BuildImage except has some extra parameter to put into file system descriptor.


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call 
to StarBurn_ISO9660JolietFileTree_Create().

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__LONG__StartingLBA - Starting LBA to build the image from (it should be the next writable address of the track on the 
CD/DVD/Blu-Ray/HD-DVD media, 0 for empty disc).

p__LONG__TreeLevelToProcess - Top tree level to process, levels that exceed this value will be ignored and not included 
into the file system image. For now this parameter is ignored and whole tree will be put into the image.

p__BOOLEAN__IsXA - Is CDROM XA or CDROM data (do we need CDROM XA marker to be included to the the image).

p__PCHAR__VolumeSetName - Pointer to the volume set.

p__PCHAR__PublisherPreparerName - Pointer to the publisher and preparer name.

p__PCHAR__ApplictionName - Pointer to the application name.

p__PCHAR__SystemID - Pointer to system ID.

p__PCHAR__CopyrightFile - Pointer to copyright file.

p__PCHAR__BibliographicFile - Pointer to bibliographic file.

p__PCHAR__CreationDate - Pointer to creation date.

p__PCHAR__ModificationDate - Pointer to modification date.

p__PCHAR__ExpirationDate - Pointer to expiration date.

p__PCHAR__EffectiveDate - Pointer to effective date.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message.


Remarks

Please see the BuildImage sample that will demonstrate how progress indication can be created and what parameters in general 
are passed into the callback function during the operations with file tree object. StarBurn_ISO9660JolietFileTree_BuildImageEx
can be used instead of StarBurn_ISO9660JolietFileTree_BuildImage. See ISO9660_XXX constants to verify correct string parameter 
lengthes.


Example

This example allocates Joliet file tree from the directory, builds the image and destroys the file tree after it's not needed 
any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to build the image, start with LBA 0 and include up to 8 levels into the image 
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_BuildImageEx(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    0,
    8,
    FALSE,
    "Volume",
    "Publisher",
    "Application",
    "SystemID",
    "CopyFile",
    "BiblioFile",
    "CreateDate",
    "ModifyDate",
    "ExpireDate",
    "EffectDate"
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Perform actions with Joliet tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_Destroy, PCALLBACK, EXCEPTION_NUMBER, StarBurn_ISO9660JolietFileTree_BuildImage

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_BuildImageEx(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN LONG p__LONG__StartingLBA,
    IN LONG p__LONG__TreeLevelToProcess,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN PCHAR p__PCHAR__VolumeSetName,
    IN PCHAR p__PCHAR__PublisherPreparerName,
    IN PCHAR p__PCHAR__ApplicationName,
    IN PCHAR p__PCHAR__SystemID,
    IN PCHAR p__PCHAR__CopyrightFile,
    IN PCHAR p__PCHAR__BibliographicFile,
    IN PCHAR p__PCHAR__CreationDate,
    IN PCHAR p__PCHAR__ModificationDate,
    IN PCHAR p__PCHAR__ExpirationDate,
    IN PCHAR p__PCHAR__EffectiveDate
    );


/*

This function returns ISO9660 or Joliet built file system image size in UCHARs. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create and StarBurn_ISO9660JolietFileTree_BuildImage was applied to later.

p__PULONG__HighPartSizeInUCHARs - Pointer to the 32-bit unsigned long that will receive high part of 64-bit image size.


Returns

Built ISO9660 or Joliet file system image size in UCHARs. This function cannot fail.


Remarks

Used to determine the size of the built file system image so it will be clear will it fit on the CD/DVD/Blu-Ray/HD-DVD media (if burning)
or on hard disk (if storing file system image as file on the disk) or not.


Example

This example allocates Joliet file tree from the directory, builds file system image, gets file system image size in UCHARs, 
checks for compatibility and destroys the file tree after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
LARGE_INTEGER l__LARGE_INTEGER__FileSystemImageSizeInUCHARs;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to build the image, start with LBA 0 and include up to 8 levels into the image 
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_BuildImage(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    0,
    8,
    FALSE,
    "Volume",
    "Publisher",
    "Application"
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Get file system image size in UCHARs
l__LARGE_INTEGER__FileSystemImageSizeInUCHARs.LowPart = 
StarBurn_ISO9660JolietFileTree_GetSizeInUCHARs( 
    l__PVOID__FileTree,
    &l__LARGE_INTEGER__FileSystemImageSizeInUCHARs.HighPart
    );

// Check for enough space on the media here (either hard disk or CD/DVD/Blu-Ray/HD-DVD)
if ( l__LARGE_INTEGER__FileSystemImageSizeInUCHAR.QuadPart < ... )
{
// Handle error here...
}

// Perform actions with Joliet tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_BuildImage, StarBurn_Destroy, PCALLBACK, EXCEPTION_NUMBER 

*/

STARBURN_IMPEX_API
LONG
__stdcall
StarBurn_ISO9660JolietFileTree_GetSizeInUCHARs(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    OUT PLONG p__PLONG__HighPartSizeInUCHARs
    );


/*

This function reads ISO9660 or Joliet file system image from current offset into the user's data buffer. ISO9660 or Joliet 
file tree must have assigned all the logical block offsets and all file system internal structures allocated and initialized. 
The data that is read can be either stored in the file on the hard disk or directly written to CD/DVD/Blu-Ray/HD-DVD media.


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create and StarBurn_ISO9660FileTree_BuildImage was applied to.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__LONG__IoTransferSizeInUCHARs - Number of UCHARs to read from the image from the current offset.

p__PUCHAR__DataBuffer - Pointer to data buffer readen UCHARs will be stored.


Returns

Execution status. EN_SUCCESS if the operation successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message.


Remarks

Please see the BuildImage sample that will demonstrate how file system image can be stored on the hard disk drive and either 
burn later to CD/DVD/Blu-Ray/HD-DVD media or used with CD/DVD/Blu-Ray/HD-DVD emulation software packages. Also TrackAtOnceFromTree sample can be checked out
to see how ISO9660 or Joliet image can be recorded on the CD/DVD/Blu-Ray/HD-DVD media w/o intermediate buffering on the hard disk.


Example

This example allocates Joliet file tree from the directory, builds file system image, reads some data from it and destroys 
the file tree after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
UCHAR l__UCHAR__DataBuffer[ 4096 ];
LARGE_INTEGER l__LARGE_INTEGER__NumberOfUCHARs;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to build the image, start with LBA 0 and include up to 8 levels into the image 
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_BuildImage(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    0,
    8
    FALSE,
    "Volume",
    "Publisher",
    "Application"
    );

// Prepare data buffer
RtlZeroMemory(
    &l__UCHAR__DataBuffer,
    sizeof( l__UCHAR__DataBuffer )
    );

// Set transfer size
l__LARGE_INTEGER__NumberOfUCHARs.QuadPart = sizeof( l__UCHAR__DataBuffer );

// Try to read
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_Read(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    l__LARGE_INTEGER__NumberOfUCHARs.LowPart,
    ( PUCHAR )( &l__UCHAR__DataBuffer )
    );

// Check for success
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with data buffer here...        

// Perform actions with Joliet tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_BuildImage, StarBurn_Destroy, PCALLBACK, EXCEPTION_NUMBER 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_Read(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN LONG p__LONG__IoTransferSizeInUCHARs,
    OUT PUCHAR p__PUCHAR__DataBuffer 
    );


/*

This function seeks the ISO9660 or Joliet file system image from current offset to the very beginning so read operation will 
start from the 0 offset of the file system image. ISO9660 or Joliet file tree must have assigned all the logical block 
offsets and all file system internal structures allocated and initialized. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660FileTree_Create or StarBurn_JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_CreateFromRoot and 
StarBurn_ISO9660FileTree_BuildImage was applied to.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message.


Remarks

Please see the BuildImage sample that will demonstrate how file system image can be stored on the hard disk drive and 
either burn later to CD/DVD/Blu-Ray/HD-DVD media or used with CD/DVD/Blu-Ray/HD-DVD emulation software packages. StarBurn_ISO9660JolietFileTree_SeekToBegin 
is used to rewind the file system image after some part of it was read. Rewinding can be used when the user will want to 
write the same file system image to the media multiple times.


Example

This example allocates Joliet file tree from the directory, builds file system image, reads some stuff from it and destroys 
the file tree after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
UCHAR l__UCHAR__DataBuffer[ 4096 ];
LARGE_INTEGER l__LARGE_INTEGER__NumberOfUCHARs;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to build the image, start with LBA 0 and include up to 8 levels into the image 
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_BuildImage(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    0,
    8
    FALSE,
    "Volume",
    "Publisher",
    "Application"
    );

// Prepare data buffer
RtlZeroMemory(
    &l__UCHAR__DataBuffer,
    sizeof( l__UCHAR__DataBuffer )
    );

// Set transfer size
l__LARGE_INTEGER__NumberOfUCHARs.QuadPart = sizeof( l__UCHAR__DataBuffer );

// Try to read
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_Read(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    l__LARGE_INTEGER__NumberOfUCHARs.LowPart,
    ( PUCHAR )( &l__UCHAR__DataBuffer )
    );

// Check for success
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with data buffer here...        

// Try to seek to the very beging of the "virtual" file system image
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_SeekToBegin(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError
    );

// Check for success
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with image once again...

// Perform actions with Joliet tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Read, StarBurn_Destroy, PCALLBACK, EXCEPTION_NUMBER,

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_SeekToBegin(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError
    );


/*

This function creates CD/DVD/Blu-Ray/HD-DVD burner device object. This object will be used later to perform CD/DVD/Blu-Ray/HD-DVD 
releated actions.


Parameters

p__PPVOID__CdvdBurnerGrabber - Pointer to pointer to the object that toolkit will set to the CdvdBurnerGrabber object it 
will allocate.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PCALLBACK - Callback that will be called to indicate progress of various actions.

p__PVOID__Context - Context value that will be passed to callback function.

p__UCHAR__PortID - SCSI port ID device is located at.

p__UCHAR__BusID - SCSI bus ID device is located at.

p__UCHAR__TargetID - SCSI bus target device is located at.

p__UCHAR__LUN - SCSI LUN device is located at.

p__LONG__CacheSizeInMBs - Cache size to use during I/O operations, 0 is a special value that tells the toolkit to allocate 
default cache size.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please take a look at FindDevice sample to find out how StarBurn_CdvdBurnerGrabber_CreateEx could be used to create CD/DVD/Blu-Ray/HD-DVD
burner object. Please note that StarBurn_CdvdBurnerGrabber_Create would create ASPI device thus would work not only under
Windows NT/2000/XP/2000 but also under Windows 95/98/Me. ASPI is natively supported under Windows 95/98/Me and we provide own 
ASPI-to-SPTI wrapper for StarBurn). If you don't need Windows 95/98/Me support it's a good idea to use new extended variant
of the call StarBurn_CdvdBurnerGrabber_CreateEx as it creates device handle using SPTI transport.


Example

This example allocates CdvdBurnerGrabber object and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_CreateEx, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_Create(
    OUT PVOID *p__PPVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCALLBACK p__PCALLBACK,
    IN PVOID p__PVOID__Context,
    IN UCHAR p__UCHAR__PortID,
    IN UCHAR p__UCHAR__BusID,
    IN UCHAR p__UCHAR__TargetID,
    IN UCHAR p__UCHAR__LUN,
    IN LONG p__LONG__CacheSizeInMBs
    );


/*

This function returns CD/DVD/Blu-Ray/HD-DVD burner device object information. This data can be used to report the capabilities of the device 
to the user.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before with the call to 
StarBurn_CdvdBurnerGrabber_Create().

p__PCHAR__VendorID - Pointer to array of CHARs that will be used to store vendor ID string.

p__PCHAR__ProductID - Pointer to array of CHARs that will be used to store product ID string.

p__PCHAR__ProductRevisionLevel - Pointer to array of CHARs that will be used to store product revision level string.

p__PULONG__BufferSizeInUCHARs - Pointer to ULONG that will contain the device internal cache buffer size in UCHARs.


Result

None. This function cannot fail. 


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and what use can be taken from CdvdBurnerGrabber device information. 


Example

This example allocates CdvdBurnerGrabber object, retrieves device information and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
ULONG l__ULONG__CacheBufferSizeInUCHARs;
CHAR l__CHAR__ExceptionText[ 1024 ];
CHAR l__CHAR__VendorID[ 1024 ];
CHAR l__CHAR__ProductID[ 1024 ];
CHAR l__CHAR__ProductRevisionLevel[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare vendor ID and product ID and product revision level buffers

RtlZeroMemory(
    &l__CHAR__VendorID,
    sizeof( l__CHAR__VendorID )
    );

RtlZeroMemory(
    &l__CHAR__ProductID,
    sizeof( l__CHAR__ProductID )
    );

RtlZeroMemory(
    &l__CHAR__ProductRevisionLevel,
    sizeof( l__CHAR__ProductRevisionLevel )
    );

// Get CdvdBurnerGrabber device information
StarBurn_CdvdBurnerGrabber_GetDeviceInformation(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__VendorID ),
    ( PCHAR )( &l__CHAR__ProductID ),
    ( PCHAR )( &l__CHAR__ProductRevisionLevel ),
    &l__ULONG__CacheBufferSizeInUCHARs
    );

// Do something with CdvdBurnerGrabber device object and it's information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_CdvdBurnerGrabber_GetDeviceInformation(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__VendorID,
    OUT PCHAR p__PCHAR__ProductID,
    OUT PCHAR p__PCHAR__ProductRevisionLevel,
    OUT PULONG p__PULONG__BufferSizeInUCHARs
    );


/*

This function returns CD/DVD/Blu-Ray/HD-DVD burner device object extended information. This data can be used to report the capabilities of the
device to the user.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before with the call to 
StarBurn_CdvdBurnerGrabber_Create().

p__PBOOLEAN__IsCDRRead - Pointer to the boolean variable that will receive is device capable of reading CD-R discs or not.

p__PBOOLEAN__IsCDERead - Pointer to the boolean variable that will receive is device capable of reading CD-RW discs or not.

p__PBOOLEAN__IsDVDROMRead - Pointer to the boolean variable that will receive is device capable of reading DVD-ROM discs 
or not.

p__PBOOLEAN__IsDVDRRead - Pointer to the boolean variable that will receive is device capable of reading DVD-R discs or not.

p__PBOOLEAN__IsDVDRAMRead - Pointer to the boolean variable that will receive is device capable of reading DVD-RAM discs 
or not.

p__PBOOLEAN__IsTestWrite - Pointer to the boolean variable that will receive is device capable of test recording or not.

p__PBOOLEAN__IsCDRWrite - Pointer to the boolean variable that will receive is device capable of writing CD-R discs or not.

p__PBOOLEAN__IsCDEWrite - Pointer to the boolean variable that will receive is device capable of writing CD-RW discs or not.

p__PBOOLEAN__IsDVDRWrite - Pointer to the boolean variable that will receive is device capable of writing DVD-R discs or not.

p__PBOOLEAN__IsDVDRAMWrite - Pointer to the boolean variable that will receive is device capable of writing DVD-RAM discs 
or not.


Result

None. This function cannot fail. 


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and what use can be taken from CdvdBurnerGrabber device extended information. 


Example

This example allocates CdvdBurnerGrabber object, retrieves device extended information and destroys the device object after 
it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
ULONG l__ULONG__CacheBufferSizeInUCHARs;
CHAR l__CHAR__ExceptionText[ 1024 ];
BOOLEAN l__BOOLEAN__IsCDRRead;
BOOLEAN l__BOOLEAN__IsCDERead;
BOOLEAN l__BOOLEAN__IsDVDROMRead;
BOOLEAN l__BOOLEAN__IsDVDRRead;
BOOLEAN l__BOOLEAN__IsDVDRAMRead;
BOOLEAN l__BOOLEAN__IsTestWrite;
BOOLEAN l__BOOLEAN__IsCDRWrite;
BOOLEAN l__BOOLEAN__IsCDEWrite;
BOOLEAN l__BOOLEAN__IsDVDRWrite;
BOOLEAN l__BOOLEAN__IsDVDRAMWrite;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Get CdvdBurnerGrabber device information here...

// Get CdvdBurnerGrabber device extended information
StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormats(
    l__PVOID__CdvdBurnerGrabber,
    &l__BOOLEAN__IsCDRRead,
    &l__BOOLEAN__IsCDERead,
    &l__BOOLEAN__IsDVDROMRead,
    &l__BOOLEAN__IsDVDRRead,
    &l__BOOLEAN__IsDVDRAMRead,
    &l__BOOLEAN__IsTestWrite,
    &l__BOOLEAN__IsCDRWrite,
    &l__BOOLEAN__IsCDEWrite,
    &l__BOOLEAN__IsDVDRWrite,
    &l__BOOLEAN__IsDVDRAMWrite
    );

// Do something with CdvdBurnerGrabber device object and it's extended information here...      

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_GetDeviceInformation, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormatsEx 

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormats(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PBOOLEAN p__PBOOLEAN__IsCDRRead,
    OUT PBOOLEAN p__PBOOLEAN__IsCDERead,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDROMRead,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDRRead,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDRAMRead,
    OUT PBOOLEAN p__PBOOLEAN__IsTestWrite,
    OUT PBOOLEAN p__PBOOLEAN__IsCDRWrite,
    OUT PBOOLEAN p__PBOOLEAN__IsCDEWrite,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDRWrite,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDRAMWrite
    );


/*

This function returns CD/DVD/Blu-Ray/HD-DVD burner device object extended information. This data can be used to report the capabilities 
of the device to the user.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before with the call to 
StarBurn_CdvdBurnerGrabber_Create() or StarBurn_CdvdBurnerGrabber_CreateEx() API calls.

p__PSTARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS - Pointer to pre-allocated and pre-initialized structure containing set of capabilities flags.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree sample that will demonstrate how ISO9660 or Joliet file system image can be burn on the 
CD/DVD/Blu-Ray/HD-DVD media and what use can be taken from CdvdBurnerGrabber device extended information. 


Example

This example allocates CdvdBurnerGrabber object, retrieves device extended information and destroys the device object after 
it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
ULONG l__ULONG__CacheBufferSizeInUCHARs;
CHAR l__CHAR__ExceptionText[ 1024 ];
STARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS l__STARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Get CdvdBurnerGrabber device information here...

// Prepare advanced supported media formats
RtlZeroMemory(
	&l__STARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS,
	sizeof( l__STARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS )
	);

// Set structure size in UCHARs
l__STARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS.m__ULONG__SizeInUCHARs = sizeof( l__STARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS );

// Get CdvdBurnerGrabber device extended information
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetAdvancedSupportedMediaFormats(
    l__PVOID__CdvdBurnerGrabber,
	&l__STARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS
    );

// Do something with CdvdBurnerGrabber device object and it's extended information here...      

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_GetDeviceInformation, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormatsEx, StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormats,
StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormatsExEx  

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetAdvancedSupportedMediaFormats(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
	IN PSTARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS p__PSTARBURN_ADVANCED_SUPPORTED_MEDIA_FORMATS
    );


/*

This function returns DVD+R(W) burner device object extended information. This data can be used to report the capabilities of the
device to the user.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before with the call to 
StarBurn_CdvdBurnerGrabber_Create().

p__PBOOLEAN__IsDVDPLUSRWRead - Pointer to the boolean variable that will receive is device capable of reading DVD+RW discs or not.

p__PBOOLEAN__IsDVDPLUSRRead - Pointer to the boolean variable that will receive is device capable of reading DVD+R discs or not.

p__PBOOLEAN__IsDVDPLUSRWWrite - Pointer to the boolean variable that will receive is device capable of writing DVD+RW discs or not.

p__PBOOLEAN__IsDVDPLUSRWrite - Pointer to the boolean variable that will receive is device capable of writing DVD+R discs or not.


Result

None. This function cannot fail. 


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the DVD+R(W) media and what use can be taken from CdvdBurnerGrabber device extended information. 


Example

This example allocates CdvdBurnerGrabber object, retrieves device extended information and destroys the device object after 
it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
ULONG l__ULONG__CacheBufferSizeInUCHARs;
CHAR l__CHAR__ExceptionText[ 1024 ];
BOOLEAN l__BOOLEAN__IsDVDPLUSRWRead;
BOOLEAN l__BOOLEAN__IsDVDPLUSRRead;
BOOLEAN l__BOOLEAN__IsDVDPLUSRWWrite;
BOOLEAN l__BOOLEAN__IsDVDPLUSRWrite;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Get CdvdBurnerGrabber device information here...

// Get CdvdBurnerGrabber device extended information
StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormatsEx(
    l__PVOID__CdvdBurnerGrabber,
    &l__BOOLEAN__IsDVDPLUSRWRead,
    &l__BOOLEAN__IsDVDPLUSRRead,
    &l__BOOLEAN__IsDVDPLUSRWWrite,
    &l__BOOLEAN__IsDVDPLUSRWrite
    );

// Do something with CdvdBurnerGrabber device object and it's extended information here...      

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_GetDeviceInformation, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormats

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormatsEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDPLUSRWRead,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDPLUSRRead,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDPLUSRWWrite,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDPLUSRWrite
    );


/*

This function returns DVD+R(W) burner device object extended extended information. This data can be used to report the 
capabilities of the device to the user.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before with the call to 
StarBurn_CdvdBurnerGrabber_Create().

p__PBOOLEAN__IsDVDPLUSRWRead - Pointer to the boolean variable that will receive is device capable of reading DVD+RW discs or not.

p__PBOOLEAN__IsDVDPLUSRRead - Pointer to the boolean variable that will receive is device capable of reading DVD+R discs or not.

p__PBOOLEAN__IsDVDPLUSRDLRead - Pointer to the boolean variable that will receive is device capable of reading DVD+R DL discs or not.

p__PBOOLEAN__IsDVDPLUSRWWrite - Pointer to the boolean variable that will receive is device capable of writing DVD+RW discs or not.

p__PBOOLEAN__IsDVDPLUSRWrite - Pointer to the boolean variable that will receive is device capable of writing DVD+R discs or not.

p__PBOOLEAN__IsDVDPLUSRDLWrite - Pointer to the boolean variable that will receive is device capable of writing DVD+R DL discs or not.


Result

None. This function cannot fail. 


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the DVD+R(W) media and what use can be taken from CdvdBurnerGrabber device extended information. 


Example

This example allocates CdvdBurnerGrabber object, retrieves device extended extended information and destroys the device object 
after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
ULONG l__ULONG__CacheBufferSizeInUCHARs;
CHAR l__CHAR__ExceptionText[ 1024 ];
BOOLEAN l__BOOLEAN__IsDVDPLUSRWRead;
BOOLEAN l__BOOLEAN__IsDVDPLUSRRead;
BOOLEAN l__BOOLEAN__IsDVDPLUSRDLRead;
BOOLEAN l__BOOLEAN__IsDVDPLUSRWWrite;
BOOLEAN l__BOOLEAN__IsDVDPLUSRWrite;
BOOLEAN l__BOOLEAN__IsDVDPLUSRDLWrite;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Get CdvdBurnerGrabber device information here...

// Get CdvdBurnerGrabber device extended information
StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormatsExEx(
    l__PVOID__CdvdBurnerGrabber,
    &l__BOOLEAN__IsDVDPLUSRWRead,
    &l__BOOLEAN__IsDVDPLUSRRead,
    &l__BOOLEAN__IsDVDPLUSRDLRead,
    &l__BOOLEAN__IsDVDPLUSRWWrite,
    &l__BOOLEAN__IsDVDPLUSRWrite,
    &l__BOOLEAN__IsDVDPLUSRDLWrite
    );

// Do something with CdvdBurnerGrabber device object and it's extended information here...      

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_GetDeviceInformation, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormats

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_CdvdBurnerGrabber_GetSupportedMediaFormatsExEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDPLUSRWRead,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDPLUSRRead,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDPLUSRDLRead,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDPLUSRWWrite,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDPLUSRWrite,
    OUT PBOOLEAN p__PBOOLEAN__IsDVDPLUSRDLWrite
    );


/*

This function tests is CD/DVD/Blu-Ray/HD-DVD burner device object unit ready or not. This information can be used later to start I/O 
operations.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn  on the CD/DVD/Blu-Ray/HD-DVD media and what StarBurn_CdvdBurnerGrabber_TestUnitReady can be used for. Also it's a good
idea to use extended and "double extended" variants of this call (StarBurn_CdvdBurnerGrabber_TestUnitReadyEx and 
StarBurn_CdvdBurnerGrabber_TestUnitReadyExEx) when required.


Example

This example allocates CdvdBurnerGrabber object, tests unit ready and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to test unit ready
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_TestUnitReady(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_TestUnitReadyEx, StarBurn_CdvdBurnerGrabber_TestUnitReadyExEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_TestUnitReady(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION
    );


/*

This function tests is CD/DVD/Blu-Ray/HD-DVD burner device object unit ready or not. This information can be used later to start 
I/O operations. The only difference between this and simple StarBurn_CdvdBurnerGrabber_TestUnitReady() is that this
code passed parameter to wait for unit to become ready. And "simple" code uses default timeout of 20 seconds.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__ULONG__NumberOfSecondsToWait - Number of seconds to wait (not less than the number, maybe more) until the unit would not become into ready state.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file 
system image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and what StarBurn_CdvdBurnerGrabber_TestUnitReady and it's more extended
"clone" StarBurn_CdvdBurnerGrabber_TestUnitReadyEx and "double extended" StarBurn_CdvdBurnerGrabber_TestUnitReadyExEx can be 
used for. 


Example

This example allocates CdvdBurnerGrabber object, tests unit ready for 10 seconds (instead of default 20) and destroys 
the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to test unit ready for 10 seconds
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_TestUnitReadyEx(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	10 // 10 seconds to test unit to become into ready state
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_TestUnitReady, StarBurn_CdvdBurnerGrabber_TestUnitReadyExEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_TestUnitReadyEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN ULONG p__ULONG__NumberOfSecondsToWait
    );


/*

This function tests is CD/DVD/Blu-Ray/HD-DVD burner device supports BUP (Buffer Underrun Protection) or not and what is BUP current status 
(if supported). This information can be used later to set BUP status before starting write operations.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PBOOLEAN__IsBUPEnabled - Pointer to the BOOLEAN variable that will be set to TRUE if BUP is currently enabled on the 
CD/DVD/Blu-Ray/HD-DVD device, set to FALSE if BUP is disabled.

p__PBOOLEAN__IsBUPSupported - Pointer to the BOOLEAN variable that will be set to TRUE if BUP is generally supported by 
the CD/DVD/Blu-Ray/HD-DVD device, set to FALSE if BUP is not supported.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile sample that will demonstrate how ISO9660 or Joliet file system image
 can be burn on the CD/DVD/Blu-Ray/HD-DVD media and what StarBurn_CdvdBurnerGrabber_GetBUP can be used for. 


Example

This example allocates CdvdBurnerGrabber object, gets BUP status and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
BOOLEAN l__BOOLEAN__IsBUPEnabled;
BOOLEAN l__BOOLEAN__IsBUPSupported;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get BUP on the device
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetBUP(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    &l__BOOLEAN__IsBUPEnabled,
    &l__BOOLEAN__IsBUPSupported
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetBUP(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    OUT PBOOLEAN p__PBOOLEAN__IsBUPEnabled,
    OUT PBOOLEAN p__PBOOLEAN__IsBUPSupported
    );


/*

This function sets BUP (Buffer Underrun Protection) on CD/DVD/Blu-Ray/HD-DVD burner device that supports BUP. BUP must be enabled for 
successful completion of write operations.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__BOOLEAN__IsBUPEnabled - BOOLEAN variable that keeps TRUE if BUP is must be enabled on the CD/DVD/Blu-Ray/HD-DVD device, FALSE if BUP 
must be disabled.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and what StarBurn_CdvdBurnerGrabber_GetBUP can be used for. 


Example

This example allocates CdvdBurnerGrabber object, gets BUP status and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
BOOLEAN l__BOOLEAN__IsBUPEnabled;
BOOLEAN l__BOOLEAN__IsBUPSupported;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get BUP on the device
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetBUP(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    &l__BOOLEAN__IsBUPEnabled,
    &l__BOOLEAN__IsBUPSupported
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Check is BUP supported, if yes - try to enable it
if ( l__BOOLEAN__IsBUPSupported == TRUE )
{

// Try to set BUP on the device
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_SetBUP(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    TRUE
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>
 
See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_GetBUP, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION 
 
*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_SetBUP(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN BOOLEAN p__BOOLEAN__IsBUPEnabled
    );


/*

This function sets current read and write speeds on CD/DVD/Blu-Ray/HD-DVD burner device This speeds later will be used during all read and 
write operations.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__ULONG__ReadSpeed - ULONG with read speed to set.

p__ULONG__WriteSpeed - ULONG with write speed to set.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree, TrackAtOnceFromFile, GrabTrack, GrabDisc samples that will demonstrate how 
StarBurn_CdvdBurnerGrabber_SetSpeeds can be used for setting CD/DVD/Blu-Ray/HD-DVD device read and write speeds. 

[ WARNING! It's required to have media inserted for this function to work properly! ]


Example

This example allocates CdvdBurnerGrabber object, sets top supported read and write speeds and destroys the device 
object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to set top supported CD/DVD/Blu-Ray/HD-DVD read/write speeds on the device
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_SetSpeeds(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    0xFFFF,
    0xFFFF
    );
    
// Check for correct reply
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_CreateEx, StarBurn_CdvdBurnerGrabber_SetReadSpeed, StarBurn_CdvdBurnerGrabber_GetSpeeds

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_SetSpeeds(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN ULONG p__ULONG__ReadSpeed,
    IN ULONG p__ULONG__WriteSpeed
    );


/*

This function gets current read and write and top supported read and write speeds on CD/DVD/Blu-Ray/HD-DVD burner device. This speeds 
later will be used to set current speeds during all read and write operations.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PULONG__CurrentReadSpeed - Pointer to ULONG that will receive current read speed.

p__PULONG__MaximumReadSpeed - Pointer to ULONG that will receive maximum read speed.

p__PULONG__CurrentWriteSpeed - Pointer to ULONG that will receive current write speed.

p__PULONG__MaximumWriteSpeed - Pointer to ULONG that will receive maximum write speed.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how StarBurn_CdvdBurnerGrabber_GetSpeeds
can be used to determine current and top supported CD/DVD/Blu-Ray/HD-DVD device read and write speeds and how 
StarBurn_CdvdBurnerGrabber_SetSpeeds can be used to set top supported speeds. 

[ WARNING! It's required to have media inserted for this function to work properly! ]


Example

This example allocates CdvdBurnerGrabber object, gets all (current and top supported) read and write speeds and destroys 
the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
ULONG l__ULONG__CurrentReadSpeed;
ULONG l__ULONG__MaximumReadSpeed;
ULONG l__ULONG__CurrentWriteSpeed;
ULONG l__ULONG__MaximumWriteSpeed;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get current and top supported CD/DVD/Blu-Ray/HD-DVD read/write speeds on the device
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetSpeeds(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    &l__ULONG__CurrentReadSpeed,
    &l__ULONG__MaximumReadSpeed,
    &l__ULONG__CurrentWriteSpeed,
    &l__ULONG__MaximumWriteSpeed
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and it's speeds here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetSpeeds(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    OUT PULONG p__PULONG__CurrentReadSpeed,
    OUT PULONG p__PULONG__MaximumReadSpeed,
    OUT PULONG p__PULONG__CurrentWriteSpeed,
    OUT PULONG p__PULONG__MaximumWriteSpeed
    );


/*

This function sends OPC (Optimum Power Calibration) for current write speed on CD/DVD/Blu-Ray/HD-DVD burner device and current CD/DVD/Blu-Ray/HD-DVD media. 
The set laser level will be used later during all write operations.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and how StarBurn_CdvdBurnerGrabber_SendOPC can be used to set optimum laser level on CD/DVD/Blu-Ray/HD-DVD
device for current write speed and CD/DVD/Blu-Ray/HD-DVD media. 


Example

This example allocates CdvdBurnerGrabber object, sends optimum power calibration for current write speed and current CD/DVD/Blu-Ray/HD-DVD 
media and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to send optimum power calibration
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_SendOPC(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_SendOPC(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION
    );


/*

This function records ISO9660 or Joliet file system image located in a virtual file tree created with 
StarBurn_ISO9660JolietFileTree_Create or ISO image with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in Session-At-Once mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PDISC_LAYOUT - Pointer to disc layout filled with file tree specific data.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is a just ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE is next session is allowed on this media, FALSE if next session will 
not be allowed on this media.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the SessionAtOnceFromTree sample that will demonstrate how "virtual" ISO9660 or Joliet file system image can be burn 
on the CD/DVD/Blu-Ray/HD-DVD media and with the help of StarBurn_CdvdBurnerGrabber_SessionAtOnce. SessionAtOnceFromFile sample shows how to
burn ISO image. 


Example

This example allocates CdvdBurnerGrabber object, records the ISO9660 or Joliet file system image from file tree to the CD/DVD/Blu-Ray/HD-DVD 
media and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
PVOID l__PVOID__FileTree;
DISC_LAYOUT l__DISC_LAYOUT;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to create ISO9660 or Joliet file system image with help of StarBurn_ISO9660JolietFileTree_Create and 
// StarBurn_ISO9660JolietFileTree_BuildImage, l__PVOID__FileTree used as the pointer to the object...

// Fill DISC_LAYOUT structure here

RtlZeroMemory(
    &l__DISC_LAYOUT,
    sizeof( l__DISC_LAYOUT )
    );

l__DISC_LAYOUT.m__LONG__NumberOfEntries = 1;

l__DISC_LAYOUT.m__DISC_LAYOUT_ENTRY[ 0 ].m__PVOID__ISO9660JolietFileTree = l__PVOID__FileTree;

// Try to record the ISO9660 or Joliet file system image in Session-At-Once mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_SessionAtOnce(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    &l__DISC_LAYOUT,
    FALSE,
    FALSE,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_SessionAtOnce(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PDISC_LAYOUT p__PDISC_LAYOUT,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function records raw image with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in raw Session-At-Once mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PCHAR__MDS - Pointer to MDS file name.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).

p__BOOLEAN__IsRawSaoSubManualLeadIn - Should we write lead-in manually (TRUE) or should we rely on the drive doing this (FALSE).

p__BOOLEAN__IsAmplifyWeak - Should we amplify weak patterns (TRUE) or just forward all the data to the drive "AS IS" (FALSE).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the SessionAtOnceRawRawPW sample that will demonstrate how burn raw image to CD media in RAW SAO + SUB (raw 
Session-At-Once) mode. 


Example

This example allocates CdvdBurnerGrabber object, records raw image to the CD media and destroys the device object after it's 
not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to record the raw image in RAW SUB Session-At-Once mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_SessionAtOnceRawRawPW(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    "Image.MDS",
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS,
    TRUE,	// Write lead-in manually
    TRUE 	// Amplify weak
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_SessionAtOnce,
StarBurn_CdvdBurnerGrabber_SessionAtOnceRawRawPW

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_SessionAtOnceRawRawPW(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCHAR p__PCHAR__MDS,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds,
    IN BOOLEAN p__BOOLEAN__IsRawSaoSubManualLeadIn,
    IN BOOLEAN p__BOOLEAN__IsAmplifyWeak
    );


/*

This function records ISO9660 or Joliet file system image located in a virtual file tree created with 
StarBurn_ISO9660JolietFileTree_Create with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in Track-At-Once mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PVOID__FileTree - Pointer to ISO9660 or Joliet file system image located in a file tree.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is a just ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE is next session is allowed on this media, FALSE if next session will 
not be allowed on this media.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree sample that will demonstrate how "virtual" ISO9660 or Joliet file system image can be burn 
on the CD/DVD/Blu-Ray/HD-DVD media and with the help of StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree.


Example

This example allocates CdvdBurnerGrabber object, records the ISO9660 or Joliet file system image from file tree to the CD/DVD/Blu-Ray/HD-DVD 
media and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
PVOID l__PVOID__FileTree;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to create ISO9660 or Joliet file system image with help of StarBurn_ISO9660JolietFileTree_Create and 
// StarBurn_ISO9660JolietFileTree_BuildImage, l__PVOID__FileTree used as the pointer to the object...

// Try to record the ISO9660 or Joliet file system image in Track-At-Once mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    l__PVOID__FileTree,
    FALSE,
    FALSE,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PVOID p__PVOID__FileTree,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function records ISO9660 or Joliet file system image located in a file on the hard disk (also it can be sound file if an 
audio CD is mastered) with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in Track-At-Once mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PCHAR__ISOSoundImagePathAndFileName - Pointer to ISO9660 or Joliet file system image or sound file located in a file and stored 
on the hard disk.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE is next session is allowed on this media, FALSE if next session 
will not be allowed on this media.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromFile sample that will demonstrate how ISO9660 or Joliet file system image can be burn on the 
CD/DVD/Blu-Ray/HD-DVD media and with the help of StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile with currently set write speed and currently set 
optimum power calibration. 


Example

This example allocates CdvdBurnerGrabber object, records the ISO9660 or Joliet file system image to the CD/DVD/Blu-Ray/HD-DVD media and 
destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to record the ISO9660 or Joliet file system image in Track-At-Once mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    "C:\\ISO9660.ISO",
    FALSE,
    FALSE,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCHAR p__PCHAR__ISOSoundImagePathAndFileName,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function records ISO9660 or Joliet file system image located in a file on the hard disk (also it can be sound file if an 
audio CD is mastered) with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in Track-At-Once mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PCHAR__ISOSoundImagePathAndFileName - Pointer to ISO9660 or Joliet file system image or sound file located in a file and stored 
on the hard disk.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE is next session is allowed on this media, FALSE if next session 
will not be allowed on this media.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).

p__USHORT__AudioPauseLengthInLBs - Audio pause length in logical blocks.

p__BOOLEAN__IsAudioPauseChange - Is audio pause change.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromFile sample that will demonstrate how ISO9660 or Joliet file system image can be burn on the 
CD/DVD/Blu-Ray/HD-DVD media and with the help of StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile with currently set write speed 
and currently set optimum power calibration. The same sample uses extended version of the call to control audio pause length.


Example

This example allocates CdvdBurnerGrabber object, records sound track image to the CD media and destroys the device object after 
it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber = NULL;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError = ERROR_SUCCESS;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to sound track image in Track-At-Once mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFileEx(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    "C:\\TRACK.WAV",
    FALSE,
    FALSE,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS,
	0x0000,	// Zero-sized pause between tracks
	TRUE	// Yes, apply pause change
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFileEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCHAR p__PCHAR__ISOSoundImagePathAndFileName,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds,
	IN USHORT p__USHORT__AudioPauseLengthInLBs,
	IN BOOLEAN p__BOOLEAN__IsAudioPauseChange
    );


/*

This function records ISO9660 or Joliet file system image located in a file on the hard disk (also it can be one sound file or 
full set of sound files if an audio CD is mastered) with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in Disc-At-Once PQ mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PDAO_DISC_LAYOUT - Pointer to preinitialized DAO disc layout.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE if next session is allowed on this media, FALSE if next session 
will not be allowed on this media.

p__BOOLEAN__IsSubChannelRepairRequired - BOOLEAN set to TRUE if you want library to repair broken sub-channel in the image
and FALSE otherwise (if you want to burn all the data AS IS -- maybe required to keep working "special" software titles).

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the DiscAtOnceFromFile sample that will demonstrate how ISO9660 or Joliet file system image (also it can be one sound 
file or full set of sound files if an audio CD is mastered) can be burn on the CD/DVD/Blu-Ray/HD-DVD media and with the help of 
StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromFile with currently set write speed and currently set optimum power calibration. 


Example

This example allocates CdvdBurnerGrabber object, records the ISO9660 or Joliet file system image to the CD/DVD/Blu-Ray/HD-DVD media and 
destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
DAO_DISC_LAYOUT l__DAO_DISC_LAYOUT;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare DAO disc layout
RtlZeroMemory(
    &l__DAO_DISC_LAYOUT,
    sizeof( l__DAO_DISC_LAYOUT )
    );

// Set file name
strcpy(
    l__DAO_DISC_LAYOUT.m__DAO_DISC_LAYOUT_ENTRY.m__CHAR__TrackName,
    "C:\\ISO9660.ISO"
    );

// Set number of tracks
l__DAO_DISC_LAYOUT.m__LONG__NumberOfTracks = 1;

// Try to record the ISO9660 or Joliet file system image in Disc-At-Once PQ mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromFile(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    &l__DAO_DISC_LAYOUT,
    FALSE, // No XA, just ordinary CDROM
    FALSE, // No test write, real burn
    FALSE, // No next session allowed
	FALSE, // No sub-channel repair		
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFile 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromFile(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PDAO_DISC_LAYOUT p__PDAO_DISC_LAYOUT,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
	IN BOOLEAN p__BOOLEAN__IsSubChannelRepairRequired,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function records ISO9660 or Joliet file system image located in a file on the hard disk (also it can be one sound file or 
full set of sound files if an audio CD is mastered) with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in Disc-At-Once raw P-W mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PDAO_DISC_LAYOUT - Pointer to preinitialized DAO disc layout.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE is next session is allowed on this media, FALSE if next session 
will not be allowed on this media.

p__BOOLEAN__IsSubChannelRepairRequired -- BOOLEAN set to TRUE if you want library to repair broken sub-channel in the image
and FALSE otherwise (if you want to burn all the data AS IS -- maybe required to keep working "special" software titles).

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the DiscAtOnceFromFile sample that will demonstrate how ISO9660 or Joliet file system image (also it can be one sound 
file or full set of sound files if an audio CD is mastered) can be burn on the CD/DVD/Blu-Ray/HD-DVD media and with the help of 
StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFile with currently set write speed and currently set optimum power calibration. 


Example

This example allocates CdvdBurnerGrabber object, records the ISO9660 or Joliet file system image to the CD/DVD/Blu-Ray/HD-DVD media and 
destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
DAO_DISC_LAYOUT l__DAO_DISC_LAYOUT;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare DAO disc layout
RtlZeroMemory(
    &l__DAO_DISC_LAYOUT,
    sizeof( l__DAO_DISC_LAYOUT )
    );

// Set file name
strcpy(
    l__DAO_DISC_LAYOUT.m__DAO_DISC_LAYOUT_ENTRY.m__CHAR__TrackName,
    "C:\\ISO9660.ISO"
    );

// Set number of tracks
l__DAO_DISC_LAYOUT.m__LONG__NumberOfTracks = 1;

// Try to record the ISO9660 or Joliet file system image in Disc-At-Once raw P-W mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFile(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    &l__DAO_DISC_LAYOUT,
    FALSE, // No XA, just ordinary CDROM
    FALSE, // No test write, real burn
    FALSE, // No next session allowed
	FALSE, // No sub-channel repair		
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromFile 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFile(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PDAO_DISC_LAYOUT p__PDAO_DISC_LAYOUT,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
	IN BOOLEAN p__BOOLEAN__IsSubChannelRepairRequired,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function records ISO9660 or Joliet file system image located in a pipe with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device
in Track-At-Once mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__HANDLE - Handle to ISO9660 or Joliet file system image or sound file located in a pipe.

p__LARGE_INTEGER__SizeInUCHARs - Pipe contents size in UCHARs.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE is next session is allowed on this media, FALSE if next session 
will not be allowed on this media.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromPipeEx API call as it allows to burn not only data but also audio compilations from pipes.


Example

This example allocates CdvdBurnerGrabber object, records the ISO9660 or Joliet file system image to the CD/DVD/Blu-Ray/HD-DVD media and 
destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
HANDLE l__HANDLE__Pipe = INVALID_HANDLE_VALUE;
LARGE_INTEGER l__LARGE_INTEGER__SizeInUCHARs;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare file system image or file and keep in pipe

// Try to record the ISO9660 or Joliet file system image in Track-At-Once mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    l__HANDLE__Pipe,
    l__LARGE_INTEGER__SizeInUCHARs,
    FALSE,
    FALSE,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipeEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN HANDLE p__HANDLE,
    IN LARGE_INTEGER p__LARGE_INTEGER__SizeInUCHARs,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function closes session on on CD/DVD/Blu-Ray/HD-DVD burner device after something was written using 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe or 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burnon the CD/DVD/Blu-Ray/HD-DVD media and with the help of the StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree,
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile or StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe and how session can be closed with
the help of StarBurn_CdvdBurnerGrabber_CloseSession. 


Example

This example allocates CdvdBurnerGrabber object, records the ISO9660 or Joliet file system image to the CD/DVD/Blu-Ray/HD-DVD media, closes 
session and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to record the ISO9660 or Joliet file system image in Track-At-Once mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    "C:\\ISO9660.ISO",
    FALSE,
    FALSE,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to close session
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_CloseSession(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>
 

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_CloseSession(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION
    );


/*

This function gets DVD protection system of inserted DVD media into DVD device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PUCHAR__DVDProtectionSystem - Pointer to UCHAR that will keep DVD protection system in case of success.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the GrabDisc sample to see how to grab DVD disc into MDS format and how StarBurn_CdvdBurnerGrabber_GetDVDProtectionSystem
can be used to determine protection system of currently inserted DVD disc.


Example

This example allocates CdvdBurnerGrabber object, gets protection system and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UCHAR l__UCHAR__DVDProtectionSystem = DVD_PROTECTION_NONE;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get inserted disc type, supposed to be DVD...

// Try to get DVD protection system
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetDVDProtectionSystem(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    &l__UCHAR__DVDProtectionSystem
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_GetDVDProtectionSystem 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetDVDProtectionSystem(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    OUT PUCHAR p__PUCHAR__DVDProtectionSystem
    );


/*

This function authorizes DVD that has CSS protection system.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the GrabDisc sample to see how to grab DVD disc into MDS format and how StarBurn_CdvdBurnerGrabber_GetDVDProtectionSystem
can be used to determine protection system of currently inserted DVD disc and how StarBurn_CdvdBurnerGrabber_AuthorizeDVD() can
be used to authorize CSS protected DVD.


Example

This example allocates CdvdBurnerGrabber object, gets protection system, authorizes DVD disc and destroys the device object after 
it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UCHAR l__UCHAR__DVDProtectionSystem = DVD_PROTECTION_NONE;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get inserted disc type, supposed to be DVD...

// Try to get DVD protection system
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetDVDProtectionSystem(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    &l__UCHAR__DVDProtectionSystem
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to authorize the DVD disc (it's expected that DVD disc has CSS protection)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_AuthorizeDVD(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION
    );

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_GetDVDProtectionSystem 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_AuthorizeDVD(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION
    );


/*

This function ejects the media on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and how StarBurn_CdvdBurnerGrabber_Eject can be used to eject the CD/DVD/Blu-Ray/HD-DVD media to initiate file system 
unmount/mount sequence (to refresh contents of just burn CD/DVD/Blu-Ray/HD-DVD media). 


Example

This example allocates CdvdBurnerGrabber object, ejects the media and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to eject the media
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Eject(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_Eject(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION
    );


/*

This function loads the media on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the DiscOnceFromTree sample demonstrating how ISO9660 or Joliet file system image can be burnt on the CD media and 
how StarBurn_CdvdBurnerGrabber_Load can be used to load the CD media to initiate file system mount sequence.


Example

This example allocates CdvdBurnerGrabber object, ejects the media, loads it and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to eject the media here...

// Try to load the media
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Load(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_LoadEx, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_Load(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION
    );


/*

This function loads the media on CD/DVD/Blu-Ray/HD-DVD burner device. Unlike StarBurn_CdvdBurnerGrabber_Load(...) this API call allows to control
should it return immediately or wait until the drive would become into ready state.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__BOOLEAN__IsWaitRequired - Should the library wait for CD/DVD/Blu-Ray/HD-DVD drive to become into ready state.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the DiscAtOnceFromTree sample demonstrating how ISO9660 or Joliet file system image can be burnt to the CD media 
and how StarBurn_CdvdBurnerGrabber_Load can be used to load the CD media to initiate file system mount sequence.


Example

This example allocates CdvdBurnerGrabber object, ejects the media, loads it (waiting for the drive to become into ready state) and 
destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to eject the media here...

// Try to load the media
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_LoadEx(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	TRUE // We want to return only after drive would become into ready state
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_Load, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_LoadEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN BOOLEAN p__BOOLEAN__IsWaitRequired
    );


/*

This function locks the media inside the CD/DVD/Blu-Ray/HD-DVD device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromFile and TrackAtOnceFromTree sample that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media. StarBurn_CdvdBurnerGrabber_Lock can be used to lock the CD/DVD/Blu-Ray/HD-DVD media to prevent 
media removal from the device while burning (or any I/O process) is in progress.


Example

This example allocates CdvdBurnerGrabber object, locks it and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to lock the media
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Lock(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_Release 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_Lock(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION
    );


/*

This function releases the media inside the CD/DVD/Blu-Ray/HD-DVD device after the media was locked before.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromFile and TrackAtOnceFromTree sample that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media. StarBurn_CdvdBurnerGrabber_Lock can be used to lock the CD/DVD/Blu-Ray/HD-DVD media to prevent 
media removal from the device while burning (or any I/O process) is in progress. StarBurn_CdvdBurnerGrabber_Release
can be used to release (unlock) the media that was locked before.


Example

This example allocates CdvdBurnerGrabber object, locks it, releases (unlocks) and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to lock media here...

// Try to release (unlock) the media
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Release(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_Lock 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_Release(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION
    );


/*

This function erases the rewritable media inserted into CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__ERASE_TYPE - Erase type (ERASE_TYPE_BLANK_DISC_FULL and ERASE_TYPE_BLANK_DISC_FAST supported for now).


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the Blank sample that will demonstrate how to erase the rewrittable disc.


Example

This example allocates CdvdBurnerGrabber object, erases the media and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to erase the media
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Blank(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ERASE_TYPE_BLANK_DISC_FAST
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, ERASE_TYPE

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_Blank(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN ERASE_TYPE p__ERASE_TYPE
    );


/*

This function formats Blu-Ray rewritable media (BD-RE) inserted into the Blu-Ray burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__ULONG__FormatProfileNumber - Format profile number to use.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the BluRayFormat sample that will demonstrate how to format rewrittable Blu-Ray disc (BD-RE).


Example

This example allocates CdvdBurnerGrabber object, formats the BD-RE media and destroys the device object after 
it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber = NULL;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError = ERROR_SUCCESS;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
ULONG l__ULONG__FormatProfileNumber = 0;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Check for the BD-RE media inserted

// Get possible format profiles and pick up format profile number

// Try to format the Blu-Ray rewrittable media (BD-RE)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_BluRayFormat(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	l__ULONG__FormatProfileNumber
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_BluRayFormatQuery, PCALLBACK, 
EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_BluRayFormat(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN ULONG p__ULONG__FormatProfileNumber
    );


/*

This function queries available Blu-Ray formats for the currently inserted Blu-Ray rewritable media (BD-RE).


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PUCHAR__FormatProfileBuffer - Pointer to the profile format buffer.

p__PULONG__FormatProfileBufferSizeInUCHARS - Pointer to the format profile buffer size in UCHAR(s). 


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes). If the passed buffer size is too
small StarBurn will set p__PULONG__FormatProfileBufferSizeInUCHARs to the required buffer size in UCHAR(s). After
completion p__PULONG__FormatProfileBufferSizeInUCHARs will be set to the number of UCHAR(s) copied.


Remarks

Please see the BluRayFormat sample that will demonstrate how to format rewrittable Blu-Ray media (BD-RE) and query 
all available format profiles.


Example

This example allocates CdvdBurnerGrabber object, queries available Blu-Ray formats and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber = NULL;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError = ERROR_SUCCESS;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UCHAR l__UCHAR__FormatProfileBuffer[ PAGE_SIZE_IN_UCHARS ];
ULONG l__ULONG__FormatProfileBufferSizeInUCHARs = sizeof( l__UCHAR__FormatProfileBuffer );

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Check for the BD-RE media inserted

// Query available Blu-Ray formats 
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_BluRayFormatQuery(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	&l__UCHAR__FormatProfileBuffer,
	&l__ULONG__FormatProfileBufferSizeInUCHARs
    );

// Try to format the Blu-Ray rewrittable media

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_BluRayFormat, PCALLBACK, 
EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_BluRayFormatQuery(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	OUT PUCHAR p__PUCHAR__FormatProfileBuffer,
	OUT PULONG p__PULONG__FormatProfileBufferSizeInUCHARs
    );


/*

This function gets track information of the asked track number on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__LONG__TrackNumber - Track number to get information about.

p__PSTARBURN_TRACK_INFORMATION - Pointer to the track information.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree sample that will demonstrate how ISO9660 or Joliet file system image can be burn on the 
CD/DVD/Blu-Ray/HD-DVD media and how StarBurn_CdvdBurnerGrabber_GetTrackInformation can be used to get "invisible" track information on the 
CD/DVD/Blu-Ray/HD-DVD media to check parameters of the track for validness (is track blank, number of free logical blocks etc).


Example

This example allocates CdvdBurnerGrabber object, gets "invisible" track information and destroys the device object after 
it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
STARBURN_TRACK_INFORMATION l__STARBURN_TRACK_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare track information buffer
RtlZeroMemory(
    &l__STARBURN_TRACK_INFORMATION,
    sizeof( l__STARBURN_TRACK_INFORMATION )
    );

// Try to get "invisible" track information
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetTrackInformation(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    TRACK_NUMBER_INVISIBLE,
    ( PSTARBURN_TRACK_INFORMATION )( &l__STARBURN_TRACK_INFORMATION )
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and track information here...      

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_GetDiscInformation, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, STARBURN_TRACK_INFORMATION, STARBURN_DISC_INFORMATION

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetTrackInformation(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN LONG p__LONG__TrackNumber,
    OUT PSTARBURN_TRACK_INFORMATION p__PSTARBURN_TRACK_INFORMATION
    );

/*

This function gets track extended information of the asked track number on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__LONG__TrackNumber - Track number to get information about.

p__PSTARBURN_TRACK_INFORMATION_EX - Pointer to the track extended information.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree sample that will demonstrate how ISO9660 or Joliet file system image can be burn on the 
CD/DVD/Blu-Ray/HD-DVD media and how StarBurn_CdvdBurnerGrabber_GetTrackInformation can be used to get "invisible" track information on the 
CD/DVD/Blu-Ray/HD-DVD media to check parameters of the track for validness (is track blank, number of free logical blocks etc).


Example

This example allocates CdvdBurnerGrabber object, gets "invisible" track information and destroys the device object after 
it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
STARBURN_TRACK_INFORMATION_EX l__STARBURN_TRACK_INFORMATION_EX;

// Prepare exception text buffer
RtlZeroMemory(
&l__CHAR__ExceptionText,
sizeof( l__CHAR__ExceptionText )
);

// Prepare CDB failure information
RtlZeroMemory(
&l__CDB_FAILURE_INFORMATION,
sizeof( l__CDB_FAILURE_INFORMATION )
);

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
&l__PVOID__CdvdBurnerGrabber,
( PCHAR )( &l__CHAR__ExceptionText ),
sizeof( l__CHAR__ExceptionText ),
&l__ULONG__SystemError,
&l__CDB_FAILURE_INFORMATION,
( PCALLBACK )( StarBurn_Callback ),
0,
0,
4,
0,
32
);

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare track information buffer
RtlZeroMemory(
&l__STARBURN_TRACK_INFORMATION_EX,
sizeof( l__STARBURN_TRACK_INFORMATION_EX )
);

// Try to get "invisible" track information
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetTrackInformationEx(
l__PVOID__CdvdBurnerGrabber,
( PCHAR )( &l__CHAR__ExceptionText ),
sizeof( l__CHAR__ExceptionText ),
&l__ULONG__SystemError,
&l__CDB_FAILURE_INFORMATION,
TRACK_NUMBER_INVISIBLE,
( PSTARBURN_TRACK_INFORMATION_EX )( &l__STARBURN_TRACK_INFORMATION_EX )
);

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and track information here...      

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_GetDiscInformation, StarBurn_CdvdBurnerGrabber_GetTrackInformation, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, STARBURN_TRACK_INFORMATION_EX, STARBURN_TRACK_INFORMATION, STARBURN_DISC_INFORMATION

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetTrackInformationEx(
	IN PVOID p__PVOID__CdvdBurnerGrabber,
	OUT PCHAR p__PCHAR__ExceptionText,
	IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
	OUT PULONG p__PULONG__SystemError,
	OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN LONG p__LONG__TrackNumber,
	OUT PSTARBURN_TRACK_INFORMATION_EX p__PSTARBURN_TRACK_INFORMATION_EX
	);



/*

This function gets disc information of the currently inserted disc on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PSTARBURN_DISC_INFORMATION - Pointer to the disc information.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree sample that will demonstrate how ISO9660 or Joliet file system image can be burn on the 
CD/DVD/Blu-Ray/HD-DVD  media and how StarBurn_CdvdBurnerGrabber_GetDiscInformation can be used to get current disc information on the CD/DVD/Blu-Ray/HD-DVD 
media to check parameters of the disc for validness (is disc blank, last session status etc).


Example

This example allocates CdvdBurnerGrabber object, gets disc information and destroys the device object after it's not needed any 
more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
STARBURN_DISC_INFORMATION l__STARBURN_DISC_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare disc information buffer
RtlZeroMemory(
    &l__STARBURN_DISC_INFORMATION,
    sizeof( l__STARBURN_DISC_INFORMATION )
    );

// Try to get current disc information
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetDiscInformation(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PSTARBURN_DISC_INFORMATION )( &l__STARBURN_DISC_INFORMATION )
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and disc information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_GetTrackInformation, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, STARBURN_DISC_INFORMATION, STARBURN_TRACK_INFORMATION

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetDiscInformation(
	IN PVOID p__PVOID__CdvdBurnerGrabber,
	OUT PCHAR p__PCHAR__ExceptionText,
	IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
	OUT PULONG p__PULONG__SystemError,
	OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	OUT PSTARBURN_DISC_INFORMATION p__PSTARBURN_DISC_INFORMATION
	);

/*

This function gets disc used space of the currently inserted disc on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PLARGE_INTEGER__UsedSpace - Pointer to the used space of disc.

Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Example

This example allocates CdvdBurnerGrabber object, gets used disc space and destroys the device object after it's not needed any 
more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
LARGE_INTEGER l__LARGE_INTEGER__UsedSpace;

l__LARGE_INTEGER__UsedSpace.QuadPart = 0;

// Prepare exception text buffer
RtlZeroMemory(
&l__CHAR__ExceptionText,
sizeof( l__CHAR__ExceptionText )
);

// Prepare CDB failure information
RtlZeroMemory(
&l__CDB_FAILURE_INFORMATION,
sizeof( l__CDB_FAILURE_INFORMATION )
);

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
&l__PVOID__CdvdBurnerGrabber,
( PCHAR )( &l__CHAR__ExceptionText ),
sizeof( l__CHAR__ExceptionText ),
&l__ULONG__SystemError,
&l__CDB_FAILURE_INFORMATION,
( PCALLBACK )( StarBurn_Callback ),
0,
0,
4,
0,
32
);

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}


// Try to get current disc used space
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetDiscUsedSpace(
l__PVOID__CdvdBurnerGrabber,
( PCHAR )( &l__CHAR__ExceptionText ),
sizeof( l__CHAR__ExceptionText ),
&l__ULONG__SystemError,
&l__CDB_FAILURE_INFORMATION,
&l__LARGE_INTEGER__UsedSpace
);

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and disc information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_GetDiscInformation, StarBurn_CdvdBurnerGrabber_GetTrackInformation, StarBurn_CdvdBurnerGrabber_GetTOCInformation,  PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, STARBURN_DISC_INFORMATION, STARBURN_TRACK_INFORMATION, STARBURN_TOC_INFORMATION

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetDiscUsedSpace(
	IN PVOID p__PVOID__CdvdBurnerGrabber,
	OUT PCHAR p__PCHAR__ExceptionText,
	IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
	OUT PULONG p__PULONG__SystemError,
	OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	OUT PLARGE_INTEGER p__PLARGE_INTEGER__UsedSpace
	);


/*

This function gets disc free space of the currently inserted disc on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__CD_MODE - CD mode. Ignored if currently inserted disc type is DVD.

p__PLONG__FreeSpaceInLBs - Pointer to the LONG will be filled with number of free logical blocks on the disc.

p__PLARGE_INTEGER__FreeSpaceInUCHARS - Pointer to the LARGE_INTEGER will be filled with free space in UCHARs on the disc.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

If currently inserted disc type is DVD then parameter p__CD_MODE is ignored.For DVD disc type default LB size is 2048 UCHARs.
If p__CD_MODE set to CD_MODE_UNKNOWN or CD_MODE_RESERVED function return p__PLARGE_INTEGER__FreeSpaceInUCHARS is zero.  


Example

This example allocates CdvdBurnerGrabber object, gets free disc space and destroys the device object after it's not needed any 
more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
CD_MODE l__CD_MODE(CD_MODE_DATA);
LONG l__LONG__FreeSpaceInLBs(0);
LARGE_INTEGER l__LARGE_INTEGER__FreeSpaceInUCHARs;

l__LARGE_INTEGER__FreeSpaceInUCHARs.QuadPart = 0;

// Prepare exception text buffer
RtlZeroMemory(
&l__CHAR__ExceptionText,
sizeof( l__CHAR__ExceptionText )
);

// Prepare CDB failure information
RtlZeroMemory(
&l__CDB_FAILURE_INFORMATION,
sizeof( l__CDB_FAILURE_INFORMATION )
);

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
&l__PVOID__CdvdBurnerGrabber,
( PCHAR )( &l__CHAR__ExceptionText ),
sizeof( l__CHAR__ExceptionText ),
&l__ULONG__SystemError,
&l__CDB_FAILURE_INFORMATION,
( PCALLBACK )( StarBurn_Callback ),
0,
0,
4,
0,
32
);

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get current disc free space
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetDiscFreeSpace(
l__PVOID__CdvdBurnerGrabber,
l__CD_MODE,
&l__LONG__FreeSpaceInLBs,
&l__LARGE_INTEGER__FreeSpaceInUCHARs
);

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and disc information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_GetDiscInformation, StarBurn_CdvdBurnerGrabber_GetTrackInformation, StarBurn_CdvdBurnerGrabber_GetTOCInformation,  PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, STARBURN_DISC_INFORMATION, STARBURN_TRACK_INFORMATION, STARBURN_TOC_INFORMATION

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetDiscFreeSpace(
	IN PVOID p__PVOID__CdvdBurnerGrabber,
	IN STARBURN_CD_MODE p__CD_MODE,
	OUT PLONG p__PLONG__FreeSpaceInLBs,
	OUT PLARGE_INTEGER p__PLARGE_INTEGER__FreeSpaceInUCHARs
	);


/*

This function detect blank state of currently inserted disc in CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PBOOLEAN__IsBlank - Pointer to the BOOLEAN will be set to TRUE if the disc is blank and FALSE otherwise.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks


Example

This example allocates CdvdBurnerGrabber object, detect is disc blank and destroys the device object after it's not needed any 
more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
BOOLEAN l__BOOLEAN__IsDiscBlank(FALSE);

// Prepare exception text buffer
RtlZeroMemory(
&l__CHAR__ExceptionText,
sizeof( l__CHAR__ExceptionText )
);

// Prepare CDB failure information
RtlZeroMemory(
&l__CDB_FAILURE_INFORMATION,
sizeof( l__CDB_FAILURE_INFORMATION )
);

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
&l__PVOID__CdvdBurnerGrabber,
( PCHAR )( &l__CHAR__ExceptionText ),
sizeof( l__CHAR__ExceptionText ),
&l__ULONG__SystemError,
&l__CDB_FAILURE_INFORMATION,
( PCALLBACK )( StarBurn_Callback ),
0,
0,
4,
0,
32
);

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to detect is disc blank
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_IsDiscBlank(
( PCHAR )( &l__CHAR__ExceptionText ),
sizeof( l__CHAR__ExceptionText ),
&l__ULONG__SystemError,
&l__CDB_FAILURE_INFORMATION,
&l__BOOLEAN__IsDiscBlank
);

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and disc information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_GetDiscInformation, StarBurn_CdvdBurnerGrabber_GetTrackInformation, StarBurn_CdvdBurnerGrabber_GetTOCInformation,  PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, STARBURN_DISC_INFORMATION, STARBURN_TRACK_INFORMATION, STARBURN_TOC_INFORMATION

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_IsDiscBlank(
	IN PVOID p__PVOID__CdvdBurnerGrabber,
	OUT PCHAR p__PCHAR__ExceptionText,
	IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
	OUT PULONG p__PULONG__SystemError,
	OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	OUT PBOOLEAN p__PBOOLEAN__IsBlank
	);


/*

This function checks if the SPTD (SCSI Pass Through Direct) driver is present and gets SPTD driver version.


Parameters

p__PUCHAR__SptdMajorVersion - Pointer to the major SPTD driver version.

p__PUCHAR__SptdMinorVersion - Pointer to the minor SPTD driver version.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status. EN_SUCCESS if everythins is OK.


Remarks


Example

This example just checks for the SPTD presence and queries SPTD driver version.

<code>

// Somewhere in the data region
EXCEPTION_NUMBER l__EXCEPTION_NUMBER = EN_SUCCESS;
ULONG l__ULONG__SystemError = ERROR_SUCCESS;
UCHAR l__UCHAR__Major = 0;
UCHAR l__UCHAR__Minor = 0;

// Try to get SPTD driver version
l__EXCEPTION_NUMBER =
StarBurn_SPTD_GetVersion(
&l__UCHAR__Major,
&l__UCHAR__Minor,
&l__ULONG__SystemError
);

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with the SPTD here...       

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_CreateExEx, EXCEPTION_NUMBER

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_SPTD_GetVersion(									   
	OUT PUCHAR p__PUCHAR__SptdMajorVersion,
	OUT PUCHAR p__PUCHAR__SptdMinorVersion,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function gets TOC information of the currently inserted disc in the CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PTOC_INFORMATION - Pointer to the TOC information.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the GrabTrack sample that will demonstrate how ISO9660 or Joliet file system image can be grabbed from the 
CD/DVD/Blu-Ray/HD-DVD media and how StarBurn_CdvdBurnerGrabber_GetTOCInformation can be used to get current TOC information on the CD/DVD/Blu-Ray/HD-DVD 
media to determine session information.


Example

This example allocates CdvdBurnerGrabber object, gets TOC information and destroys the device object after it's not needed 
any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
TOC_INFORMATION l__TOC_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare TOC information buffer
RtlZeroMemory(
    &l__TOC_INFORMATION,
    sizeof( l__TOC_INFORMATION )
    );

// Try to get current TOC information
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetTOCInformation(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PTOC_INFORMATION )( &l__TOC_INFORMATION )
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and disc information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, TOC_INFORMATION, 
TOC_ENTRY

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetTOCInformation(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    OUT PTOC_INFORMATION p__PTOC_INFORMATION
    );


/*

This function grabs track from the currently inserted disc on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__UCHAR__TrackNumber - Track number to grab.

p__PCHAR__FileName - Pointer to file name track will be stored to.

p__LONG__Retries - Number of retries.

p__BOOLEAN__IsBadBlockIgnore - Is bad block ignore.

p__BOOLEAN__IsSingleLBTransferForced - Is single LB transfer forced.

p__ULONG__ReadReportDelayInSeconds - Read report delay in seconds.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the GrabTrack sample that will demonstrate how ISO9660 or Joliet file system image can be grabbed from the CD/DVD/Blu-Ray/HD-DVD 
media and how StarBurn_CdvdBurnerGrabber_GrabTrack can be used to grab track actually from the CD/DVD/Blu-Ray/HD-DVD media.


Example

This example allocates CdvdBurnerGrabber object, grabs first track and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
TOC_INFORMATION l__TOC_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare TOC information buffer
RtlZeroMemory(
    &l__TOC_INFORMATION,
    sizeof( l__TOC_INFORMATION )
    );

// Get TOC information here and analyze it...

// Try to grab the track (from TOC we know that this is audio track) with 2 retries and read report status every 1 second
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GrabTrack(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    1,
    "track01.mp3",
    NUMBER_OF_READ_RETRIES,
    TRUE,
    FALSE,
    READ_REPORT_DELAY_IN_SECONDS
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and disc information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, TOC_INFORMATION, 
TOC_ENTRY, StarBurn_CdvdBurnerGrabber_GrabCD, StarBurn_CdvdBurnerGrabber_GrabDVD

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GrabTrack(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN UCHAR p__UCHAR__TrackNumber,
    IN PCHAR p__PCHAR__FileName,
    IN LONG p__LONG__Retries,
    IN BOOLEAN p__BOOLEAN__IsBadBlockIgnore,
    IN BOOLEAN p__BOOLEAN__IsSingleLBTransferForced,
    IN ULONG p__ULONG__ReadReportDelayInSeconds
    );


/*

This function grabs range of logical blocks from the currently inserted disc on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__LONG__StartingLBA - Beginning of the LBA range to grab.

p__LONG__EndingLBA - Ending of the LBA range to grab.

p__PCHAR__FileName - Pointer to file name track will be stored to.

p__LONG__Retries - Number of retries.

p__BOOLEAN__IsBadBlockIgnore - Is bad block ignore.

p__BOOLEAN__IsSingleLBTransferForced - Is single LB transfer forced.

p__ULONG__ReadReportDelayInSeconds - Read report delay in seconds.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the GrabTrack sample that will demonstrate how ISO9660 or Joliet file system image can be grabbed from the CD/DVD/Blu-Ray/HD-DVD 
media and how StarBurn_CdvdBurnerGrabber_GrabTrack can be used to grab track actually from the CD/DVD/Blu-Ray/HD-DVD media. To grab not whole
track but just range of logical blocks TOC must be get first by call to StarBurn_CdvdBurnerGrabber_GetTOCInformation and after
this StarBurn_CdvdBurnerGrabber_GrabRange can be used to grab range of logical blocks. Attention! Care should be taken b/s the
range is inclusive. So grabbing the range 10 - 100 will take 91 logical blocks from 10 and up to 100.


Example

This example allocates CdvdBurnerGrabber object, grabs range of logical blocks track and destroys the device object after it's 
not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
TOC_INFORMATION l__TOC_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare TOC information buffer
RtlZeroMemory(
    &l__TOC_INFORMATION,
    sizeof( l__TOC_INFORMATION )
    );

// Get TOC information here and analyze it...

// Try to grab the range of 1001 logical blocks (range is both sides inclusive) (from TOC we know that this range 0 = 1000 is 
// valid) with 2 retries and read report status every 1 second
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GrabRange(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    0,
    1000,
    "track01range",
    NUMBER_OF_READ_RETRIES,
    TRUE,
    FALSE,
    READ_REPORT_DELAY_IN_SECONDS
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and disc information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, TOC_INFORMATION, 
TOC_ENTRY, StarBurn_CdvdBurnerGrabber_GrabCD, StarBurn_CdvdBurnerGrabber_GrabDVD

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GrabRange(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN LONG p__LONG__StartingLBA,
    IN LONG p__LONG__EndingLBA,
    IN PCHAR p__PCHAR__FileName,
    IN LONG p__LONG__Retries,
    IN BOOLEAN p__BOOLEAN__IsBadBlockIgnore,
    IN BOOLEAN p__BOOLEAN__IsSingleLBTransferForced,
    IN ULONG p__ULONG__ReadReportDelayInSeconds
    );


/*

This function reads one logical block from the currently inserted disc on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__LONG__LBA - LBA of logical block to read.

p__PUCHAR__Buffer - Pointer to output buffer.

p__ULONG__BufferSize - Output buffer size.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks


Example

This example allocates CdvdBurnerGrabber object, reads one logical block and destroys the device object after it's 
not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
TOC_INFORMATION l__TOC_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare TOC information buffer
RtlZeroMemory(
    &l__TOC_INFORMATION,
    sizeof( l__TOC_INFORMATION )
    );

// Get TOC information here and analyze it...

// Allocate buffer
UCHAR l__UCHAR__Buffer[4096];

// Try to grab one logical block with address 1000 (from TOC we know that this address 1000 is valid)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_ReadLB(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    1000,
    l__UCHAR__Buffer,
    4096
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and disc information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, TOC_INFORMATION, 
TOC_ENTRY, StarBurn_CdvdBurnerGrabber_GrabCD, StarBurn_CdvdBurnerGrabber_GrabDVD, StarBurn_CdvdBurnerGrabber_GrabRange

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_ReadLB(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN LONG p__LONG__LBA,
    IN PUCHAR p__PUCHAR__Buffer,
    IN LONG p__ULONG__BufferSize
    );


/*

This function reads one or more logical block(s) from the currently inserted CD in RAW format.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__UCHAR__ExpectedLBType - Expected logical block type. See EXPECTED_LB_TYPE_XXX constants.

p__LONG__LBA - Starting logical block number to read from.

p__ULONG__DataBufferSizeInLBs - Data buffer/request size in logical block(s). 

p__UCHAR__ErrorField - Error format. See ERROR_FIELD_XXX constants. 

p__BOOLEAN__IsEDC_ECC - TRUE if you want EDC/ECC data included in the output stream, FALSE if you don't want EDC/ECC.

p__BOOLEAN__IsUserData - TRUE if you want user data (main payload) included in the output stream, FALSE if you don't want user data.

p__UCHAR__HeaderCodes - Header format. See HEADER_CODE_XXX constants.

p__BOOLEAN__IsSYNC - TRUE if you want SYNC pattern included in the output stream, FALSE if you don't want SYNC pattern.

p__UCHAR__SubChannelSelectionBits - Sub-channel selection. See SUBCHANNEL_XXX constants.

p__PUCHAR__DataBuffer - Pointer to data buffer to receive the payload. 

p__ULONG__DataBufferSizeInUCHARs - Data buffer size in unsigned char(s).


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Make sure your data buffer is page-aligned, transfer size is less then 64KB and all of the input parameters are valid.


Example

This example allocates CdvdBurnerGrabber object, reads 2 (two) RAW logical blocks and destroys the device object after it's 
not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
TOC_INFORMATION l__TOC_INFORMATION;
UCHAR l__UCHAR__Buffer[ 8192 ]; // We do allocate buffer on the stack but it's not correct. Page-aligned memory must be used.

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Prepare the buffer
RtlZeroMemory(
	&l__UCHAR__Buffer,
	sizeof( l__UCHAR__Buffer )
	);

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare TOC information buffer
RtlZeroMemory(
    &l__TOC_INFORMATION,
    sizeof( l__TOC_INFORMATION )
    );

// Get TOC information here and analyze it

// Get currently inserted disc and analyze it. We can do RAW read from CD media only

// Probe supported read modes as we need to read in the ones drive really supports

// Try to grab two RAW logical blocks starting from LBA 100 (from TOC we know that address 100 is valid)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_ReadRaw(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	EXPECTED_LB_TYPE_ANY, 				// Accept any logical blocks
	100, 								// Start from logical block number 100
	2, 									// 2 logical blocks only
	ERROR_FIELD_NO_ERROR, 				// No error data included
	TRUE,								// YES, we need EDC/ECC data
	TRUE,								// YES, we need user data
	HEADER_CODE_ALL_HEADERS,			// We need ALL of the headers
	TRUE,								// YES, we need SYNC pattern
	SUBCHANNEL_RAW_PW,					// Read RAW P-W sub-channel from the disc
	( PUCHAR )( &l__UCHAR__Buffer ),    // Pointer to data buffer to receive the payload
	sizeof( l__UCHAR__Buffer )			// Data buffer size in unsigned char(s)
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and read sectors here

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, TOC_INFORMATION, 
TOC_ENTRY, StarBurn_CdvdBurnerGrabber_GrabCD, StarBurn_CdvdBurnerGrabber_GrabDVD, StarBurn_CdvdBurnerGrabber_GrabRange,
StarBurn_CdvdBurnerGrabber_ReadLB, StarBurn_CdvdBurnerGrabber_ReadCooked 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_ReadRaw(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN UCHAR p__UCHAR__ExpectedLBType,
	IN LONG p__LONG__LBA,
	IN ULONG p__ULONG__DataBufferSizeInLBs,
	IN UCHAR p__UCHAR__ErrorField,
	IN BOOLEAN p__BOOLEAN__IsEDC_ECC,
	IN BOOLEAN p__BOOLEAN__IsUserData,
	IN UCHAR p__UCHAR__HeaderCodes,
	IN BOOLEAN p__BOOLEAN__IsSYNC,
	IN UCHAR p__UCHAR__SubChannelSelectionBits,
	OUT PUCHAR p__PUCHAR__DataBuffer,
	IN ULONG p__ULONG__DataBufferSizeInUCHARs
	);


/*

This function reads one or more logical block(s) from the currently inserted CD/DVD/Blu-Ray/HD-DVD in cooked format.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PUCHAR__Read - Pointer to data buffer to receive read data to.

p__ULONG__ReadSizeInUCHARs - Read size in unsigned char(s).

p__LONG__LBA - Starting LBA to read from.

p__ULONG__TransferSizeInLBs - Whole transfer size in logical block(s).


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Make sure your data buffer is page-aligned, transfer size is less then 64KB and all of the input parameters are valid.


Example

This example allocates CdvdBurnerGrabber object, reads 2 (two) cooked logical blocks and destroys the device object after it's 
not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
TOC_INFORMATION l__TOC_INFORMATION;
UCHAR l__UCHAR__Buffer[ 8192 ]; // We do allocate buffer on the stack but it's not correct. Page-aligned memory must be used.

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Prepare the buffer
RtlZeroMemory(
	&l__UCHAR__Buffer,
	sizeof( l__UCHAR__Buffer )
	);

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare TOC information buffer
RtlZeroMemory(
    &l__TOC_INFORMATION,
    sizeof( l__TOC_INFORMATION )
    );

// Get TOC information here and analyze it

// Get currently inserted disc and analyze it

// Try to grab two cooked logical blocks starting from LBA 100 (from TOC we know that address 100 is valid)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_ReadCooked(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	( PUCHAR )( &l__UCHAR__Buffer ),    // Pointer to data buffer to receive the payload
	sizeof( l__UCHAR__Buffer ),			// Data buffer size in unsigned char(s)
	100, 								// Start from logical block number 100
	2									// 2 logical blocks
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and read sectors here

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, TOC_INFORMATION, 
TOC_ENTRY, StarBurn_CdvdBurnerGrabber_GrabCD, StarBurn_CdvdBurnerGrabber_GrabDVD, StarBurn_CdvdBurnerGrabber_GrabRange,
StarBurn_CdvdBurnerGrabber_ReadLB, StarBurn_CdvdBurnerGrabber_ReadRaw

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_ReadCooked(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	OUT PUCHAR p__PUCHAR__Read,
	IN ULONG p__ULONG__ReadSizeInUCHARs,
	IN LONG p__LONG__LBA,
	IN ULONG p__ULONG__TransferSizeInLBs
	);


/*

This function grabs disc image from the currently inserted disc on CD/DVD/Blu-Ray/HD-DVD burner device and store it in MDS format.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PCHAR__FileName - Pointer to file name disc will be stored to (basic name, other one will be generated from it).

p__READ_MODE - Read mode (raw, raw + PQ sub-channel or raw + raw P-W sub-channel).

p__LONG__Retries - Number of retries on bad block hit.

p__BOOLEAN__IsBadBlockIgnore - Is bad block ignore.

p__BOOLEAN__IsSingleLBTransferForced - Is single LB transfer forced.

p__ULONG__ReadReportDelayInSeconds - Read report delay in seconds.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the GrabDisc sample that will demonstrate how whole disc image can be grabbed from the CD/DVD/Blu-Ray/HD-DVD media and how 
StarBurn_CdvdBurnerGrabber_GrabCD can be used to grab disc from the CD/DVD/Blu-Ray/HD-DVD media.


Example

This example allocates CdvdBurnerGrabber object, grabs disc and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
TOC_INFORMATION l__TOC_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare TOC information buffer
RtlZeroMemory(
    &l__TOC_INFORMATION,
    sizeof( l__TOC_INFORMATION )
    );

// Get TOC information here and analyze it...

// Try to grab the disc with 2 retries on bad block hit and single read status report per every 1 second, also use fast software error correction
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GrabCD(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    "disc01",
    READ_MODE_RAW,
    NUMBER_OF_READ_RETRIES,
    TRUE,
    FALSE,
    READ_REPORT_DELAY_IN_SECONDS,
    TRUE
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and disc information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, TOC_INFORMATION, 
TOC_ENTRY, StarBurn_CdvdBurnerGrabber_GrabTrack

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GrabCD(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCHAR p__PCHAR__FileName,
    IN READ_MODE p__READ_MODE,
    IN LONG p__LONG__Retries,
    IN BOOLEAN p__BOOLEAN__IsBadBlockIgnore,
    IN BOOLEAN p__BOOLEAN__IsSingleLBTransferForced,
    IN ULONG p__ULONG__ReadReportDelayInSeconds,
    IN BOOLEAN p__BOOLEAN__IsDisableHardwareErrorCorrection
    );


/*

This function grabs disc image from the currently inserted disc on CD/DVD/Blu-Ray/HD-DVD burner device and store it in MDS format, disc image
will be stored into the series of files.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PCHAR__FileName - Pointer to file name disc will be stored to (basic name, other one will be generated from it).

p__LONG__SplitFileSizeInMBs - Split file size in megabytes.

p__LONG__Retries - Number of retries on bad block hit.

p__BOOLEAN__IsBadBlockIgnore - Is bad block ignore.

p__BOOLEAN__IsSingleLBTransferForced - Is single LB transfer forced.

p__ULONG__ReadReportDelayInSeconds - Read report delay in seconds.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the GrabDisc sample that will demonstrate how whole disc image can be grabbed from the CD/DVD/Blu-Ray/HD-DVD media and how 
StarBurn_CdvdBurnerGrabber_GrabDVD can be used to grab disc from the CD/DVD/Blu-Ray/HD-DVD media. For now only DVD media can be grabbed
with this [Split] variant of grabbing code.


Example

This example allocates CdvdBurnerGrabber object, grabs disc and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
TOC_INFORMATION l__TOC_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare TOC information buffer
RtlZeroMemory(
    &l__TOC_INFORMATION,
    sizeof( l__TOC_INFORMATION )
    );

// Get TOC information here and analyze it...

// Try to grab the disc with 2 retries on bad block hit and single read status report per every 1 second, store all the CD/DVD/Blu-Ray/HD-DVD
// image into series of files 1024MB (1GB) each
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GrabDVD(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    "disc01",
    1024, // 1GB
    NUMBER_OF_READ_RETRIES,
    TRUE,
    FALSE,
    READ_REPORT_DELAY_IN_SECONDS    
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and disc information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, TOC_INFORMATION, 
TOC_ENTRY, StarBurn_CdvdBurnerGrabber_GrabTrack

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GrabDVD(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCHAR p__PCHAR__FileName,
    IN LONG p__LONG__SplitFileSizeInMBs,
    IN LONG p__LONG__Retries,
    IN BOOLEAN p__BOOLEAN__IsBadBlockIgnore,
    IN BOOLEAN p__BOOLEAN__IsSingleLBTransferForced,
    IN ULONG p__ULONG__ReadReportDelayInSeconds
    );


/*

This function probes supported read modes on the currently inserted disc on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__BOOLEAN__IsCooked - Is cooked mode supported.

p__BOOLEAN__IsRaw - Is raw mode supported.

p__BOOLEAN__IsRawPQ - Is raw + PQ sub-channel mode supported.

p__BOOLEAN__IsRawRawPW - Is raw + raw P-W sub-channel mode supported.

p__BOOLEAN__IsPQ - Is PQ sub-channel mode supported.

p__BOOLEAN__IsRawPW - Is raw P-W sub-channel mode supported.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the GrabDisc sample that will demonstrate how whole disc image can be grabbed from the CD/DVD/Blu-Ray/HD-DVD media and how 
StarBurn_CdvdBurnerGrabber_ProbeSupportedReadModes can be used to determine supported read modes.

[ WARNING! It's required to have media inserted for this function to work properly! ]


Example

This example allocates CdvdBurnerGrabber object, probes supported read modes and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
BOOLEAN l__BOOLEAN__IsCooked = FALSE;
BOOLEAN l__BOOLEAN__IsRaw = FALSE;
BOOLEAN l__BOOLEAN__IsRawPQ = FALSE;
BOOLEAN l__BOOLEAN__IsRawRawPW = FALSE;
BOOLEAN l__BOOLEAN__IsPQ = FALSE;
BOOLEAN l__BOOLEAN__IsRawPW = FALSE;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to probe supported read modes
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_ProbeSupportedReadModes(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    &l__BOOLEAN__IsCooked,
    &l__BOOLEAN__IsRaw,
    &l__BOOLEAN__IsRawPQ,
    &l__BOOLEAN__IsRawRawPW,
    &l__BOOLEAN__IsPQ,
    &l__BOOLEAN__IsRawPW
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and supported read modes information here...       

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, TOC_INFORMATION, 
TOC_ENTRY, StarBurn_CdvdBurnerGrabber_GrabCD, StarBurn_CdvdBurnerGrabber_GrabDVD

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_ProbeSupportedReadModes(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    OUT PBOOLEAN p__PBOOLEAN__IsCooked,
    OUT PBOOLEAN p__PBOOLEAN__IsRaw,
    OUT PBOOLEAN p__PBOOLEAN__IsRawQ,
    OUT PBOOLEAN p__PBOOLEAN__IsRawRawPW,
    OUT PBOOLEAN p__PBOOLEAN__IsPQ,
    OUT PBOOLEAN p__PBOOLEAN__IsRawPW
    );


/*

This function probes supported read modes on the currently inserted disc on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__BOOLEAN__IsTrackAtOnce - Is Track-At-Once supported.

p__BOOLEAN__IsSessionAtOnce - Is Session-At-Once supported.

p__BOOLEAN__IsDiscAtOncePQ - Is Disc-At-Once PQ supported.

p__BOOLEAN__IsDiscAtOnceRawPW - Is Disc-At-Once raw PW supported.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the burning samples that will demonstrate how disc can be recorded and how 
StarBurn_CdvdBurnerGrabber_ProbeSupportedWriteModes can be used to determine supported write modes.

[ WARNING! It's required to have media inserted for this function to work properly! ]


Example

This example allocates CdvdBurnerGrabber object, probes supported write modes and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
BOOLEAN l__BOOLEAN__IsTrackAtOnce = FALSE;
BOOLEAN l__BOOLEAN__IsSessionAtOnce = FALSE;
BOOLEAN l__BOOLEAN__IsDiscAtOncePQ = FALSE;
BOOLEAN l__BOOLEAN__IsDiscAtOnceRawPW = FALSE;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to probe supported write modes
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_ProbeSupportedWriteModes(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    &l__BOOLEAN__IsTrackAtOnce,
    &l__BOOLEAN__IsSessionAtOnce,
    &l__BOOLEAN__IsDiscAtOncePQ,
    &l__BOOLEAN__IsDiscAtOnceRawPW
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object and supported write modes information here...      

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, StarBurn_CdvdBurnerGrabber_SessionAtOnce,
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_ProbeSupportedWriteModes(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    OUT PBOOLEAN p__PBOOLEAN__IsTrackAtOnce,
    OUT PBOOLEAN p__PBOOLEAN__IsSessionAtOnce,
    OUT PBOOLEAN p__PBOOLEAN__IsDiscAtOncePQ,
    OUT PBOOLEAN p__PBOOLEAN__IsDiscAtOnceRawPW
    );


/*

This function finds device of the specified device type.


Parameters

p__UCHAR__DeviceType - SCSI device type to find

p__BOOLEAN__IsFindFirst - TRUE if the function will return after locating first device, FALSE to process all the devices.

p__PCALLBACK - Callback function that will be called with FIND_DEVICE CALLBACK_NUMBER, callback context and adapter ID 
and Target ID of the device.

p__PVOID__CallbackContext - Callback context that will be passed as second parameter into call to p__PCALLBACK.


Result

Number of devices found. If zero - nothing was found.


Remarks

Please see the FindDevice sample that will demonstrate how to find CD/DVD/Blu-Ray/HD-DVD devices installed in the system.


Example

This example finds first first CD/DVD/Blu-Ray/HD-DVD device, allocates CdvdBurnerGrabber object, and destroys the device object after 
it's not needed any more.

<code>

VOID
__stdcall
Find_Callback(
    IN CALLBACK_NUMBER p__CALLBACK_NUMBER,
    IN PVOID p__PVOID__CallbackContext,
    IN PVOID p__PVOID__CallbackSpecial1,
    IN PVOID p__PVOID__CallbackSpecial2
    )
{

PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on passed address (bus ID is always 0 in case of ASPI and LUN cannot be probed so 
// always 0 as well) with 32MB of cache)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    ( UCHAR )( p__PVOID__CallbackSpecial1) ,
    0,
    ( UCHAR )( p__PVOID__CallbackSpecial2) ,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

}

// Somewhere in the code

// Try to find device
if ( 
StarBurn_FindDevice(
    SCSI_DEVICE_RO_DIRECT_ACCESS,
    TRUE,
    ( PCALLBACK )( Find_Callback ),
    NULL
    ) == 0
)
{
// Handle error here...
}
else
{
// All actions are in the callback function...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
LONG
__stdcall
StarBurn_FindDevice(
    IN UCHAR p__UCHAR__DeviceType,
    IN BOOLEAN p__BOOLEAN__IsFindFirst,
    IN PCALLBACK p__CALLBACK,
    IN PVOID p__PVOID__CallbackContext
    );


/*

This function records VCD/MPEG1 image located in a file on the hard disk with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in
Track-At-Once mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PCHAR__MPEG1ImagePathAndFileName - Pointer to VCD/MPEG1 image file located in a file and stored on the hard disk.

p__PCHAR__AlbumIdentifier - Pointer to album identifier.

p__USHORT__NumberOfVolumesInAlbum - Number of volumes in album.

p__USHORT__AlbumSetSequenceNumber - Album set sequence number.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the VideoCD sample that will demonstrate how VCD/MPEG1 image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and with the help of 
StarBurn_CdvdBurnerGrabber_VideoCD with currently set write speed and currently set optimum power calibration. 


Example

This example allocates CdvdBurnerGrabber object, records the VCD/MPEG1 image to the CD/DVD/Blu-Ray/HD-DVD media and destroys the device object 
after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to record the VCD/MPEG1 image (in Track-At-Once mode)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_VideoCD(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    "C:\\MOVIE.MPEG1",
    "Album",
    0x0001,
    0x0001,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_SuperVideoCD 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_VideoCD(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCHAR p__PCHAR__MPEG1ImagePathAndFileName,
    IN PCHAR p__PCHAR__AlbumIdentifier,
    IN USHORT p__USHORT__NumberOfVolumesInAlbum,
    IN USHORT p__USHORT__AlbumSetSequenceNumber,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function records VCD/MPEG1 image located in a file on the hard disk with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in
selected write mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__WRITE_MODE - Write mode to use.

p__PCHAR__MPEG1ImagePathAndFileName - Pointer to VCD/MPEG1 image file located in a file and stored on the hard disk.

p__PCHAR__AlbumIdentifier - Pointer to album identifier.

p__USHORT__NumberOfVolumesInAlbum - Number of volumes in album.

p__USHORT__AlbumSetSequenceNumber - Album set sequence number.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the VideoCDEx sample that will demonstrate how VCD/MPEG1 image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and with the help of 
StarBurn_CdvdBurnerGrabber_VideoCDEx with currently set write speed and currently set optimum power calibration. 


Example

This example allocates CdvdBurnerGrabber object, records the VCD/MPEG1 image to the CD/DVD/Blu-Ray/HD-DVD media and destroys the device object 
after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to record the VCD/MPEG1 image (in Session-At-Once mode)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_VideoCDEx(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    WRITE_MODE_SESSION_AT_ONCE,
    "C:\\MOVIE.MPEG1",
    "Album",
    0x0001,
    0x0001,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_SuperVideoCD, StarBurn_CdvdBurnerGrabber_VideoCD, StarBurn_CdvdBurnerGrabber_SuperVideoCDEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_VideoCDEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN WRITE_MODE p__WRITE_MODE,
    IN PCHAR p__PCHAR__MPEG1ImagePathAndFileName,
    IN PCHAR p__PCHAR__AlbumIdentifier,
    IN USHORT p__USHORT__NumberOfVolumesInAlbum,
    IN USHORT p__USHORT__AlbumSetSequenceNumber,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function records SVCD/MPEG2 image located in a file on the hard disk with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PCHAR__MPEG2ImagePathAndFileName - Pointer to SVCD/MPEG2 image file located in a file and stored on the hard disk.

p__PCHAR__AlbumIdentifier - Pointer to album identifier.

p__USHORT__NumberOfVolumesInAlbum - Number of volumes in album.

p__USHORT__AlbumSetSequenceNumber - Album set sequence number.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the SuperVideoCD sample that will demonstrate how SVCD/MPEG2 image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and with the help of 
StarBurn_CdvdBurnerGrabber_SuperVideoCD with currently set write speed and currently set optimum power calibration. 


Example

This example allocates CdvdBurnerGrabber object, records the SVCD/MPEG2 image to the CD/DVD/Blu-Ray/HD-DVD media and destroys the device 
object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
ULONG l__ULONG__Status;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to record the SVCD/MPEG2 image (in Track-At-Once mode)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_SuperVideoCD(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    "C:\\MOVIE.MPEG2",
    "Album",
    0x0001,
    0x0001,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_VideoCD 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_SuperVideoCD(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCHAR p__PCHAR__MPEG2ImagePathAndFileName,
    IN PCHAR p__PCHAR__AlbumIdentifier,
    IN USHORT p__USHORT__NumberOfVolumesInAlbum,
    IN USHORT p__USHORT__AlbumSetSequenceNumber,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function records SVCD/MPEG2 image located in a file on the hard disk with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in
selected write mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__WRITE_MODE - Write mode to use.

p__PCHAR__MPEG2ImagePathAndFileName - Pointer to SVCD/MPEG2 image file located in a file and stored on the hard disk.

p__PCHAR__AlbumIdentifier - Pointer to album identifier.

p__USHORT__NumberOfVolumesInAlbum - Number of volumes in album.

p__USHORT__AlbumSetSequenceNumber - Album set sequence number.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the SuperVideoCDEx sample that will demonstrate how SVCD/MPEG2 image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and with the help of 
StarBurn_CdvdBurnerGrabber_SuperVideoCDEx with currently set write speed and currently set optimum power calibration. 


Example

This example allocates CdvdBurnerGrabber object, records the SVCD/MPEG2 image to the CD/DVD/Blu-Ray/HD-DVD media and destroys the device object 
after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to record the SVCD/MPEG2 image (in Session-At-Once mode)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_SuperVideoCDEx(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    WRITE_MODE_SESSION_AT_ONCE,
    "C:\\MOVIE.MPEG2",
    "Album",
    0x0001,
    0x0001,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_SuperVideoCD, StarBurn_CdvdBurnerGrabber_VideoCD, StarBurn_CdvdBurnerGrabber_VideoCDEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_SuperVideoCDEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN WRITE_MODE p__WRITE_MODE,
    IN PCHAR p__PCHAR__MPEG2ImagePathAndFileName,
    IN PCHAR p__PCHAR__AlbumIdentifier,
    IN USHORT p__USHORT__NumberOfVolumesInAlbum,
    IN USHORT p__USHORT__AlbumSetSequenceNumber,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function returns inserted to CD/DVD/Blu-Ray/HD-DVD burner device disc type. This data can be used to report it to the user and to select
the stream type to record.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before with the call to 
StarBurn_CdvdBurnerGrabber_Create(...) or StarBurn_CdvdBurnerGrabber_CreateEx(...) API calls.


Result

Inserted disc type. This function cannot fail. 


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and what use can be taken from inserted disc type information.


Example

This example allocates CdvdBurnerGrabber object, retrieves inserted disc type and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
DISC_TYPE l__DISC_TYPE = DISC_TYPE_UNKNOWN;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Get inserted disc type
l__DISC_TYPE = StarBurn_CdvdBurnerGrabber_GetInsertedDiscType( l__PVOID__CdvdBurnerGrabber );

// Do something with CdvdBurnerGrabber device object and it's inserted disc type here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
DISC_TYPE
__stdcall
StarBurn_CdvdBurnerGrabber_GetInsertedDiscType(
    IN PVOID p__PVOID__CdvdBurnerGrabber
    );


/*

This function cancels current read or write process on the CD/DVD/Blu-Ray/HD-DVD burner. 


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before with the call to StarBurn_CdvdBurnerGrabber_Create().


Result

Nothing. This function cannot fail. 


Remarks

There is no sample provided for this code so please check the code below.


Example

This example allocates CdvdBurnerGrabber object, cancels current I/O process and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Initiate some I/O process here

// Cancel initiated I/O process
StarBurn_CdvdBurnerGrabber_Cancel();

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, StarBurn_CdvdBurnerGrabber_VideoCD,
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, StarBurn_CdvdBurnerGrabber_SuperVideoCD, StarBurn_CdvdBurnerGrabber_GrabTrack,
StarBurn_CdvdBurnerGrabber_GrabCD, StarBurn_CdvdBurnerGrabber_GrabDVD

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_CdvdBurnerGrabber_Cancel(
    IN PVOID p__PVOID__CdvdBurnerGrabber
    );


/*

This function sets boot image for created ISO9660 or Joliet file tree. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to ISO9660 or Joliet file tree to add boot image to.

p__PCHAR__AbsoluteFileName - Pointer to absolute file name of the boot image.

p__UCHAR__SystemType - System type value.

p__UCHAR__MediaType - Media type value.

p__UCHAR__SectorsToLoad - Number of sectors to load

p__BOOLEAN__HideNode - Indicates will the node be present in the root folder or not

p__PCHAR__ExceptionText - Pointer to exception text buffer.

p__ULONG__ExceptionTextSizeInUCHARs - Exception text size in UCHARs.

p__PULONG__SystemError - Pointer to system error.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. 


Remarks

Please see the TrackAtOnceFromTreeWithBoot sample that will demonstrate how ISO9660 or Joliet file system image can be created, boot image added and whole
result burn to the CD/DVD/Blu-Ray/HD-DVD media.


Example

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
PVOID l__PVOID__ISO9660JolietFileTree;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Create and add something to ISO9660 file tree here

// Try to set boot image
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_SetBootImage(
    l__PVOID__ISO9660JolietFileTree,
	"C:\\bootimage.bin", // Here is our boot image we gonna use
    6, // Just stick with 6 here...
    ELTORITO_MEDIA_FLOPPY144,
	1,// set only one sector to load
	FALSE, // don't hide the file
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError
    );

// Check for correct reply
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromTree,
StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromTree, StarBurn_CdvdBurnerGrabber_SessionAtOnce

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_SetBootImage(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PCHAR p__PCHAR__AbsoluteFileName,    
    IN UCHAR p__UCHAR__SystemType,
    IN UCHAR p__UCHAR__MediaType,
	IN UCHAR p__UCHAR__SectorsToLoad,
	IN BOOLEAN p__BOOLEAN__HideNode,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError	
    );


STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_SetBootImageEx(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PCHAR p__PCHAR__AbsoluteFileName,    
	IN PCHAR p__PCHAR__BootImageFileName,
	IN ULONG p__ULONG__BootImageFileAttributes,
    IN UCHAR p__UCHAR__SystemType,
    IN UCHAR p__UCHAR__MediaType,
	IN UCHAR p__UCHAR__SectorsToLoad,
	IN USHORT p__USHORT__LoadSegment,
	IN BOOLEAN p__BOOLEAN__IsHideNode,
	IN BOOLEAN p__BOOLEAN__IsBootInformationPatch,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError	
    );


/*

This function imports track for created ISO9660 or Joliet file tree. 


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before with the call to StarBurn_CdvdBurnerGrabber_Create().

p__PVOID__ISO9660JolietFileTree - Pointer to ISO9660 or Joliet file tree to import track to.

p__UCHAR__TrackNumber - Track number to import.

p__BOOLEAN__ImportJolietStructures - Should we try to import Joliet structures (TRUE) or proceed with ISO9660 only (FALSE).

p__PCHAR__ExceptionText - Pointer to exception text buffer.

p__ULONG__ExceptionTextSizeInUCHARs - Exception text size in UCHARs.

p__PULONG__SystemError - Pointer to system error.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTreeWithImport sample that will demonstrate how ISO9660 or Joliet file system image can be created, existing track imported and 
whole result burn to the CD/DVD/Blu-Ray/HD-DVD media.

[ WARNING! It's required to create empty file tree, import existing disc content into it and only after this add new or delete existing
file tree nodes. Reversed direction should not be tried! ]


Example

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
PVOID l__PVOID__ISO9660JolietFileTree;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Create and add something to ISO9660 file tree here

// Try to import file system structures from the track
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_ImportTrack(
	l__PVOID__CdvdBurnerGrabber,
    l__PVOID__ISO9660JolietFileTree,
	0x01, // First track,
	TRUE, // Try to proceed as Joliet
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError
    );

// Check for correct reply
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, 
StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromTree, StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromTree, 
StarBurn_CdvdBurnerGrabber_SessionAtOnce, StarBurn_CdvdBurnerGrabber_ImportFile

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_ImportTrack(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN UCHAR p__UCHAR__TrackNumber,
    IN BOOLEAN p__BOOLEAN__ImportJolietStructures,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError
    );


/*

This function imports file for created ISO9660 or Joliet file tree. 


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before with the call 
to StarBurn_CdvdBurnerGrabber_Create().

p__PVOID__ISO9660JolietFileTree - Pointer to ISO9660 or Joliet file tree to import track to.

p__PCHAR__ImportFileName - Pointer to the file name to import file system structures from.

p__BOOLEAN__ImportJolietStructures - Should we try to import Joliet structures (TRUE) or proceed with ISO9660 only 
(FALSE).

p__PCHAR__ExceptionText - Pointer to exception text buffer.

p__ULONG__ExceptionTextSizeInUCHARs - Exception text size in UCHARs.

p__PULONG__SystemError - Pointer to system error.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTreeWithImportFromFile sample that will demonstrate how ISO9660 or Joliet file system
image can be created, existing file imported and whole result burn to the CD/DVD/Blu-Ray/HD-DVD media.


Example

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
PVOID l__PVOID__ISO9660JolietFileTree;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Create and add something to ISO9660 file tree here

// Try to import file system structures from the file
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_ImportFile(
	l__PVOID__CdvdBurnerGrabber,
    l__PVOID__ISO9660JolietFileTree,
	"Image.ISO", // Import FS structures from file called "Image.ISO"
	TRUE, // Try to proceed as Joliet
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError
    );

// Check for correct reply
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, 
StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromTree, StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromTree, 
StarBurn_CdvdBurnerGrabber_SessionAtOnce, StarBurn_CdvdBurnerGrabber_ImportTrack

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_ImportFile(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PCHAR p__PCHAR__ImportFileName,
    IN BOOLEAN p__BOOLEAN__ImportJolietStructures,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError
    );


/*

This function records ISO9660 or Joliet file system image located in file tree object with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in Disc-At-Once PQ mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PVOID__ISO9660JolietFileTree - Pointer to ISO9660 or Joliet file tree object.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE if next session is allowed on this media, FALSE if next session 
will not be allowed on this media.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the DiscAtOnceFromTree sample that will demonstrate how ISO9660 or Joliet file system image located in a file tree object can be burn on the CD/DVD/Blu-Ray/HD-DVD 
media and with the help of StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromTree with currently set write speed and currently set optimum power calibration. 


Example

This example allocates CdvdBurnerGrabber object, creates ISO9660 or Joliet file system image located in a file tree object and burns it to the CD/DVD/Blu-Ray/HD-DVD media and 
destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
DAO_DISC_LAYOUT l__DAO_DISC_LAYOUT;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Create and initialize ISO9660 or Joliet file tree object here pointed by l__PVOID__ISO9660JolietFileTree

// Try to record the ISO9660 or Joliet file system image in Disc-At-Once PQ mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromTree(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	l__PVOID__ISO9660JolietFileTree,
    FALSE, // No XA, just ordinary CDROM
    FALSE, // No test write, real burn
    FALSE, // No next session allowed
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFile 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_DiscAtOncePQFromTree(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN PVOID p__PVOID__ISO9660FileTree,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function records ISO9660 or Joliet file system image located in file tree object with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in Disc-At-Once 
raw P-W mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PVOID__ISO9660JolietFileTree - Pointer to ISO9660 or Joliet file tree object.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE if next session is allowed on this media, FALSE if next session 
will not be allowed on this media.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the DiscAtOnceFromTree sample that will demonstrate how ISO9660 or Joliet file system image located in a file tree object can be burn on the CD/DVD/Blu-Ray/HD-DVD 
media and with the help of StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromTree with currently set write speed and currently set optimum power calibration. 


Example

This example allocates CdvdBurnerGrabber object, creates ISO9660 or Joliet file system image located in a file tree object and burns it to the CD/DVD/Blu-Ray/HD-DVD media and 
destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
DAO_DISC_LAYOUT l__DAO_DISC_LAYOUT;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Create and initialize ISO9660 or Joliet file tree object here pointed by l__PVOID__ISO9660JolietFileTree

// Try to record the ISO9660 or Joliet file system image in Disc-At-Once raw P-W mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromTree(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	l__PVOID__ISO9660JolietFileTree,
    FALSE, // No XA, just ordinary CDROM
    FALSE, // No test write, real burn
    FALSE, // No next session allowed
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFile 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromTree(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN PVOID p__PVOID__ISO9660FileTree,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

Sets CD-Text item for the specified CD/DVD/Blu-Ray/HD-DVD device.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to CStarBurn_CdvdBurnerGrabber object.

p__CHAR__TrackIndex - 1-based track number. Or 0 for the common DISC information.

PCHAR p__PCHAR__Artist - Pointer to zero-terminated string with the name of artist/performer/singer.

PCHAR p__PCHAR__Title - Pointer to zero-terminated string with the track title/song name.

p__PCHAR__ExceptionText - Pointer to buffer for exception text.

p__ULONG__ExceptionTextSizeInUCHARs - Exception text size in UCHARs.

p__PULONG__SystemError - Pointer to system error.


Result

Exception number


Remarks

Please check DiscAtOnceFromFile sample to find out how to use StarBurn_CdvdBurnerGrabber_SetCDTextItem() in the 
right way. Note, that this function is used to burn CD-TEXT for audio discs using StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFile.


Example

This example allocates CdvdBurnerGrabber object, specifies the CD-Text for a disc and for 3 track and burns the disc.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
DAO_DISC_LAYOUT l__DAO_DISC_LAYOUT;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add files to burn here by filling l__DAO_DISC_LAYOUT information

// Try to set CD-Text information for 3d track
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_SetCDTextItem(
	l__PVOID__CdvdBurnerGrabber,
	3,
    "My band",
    "My new song",
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status
    );

// Check for success
if (l__EXCEPTION_NUMBER != EN_SUCCESS)
{
// Handle error here...
}
            
// Try to set CD-Text information for the whole disc
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_SetCDTextItem(
	l__PVOID__CdvdBurnerGrabber,
    0,
    "My band",
    "My first album",
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status
    );

// Check for success
if (l__EXCEPTION_NUMBER != EN_SUCCESS)
{
// Handle error here...
}
        
// Try to burn ISO/sound/MDS image to the disc as CDROM XA (MODE2 Form1) or CDDA (CD digital audio) in Disc-At-Once raw P-W mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFile( 
	l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    &l__CDB_FAILURE_INFORMATION,
    &l__DAO_DISC_LAYOUT,
    FALSE, 
    l__BOOLEAN__IsTestWrite,
    FALSE, // Next session allowed
    FALSE, // Do NOT repair broken sub-channel
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFile, StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_CreateEx 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_SetCDTextItem(
	IN PVOID p__PVOID__CdvdBurnerGrabber,
	IN CHAR p__CHAR__TrackIndex,
	IN const PCHAR p__PCHAR__Artist,
	IN const PCHAR p__PCHAR__Title,
	OUT PCHAR p__PCHAR__ExceptionText,
	IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function devastates created UDF tree from the pointed root recursively.


Parameters

p__PUDF_TREE_ITEM__Root - Pointer to allocated and formatted UDF tree root node.

p__PUDF_CONTROL_BLOCK - Pointer to UDF control block.


Result

Nothing. This function cannot fail. 


Remarks

Please check DVDVideoBuildImage and DVDVideoTrackAtOnceFromTree samples to find out how to use StarBurn_UDF_Destroy() in the right way.


Example

This example allocates CdvdBurnerGrabber object, creates and destroys UDF tree and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UDF_TREE_ITEM l__UDF_TREE_ITEM__Director[ 10 ];
UDF_CONTROL_BLOCK l__UDF_CONTROL_BLOCK;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add nodes with StarBurn_UDF_FormatTreeItemAsXxx here

// Create UDF tree with StarBurn_UDF_CreateEx() here

// Do something with the UDF tree here (maybe burn to CdvdBurnerGrabber object)

// Clean up UDF stuff with StarBurn_UDF_CleanUp() here

// Destroy UDF tree from the root
StarBurn_UDF_Destroy(
	&l__UDF_TREE_ITEM__Directory[ 0 ],
	&l__UDF_CONTROL_BLOCK
	);

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_UDF_CreateEx, StarBurn_UDF_CleanUp, StarBurn_UDF_FormatTreeItemAsDirectory, StarBurn_UDF_FormatTreeItemAsFile

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_UDF_Destroy(
    IN PUDF_TREE_ITEM p__PUDF_TREE_ITEM__Root,
    IN PUDF_CONTROL_BLOCK p__PUDF_CONTROL_BLOCK
    );


/*

This function creates UDF tree from the allocated data buffers.


Parameters

p__PUDF_TREE_ITEM__UDFRoot - Pointer to UDF root node.

p__PUDF_TREE_ITEM__ISO9660UDFBridgeRootVideo - Pointer to UDF root node for VIDEO_TS directory.

p__PUDF_TREE_ITEM__ISO9660UDFBridgeRootAudio - Pointer to UDF root node for AUDIO_TS directory.

p__PUDF_CONTROL_BLOCK - Pointer to UDF control block.

p__PCHAR__ExceptionText - Pointer to exception text.

p__ULONG__ExceptionTextSizeInUCHARs - Exception text size in UCHARs.

p__PULONG__SystemError - Pointer to system error.

p__PCHAR__VolumeLabel - Pointer to volume label for UDF image.

p__PCHAR__PublisherPreparerName - Pointer to publisher and preparer name.

p__PCHAR__ApplicationName - Pointer to application name.

p__LONG__Year - Year of creation.

p__LONG__Month - Month of creation.

p__LONG__Day - Day of creation.

p__LONG__Hour - Hour of creation.

p__LONG__Minute - Minute of creation.

p__LONG__Second - Second of creation.

p__LONG__MilliSecond - Millisecond of creation.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. 


Remarks

Please check DVDVideoBuildImage and DVDVideoTrackAtOnceFromTree samples to find out how to use StarBurn_UDF_CreateEx() in the right way.


Example

This example allocates CdvdBurnerGrabber object, creates and destroys UDF tree and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UDF_TREE_ITEM l__UDF_TREE_ITEM__Directory[ 10 ];
UDF_CONTROL_BLOCK l__UDF_CONTROL_BLOCK;

unsigned char g__UCHAR__FileSystemHead[ ( UDF_HEAD_SIZE_IN_LOGICAL_BLOCKS * UDF_LOGICAL_BLOCK_SIZE_IN_UCHARS ) ];
unsigned char g__UCHAR__FileSystemTail[ ( UDF_TAIL_SIZE_IN_LOGICAL_BLOCKS * UDF_LOGICAL_BLOCK_SIZE_IN_UCHARS ) ];
unsigned char g__UCHAR__FileSystemStructures[ ( 1024 * UDF_LOGICAL_BLOCK_SIZE_IN_UCHARS ) ];

UDF_TREE_ITEM g__UDF_TREE_ITEM__File[ 200 ]; // File[ 0 ] is not used

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add nodes with StarBurn_UDF_FormatTreeItemAsXxx here

// Create UDF tree with StarBurn_UDF_CreateEx() here
l__EXCEPTION_NUMBER = 
StarBurn_UDF_CreateEx(
    &l__UDF_TREE_ITEM__Directory[ 1 ], // This is ROOT
    &l__UDF_TREE_ITEM__Directory[ 2 ], // This is VIDEO_TS and not ROOT, for VIDEO_TS listing
    &l__UDF_TREE_ITEM__Directory[ 3 ], // This is AUDIO_TS and not ROOT, for AUDIO_TS listing
    &l__UDF_CONTROL_BLOCK,
    ( CHAR * )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    "VolumeLabel",
	"PublisherName",
	"ApplicationName",
	2006,	// Year
	10,		// Month
	20,		// Day,
	12,		// Hour
	10,		// Minute
	0,		// Second
	50		// Millisecond
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with the UDF tree here (maybe burn to CdvdBurnerGrabber object)

// Clean up UDF stuff with StarBurn_UDF_CleanUp() here

// Destroy UDF tree from the root
StarBurn_UDF_Destroy(
	&l__UDF_TREE_ITEM__Directory[ 0 ],
	&l__UDF_CONTROL_BLOCK
	);

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_UDF_Destroy, StarBurn_UDF_CleanUp, StarBurn_UDF_FormatTreeItemAsDirectory, StarBurn_UDF_FormatTreeItemAsFile

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_UDF_CreateEx(
    IN PUDF_TREE_ITEM p__PUDF_TREE_ITEM__UDFRoot,
    IN PUDF_TREE_ITEM p__PUDF_TREE_ITEM__ISO9660UDFBridgeRootVideo,
    IN PUDF_TREE_ITEM p__PUDF_TREE_ITEM__ISO9660UDFBridgeRootAudio,
    IN PUDF_CONTROL_BLOCK p__PUDF_CONTROL_BLOCK,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN PCHAR p__PCHAR__VolumeLabel,
    IN PCHAR p__PCHAR__PublisherPreparerName,
    IN PCHAR p__PCHAR__ApplicationName,
	IN LONG p__LONG__Year,
	IN LONG p__LONG__Month,
	IN LONG p__LONG__Day,
	IN LONG p__LONG__Hour,
	IN LONG p__LONG__Minute,
	IN LONG p__LONG__Second,
	IN LONG p__LONG__MilliSecond
    );


/*

This function formats UDF tree item as file.


Parameters

p__PUDF_TREE_ITEM - Pointer to UDF tree item to format as file.

p__ULONG__GUID - Globally unique identifier.

p__PCHAR__Name - Pointer to name of the node to use in UDF volume.

p__PCHAR__FullPath - Pointer to file path on the disk.

p__PUDF_TREE_ITEM__Parent - Pointer to parent node.


Result

Execution status. NO_ERROR means everything is OK and Win32 system error is returned otherwise.


Remarks

Please check DVDVideoBuildImage and DVDVideoTrackAtOnceFromTree samples to find out how to use StarBurn_UDF_FormatTreeItemAsFile() in the right way.


Example

This example allocates CdvdBurnerGrabber object, creates and destroys UDF tree and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UDF_TREE_ITEM l__UDF_TREE_ITEM__Directory[ 10 ];
UDF_CONTROL_BLOCK l__UDF_CONTROL_BLOCK;
UDF_TREE_ITEM g__UDF_TREE_ITEM__File[ 200 ]; // File[ 0 ] is not used

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Format file node 1 as file
l__ULONG__SystemError =
StarBurn_UDF_FormatTreeItemAsFile(
    &g__UDF_TREE_ITEM__File[ 1 ],
    ( ++l__ULONG__GUID ),
    "video_ts.ifo",
    "c:\\VOB\\video_ts.ifo",
    &l__UDF_TREE_ITEM__Directory[ 2 ]
    );

// Handle error case here if l__ULONG__SystemError is not NO_ERROR...

// Create UDF tree with StarBurn_UDF_CreateEx() here
l__EXCEPTION_NUMBER = 
StarBurn_UDF_CreateEx(
    &l__UDF_TREE_ITEM__Directory[ 1 ], // This is ROOT
    &l__UDF_TREE_ITEM__Directory[ 2 ], // This is VIDEO_TS and not ROOT, for VIDEO_TS listing
    &l__UDF_TREE_ITEM__Directory[ 3 ], // This is AUDIO_TS and not ROOT, for AUDIO_TS listing
    &l__UDF_CONTROL_BLOCK,
    ( CHAR * )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    "VolumeLabel",
	"PublisherName",
	"ApplicationName",
	2006,	// Year
	10,		// Month
	20,		// Day,
	12,		// Hour
	10,		// Minute
	0,		// Second
	50		// Millisecond
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with the UDF tree here (maybe burn to CdvdBurnerGrabber object)

// Clean up UDF stuff with StarBurn_UDF_CleanUp() here

// Destroy UDF tree from the root
StarBurn_UDF_Destroy(
	&l__UDF_TREE_ITEM__Directory[ 0 ],
	&l__UDF_CONTROL_BLOCK
	);

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_UDF_Destroy, StarBurn_UDF_CleanUp, StarBurn_UDF_FormatTreeItemAsDirectory

*/

STARBURN_IMPEX_API
unsigned long
__stdcall
StarBurn_UDF_FormatTreeItemAsFile(
    PUDF_TREE_ITEM p__PUDF_TREE_ITEM,
    unsigned long p__ULONG__GUID,
    char *p__PCHAR__Name,
    char *p__PCHAR__FullPath,
    PUDF_TREE_ITEM p__PUDF_TREE_ITEM__Parent
    );


/*

This function formats UDF tree item as directory.


Parameters

p__PUDF_TREE_ITEM - Pointer to UDF tree item to format as file.

p__ULONG__GUID - Globally unique identifier.

p__PCHAR__Name - Pointer to name of the node to use in UDF volume.

p__PUDF_TREE_ITEM__Parent - Pointer to parent node.


Result

Nothing. This function cannot fail. 


Remarks

Please check DVDVideoBuildImage and DVDVideoTrackAtOnceFromTree samples to find out how to use StarBurn_UDF_FormatTreeItemAsDirectory() in the right way.


Example

This example allocates CdvdBurnerGrabber object, creates and destroys UDF tree and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UDF_TREE_ITEM l__UDF_TREE_ITEM__Directory[ 10 ];
UDF_CONTROL_BLOCK l__UDF_CONTROL_BLOCK;

unsigned char g__UCHAR__FileSystemHead[ ( UDF_HEAD_SIZE_IN_LOGICAL_BLOCKS * UDF_LOGICAL_BLOCK_SIZE_IN_UCHARS ) ];
unsigned char g__UCHAR__FileSystemTail[ ( UDF_TAIL_SIZE_IN_LOGICAL_BLOCKS * UDF_LOGICAL_BLOCK_SIZE_IN_UCHARS ) ];
unsigned char g__UCHAR__FileSystemStructures[ ( 1024 * UDF_LOGICAL_BLOCK_SIZE_IN_UCHARS ) ];

UDF_TREE_ITEM g__UDF_TREE_ITEM__File[ 200 ]; // File[ 0 ] is not used

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Format VIDEO_TS directory
StarBurn_UDF_FormatTreeItemAsDirectory(
	&l__UDF_TREE_ITEM__Directory[ 2 ],
    ( ++l__ULONG__GUID ),
    "VIDEO_TS",
    &l__UDF_TREE_ITEM__Directory[ 1 ]
    );

// Format file node 1 as file
l__ULONG__SystemError =
StarBurn_UDF_FormatTreeItemAsFile(
    &g__UDF_TREE_ITEM__File[ 1 ],
    ( ++l__ULONG__GUID ),
    "video_ts.ifo",
    "c:\\VOB\\video_ts.ifo",
    &l__UDF_TREE_ITEM__Directory[ 2 ]
    );

// Handle error case here if l__ULONG__SystemError is not NO_ERROR...

// Create UDF tree with StarBurn_UDF_CreateEx() here
l__EXCEPTION_NUMBER = 
StarBurn_UDF_CreateEx(
    ( PUCHAR )( &g__UCHAR__FileSystemHead ),
    sizeof( g__UCHAR__FileSystemHead ),
    ( PUCHAR )( &g__UCHAR__FileSystemTail ),
    sizeof( g__UCHAR__FileSystemTail ),
    ( PUCHAR )( &g__UCHAR__FileSystemStructures ),
    &l__UDF_TREE_ITEM__Directory[ 1 ], // This is ROOT
    &l__UDF_TREE_ITEM__Directory[ 2 ], // This is VIDEO_TS and not ROOT, for VIDEO_TS listing
    &l__UDF_TREE_ITEM__Directory[ 3 ], // This is AUDIO_TS and not ROOT, for AUDIO_TS listing
    &l__UDF_CONTROL_BLOCK,
    ( CHAR * )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    "VolumeLabel",
	"PublisherName",
	"ApplicationName",
	2006,	// Year
	10,		// Month
	20,		// Day,
	12,		// Hour
	10,		// Minute
	0,		// Second
	50		// Millisecond
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with the UDF tree here (maybe burn to CdvdBurnerGrabber object)

// Clean up UDF stuff with StarBurn_UDF_CleanUp() here

// Destroy UDF tree from the root
StarBurn_UDF_Destroy(
	&l__UDF_TREE_ITEM__Directory[ 0 ],
	&l__UDF_CONTROL_BLOCK
	);

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_UDF_Destroy, StarBurn_UDF_CleanUp, StarBurn_UDF_FormatTreeItemAsFile

*/

STARBURN_IMPEX_API
void
__stdcall
StarBurn_UDF_FormatTreeItemAsDirectory(
    PUDF_TREE_ITEM p__PUDF_TREE_ITEM,
    unsigned long p__ULONG__GUID,
    char *p__PCHAR__Name,
    PUDF_TREE_ITEM p__PUDF_TREE_ITEM__Parent
    );


/*

This function removes created UDF tree from the pointed UDF tree node sequentially. Processes file formatted UDF nodes and either closes file handles
or frees memory (non-cached vs. cached content).


Parameters

p__PUDF_TREE_ITEM - Pointer to allocated and formatted as file UDF tree root node.

p__ULONG__NumberOfTreeItems - Number of tree items to process.


Result

Nothing. This function cannot fail. 


Remarks

Please check DVDVideoBuildImage and DVDVideoTrackAtOnceFromTree samples to find out how to use StarBurn_UDF_CleanUp() in the right way.


Example

This example allocates CdvdBurnerGrabber object, creates and destroys UDF tree and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UDF_TREE_ITEM l__UDF_TREE_ITEM__Directory[ 10 ];
UDF_TREE_ITEM l__UDF_TREE_ITEM__File[ 10 ];
UDF_CONTROL_BLOCK l__UDF_CONTROL_BLOCK;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if ( l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add nodes with StarBurn_UDF_FormatTreeItemAsXxx here

// Create UDF tree with StarBurn_UDF_CreateEx() here

// Do something with the UDF tree here (maybe burn to CdvdBurnerGrabber object)

// Clean up UDF stuff 
StarBurn_UDF_CleanUp(
	&l__UDF_TREE_ITEN__File[ 0 ],
	10
	);

// Destroy UDF tree from the root
StarBurn_UDF_Destroy(
	&l__UDF_TREE_ITEM__Directory[ 0 ],
	&l__UDF_CONTROL_BLOCK
	);

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_UDF_CreateEx, StarBurn_UDF_Destroy, StarBurn_UDF_FormatTreeItemAsDirectory, StarBurn_UDF_FormatTreeItemAsFile

*/

STARBURN_IMPEX_API
void
__stdcall
StarBurn_UDF_CleanUp(
    PUDF_TREE_ITEM p__PUDF_TREE_ITEM,
    unsigned long p__ULONG__NumberOfTreeItems
    );


/*++

    Creates the UDF Tree Node

Arguments:

    Pointer to exception text,
    Exception text size in UCHARs,
    Pointer to system error,
    Pointer to root directory or individual file path and name to start from,
    Pointer to the new root directory or individual file name (to be stored in UDF image),
    Pointer to file tree node to which we'll add
	Pointer to pointer to the new created file tree node

Return Value:

    Exception number

--*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_UDF_Add(
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN PCHAR p__PCHAR__DirectoryOrFileAbsolutePathAndName,
    IN PCHAR p__PCHAR__DirectoryOrFileNewName,
    IN PVOID p__PVOID__UDF__Parent,
	OUT PVOID *p__PPVOID__UDF__NewChild
    );


/*++

    Destroys UDF Tree Node and all its kids

Arguments:

    Pointer to file tree node to which we'll destroy	

Return Value:

    Exception number

--*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_UDF_DestroyNodeAndKids(
    IN PVOID p__PVOID__UDF__Parent
    );


/*++

    Returns the object to current Tree Node

Arguments:

    Pointer to file tree node

Return Value:

    Pointer to UDF_TREE_ITEM object associated with passed node

--*/

STARBURN_IMPEX_API
PUDF_TREE_ITEM
__stdcall
StarBurn_UDF_GetNodeObject(
    IN PVOID p__PVOID__UDF__Parent
    );


//
// UDF undecorated code (begin)
//


//
// StarBurn_UDF_Create() function is obsolete. Use StarBurn_UDF_CreatEx() instead of it
//

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_UDF_Create(
    IN PUDF_TREE_ITEM p__PUDF_TREE_ITEM__UDFRoot,
    IN PUDF_TREE_ITEM p__PUDF_TREE_ITEM__ISO9660UDFBridgeRootVideo,
    IN PUDF_TREE_ITEM p__PUDF_TREE_ITEM__ISO9660UDFBridgeRootAudio,
    IN PUDF_CONTROL_BLOCK p__PUDF_CONTROL_BLOCK,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN PCHAR p__PCHAR__VolumeLabel
    );


//
// StarBurn_UDF_GetFirstChild function is not documented
//
STARBURN_IMPEX_API
PVOID
__stdcall
StarBurn_UDF_GetFirstChild(
	IN PVOID p__PVOID__UDF__Parent
	);

//
// StarBurn_UDF_GetNextSibling function is not documented
//
STARBURN_IMPEX_API
PVOID
__stdcall
StarBurn_UDF_GetNextSibling(
	IN PVOID p__PVOID__UDF__Parent
	);

//
// StarBurn_UDF_GetParent function is not documented
//
STARBURN_IMPEX_API
PVOID
__stdcall
StarBurn_UDF_GetParent(
	IN PVOID p__PVOID__UDF__Parent
	);



//
// UDF undecorated code (end)
//


/*

This function returns StarWave library version.


Parameters

p__PULONG__StarWaveVersion - Pointer to the variable to receive StarWave build version.


Result

Execution status. This call cannot fail unless wrong pointer is passed as input parameter.


Remarks

Actually StarWave version build number is synchronized with StarBurn build number. So there's no real use in calling this API
call any more.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_VersionGet API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_UncompressedFileSupportedIs,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress, StarBurn_StarWave_CompressedFileSupportedIs

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_VersionGet(
	OUT PULONG p__PULONG__StarWaveVersion
	);


/*

This function creates compressed file reader object from passed compressed audio file name.


Parameters

p__PPVOID__CompressedFileReaderObject - Pointer to pointer to compressed file reader object after it's creation.

p__PCHAR__CompressedFileName - Pointer to compressed file name to create compressed file reader object from.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_CompressedFileReaderObjectCreate API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet, StarBurn_StarWave_CompressedFileSupportedIs
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_CompressedFileReaderObjectCreate(
	OUT PVOID *p__PPVOID__CompressedFileReaderObject,
	IN PCHAR p__PCHAR__CompressedFileName
	);


/*

This function destroys compressed file reader object.


Parameters

p__PPVOID__CompressedFileReaderObject - Pointer to pointer to compressed file reader object to destroy.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_CompressedFileReaderObjectDestroy API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_VersionGet, StarBurn_StarWave_CompressedFileSupportedIs, StarBurn_StarWave_CompressedFileRecompress, 
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_CompressedFileReaderObjectDestroy(
	OUT PVOID *p__PPVOID__CompressedFileReaderObject
	);


/*

This function reads uncompressed payload data chunk from underlying compressed file reader object.


Parameters

p__PVOID__CompressedFileReaderObject - Pointer to compressed file reader object.

p__PVOID__ReadDataBuffer - Pointer to output buffer to handle just read uncompressed data.

p__ULONG__ReadSizeInUCHARs - Data chunk (uncompressed) to read size in UCHARs.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_CompressedFileReaderObjectRead API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileSupportedIs
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_CompressedFileReaderObjectRead(
	IN PVOID p__PVOID__CompressedFileReaderObject,
	OUT PVOID p__PVOID__ReadDataBuffer,
	IN ULONG p__ULONG__ReadSizeInUCHARs
	);


/*

This function seeks all of the internal object pointers to the very beginning of it so following read operations would start
from the very beginning instead of the currently set position.


Parameters

p__PVOID__CompressedFileReaderObject - Pointer to compressed file reader object.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_CompressedFileReaderObjectBeginSeek API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileSupportedIs, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek(
	IN PVOID p__PVOID__CompressedFileReaderObject
	);


/*

This function returns uncompressed payload size in UCHARs for underlying compressed file reader object.


Parameters

p__PVOID__CompressedFileReaderObject - Pointer to compressed file reader object.

p__PULONG__UncompressedSizeInUCHARs - Pointer to the variable to receive uncompressed payload size in UCHARs.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileSupportedIs
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet(
	IN PVOID p__PVOID__CompressedFileReaderObject,
	OUT PULONG p__PULONG__UncompressedSizeInUCHARs
	);


/*

This function uncompresses compressed file to either WAV or RAW PCM.


Parameters

p__PCHAR__SourceCompressedFileName - Pointer to source compressed file name.

p__PCHAR__DestinationUncompressedFileName - Pointer to destination uncompressed file name.

p__ULONG__WorkingBufferSizeInUCHARs - Working buffer size in UCHARs (recommended to have it equal to STARBURN_STARWAVE_IO_BUFFER_SIZE_IN_UCHARS).

p__BOOLEAN__IsWavHeaderRequired - Is WAV header required for destination file (WAV would be result) or not (RAW would be result).

p__PULONG__UncompressedSizeInUCHARs - Pointer to the variable to receive uncompressed payload size in UCHARs.

p__PSTARBURN_STARWAVE_CALLBACK - Pointer to callback function to process progress indication and I/O cancellation.

p__PVOID__Context - Pointer to the context value passed to callback function.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_CompressedFileUncompress API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileRecompress, StarBurn_StarWave_CompressedFileSupportedIs

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_CompressedFileUncompress(
	IN PCHAR p__PCHAR__SourceCompressedFileName,
	IN PCHAR p__PCHAR__DestinationUncompressedFileName,
	IN ULONG p__ULONG__WorkingBufferSizeInUCHARs,
	IN BOOLEAN p__BOOLEAN__IsWavHeaderRequired,
	OUT PULONG p__PULONG__UncompressedSizeInUCHARs,
	IN PSTARBURN_STARWAVE_CALLBACK p__PSTARBURN_STARWAVE_CALLBACK,
	IN PVOID p__PVOID__Context
	);


/*

This function compresses uncompressed file to new one with asked compression.


Parameters

p__PCHAR__SourceUncompressedFileName - Pointer to source uncompressed file name.

p__PCHAR__DestinationCompressedFileName - Pointer to destination compressed file name.

p__ULONG__WorkingBufferSizeInUCHARs - Working buffer size in UCHARs (recommended to have it equal to STARBURN_STARWAVE_IO_BUFFER_SIZE_IN_UCHARS).

p__PSTARBURN_STARWAVE_CALLBACK - Pointer to callback function to process progress indication and I/O cancellation.

p__PVOID__Context - Pointer to the context value passed to callback function.

p__STARBURN_STARWAVE_COMPRESSION - Compression template.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_UncompressedFileCompress API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_CompressedFileSupportedIs
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_UncompressedFileCompress(
	IN PCHAR p__PCHAR__SourceUncompressedFileName,
	IN PCHAR p__PCHAR__DestinationCompressedFileName,
	IN ULONG p__ULONG__WorkingBufferSizeInUCHARs,
	IN PSTARBURN_STARWAVE_CALLBACK p__PSTARBURN_STARWAVE_CALLBACK,
	IN PVOID p__PVOID__Context,
	IN STARBURN_STARWAVE_COMPRESSION p__STARBURN_STARWAVE_COMPRESSION
	);


/*

This function recompresse already compressed file to new one with another compression.


Parameters

p__PCHAR__SourceCompressedFileName - Pointer to source compressed file name.

p__PCHAR__DestinationRecompressedFileName - Pointer to destination compressed file name.

p__ULONG__WorkingBufferSizeInUCHARs - Working buffer size in UCHARs (recommended to have it equal to STARBURN_STARWAVE_IO_BUFFER_SIZE_IN_UCHARS).

p__PULONG__UncompressedSizeInUCHARs - Pointer to the variable to receive uncompressed source stream size in UCHARs.

p__PSTARBURN_STARWAVE_CALLBACK - Pointer to callback function to process progress indication and I/O cancellation.

p__PVOID__Context - Pointer to the context value passed to callback function.

p__STARBURN_STARWAVE_COMPRESSION - Compression template.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_CompressedFileRecompress API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileSupportedIs

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_CompressedFileRecompress(
	IN PCHAR p__PCHAR__SourceCompressedFileName,
	IN PCHAR p__PCHAR__DestinationRecompressedFileName,
	IN ULONG p__ULONG__WorkingBufferSizeInUCHARs,
	OUT PULONG p__PULONG__UncompressedSizeInUCHARs,
	IN PSTARBURN_STARWAVE_CALLBACK p__PSTARBURN_STARWAVE_CALLBACK,
	IN PVOID p__PVOID__Context,
	IN STARBURN_STARWAVE_COMPRESSION p__STARBURN_STARWAVE_COMPRESSION
	);


/*

This function creates compressed file writer object.


Parameters

p__PPVOID__CompressedFileWriterObject - Pointer to pointer to compressed file writer object.

p__PCHAR__CompressedFileName - Pointer to compressed file name.

p__STARBURN_STARWAVE_COMPRESSION - Compression template.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_CompressedFileWriterObjectCreate API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectWrite, StarBurn_StarWave_CompressedFileSupportedIs,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress, 

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_CompressedFileWriterObjectCreate(
	OUT PVOID *p__PPVOID__CompressedFileWriterObject,
	IN PCHAR p__PCHAR__CompressedFileName,
	IN STARBURN_STARWAVE_COMPRESSION p__STARBURN_STARWAVE_COMPRESSION
	);


/*

This function destroys compressed file writer object.


Parameters

p__PPVOID__CompressedFileWriterObject - Pointer to pointer to compressed file writer object.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_CompressedFileWriterObjectDestroy API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_UncompressedFileCompress, StarBurn_StarWave_CompressedFileRecompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileSupportedIs

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_CompressedFileWriterObjectDestroy(
	OUT PVOID *p__PPVOID__CompressedFileWriterObject
	);


/*

This function writes uncompressed data chunk to compressed file writer object.


Parameters

p__PVOID__CompressedFileWriterObject - Pointer to compressed file writer object.

p__PVOID__WriterDataBuffer - Pointer to data buffer to write.

p__ULONG__WriteSizeInUCHARs - Data buffer to write size in UCHARs.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_CompressedFileWriterObjectWrite API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileSupportedIs,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress 

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_CompressedFileWriterObjectWrite(
	OUT PVOID p__PVOID__CompressedFileWriterObject,
	IN PVOID p__PVOID__WriterDataBuffer,
	IN ULONG p__ULONG__WriterSizeInUCHARs
	);


/*

This function checks is file name actually points to supported compressed audio file.


Parameters

p__PCHAR__CompressedFileName - Pointer to compressed file name.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_CompressedFileSupportedIs API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_CompressedFileSupportedIs(
	IN PCHAR p__PCHAR__CompressedFileName
	);


/*

This function checks is file name actually points to supported uncompressed audio file.


Parameters

p__PCHAR__UncompressedFileName - Pointer to uncompressed file name.


Result

Execution status. 


Remarks

None.


Example

See AudioCompressor StarBurn sample application as an example how to use StarBurn_StarWave_UncompressedFileSupportedIs API call.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress, StarBurn_StarWave_CompressedFileSupportedIs

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_StarWave_UncompressedFileSupportedIs(
	IN PCHAR p__PCHAR__UncompressedFileName
	);


/*

This function compress audio file from WAV (44100Hz, 16, stereo) format to MP3 and OGG format.


Parameters

p__PCHAR_SrcFileName - Pointer to source file full path (WAV file)

p__PCHAR_DstFileName - Pointer to destination file full path (MP3 or OGG file)

p_PSTARBURN_STARWAVE2_INIT_PARAMS - Pointer to initialization structure (See STARBURN_STARWAVE2_INIT_PARAMS)

p__PSTARBURN_STARWAVE_CALLBACK - Pointer to callback function.

p__PVOID__CallbackContext - Pointer to callback context.

p__PCHAR__ExceptionText - Error text buffer size in UCHARs.

p__ULONG__ExceptionTextSizeInUCHARs - Error text buffer size in UCHARs.

p__PULONG__SystemError - Pointer to system error value (error code WIN32/Vorbis/Nlame). For detailed information see p__PCHAR__ExceptionText.


Result

Return true if finish successful, otherwise false. If function return false see  error code (p__PULONG__SystemError), and error detailed information (p__PCHAR__ExceptionText).


Remarks

None.


Example

See AudioCompressor StarBurn sample applications as an example how to use 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarWave2_EncodeMP3OGGFromWAV(
	IN PCHAR p__PCHAR_SrcFileName,
	IN PCHAR p__PCHAR_DstFileName,
	IN PSTARBURN_STARWAVE2_INIT_PARAMS p_PSTARBURN_STARWAVE2_INIT_PARAMS,
	IN PSTARBURN_STARWAVE_CALLBACK p__PSTARBURN_STARWAVE_CALLBACK,
	IN PVOID p__PVOID__CallbackContext,
	OUT PCHAR p__PCHAR__ExceptionText,
	IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
	OUT PULONG p__PULONG__SystemError
);

/*

This function creates DVD-Video file system object from passed pointer to VIDEO_TS directory with DVD corresponding files.


Parameters

p__PPVOID__DVDVideo - Pointer to pointer to resulting DVD-Video file system object.

p__PCHAR__VideoTsDirectory - Pointer to VIDEO_TS directory with corresponding DVD files.

p__BOOLEAN__IsPatchingEnabled - Should be set to TRUE to allow StarBurn core to modify IFO/BUP files and FALSE otherwise.

p__PCHAR__ExceptionText - Pointer to buffer to receive formatted error message in case of exception.

p__ULONG__ExceptionTextSizeInUCHARs - Error text buffer size in UCHARs.

p__PULONG__SystemError - Pointer to system error value (if function would return EN_SYSTEM_CALL_FAILED).

p__PCHAR__VolumeLabel - Pointer to volume label resulting DVD-Video compilation would receive.

p__PCHAR__PublisherPreparerName - Pointer to publisher and preparer name resulting DVD-Video compilation would receive.

p__PCHAR__ApplicationName - Pointer to application name resulting DVD-Video compilation would receive.

p__LONG__Year - Year which would be set as DVD-Video compilation creation year.

p__LONG__Month - Month which would be set as DVD-Video compilation creation month.

p__LONG__Day - Day which would be set as DVD-Video compilation creation day.

p__LONG__Hour - Hour which would be set as DVD-Video compilation creation hour.

p__LONG__Minute - Minute which would be set as DVD-Video compilation creation minute.

p__LONG__Second - Second which would be set as DVD-Video compilation creation second.

p__LONG__MilliSecond - Millisecond which would be set as DVD-Video compilation creation millisecond.


Result

Execution status. 


Remarks

None.


Example

See DVDVideoTrackAtOnceFromFileEx and DVDVideoBuildImageEx StarBurn sample applications as an example how to use 
StarBurn_DVDVideo_Create API call and all of the companion DVD-Video sub-API calls.


See Also

StarBurn_DVDVideo_Destroy, StarBurn_DVDVideo_SeekToBegin, StarBurn_DVDVideo_Read, StarBurn_DVDVideo_GetSizeInUCHARs, 
StarBurn_DVDVideo_GetTreePointer 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_DVDVideo_Create(
	OUT PVOID *p__PPVOID__DVDVideo,
	IN PCHAR p__PCHAR__VideoTsDirectory,
	IN BOOLEAN p__BOOLEAN__IsPatchingEnabled,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN PCHAR p__PCHAR__VolumeLabel,
    IN PCHAR p__PCHAR__PublisherPreparerName,
    IN PCHAR p__PCHAR__ApplicationName,
	IN LONG p__LONG__Year,
	IN LONG p__LONG__Month,
	IN LONG p__LONG__Day,
	IN LONG p__LONG__Hour,
	IN LONG p__LONG__Minute,
	IN LONG p__LONG__Second,
	IN LONG p__LONG__MilliSecond
    );


/*

This function destroys DVD-Video file system object created with StarBurn_DVDVideo_Create API call.


Parameters

p__PVOID__DVDVideo - Pointer to source DVD-Video file system object we need to deallocate.


Result

Nothing.


Remarks

None.


Example

See DVDVideoTrackAtOnceFromFileEx and DVDVideoBuildImageEx StarBurn sample applications as an example how to use 
StarBurn_DVDVideo_Destroy API call and all of the companion DVD-Video sub-API calls.


See Also

StarBurn_DVDVideo_Create, StarBurn_DVDVideo_SeekToBegin, StarBurn_DVDVideo_Read, StarBurn_DVDVideo_GetSizeInUCHARs, 
StarBurn_DVDVideo_GetTreePointer 

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_DVDVideo_Destroy(
	IN PVOID p__PVOID__DVDVideo
    );


/*

This function moves DVD-Video file system object (created with StarBurn_DVDVideo_Create API call) current read position to the 
very beginning.


Parameters

p__PVOID__DVDVideo - Pointer to source DVD-Video file system object we need to rewind.

p__PCHAR__ExceptionText - Pointer to buffer to receive formatted error message in case of exception.

p__ULONG__ExceptionTextSizeInUCHARs - Error text buffer size in UCHARs.

p__PULONG__SystemError - Pointer to system error value (if function would return EN_SYSTEM_CALL_FAILED).


Result

Execution status.


Remarks

None.


Example

See DVDVideoTrackAtOnceFromFileEx and DVDVideoBuildImageEx StarBurn sample applications as an example how to use 
StarBurn_DVDVideo_SeekToBegin API call and all of the companion DVD-Video sub-API calls.


See Also

StarBurn_DVDVideo_Create, StarBurn_DVDVideo_Destroy, StarBurn_DVDVideo_Read, StarBurn_DVDVideo_GetSizeInUCHARs, 
StarBurn_DVDVideo_GetTreePointer

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_DVDVideo_SeekToBegin(
    IN PVOID p__PVOID__DVDVideo,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError
    );


/*

This function reads requested number of UCHARs from DVD-Video file system object (created with StarBurn_DVDVideo_Create API 
call) from it's current read position. 


Parameters

p__PVOID__DVDVideo - Pointer to source DVD-Video file system object we need to read data from.

p__PCHAR__ExceptionText - Pointer to buffer to receive formatted error message in case of exception.

p__ULONG__ExceptionTextSizeInUCHARs - Error text buffer size in UCHARs.

p__PULONG__SystemError - Pointer to system error value (if function would return EN_SYSTEM_CALL_FAILED).

p__LARGE_INTEGER__IoTransferSizeInUCHARs - Number of UCHARs we want to read from file system object.

p__PUCHAR__DataBuffer - Pointer to output data buffer we want file system object data to be placed after read.


Result

Execution status.


Remarks

None.


Example

See DVDVideoTrackAtOnceFromFileEx and DVDVideoBuildImageEx StarBurn sample applications as an example how to use 
StarBurn_DVDVideo_Read API call and all of the companion DVD-Video sub-API calls.


See Also

StarBurn_DVDVideo_Create, StarBurn_DVDVideo_Destroy, StarBurn_DVDVideo_SeekToBegin, StarBurn_DVDVideo_GetSizeInUCHARs, 
StarBurn_DVDVideo_GetTreePointer

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_DVDVideo_Read(
    IN PVOID p__PVOID__DVDVideo,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
	IN LARGE_INTEGER p__LARGE_INTEGER__IoTransferSizeInUCHARs,
	OUT PUCHAR p__PUCHAR__DataBuffer
    );


/*

This function gets file system content size in UCHARs from DVD-Video file system object created with StarBurn_DVDVideo_Create 
API call. 


Parameters

p__PVOID__DVDVideo - Pointer to source DVD-Video file system object we need to get payload size in UCHARs.

p__PLARGE_INTEGER__SizeInUCHARs - Pointer to the variable to receive file system payload size in UCHARs.


Result

Execution status.


Remarks

None.


Example

See DVDVideoTrackAtOnceFromFileEx and DVDVideoBuildImageEx StarBurn sample applications as an example how to use 
StarBurn_DVDVideo_GetSizeInUCHARs API call and all of the companion DVD-Video sub-API calls.


See Also

StarBurn_DVDVideo_Create, StarBurn_DVDVideo_Destroy, StarBurn_DVDVideo_SeekToBegin, StarBurn_DVDVideo_Read, 
StarBurn_DVDVideo_GetTreePointer

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_DVDVideo_GetSizeInUCHARs(
    IN PVOID p__PVOID__DVDVideo,
	OUT PLARGE_INTEGER p__PLARGE_INTEGER__SizeInUCHARs
    );


/*

This function returns pointer to ISO9660 file tree object embedded to DVD-Video file system object created with 
StarBurn_DVDVideo_Create API call. 


Parameters

p__PVOID__DVDVideo - Pointer to source DVD-Video file system object we need to get ISO9660 file tree object pointer.

p__PPVOID__ISO9660JolietFileTree - Pointer to the variable to receive ISO9660 file tree object pointer.


Result

Execution status.


Remarks

None.


Example

See DVDVideoTrackAtOnceFromFileEx and DVDVideoBuildImageEx StarBurn sample applications as an example how to use 
StarBurn_DVDVideo_GetTreePointer API call and all of the companion DVD-Video sub-API calls.


See Also

StarBurn_DVDVideo_Create, StarBurn_DVDVideo_Destroy, StarBurn_DVDVideo_SeekToBegin, StarBurn_DVDVideo_Read, 
StarBurn_DVDVideo_GetSizeInUCHARs

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_DVDVideo_GetTreePointer(
    IN PVOID p__PVOID__DVDVideo,
	OUT PVOID *p__PPVOID__ISO9660JolietFileTree
    );


/*

This function returns ISO9660 or Joliet file tree file size in UCHARs. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PVOID__ISO9660JolietFileTreeNode - Pointer to the ISO9660 or Joliet file tree node object that is either result of previous
tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and StarBurn_ISO9660JolietFileTree_GetNextKid() 
or the result of call to StarBurn_ISO9660JolietFileTree_GetRoot(). The function is valid only for nodes that correspond to files.

p__PLARGE_INTEGER__FileSizeInUCHARs - Pointer to the variable to receive ISO9660 or Joliet file tree node file size in UCHARs.


Returns

Execution status.


Remarks

This call is identical to the StarBurn_ISO9660JolietFileTree_GetNodePowerInUCHARs(...) except it has a bit different semantics.


Example

This example allocates Joliet file tree, get root node, gets file size in UCHARs and destroys it (tree) after it's not needed 
any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__RootNode;
LARGE_INTEGER l__LARGE_INTEGER__FileSizeInUCHARs;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( StarBurn_Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Add directories or files with the help of the StarBurn_ISO9660JolietFileTree_Add here...

// Get root node here
l__PVOID__RootNode = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct response
if ( l__PVOID__RootNode == NULL )
{
// Handle error here...
}

// Get file size in UCHARs here
l__EXCEPTION_NUMBER =
StarBurn_ISO9660JolietFileTree_GetFileSizeInUCHARs( 
    l__PVOID__FileTree,
    l__PVOID__RootNode,
    &l__LARGE_INTEGER__FileSizeInUCHARs
    );

// Do something with Joliet file tree root node here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, 
StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_Destroy, 
StarBurn_ISO9660JolietFileTree_GetNodePowerInUCHARs

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_GetFileSizeInUCHARs(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode,
    OUT PLARGE_INTEGER p__PLARGE_INTEGER__FileSizeInUCHARs
    );


/*

This function returns ISO9660 or Joliet file tree node SYSTEMTIME. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to ISO9660 or Joliet file tree current node belongs to.

p__PVOID__ISO9660JolietFileTreeNode - Pointer to ISO9660 or Joliet file tree to get SYSTEMTIME for.

p__PSYSTEMTIME - Pointer to the output SYSTEMTIME for ISO9660 or Joliet file tree node.


Result

Execution status.


Remarks

None.


Example

There are no examples for StarBurn_ISO9660JolietFileTree_GetNodeSystemTime(...) API call.


See Also

StarBurn_ISO9660JolietFileTree_GetNodeISO9660DateTime, StarBurn_ISO9660JolietFileTree_Create, 
StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_ISO9660JolietFileTree_GetNextKid, 
StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_Destroy, StarBurn_ISO9660JolietFileTree_GetNodePowerInUCHARs

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_GetNodeSystemTime(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode,
	OUT PSYSTEMTIME p__PSYSTEMTIME
    );


/*

This function returns ISO9660 or Joliet file tree node ISO9660 time stamp (date and time). 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to ISO9660 or Joliet file tree current node belongs to.

p__PVOID__ISO9660JolietFileTreeNode - Pointer to ISO9660 or Joliet file tree to get ISO9660 time stamp for.

p__PISO9660_DATE_TIME - Pointer to ISO9660 time stamp (date and time).


Result

Execution status.


Remarks

None.


Example

There are no examples for StarBurn_ISO9660JolietFileTree_GetNodeISO9660DateTime(...) API call.


See Also

StarBurn_ISO9660JolietFileTree_GetNodeSystemTime, StarBurn_ISO9660JolietFileTree_Create, 
StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_ISO9660JolietFileTree_GetNextKid, 
StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_Destroy, StarBurn_ISO9660JolietFileTree_GetNodePowerInUCHARs

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_GetNodeISO9660DateTime(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode,
	OUT PISO9660_DATE_TIME p__PISO9660_DATE_TIME
    );

/*

This function returns ISO9660 or Joliet file tree node starting LBA after the image was built. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object that toolkit allocated during call to 
StarBurn_ISO9660JolietFileTree_Create().

p__PVOID__ISO9660JolietFileTreeNode - Pointer to the ISO9660 or Joliet file tree node object that is either result of previous
tree node kids enumeration with StarBurn_ISO9660JolietFileTree_GetFirstKid() and StarBurn_ISO9660JolietFileTree_GetNextKid() 
or the result of call to StarBurn_ISO9660JolietFileTree_GetRoot().

p__PLONG__StartingLBA - Pointer to the variable to receive ISO9660 or Joliet file tree node starting LBA.


Returns

Execution status.


Remarks

None.


Example

There are no examples for StarBurn_ISO9660JolietFileTree_GetNodeISO9660DateTime(...) API call.

See Also

StarBurn_ISO9660JolietFileTree_GetNodeSystemTime, StarBurn_ISO9660JolietFileTree_Create, 
StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_ISO9660JolietFileTree_GetNextKid, 
StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_Destroy, StarBurn_ISO9660JolietFileTree_GetNodePowerInUCHARs

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_GetNodeStartingLBA(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode,
    OUT PLONG p__PLONG__StartingLBA
    );

/*

This function returns is currently passed file supported as source audio file. 


Parameters

p__PCHAR__AudioFilePathAndName - Pointer to full path and name of "suspected" audio file.


Result

Execution status.


Remarks

This call is nearly obsolete and supported only for legacy software. It's *STRONGLY* recommended to use StarWave API calls
to deal with compressed and uncompressed audio streams (StarBurn_StarWave_UncompressedFileSupportedIs and of course it's
companion StarBurn_StarWave_CompressedFileSupportedIs).


Example

Please see TrackAtOnceFromFile and SessionAtOnceFromFile samples to see how to use StarBurn_IsAudioFileSupported API call and
AudioCompressor sample to see how to use StarWave API calls.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_UncompressedFileSupportedIs,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileSupportedIs

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_IsAudioFileSupported(
	IN PCHAR p__PCHAR__AudioFilePathAndName
	);


/*

This function returns audio stream size in UCHARs for passed supported as source audio file. 


Parameters

p__PCHAR__AudioFilePathAndName - Pointer to full path and name of supported audio file.

p__PLONG__StreamSizeInUCHARs - Pointer to the variable to receive audio stream size in UCHARs.

p__PULONG__SystemError - Pointer to the variable to receive system error (if function would return EN_SYSTEM_CALL_FAILED).


Result

Execution status.


Remarks

This call is nearly obsolete and supported only for legacy software. It's *STRONGLY* recommended to use StarWave API calls
to deal with compressed and uncompressed audio streams.


Example

Please see TrackAtOnceFromFile and SessionAtOnceFromFile samples to see how to use StarBurn_IsAudioFileSupported API call and
AudioCompressor sample to see how to use StarWave API calls.


See Also

StarBurn_StarWave_CompressedFileReaderObjectCreate, StarBurn_StarWave_CompressedFileReaderObjectUncompressedSizeGet,
StarBurn_StarWave_CompressedFileReaderObjectBeginSeek, StarBurn_StarWave_CompressedFileReaderObjectRead, 
StarBurn_StarWave_CompressedFileReaderObjectDestroy, StarBurn_StarWave_UncompressedFileSupportedIs,
StarBurn_StarWave_CompressedFileWriterObjectCreate, StarBurn_StarWave_CompressedFileWriterObjectWrite,
StarBurn_StarWave_CompressedFileWriterObjectDestroy, StarBurn_StarWave_UncompressedFileCompress, 
StarBurn_StarWave_CompressedFileUncompress, StarBurn_StarWave_CompressedFileRecompress, StarBurn_StarWave_VersionGet,
StarBurn_StarWave_CompressedFileSupportedIs

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_GetAudioFileStreamSizeInUCHARs(
	IN PCHAR p__PCHAR__AudioFilePathAndName,
	OUT PLONG p__PLONG__StreamSizeInUCHARs,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function returns full path to ISO9660 or Joliet file tree node. 


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to ISO9660 or Joliet file tree current node belongs to.

p__PVOID__ISO9660JolietFileTreeNode - Pointer to ISO9660 or Joliet file tree node to get ISO9660 time stamp for.

p__PCHAR__FullName - Pointer to the buffer to receive full path to ISO9660 or Joliet file tree node.


Result

Kid type of ISO9660 or Joliet file tree node (where this node was taken from). This call cannot fail.


Remarks

None.


Example

There are no examples for StarBurn_ISO9660JolietFileTree_GetFullPath(...) API call.


See Also

StarBurn_ISO9660JolietFileTree_GetNodeSystemTime, StarBurn_ISO9660JolietFileTree_Create, 
StarBurn_ISO9660JolietFileTree_Add, StarBurn_ISO9660JolietFileTree_GetRoot, StarBurn_ISO9660JolietFileTree_GetNextKid, 
StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_Destroy, StarBurn_ISO9660JolietFileTree_GetNodePowerInUCHARs

*/

STARBURN_IMPEX_API
ISO9660_KIDTYPE
__stdcall
StarBurn_ISO9660JolietFileTree_GetFullPath(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    IN PVOID p__PVOID__ISO9660JolietFileTreeNode,
	OUT PCHAR p__PCHAR__FullName
    );


/*

This function reads ATIP information from the media currently inserted into CD/DVD/Blu-Ray/HD-DVD burner device object created with the
call to the one of the StarBurn_CdvdBurnerGrabber_Create or StarBurn_CdvdBurnerGrabber_CreateEx API calls.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PUCHAR__ATIP - Pointer to the buffer to receive ATIP information.

p__ULONG__ATIPSizeInUCHARs - ATIP information buffer size in UCHARs.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the DiscAtOnceFromTree sample that will demonstrate how ATIP information could be read from the media with the
help of the StarBurn_CdvdBurnerGrabber_ReadATIP API call. 


Example

This example allocates CdvdBurnerGrabber object, reads ATIP information and destroys the device object after it's not needed 
any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UCHAR l__UCHAR__ATIP[ 4096 ];

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get ATIP information from device
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_ReadATIP(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	&l__UCHAR__ATIP,
	sizeof( l__UCHAR__ATIP )
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_ReadATIP(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	OUT PUCHAR p__PUCHAR__ATIP,
	IN ULONG p__ULONG__ATIPSizeInUCHARs
    );


/*

This function converts MSF (minute:second:frame) address into the LBA (logical block address). 


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to CD/DVD/Blu-Ray/HD-DVD burner/grabber object.

p__UCHAR__M - Minute of MSF address.

p__UCHAR__S - Second of MSF address.

p__UCHAR__F - Frame of MSF address.

p__BOOLEAN__IsForcePositive - TRUE if resulting LBA should be forced to be positive or FALSE if it could be negative.


Result

LBA (logical block address).


Remarks

No remarks.


Example

Please see DiscAtOnceFromFile sample to see how to use StarBurn_MSFToLBA API call should be used.


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_CreateEx

*/

STARBURN_IMPEX_API
LONG
__stdcall
StarBurn_CdvdBurnerGrabber_MSFToLBA(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
	IN UCHAR p__UCHAR__M,
	IN UCHAR p__UCHAR__S,
	IN UCHAR p__UCHAR__F,
	IN BOOLEAN p__BOOLEAN__IsForcePositive
    );


/*

This function returns is DVD+R DL (Dual Layer) so-called "compatible mode" (when layer would be switched exactly at 1/2 of the
data payload recorded on the disc - required for DVD-Video compilations to work properly) enabled (TRUE) or disabled (FALSE).


Parameters

Nothing.


Result

Is DVD+R DL compatible mode enabled (TRUE) or disabled (FALSE).


Remarks

"Compatible mode" should be always enabled for DVD-Video compilations (or resulting disc would not be playable on standalone
DVD players) and should be always disabled for generic data discs (or quite a lot of disc capacity would be simply wasted).


Example

There are no examples for StarBurn_GetDVDPLUSRDLCompatibleMode(...) API call.


See Also

StarBurn_SetDVDPLUSRDLCompatibleMode

*/

STARBURN_IMPEX_API
BOOLEAN
__stdcall
StarBurn_GetDVDPLUSRDLCompatibleMode(
    IN VOID
    );


/*

This function sets DVD+R DL (Dual Layer) so-called "compatible mode" (when layer would be switched exactly at 1/2 of the
data payload recorded on the disc - required for DVD-Video compilations to work properly) to enabled (TRUE) or disabled (FALSE).


Parameters

Should DVD+R DL compatible mode be enabled (TRUE) or disabled (FALSE).


Result

Nothing.


Remarks

"Compatible mode" should be always enabled for DVD-Video compilations (or resulting disc would not be playable on standalone
DVD players) and should be always disabled for generic data discs (or quite a lot of disc capacity would be simply wasted).


Example

There are no examples for StarBurn_SetDVDPLUSRDLCompatibleMode(...) API call.


See Also

StarBurn_GetDVDPLUSRDLCompatibleMode

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_SetDVDPLUSRDLCompatibleMode(
    IN BOOLEAN p__BOOLEAN__NewDVDPLUSRDLCompatibleMode
    );


/*

This function returns is so-called "safe grabbing" (when StarBurn would mix read commands with checking for device to become
ready - required to workaround broken ATAPI-to-USB bridges) enabled (TRUE) or disabled (FALSE).


Parameters

Nothing.


Result

Is "safe grabbing" mode enabled (TRUE) or disabled (FALSE).


Remarks

There's no need to play with this parameter unless you really have ATAPI device in external USB enclosure and it hangs under heavy I/O load.


Example

There are no examples for StarBurn_GetIsSafeGrabbingEnabled(...) API call.


See Also

StarBurn_SetIsSafeGrabbingEnabled

*/

STARBURN_IMPEX_API
BOOLEAN
__stdcall
StarBurn_GetIsSafeGrabbingEnabled(
    IN VOID
    );


/*

This function sets so-called "safe grabbing" (when StarBurn would mix read commands with checking for device to become
ready - required to workaround broken ATAPI-to-USB bridges) to enabled (TRUE) or disabled (FALSE).


Parameters

Is "safe grabbing" mode enabled (TRUE) or disabled (FALSE).


Result

Nothing.


Remarks

There's no need to play with this parameter unless you really have ATAPI device in external USB enclosure and it hangs under heavy I/O load.


Example

There are no examples for StarBurn_SetIsSafeGrabbingEnabled(...) API call.


See Also

StarBurn_GetIsSafeGrabbingEnabled

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_SetIsSafeGrabbingEnabled(
    IN BOOLEAN p__BOOLEAN__NewIsSafeGrabbingEnabled
    );


/*

This function returns is collision detection disabled (TRUE) or enabled (FALSE). If collision detection is enabled -
every new file added to ISO9660 or Joliet file tree would be checked to have unique name. If such a file already exist - 
special callback (collision detection one) would be called so user would be able to either replace or rename new or old file.
However if collision detection is disabled - no comparison and no actions would be performed. File would be just added to
the destination file system image AS IS, having it's original name.


Parameters

Nothing.


Result

Is collision detection mode disabled (TRUE) or enabled (FALSE).


Remarks

If new image is created from the content stored on the hard disk - there's no way for file names to be the same. So file
system image creation process could be speed up quite a lot by turning collision detection OFF (especially if there are a lot
of files inside each directory). In other cases it's not recommended to play with this option.


Example

Please see BuildImage sample to find out how collision detection could be disabled and enabled during file system image creation.


See Also

StarBurn_SetIsCollisionDetectionDisabled

*/

STARBURN_IMPEX_API
BOOLEAN
__stdcall
StarBurn_GetIsCollisionDetectionDisabled(
    IN VOID
    );


/*

This function sets collision detection to disabled (TRUE) or enabled (FALSE). If collision detection is enabled -
every new file added to ISO9660 or Joliet file tree would be checked to have unique name. If such a file already exist - 
special callback (collision detection one) would be called so user would be able to either replace or rename new or old file.
However if collision detection is disabled - no comparison and no actions would be performed. File would be just added to
the destination file system image AS IS, having it's original name.


Parameters

Is collision detection mode disabled (TRUE) or enabled (FALSE).


Result

Nothing.


Remarks

If new image is created from the content stored on the hard disk - there's no way for file names to be the same. So file
system image creation process could be speed up quite a lot by turning collision detection OFF (especially if there are a lot
of files inside each directory). In other cases it's not recommended to play with this option.


Example

Please see BuildImage sample to find out how collision detection could be disabled and enabled during file system image creation.


See Also

StarBurn_GetIsCollisionDetectionDisabled

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_SetIsCollisionDetectionDisabled(
    IN BOOLEAN p__BOOLEAN__NewIsCollisionDetectionDisabled
    );


/*

This function returns is DVD padding mode (when at least 1GB of the data would be recorded to DVD media - required for 
DVD-Video compilations to work properly on standalone DVD players) enabled (TRUE) or disabled (FALSE).


Parameters

Nothing.


Result

Is DVD padding mode enabled (TRUE) or disabled (FALSE).


Remarks

"Padding mode" should be always enabled for DVD-Video compilations (or resulting disc would not be playable on standalone
DVD players) and should be always disabled for generic data discs (or quite a lot of disc capacity would be simply wasted).


Example

There are no examples for StarBurn_GetDVDPadding(...) API call.


See Also

StarBurn_SetDVDPadding

*/

STARBURN_IMPEX_API
BOOLEAN
__stdcall
StarBurn_GetDVDPadding(
    IN VOID
    );


/*

This function sets DVD padding mode (when at least 1GB of the data would be recorded to DVD media - required for 
DVD-Video compilations to work properly on standalone DVD players) to enabled (TRUE) or disabled (FALSE).


Parameters

Is DVD padding mode enabled (TRUE) or disabled (FALSE).


Result

Nothing.


Remarks

"Padding mode" should be always enabled for DVD-Video compilations (or resulting disc would not be playable on standalone
DVD players) and should be always disabled for generic data discs (or quite a lot of disc capacity would be simply wasted).


Example

There are no examples for StarBurn_SetDVDPadding(...) API call.


See Also

StarBurn_GetDVDPadding

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_SetDVDPadding(
    IN BOOLEAN p__BOOLEAN__NewDVDPadding
    );


/*

This function returns is so-called "eject after fail" (if during burning process error would happen - should StarBurn eject
disc or not) enabled (TRUE) or disabled (FALSE).


Parameters

Nothing.


Result

Is "eject after fail" mode enabled (TRUE) or disabled (FALSE).


Remarks

It's a good idea to keep everything AS IS, however if StarBurn is used with automatic loaders or whatever sometimes it's
required to keep manual control over eject process.


Example

There are no examples for StarBurn_GetEjectAfterFail(...) API call.


See Also

StarBurn_SetEjectAfterFail

*/

STARBURN_IMPEX_API
BOOLEAN
__stdcall
StarBurn_GetEjectAfterFail(
    IN VOID
    );


/*

This function sets so-called "eject after fail" (if during burning process error would happen - should StarBurn eject
disc or not) to enabled (TRUE) or disabled (FALSE).


Parameters

Is "eject after fail" mode enabled (TRUE) or disabled (FALSE).


Result

Nothing.


Remarks

It's a good idea to keep everything AS IS, however if StarBurn is used with automatic loaders or whatever sometimes it's
required to keep manual control over eject process.


Example

There are no examples for StarBurn_SetEjectAfterFail(...) API call.


See Also

StarBurn_GetEjectAfterFail

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_SetEjectAfterFail(
    IN BOOLEAN p__BOOLEAN__NewEjectAfterFail
    );


/*

This function returns is so-called "fast read TOC" (TOC information is not 100% accurate - to get EXACT track length StarBurn
trys to read beginning and end of the track to find sub-channel index switch indicating EXACT track beginning or EXACT track end) 
mode enabled (TRUE) or disabled (FALSE).


Parameters

Nothing.


Result

Is "fast read TOC" mode enabled (TRUE) or disabled (FALSE).


Remarks

It's a good idea to keep everything AS IS, however if StarBurn takes a lot of time to analyze the disc (it can happen when
drive hardware error correction cannot be disabled and reading pre-gap and post-gap of the track is DOG SLOW) "fast read TOC"
could be switched ON.


Example

Please see GrabTrack sample no how to use StarBurn_GetFastReadTOC(...) API call.


See Also

StarBurn_SetFastReadTOC

*/

STARBURN_IMPEX_API
BOOLEAN
__stdcall
StarBurn_GetFastReadTOC(
    IN VOID
    );


/*

This function sets so-called "fast read TOC" (TOC information is not 100% accurate - to get EXACT track length StarBurn
try to read beginning and end of the track to find sub-channel index switch indicating EXACT track beginning or EXACT track end) 
mode to enabled (TRUE) or disabled (FALSE).


Parameters

Is "fast read TOC" mode enabled (TRUE) or disabled (FALSE).


Result

Nothing.


Remarks

It's a good idea to keep everything AS IS, however if StarBurn takes a lot of time to analyze the disc (it can happen when
drive hardware error correction cannot be disabled and reading pre-gap and post-gap of the track is DOG SLOW) "fast read TOC"
could be switched ON.


Example

Please see GrabTrack sample no how to use StarBurn_SetFastReadTOC(...) API call.


See Also

StarBurn_GetFastReadTOC

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_SetFastReadTOC(
    IN BOOLEAN p__BOOLEAN__NewFastReadTOC
    );


/*

This function returns buffer underrun timeout in milliseconds. It's amount of time StarBurn core would wait before resubmitting
each command to the drive if burning was faster then reading and StarBurn had exhausted software cache it uses for buffering. 
Modern hardware has BUP (Buffer Underrun Protection) and would perfectly survive in such a condition and keep burning disc 
still usable.


Parameters

Nothing.


Result

Buffer underrun timeout in milliseconds.


Remarks

Having large timeout would allow StarBurn to grab more information into software cache, at the same time having timeout small and
disc burning speed MUCH faster then reading speed from the source media (say slow hard disk or network) would produce a lot
of BUP errors, start-stop cycles and resulting recorded disc quality would be very low. In general it's a good idea not to touch
buffer underrun timeout value at all and keep everything AS IS. It's value for "hardcore tuning".


Example

There are no samples for StarBurn_GetBufferUnderrunTimeOutInMs(...) API call.


See Also

StarBurn_SetBufferUnderrunTimeOutInMs

*/

STARBURN_IMPEX_API
LONG
__stdcall
StarBurn_GetBufferUnderrunTimeOutInMs(
    IN VOID
    );


/*

This function sets buffer underrun timeout in milliseconds. It's amount of time StarBurn core would wait before resubmitting
each command to the drive if burning was faster then reading and StarBurn had exhausted software cache it uses for buffering. 
Modern hardware has BUP (Buffer Underrun Protection) and would perfectly survive in such a condition and keep burning disc 
still usable.


Parameters

Buffer underrun timeout in milliseconds.


Result

Nothing.


Remarks

Having large timeout would allow StarBurn to grab more information into software cache, at the same time having timeout small and
disc burning speed MUCH faster then reading speed from the source media (say slow hard disk or network) would produce a lot
of BUP errors, start-stop cycles and resulting recorded disc quality would be very low. In general it's a good idea not to touch
buffer underrun timeout value at all and keep everything AS IS. It's value for "hardcore tuning".


Example

There are no samples for StarBurn_SetBufferUnderrunTimeOutInMs(...) API call.


See Also

StarBurn_GetBufferUnderrunTimeOutInMs

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_SetBufferUnderrunTimeOutInMs(
	IN LONG p__LONG__NewBufferUnderrunTimeOutInMs
    );


/*

This function gets DVD region mask from DVD media inserted to CD/DVD/Blu-Ray/HD-DVD burner device object created with the call to the one of 
the StarBurn_CdvdBurnerGrabber_Create or StarBurn_CdvdBurnerGrabber_CreateEx API calls.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PUCHAR__DVDRegionMask - Pointer to the variable to receive DVD region mask.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the GrabDisc sample that will demonstrate how DVD region mask could be get from DVD media with the help of the 
StarBurn_CdvdBurnerGrabber_GetDVDRegionMask API call. 


Example

This example allocates CdvdBurnerGrabber object, gets DVD region and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UCHAR l__UCHAR__DVDRegionMask;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get DVD region mask from DVD media inserted to device
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetDVDRegionMask(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	&l__UCHAR__DVDRegionMask
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_CreateEx, StarBurn_CdvdBurnerGrabber_GetRPC,
PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetDVDRegionMask(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    OUT PUCHAR p__PUCHAR__DVDRegionMask
    );


/*

This function gets RPC (region play code) and some additional DVD region management information from "DVD part" of the CD/DVD/Blu-Ray/HD-DVD 
burner device object created with the call to the one of the StarBurn_CdvdBurnerGrabber_Create or 
StarBurn_CdvdBurnerGrabber_CreateEx API calls.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PUCHAR__TypeCode - Pointer to the variable to receive type code.

p__PUCHAR__NumberOfVendorResetsAvailable - Pointer to the variable to receive number of vendor-controlled region code resets.

p__PUCHAR__NumberOfUserControlledChangesAvailable - Pointer to the variable to receive number of user-controlled region code changes.

p__PUCHAR__RegionMask - Pointer to the variable to receive "hardware" region code mask.

p__PUCHAR__RPCScheme - Pointer to the variable to receive RPC management scheme.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see GrabDisc sample that will demonstrate how DVD region management information could be get from DVD device with the 
help of the StarBurn_CdvdBurnerGrabber_GetRPC API call. 


Example

This example allocates CdvdBurnerGrabber object, gets DVD region management information from CD/DVD/Blu-Ray/HD-DVD device object and destroys 
it after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UCHAR l__UCHAR__TypeCode;
UCHAR l__UCHAR__NumberOfVendorResetsAvailable;
UCHAR l__UCHAR__NumberOfUserControlledChangesAvailable;
UCHAR l__UCHAR__RegionMask;
UCHAR l__UCHAR__RPCScheme;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get DVD region management information from DVD device
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetRPC(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	&l__UCHAR__TypeCode,
	&l__UCHAR__NumberOfVendorResetsAvailable,
	&l__UCHAR__NumberOfUserControlledChangesAvailable,
	&l__UCHAR__RegionMask,
	&l__UCHAR__RPCScheme
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_CreateEx, 
PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_GetDVDRegionMask

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetRPC(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	OUT PUCHAR p__PUCHAR__TypeCode,
	OUT PUCHAR p__PUCHAR__NumberOfVendorResetsAvailable,
	OUT PUCHAR p__PUCHAR__NumberOfUserControlledChangesAvailable,
	OUT PUCHAR p__PUCHAR__RegionMask,
	OUT PUCHAR p__PUCHAR__RPCScheme
    );


/*

This function adds the tree created from the directory to already created ISO9660 or Joliet file tree from passed directory. 
Later this tree can be used to build  "virtual" ISO96600 or Joliet file system image. Resulting "virtual" image can be either 
stored in the file on the disk or be burn directly to the CD/DVD/Blu-Ray/HD-DVD media w/o any other intermediate operations.


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCHAR__RootDirectoryAbsolutePathAndName - Pointer to directory name to build the ISO9660 or Joliet image from. This parameters
can be NULL (but in this case p__PCHAR__RootDirectoryNewName cannot!!!) if virtual (non-present on the disk) directory must
be added to the image.

p__PCHAR__RootDirectoryNewName - Pointer to directory name to be stored in the ISO9660 or Joliet image as root name,
NULL to include default name from the previous parameter.

p__FILE_TIME - File time that will be included in file system image (See FILE_TIME).

p__PFILETIME - Pointer to FILETIME structure created node would have.

p__PPVOID__ISO9660JolietFileTreeNode__Parent - Pointer to pointer to the file tree node we'll use as parent. This is the result
of either tree walking with StarBurn_ISO9660JolietFileTree_GetFirstKid() or StarBurn_ISO9660JolietFileTree_GetNextKid() or the 
result of call to StarBurn_ISO9660JolietFileTree_GetRoot(). NULL can be passed instead of the result of 
StarBurn_ISO9660JolietFileTree_GetRoot().

p__PPVOID__ISO9660JolietFileTreeNode__NewChild - Pointer to pointer to the new created file tree node. 


Returns

Execution status. EN_SUCCESS if the tree was reallocated successfully, E_MEMORY_ALLOCATION_FAILED if there is not enough memory 
to reallocate the tree. If the exception number will be EN_SYSTEM_CALL_FAILED, variable that SystemError points to will be 
filled with system error. If something other then EN_SUCCESS will be returned buffer that ExceptionText will point to will be 
filled with formatted exception message.


Remarks

Please see the BuildImage sample that will demonstrate how progress indication can be build and what parameters in general are 
passed into the callback function during the operations with file tree object and how extended variant of adding call could
be used to solve the issue of passing the node with required creation times.


Example

This example allocates Joliet file tree with required time for root node and destroys the tree after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__Root;
SYSTEMTIME l__SYSTEMTIME;
FILETIME l__FILETIME;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get root here
l__PVOID__Root = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct reply
if ( l__PVOID__Root == NULL )
{
// Handle error here, keep in mind that root CAN be NULL if nothing was added to tree before...
}

// Format system time here

ZeroMemory(
	&l__SYSTEMTIME,
	sizeof( l__SYSTEMTIME )
	);

l__SYSTEMTIME.wYear = 1991;
	
l__SYSTEMTIME.wMonth = 3; 
	
l__SYSTEMTIME.wDayOfWeek = 1;  

l__SYSTEMTIME.wDay = 1;  

l__SYSTEMTIME.wHour = 2;  
	
l__SYSTEMTIME.wMinute = 30;  

l__SYSTEMTIME.wSecond = 40;  

l__SYSTEMTIME.wMilliseconds = 10;

// Covert system time to file time
SystemTimeToFileTime(
	&l__SYSTEMTIME,
	&l__FILETIME
	);

// Try to add all from the root directory of the drive D: to already created Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_AddEx(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    "D:\\",
    NULL,
    FILE_TIME_LAST_WRITE,
	&l__FILETIME,
    &l__PVOID__Root,
    &l__PVOID__NewNode
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Perform actions with Joliet tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, PCALLBACK, EXCEPTION_NUMBER, FILE_TREE, FILE_TIME, StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_GetRoot,
StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_Add

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_AddEx(
    OUT PVOID p__PVOID__ISO9660JolietFileTree,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN PCHAR p__PCHAR__RootDirectoryAbsolutePathAndName,
    IN PCHAR p__PCHAR__RootDirectoryNewName,
    IN FILE_TIME p__FILE_TIME,
	IN PFILETIME p__PFILETIME,
    IN PVOID *p__PPVOID__ISO9660JolietFileTreeNode__Parent,
    OUT PVOID *p__PPVOID__ISO9660JolietFileTreeNode__NewChild
    );


/*

This function verifies recorded file system tree on CD/DVD/Blu-Ray/HD-DVD burner device object used for this particular tree recording. This 
information can be used to be sure recorded disc is readable and really contains recorded information.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PVOID__FileTree - Pointer to file system tree used for recording.

p__LONG__StartingLBA - LBA (logical block address) used to start recording from.

p__PLONG__FailedLBA - Pointer to the variable to contain failed LBA (number of sector failed verification process).

p__ULONG__ReportDelayInLBs - Number of logical blocks verified before progress callback would be called.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and DiscAtOnceFromTree samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and how StarBurn_CdvdBurnerGrabber_VerifyTree can be used for verification of the 
recorded content. Also it's a good idea to use extended variant of this call StarBurn_CdvdBurnerGrabber_VerifyTreeEx when 
there's need to know how many retries for single failed logical block could be allowed.


Example

This example allocates CdvdBurnerGrabber object, burns file tree, verifies it and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
PVOID l__PVOID__FileTree;
LONG l__LONG__FailedLBA;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Create and burn ISO9660 or Joliet file tree here

// Try to verify file tree
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_VerifyTree(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	l__PVOID__FileTree,
	0, // Assume we've started to burn from LBA 0
	&l__LONG__FailedLBA,
	1000 // Call progress callback after every 1000 logical blocks processed
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_VerifyTreeEx, StarBurn_CdvdBurnerGrabber_VerifyFile

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_VerifyTree(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PVOID p__PVOID__FileTree,
	IN LONG p__LONG__StartingLBA,
	OUT PLONG p__PLONG__FailedLBA,
    IN ULONG p__ULONG__ReportDelayInLBs
    );


/*

This function verifies recorded file system tree on CD/DVD/Blu-Ray/HD-DVD burner device object used for this particular tree recording. This 
information can be used to be sure recorded disc is readable and really contains recorded information.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PVOID__FileTree - Pointer to file system tree used for recording.

p__LONG__StartingLBA - LBA (logical block address) used to start recording from.

p__PLONG__FailedLBA - Pointer to the variable to contain failed LBA (number of sector failed verification process).

p__ULONG__ReportDelayInLBs - Number of logical blocks verified before progress callback would be called.

p__LONG__NumberOfRetries - Number of read retries allowed to do on logical block failed to be readen from optical media.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and DiscAtOnceFromTree samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and how StarBurn_CdvdBurnerGrabber_VerifyTree can be used for verification of the 
recorded content (extended variant of the call is basically the same except it allows to control number of read retries). Also 
it's a good idea to use simplified variant of this call StarBurn_CdvdBurnerGrabber_VerifyTree when there's no need to know how 
many retries for single failed logical block could be allowed.


Example

This example allocates CdvdBurnerGrabber object, burns file tree, verifies it and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
PVOID l__PVOID__FileTree;
LONG l__LONG__FailedLBA;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Create and burn ISO9660 or Joliet file tree here

// Try to verify file tree
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_VerifyTreeEx(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	l__PVOID__FileTree,
	0, // Assume we've started to burn from LBA 0
	&l__LONG__FailedLBA,
	1000 // Call progress callback after every 1000 logical blocks processed,
	10 // Allow up to 10 attempts to read failed logical block
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_VerifyTree, StarBurn_CdvdBurnerGrabber_VerifyFile

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_VerifyTreeEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PVOID p__PVOID__FileTree,
	IN LONG p__LONG__StartingLBA,
	OUT PLONG p__PLONG__FailedLBA,
    IN ULONG p__ULONG__ReportDelayInLBs,
	IN LONG p__LONG__NumberOfRetries
    );


/*

This function verifies recorded file system image on CD/DVD/Blu-Ray/HD-DVD burner device object used for this particular image recording (or
maybe other image). This information can be used to be sure recorded disc is readable and really contains recorded information.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PCHAR__ImageFileName - Pointer to image file name we'll open and read from to compare the data with recorded disc.

p__LONG__StartingLBA - LBA (logical block address) used to start recording from.

p__PLONG__FailedLBA - Pointer to the variable to contain failed LBA (number of sector failed verification process).

p__ULONG__ReportDelayInLBs - Number of logical blocks verified before progress callback would be called.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromFile and VerifyFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and how StarBurn_CdvdBurnerGrabber_VerifyFile can be used for verification of the 
recorded content. 


Example

This example allocates CdvdBurnerGrabber object, burns image "IMAGE.ISO", verifies it and destroys the device object after 
it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
LONG l__LONG__FailedLBA;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Burn prepared file system image "IMAGE.ISO" here

// Try to verify file image
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_VerifyFile(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	"IMAGE.ISO",
	0, // Assume we've started to burn from LBA 0
	&l__LONG__FailedLBA,
	1000 // Call progress callback after every 1000 logical blocks processed
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_VerifyTreeEx, StarBurn_CdvdBurnerGrabber_VerifyTree

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_VerifyFile(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN PCHAR p__PCHAR__ImageFileName,
	IN LONG p__LONG__StartingLBA,
	OUT PLONG p__PLONG__FailedLBA,
    IN ULONG p__ULONG__ReportDelayInLBs
    );


/*

This function resets media state inside CD/DVD/Blu-Ray/HD-DVD burner device object. This actions allow to update disc content w/o need to
eject the disc. Could be used for multiple burnings w/o disc eject or manual disc data verification.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn on the CD/DVD/Blu-Ray/HD-DVD media. Adding call to StarBurn_CdvdBurnerGrabber_StopPlayScan and some of the manual media
read commands would allow faster (maybe better) recorded image verifications then built-in into the library.


Example

This example allocates CdvdBurnerGrabber object, burns something and does manual verification and destroys the device object 
after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Burn image here...

// Try to update device state
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_StopPlayScan(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Manually verify recorded image here...

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_StopPlayScan(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION
    );


/*

This function records ISO9660 or Joliet file system image or audio stream located in a pipe with current write speed on 
CD/DVD/Blu-Ray/HD-DVD burner device in Track-At-Once mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__HANDLE - Handle to ISO9660 or Joliet file system image or sound file located in a pipe.

p__LARGE_INTEGER__SizeInUCHARs - Pipe contents size in UCHARs.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE is next session is allowed on this media, FALSE if next session 
will not be allowed on this media.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).

p__BOOLEAN__IsAudio - Is this audio stream (TRUE) or data stream (FALSE).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromPipe API call as it's simplified variant of extended call allowing to burn data compilations only.


Example

This example allocates CdvdBurnerGrabber object, records the ISO9660 or Joliet file system image to the CD/DVD/Blu-Ray/HD-DVD media and 
destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
HANDLE l__HANDLE__Pipe = INVALID_HANDLE_VALUE;
LARGE_INTEGER l__LARGE_INTEGER__SizeInUCHARs;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare file system image or file and keep in pipe

// Try to record the ISO9660 or Joliet file system image in Track-At-Once mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipeEx(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    l__HANDLE__Pipe,
    l__LARGE_INTEGER__SizeInUCHARs,
    FALSE,
    FALSE,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS,
	FALSE // We burn data compilation
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipeEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN HANDLE p__HANDLE,
    IN LARGE_INTEGER p__LARGE_INTEGER__SizeInUCHARs,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds,
	IN BOOLEAN p__BOOLEAN__IsAudio
    );


/*

This function records ISO9660 or Joliet file system image or audio stream located in a memory with current write speed on 
CD/DVD/Blu-Ray/HD-DVD burner device in Track-At-Once mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PVOID__MemoryRegion - Pointer to memory region containing data.

p__LARGE_INTEGER__MemoryRegionSizeInUCHARs - Memory region size in UCHARs.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE is next session is allowed on this media, FALSE if next session 
will not be allowed on this media.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).

p__BOOLEAN__IsAudio - Is this audio stream (TRUE) or data stream (FALSE).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromPipe and TrackAtOnceFromPipeEx API calls to find out how to deal with content generated on-the-fly
and not statically stored in the memory.


Example

This example allocates CdvdBurnerGrabber object, reads ISO9660 or Joliet file system image to the memory, records it to the 
CD/DVD/Blu-Ray/HD-DVD media and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
PUCHAR l__PUCHAR__MemoryRegion;
LARGE_INTEGER l__LARGE_INTEGER__SizeInUCHARs;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare file system image or file and keep in memory. Pointer would be
// stored in l__UCHAR__MemoryRegion and memory region size would be stored in
// l__LARGE_INTEGER__SizeInUCHARs variable

// Try to record the ISO9660 or Joliet file system image in Track-At-Once mode
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromMemory(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PVOID )( l__PUCHAR__MemoryRegion ),
    l__LARGE_INTEGER__SizeInUCHARs,
    FALSE,
    FALSE,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS,
	FALSE // We burn data compilation
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipeEx,
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromMemoryEx  

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromMemory(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN OUT PVOID p__PVOID__MemoryRegion,
    IN LARGE_INTEGER p__LARGE_INTEGER__MemoryRegionSizeInUCHARs,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds,
	IN BOOLEAN p__BOOLEAN__IsAudio
    );


/*

This function records ISO9660 or Joliet file system image or audio stream located in a memory with current write speed on 
CD/DVD/Blu-Ray/HD-DVD burner device in Track-At-Once mode. If audio content is recorded this API call can change default 
Track-At-Once track-to-track pause length from 150 logical blocks (2 seconds) to any passed one.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PVOID__MemoryRegion - Pointer to memory region containing data.

p__LARGE_INTEGER__MemoryRegionSizeInUCHARs - Memory region size in UCHARs.

p__BOOLEAN__IsXA - BOOLEAN set to TRUE if this is CDROM XA, FALSE if this is ordinary CDROM/CDDA.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__BOOLEAN__IsNextSessionAllowed - BOOLEAN set to TRUE is next session is allowed on this media, FALSE if next session 
will not be allowed on this media.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).

p__BOOLEAN__IsAudio - Is this audio stream (TRUE) or data stream (FALSE).

p__USHORT__AudioPauseLengthInLBs - Audio pause length in logical blocks.

p__BOOLEAN__IsAudioPauseChange - Is audio pause change.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromPipe and TrackAtOnceFromPipeEx API calls to find out how to deal with content generated on-the-fly
and not statically stored in the memory.


Example

This example allocates CdvdBurnerGrabber object, reads audio track content to the memory, records it to the CD recordable media and 
destroys the device object after it's not needed any more. Also it sets track-to-track pause to zero.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber = NULL;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError = ERROR_SUCCESS;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
PUCHAR l__PUCHAR__MemoryRegion = NULL;
LARGE_INTEGER l__LARGE_INTEGER__SizeInUCHARs;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Prepare audio track and store it to the memory. Pointer would be
// stored in l__UCHAR__MemoryRegion and memory region size would be stored in
// l__LARGE_INTEGER__SizeInUCHARs variable

// Try to record the audio track in Track-At-Once mode and set zero-sized track-to-track pause
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromMemoryEx(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PVOID )( l__PUCHAR__MemoryRegion ),
    l__LARGE_INTEGER__SizeInUCHARs,
    FALSE,
    FALSE,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS,
	TRUE,	// We burn audio compilation
	0,		// Track-to-track pause length of ZERO
	TRUE	// Yes, please alter default pause length
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFile, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipeEx,
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromMemory  

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromMemoryEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN OUT PVOID p__PVOID__MemoryRegion,
    IN LARGE_INTEGER p__LARGE_INTEGER__MemoryRegionSizeInUCHARs,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds,
	IN BOOLEAN p__BOOLEAN__IsAudio,
	IN USHORT p__USHORT__AudioPauseLengthInLBs,
	IN BOOLEAN p__BOOLEAN__IsAudioPauseChange
    );


/*

This function creates CD/DVD/Blu-Ray/HD-DVD burner device object using SPTI (SCSI Pass Through Interface) transport. This object will 
be used later to perform CD/DVD/Blu-Ray/HD-DVD related actions.


Parameters

p__PPVOID__CdvdBurnerGrabber - Pointer to pointer to the object that toolkit will set to the CdvdBurnerGrabber object it 
will allocate.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PCALLBACK - Callback that will be called to indicate progress of various actions.

p__PVOID__Context - Context value that will be passed to callback function.

p__PCHAR__DeviceName - Pointer to device symbolic link name we'll use.

p__LONG__CacheSizeInMBs - Cache size to use during I/O operations, 0 is a special value that tells the toolkit to allocate 
default cache size.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please take a look at FindDeviceEx sample to find out how StarBurn_CdvdBurnerGrabber_CreateEx could be used to create 
CD/DVD/Blu-Ray/HD-DVD burner object. Please note that StarBurn_CdvdBurnerGrabber_CreateEx would create SPTI device thus would 
work only under Windows NT/2000/XP/2003. If you need Windows 95/98/Me compatibility please use StarBurn_CdvdBurnerGrabber_Create 
legacy call as it's for ASPI transport (ASPI is natively supported under Windows 95/98/Me and we provide own ASPI-to-SPTI wrapper 
for StarBurn).


Example

This example allocates CdvdBurnerGrabber object and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber using name "D:" with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_CreateEx(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
	"D:",
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_CreateExEx, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_CreateEx(
    OUT PVOID *p__PPVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCALLBACK p__PCALLBACK,
    IN PVOID p__PVOID__Context,
	IN PCHAR p__PCHAR__DeviceName,
    IN LONG p__LONG__CacheSizeInMBs
    );


/*

This function creates CD/DVD/Blu-Ray/HD-DVD burner device object using SPTD (SCSI Pass Through Direct) transport. This object will 
be used later to perform CD/DVD/Blu-Ray/HD-DVD related actions.


Parameters

p__PPVOID__CdvdBurnerGrabber - Pointer to pointer to the object that toolkit will set to the CdvdBurnerGrabber object it 
will allocate.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PCALLBACK - Callback that will be called to indicate progress of various actions.

p__PVOID__Context - Context value that will be passed to callback function.

p__PWCHAR__DeviceName - Pointer to device symbolic link name we'll use.

p__BOOLEAN__IsExclusiveAccess - Is device open with exclusive access

p__LONG__CacheSizeInMBs - Cache size to use during I/O operations, 0 is a special value that tells the toolkit to allocate 
default cache size.


Result

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please take a look at FindDeviceExEx sample to find out how StarBurn_CdvdBurnerGrabber_CreateExEx could be used to create 
CD/DVD/Blu-Ray/HD-DVD burner object. Please note that StarBurn_CdvdBurnerGrabber_CreateExEx would create SPTD device thus would 
work only under Windows NT/2000/XP/2003. If you need Windows 95/98/Me compatibility please use StarBurn_CdvdBurnerGrabber_Create 
legacy call as it's for ASPI transport (ASPI is natively supported under Windows 95/98/Me and we provide own ASPI-to-SPTI wrapper 
for StarBurn). ATTENTION! SPTD applications must be digitally signed. That's why only dynamic linking with the StarBurn.DLL is
possible if SPTD must be used (unless you'll directly license SPTD layer from Duplex Secure and will get signer for your EXE from
them).


Example

This example allocates CdvdBurnerGrabber object and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber using name "CdRom0" with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_CreateExEx(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
	L"CdRom0",
	TRUE,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_CreateEx, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_CreateExEx(
    OUT PVOID *p__PPVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCALLBACK p__PCALLBACK,
    IN PVOID p__PVOID__Context,
	IN PWCHAR p__PWCHAR__DeviceName,
	IN BOOLEAN p__BOOLEAN__IsExclusiveAccess,
    IN LONG p__LONG__CacheSizeInMBs
    );


/*

This function records VCD/MPEG1 image located in a file on the hard disk with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in
selected write mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__WRITE_MODE - Write mode to use.

p__PCHAR__MPEG1ImagePathAndFileName - Pointer to VCD/MPEG1 image file located in a file and stored on the hard disk.

p__PCHAR__TemplateImagePathAndFileName - Pointer to template file name StarBurn would record as first data track.

p__PCHAR__AlbumIdentifier - Pointer to album identifier.

p__USHORT__NumberOfVolumesInAlbum - Number of volumes in album.

p__USHORT__AlbumSetSequenceNumber - Album set sequence number.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the VideoCDEx sample that will demonstrate how VCD/MPEG1 image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and with the help of 
StarBurn_CdvdBurnerGrabber_VideoCDEx with currently set write speed and currently set optimum power calibration. This sample
is for legacy call, StarBurn_CdvdBurnerGrabber_VideoCDExEx is basically the same API call except it allows to pass user-defined
data track StarBurn would record to VCD as first track (MPEG1 file is second track on VCD).


Example

This example allocates CdvdBurnerGrabber object, records the VCD/MPEG1 image to the CD/DVD/Blu-Ray/HD-DVD media and destroys the device object 
after it's not needed any more. Custom user file name is passed to have own data track on resulting VCD.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to record the VCD/MPEG1 image (in Session-At-Once mode)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_VideoCDExEx(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    WRITE_MODE_SESSION_AT_ONCE,
    "C:\\MOVIE.MPEG1",	// Second MPEG1 track
	"C:\\DATA.ISO",		// First DATA track
    "Album",
    0x0001,
    0x0001,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_SuperVideoCD, StarBurn_CdvdBurnerGrabber_VideoCD, 
StarBurn_CdvdBurnerGrabber_SuperVideoCDEx, StarBurn_CdvdBurnerGrabber_SuperVideoCDExEx, StarBurn_CdvdBurnerGrabber_VideoCDEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_VideoCDExEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCHAR p__PCHAR__MPEG1ImagePathAndFileName,
	IN PCHAR p__PCHAR__TemplateImagePathAndFileName,
    IN PCHAR p__PCHAR__AlbumIdentifier,
    IN USHORT p__USHORT__NumberOfVolumesInAlbum,
    IN USHORT p__USHORT__AlbumSetSequenceNumber,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function records SVCD/MPEG2 image located in a file on the hard disk with current write speed on CD/DVD/Blu-Ray/HD-DVD burner device in
selected write mode.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__WRITE_MODE - Write mode to use.

p__PCHAR__MPEG2ImagePathAndFileName - Pointer to SVCD/MPEG2 image file located in a file and stored on the hard disk.

p__PCHAR__TemplateImagePathAndFileName - Pointer to template file name StarBurn would record as first data track.

p__PCHAR__AlbumIdentifier - Pointer to album identifier.

p__USHORT__NumberOfVolumesInAlbum - Number of volumes in album.

p__USHORT__AlbumSetSequenceNumber - Album set sequence number.

p__BOOLEAN__IsTestWrite - BOOLEAN set to TRUE if this is test write, FALSE if this is a real write.

p__ULONG__WriteReportDelayInSeconds - Write report delay in seconds (time between 2 WRITE_PACKET callbacks).

p__ULONG__BufferStatusReportDelayInSeconds - Buffer status report delay in seconds (time between 2 BUFFER_STATUS callbacks).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the SuperVideoCDEx sample that will demonstrate how SVCD/MPEG2 image can be burn on the CD/DVD/Blu-Ray/HD-DVD media and with the 
help of StarBurn_CdvdBurnerGrabber_SuperVideoCDEx with currently set write speed and currently set optimum power calibration. 
This sample is for legacy call, StarBurn_CdvdBurnerGrabber_SuperVideoCDExEx is basically the same API call except it allows 
to pass user-defined data track StarBurn would record to SVCD as first track (MPEG2 file is second track on VCD).


Example

This example allocates CdvdBurnerGrabber object, records the SVCD/MPEG2 image to the CD/DVD/Blu-Ray/HD-DVD media and destroys the device object 
after it's not needed any more. Custom user file name is passed to have own data track on resulting SVCD.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to record the SVCD/MPEG2 image (in Session-At-Once mode)
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_SuperVideoCDEx(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    WRITE_MODE_SESSION_AT_ONCE,
    "C:\\MOVIE.MPEG2",	// Second MPEG2 track
	"C:\\DATA.ISO",		// First DATA track
    "Album",
    0x0001,
    0x0001,
    FALSE,
    WRITE_REPORT_DELAY_IN_SECONDS,
    BUFFER_STATUS_REPORT_DELAY_IN_SECONDS
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_SendOPC, 
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_TrackAtOnceFromPipe, PCALLBACK, EXCEPTION_NUMBER, 
CDB_FAILURE_INFORMATION, StarBurn_CdvdBurnerGrabber_SuperVideoCD, StarBurn_CdvdBurnerGrabber_VideoCD, 
StarBurn_CdvdBurnerGrabber_VideoCDExEx, StarBurn_CdvdBurnerGrabber_SuperVideoCDEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_SuperVideoCDExEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PCHAR p__PCHAR__MPEG2ImagePathAndFileName,
	IN PCHAR p__PCHAR__TemplatePathAndFileName,
    IN PCHAR p__PCHAR__AlbumIdentifier,
    IN USHORT p__USHORT__NumberOfVolumesInAlbum,
    IN USHORT p__USHORT__AlbumSetSequenceNumber,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


/*

This function gets last recorded track from CD/DVD/Blu-Ray/HD-DVD media currently inserted to CD/DVD/Blu-Ray/HD-DVD burner device object. Such a track number
could be used for already recorded session import.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PUCHAR__LastTrack - Pointer to the variable to receive last track number.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see TrackAtOnceFromTreeWithImport sample that will demonstrate how ISO9660 or Joliet file system image can be burn on 
the CD/DVD/Blu-Ray/HD-DVD media and how StarBurn_CdvdBurnerGrabber_GetLastTrack can be used to get last recorded track number.


Example

This example allocates CdvdBurnerGrabber object, gets last recorded track number and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UCHAR l__UCHAR__LastRecordedTrackNumber;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get last recorded track number
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetLastTrack(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	&l__UCHAR__LastRecordedTrackNumber
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_ImportTrack

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetLastTrack(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	OUT PUCHAR p__PUCHAR__LastTrack
    );


/*

This function gets number of system descriptors in system structures stream. This value is used for updating head of
the image when creating signle track session import code.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PUCHAR__SystemStructures - Pointer to system structures pre-read into memory buffer.

p__LONG__SystemStructuresSizeInLBs - System structures size in logical blocks.


Returns

Number of system descriptors. This code cannot fail.


Remarks

Please see BuildImageWithImportFromFile sample that will demonstrate how ISO9660 or Joliet file system image can be imported
from hard disk ISO disk image and how StarBurn_CdvdBurnerGrabber_GetNumberOfSystemDescriptors(...) can be used to get number of
system descriptors when updating system image head.


Example

This example allocates CdvdBurnerGrabber object, gets number of system descriptors and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber = NULL;
LONG l__LONG__NumberOfSystemDescriptors = 0;
PUCHAR l__PUCHAR__SystemStructures = 0;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Allocate enough memory for system structures in l__PUCHAR__SystemStructures here...

// Read system structures from the optical disc to l__PUCHAR__SystemStructures buffer here...

// Try to get number of system descriptors
l__LONG__NumberOfSystemDescriptors =
StarBurn_CdvdBurnerGrabber_GetNumberOfSystemDescriptors(
    l__PVOID__CdvdBurnerGrabber,
	l__PUCHAR__SystemStructures,
	SYSTEM_STRUCTURES_SIZE_IN_LOGICAL_BLOCKS
    );

// Do something with l__LONG__NumberOfSystemDescriptors here...
    
// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create

*/

STARBURN_IMPEX_API
LONG
__stdcall
StarBurn_CdvdBurnerGrabber_GetNumberOfSystemDescriptors(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
	IN PUCHAR p__PUCHAR__SystemStructures,
	IN LONG p__LONG__SystemStructuresSizeInLBs
	);


/*

This function executes custom CDB (Command Descriptor Block) on CD/DVD/Blu-Ray/HD-DVD burner device object. This could be used to deal with
the propriatry hardware or execute some special code StarBurn does not support out-of-box.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PUCHAR__CDB - Pointer to CDB we want to execute.

p__ULONG__CDBSizeInUCHARs - CDB size in UCHARs.

p__PUCHAR__DataBuffer - Pointer to I/O data buffer.

p__ULONG__DataBufferSizeInUCHARs - I/O data buffer size in UCHARs.

p__BOOLEAN__IsDirectionToScsiTarget - Is data moved from memory-to-target (TRUE) or from target-to-memory (FALSE).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see ExecuteGeneric sample on how to send custom SCSI commands to CD/DVD/Blu-Ray/HD-DVD burner device.


Example

This example allocates CdvdBurnerGrabber object, sends custom command and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
UCHAR l__UCHAR__CDB[ 12 ];
UCHAR l__UCHAR__Data[ 0x2000 ];

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Format CDB and data buffer here...

// Try to send custom CDB to CD/DVD/Blu-Ray/HD-DVD burner device
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_ExecuteGeneric(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	&l__UCHAR__CDB,
	sizeof( l__UCHAR__CDB ),
	&l__UCHAR__Data,
	sizeof( l__UCHAR__Data ),
	TRUE
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromTree, StarBurn_CdvdBurnerGrabber_ImportTrack

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_ExecuteGeneric(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN PUCHAR p__PUCHAR__CDB,
    IN ULONG p__ULONG__CDBSizeInUCHARs,
    IN OUT PUCHAR p__PUCHAR__DataBuffer,
    IN ULONG p__ULONG__DataBufferSizeInUCHARs,
    IN BOOLEAN p__BOOLEAN__IsDirectionToScsiTarget
	);


/*

This function adds the tree created from the directory to already created ISO9660 or Joliet file tree from passed directory. 
Later this tree can be used to build  "virtual" ISO96600 or Joliet file system image. Resulting "virtual" image can be either 
stored in the file on the disk or be burn directly to the CD/DVD/Blu-Ray/HD-DVD media w/o any other intermediate operations. Unlike other
tree management calls this one deals with Unicode names (wide char variant of basic call).


Parameters

p__PVOID__ISO9660JolietFileTree - Pointer to the ISO9660 or Joliet file tree object.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCHAR__RootDirectoryAbsolutePathAndName - Pointer to directory name to build the ISO9660 or Joliet image from. This parameters
can be NULL (but in this case p__PCHAR__RootDirectoryNewName cannot!!!) if virtual (non-present on the disk) directory must
be added to the image.

p__PCHAR__RootDirectoryNewName - Pointer to directory name to be stored in the ISO9660 or Joliet image as root name,
NULL to include default name from the previous parameter.

p__FILE_TIME - File time that will be included in file system image (See FILE_TIME).

p__PPVOID__ISO9660JolietFileTreeNode__Parent - Pointer to pointer to the file tree node we'll use as parent. This is the result
of either tree walking with StarBurn_ISO9660JolietFileTree_GetFirstKid() or StarBurn_ISO9660JolietFileTree_GetNextKid() or the 
result of call to StarBurn_ISO9660JolietFileTree_GetRoot(). NULL can be passed instead of the result of 
StarBurn_ISO9660JolietFileTree_GetRoot().

p__PPVOID__ISO9660JolietFileTreeNode__NewChild - Pointer to pointer to the new created file tree node. 


Returns

Execution status. EN_SUCCESS if the tree was reallocated successfully, E_MEMORY_ALLOCATION_FAILED if there is not enough memory 
to reallocate the tree. If the exception number will be EN_SYSTEM_CALL_FAILED, variable that SystemError points to will be 
filled with system error. If something other then EN_SUCCESS will be returned buffer that ExceptionText will point to will be 
filled with formatted exception message.


Remarks

Please see the BuildImage sample that will demonstrate how progress indication can be build and what parameters in general are 
passed into the callback function during the operations with file tree object. BuildImage sample shows how to add files using
both ANSI and Unicode based naming conventions.


Example

This example allocates Joliet file tree and destroys it after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__FileTree;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__TreeNodes;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
PVOID l__PVOID__Root;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Try to create Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_Create(
    &l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    ( PCALLBACK )( Callback ),
    ( PVOID )( &l__LONG__TreeNodes ),
    TRUE,
    FALSE,
    FILE_TREE_JOLIET
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get root here
l__PVOID__Root = 
StarBurn_ISO9660JolietFileTree_GetRoot( l__PVOID__FileTree );

// Check for correct reply
if ( l__PVOID__Root == NULL )
{
// Handle error here, keep in mind that root CAN be NULL if nothing was added to tree before...
}

// Try to add all from the root directory of the drive D: to already created Joliet file tree
l__EXCEPTION_NUMBER = 
StarBurn_ISO9660JolietFileTree_AddW(
    l__PVOID__FileTree,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__Status,
    L"D:\\",
    NULL,
    FILE_TIME_LAST_WRITE,
    &l__PVOID__Root,
    &l__PVOID__NewNode
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Perform actions with Joliet tree here...

// Destroy the Joliet file tree
StarBurn_Destroy( &l__PVOID__FileTree );

// Just check for pointer (paranoid?)
if ( l__PVOID__FileTree != NULL )
{
// Handle error here...
}

</code>


See Also

StarBurn_Destroy, PCALLBACK, EXCEPTION_NUMBER, FILE_TREE, FILE_TIME, StarBurn_ISO9660JolietFileTree_Create, StarBurn_ISO9660JolietFileTree_GetRoot,
StarBurn_ISO9660JolietFileTree_GetFirstKid, StarBurn_ISO9660JolietFileTree_GetNextKid, StarBurn_ISO9660JolietFileTree_AddEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_ISO9660JolietFileTree_AddW(
    IN PVOID p__PVOID__ISO9660JolietFileTree,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    IN PWCHAR p__PWCHAR__RootDirectoryOrFileAbsolutePathAndName,
    IN PWCHAR p__PWCHAR__RootDirectoryOrFileNewName,
    IN FILE_TIME p__FILE_TIME,
    IN PVOID *p__PPVOID__ISO9660JolietFileTreeNode__Parent,
	OUT PVOID *p__PPVOID__ISO9660JolietFileTreeNode__NewChild
    );


/*

This function tests is CD/DVD/Blu-Ray/HD-DVD burner device object unit ready or not. This information can be used later to start I/O 
operations. This "double extended" variant of the call also can wait for particular amount of seconds and do "fast exit" if
there's no disc in drive.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__ULONG__NumberOfSecondsToWait - Number of seconds to wait (not less than the number, maybe more) for device to become into ready state.

p__BOOLEAN__IsFastExitUsed - Should StarBurn do "fast exit" if there's no disc in drive.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromTree and TrackAtOnceFromFile samples that will demonstrate how ISO9660 or Joliet file system 
image can be burn  on the CD/DVD/Blu-Ray/HD-DVD media and what StarBurn_CdvdBurnerGrabber_TestUnitReadyExEx can be used for. Also it's a
good idea to check either normal StarBurn_CdvdBurnerGrabber_TestUnitReady or basic extended variant of this call called
StarBurn_CdvdBurnerGrabber_TestUnitReadyEx. Some of them may work better in particular situation.


Example

This example allocates CdvdBurnerGrabber object, tests unit ready and destroys the device object after it's not needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to test unit ready
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_TestUnitReadyExEx(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	5, 		// 5 seconds to wait for device to become ready
	TRUE	// Fast exit if there's no disc in drive
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_TestUnitReady, StarBurn_CdvdBurnerGrabber_TestUnitReadyEx 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_TestUnitReadyExEx(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN ULONG p__ULONG__NumberOfSecondsToWait,
	IN BOOLEAN p__BOOLEAN__IsFastExitUsed
    );


/*

This function gets media (inserted or not) and tray (opened or closed) statuses from CD/DVD/Blu-Ray/HD-DVD burner device object.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PBOOLEAN__IsMediaPresent - Is media inserted (TRUE) or not (FALSE).

p__PBOOLEAN__IsDoorOrTrayOpen - Is tray or door opened (TRUE) or closed (FALSE).


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromFile sample that will demonstrate how ISO9660 or Joliet file system image can be burn to the 
CD/DVD/Blu-Ray/HD-DVD media and how StarBurn_CdvdBurnerGrabber_GetMediaTrayStatus can be used to determine media and tray status.


Example

This example allocates CdvdBurnerGrabber object, gets media and tray statuses and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
BOOLEAN l__BOOLEAN__IsMediaPresent;
BOOLEAN l__BOOLEAN__IsDoorOrTrayOpen;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get media and tray statuses
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetMediaTrayStatus(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	&l__BOOLEAN__IsMediaPresent,
	&l__BOOLEAN__IsDoorOrTrayOpen
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_TestUnitReady, StarBurn_CdvdBurnerGrabber_TestUnitReadyEx 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetMediaTrayStatus(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	OUT PBOOLEAN p__PBOOLEAN__IsMediaPresent,
	OUT PBOOLEAN p__PBOOLEAN__IsDoorOrTrayOpen
    );


/*

This function gets mechanical options (is device capable of programmatically load/eject and lock/unlock etc) from CD/DVD/Blu-Ray/HD-DVD burner 
device object.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PBOOLEAN__IsLockUnLockSupported - Pointer to the variable to receive is device capable of programmatically lock/unlock.

p__PBOOLEAN__IsLocked - Pointer to the variable to receive is media inside device locked right now.

p__PBOOLEAN__IsLoadEjectSupported - Pointer to the variable to receive is device capable of programmatically load/eject.

p__PUCHAR__LoadingMechanismType - Pointer to the variable to receive device loading mechanism type.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

Please see the TrackAtOnceFromFile sample that will demonstrate how ISO9660 or Joliet file system image can be burn to the 
CD/DVD/Blu-Ray/HD-DVD media and how StarBurn_CdvdBurnerGrabber_GetMechanicalOptions() can be used to determine device media control capabilities.


Example

This example allocates CdvdBurnerGrabber object, gets mechanical options and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;
BOOLEAN l__BOOLEAN__IsLockUnLockSupported = FALSE;
BOOLEAN l__BOOLEAN__IsLocked = FALSE;
BOOLEAN l__BOOLEAN__IsLoadEjectSupported = FALSE;
UCHAR l__UCHAR__LoadingMechanismType = 0x00;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to get media and tray statuses
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_GetMechanicalOptions(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	&l__BOOLEAN__IsLockUnLockSupported,
	&l__BOOLEAN__IsLocked,
	&l__BOOLEAN__IsLoadEjectSupported,
	&l__UCHAR__LoadingMechanismType
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_TestUnitReady, StarBurn_CdvdBurnerGrabber_TestUnitReadyEx, StarBurn_CdvdBurnerGrabber_GetMediaTrayStatus 

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetMechanicalOptions(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	OUT PBOOLEAN p__PBOOLEAN__IsLockUnLockSupported,
	OUT PBOOLEAN p__PBOOLEAN__IsLocked,
	OUT PBOOLEAN p__PBOOLEAN__IsLoadEjectSupported,
	OUT PUCHAR p__PUCHAR__LoadingMechanismType
    );


/*

This function sets read speed for CD/DVD/Blu-Ray/HD-DVD media currently inserted to CD/DVD/Blu-Ray/HD-DVD burner device object.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__ULONG__ReadSpeedInKBps - Read speed in kilobytes per second.


Returns

Execution status. EN_SUCCESS if the operation completed successfully. If the exception number will be EN_SYSTEM_CALL_FAILED, 
variable that SystemError points to will be filled with system error. If something other then EN_SUCCESS will be returned 
buffer that ExceptionText will point to will be filled with formatted exception message. If the exception number will be 
EN_SCSI_CDB_FAILED, CDB_FAILURE_INFORMATION will be filled with appropriate values (CDB that failed, CDB size, SCSI sense data, 
SCSI sense data size, SCSI transport, device and host adapter status codes).


Remarks

There are no examples of using StarBurn_CdvdBurnerGrabber_SetReadSpeed however this call is nearly identical to more generic
one called StarBurn_CdvdBurnerGrabber_SetSpeeds. Current one sets only read speed and generic one sets both read and write 
speeds at the same time.


Example

This example allocates CdvdBurnerGrabber object, sets maximum allowed read speed and destroys the device object after it's not 
needed any more.

<code>

// Somewhere in the data region
PVOID l__PVOID__CdvdBurnerGrabber;
EXCEPTION_NUMBER l__EXCEPTION_NUMBER;
ULONG l__ULONG__SystemError;
CHAR l__CHAR__ExceptionText[ 1024 ];
CDB_FAILURE_INFORMATION l__CDB_FAILURE_INFORMATION;

// Prepare exception text buffer
RtlZeroMemory(
    &l__CHAR__ExceptionText,
    sizeof( l__CHAR__ExceptionText )
    );

// Prepare CDB failure information
RtlZeroMemory(
    &l__CDB_FAILURE_INFORMATION,
    sizeof( l__CDB_FAILURE_INFORMATION )
    );

// Try to create CdvdBurnerGrabber on 0:0:4:0 with 32MB of cache
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_Create(
    &l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
    ( PCALLBACK )( StarBurn_Callback ),
    0,
    0,
    4,
    0,
    32
    );

// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Try to set maximum allowed read speed
l__EXCEPTION_NUMBER =
StarBurn_CdvdBurnerGrabber_SetReadSpeed(
    l__PVOID__CdvdBurnerGrabber,
    ( PCHAR )( &l__CHAR__ExceptionText ),
    sizeof( l__CHAR__ExceptionText ),
    &l__ULONG__SystemError,
    &l__CDB_FAILURE_INFORMATION,
	0xFFFF
    );
    
// Check for correct reply
if (  l__EXCEPTION_NUMBER != EN_SUCCESS )
{
// Handle error here...
}

// Do something with CdvdBurnerGrabber device object here...        

// Destroy the CdvdBurnerGrabber
StarBurn_Destroy( &l__PVOID__CdvdBurnerGrabber );

// Just check for pointer (paranoid?)
if ( l__PVOID__CdvdBurnerGrabber != NULL )
{
// Handle error here...
}

</code>

See Also

StarBurn_Destroy, StarBurn_CdvdBurnerGrabber_Create, PCALLBACK, EXCEPTION_NUMBER, CDB_FAILURE_INFORMATION,
StarBurn_CdvdBurnerGrabber_CreateEx, StarBurn_CdvdBurnerGrabber_SetSpeeds, StarBurn_CdvdBurnerGrabber_GetSpeeds

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_SetReadSpeed(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	IN ULONG p__ULONG__ReadSpeedInKBps
    );


/*

This function gets device timeout in seconds by device SCSI address.


Parameters

p__UCHAR__DevicePort - Device port.

p__UCHAR__DeviceBus - Device SCSI bus.

p__UCHAR__DeviceID - Device SCSI ID.

p__UCHAR__DeviceLUN - Device LUN.

p__PULONG__DeviceTimeOutInSeconds - Pointer to the variable to receive device timeout in seconds.


Result

Execution status.


Remarks

This one is for ASPI devices only.


Example

Please see FindDevice sample as example how to use StarBurn_GetDeviceTimeOutByDeviceAddress API call.


See Also

StarBurn_SetDeviceTimeOutByDeviceAddress

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_GetDeviceTimeOutByDeviceAddress(
    IN UCHAR p__UCHAR__DevicePort,
    IN UCHAR p__UCHAR__DeviceBus,
    IN UCHAR p__UCHAR__DeviceID,
    IN UCHAR p__UCHAR__DeviceLUN,
    OUT PULONG p__PULONG__DeviceTimeOutInSeconds
    );


/*

This function sets device timeout in seconds by device SCSI address.


Parameters

p__UCHAR__DevicePort - Device port.

p__UCHAR__DeviceBus - Device SCSI bus.

p__UCHAR__DeviceID - Device SCSI ID.

p__UCHAR__DeviceLUN - Device LUN.

p__ULONG__DeviceTimeOutInSeconds - New device timeout in seconds.


Result

Execution status.


Remarks

This one is for ASPI devices only.


Example

Please see FindDevice sample as example how to use StarBurn_SetDeviceTimeOutByDeviceAddress API call.


See Also

StarBurn_GetDeviceTimeOutByDeviceAddress

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_SetDeviceTimeOutByDeviceAddress(
    IN UCHAR p__UCHAR__DevicePort,
    IN UCHAR p__UCHAR__DeviceBus,
    IN UCHAR p__UCHAR__DeviceID,
    IN UCHAR p__UCHAR__DeviceLUN,
    IN ULONG p__ULONG__DeviceTimeOutInSeconds
    );


/*

This function gets ASPI layer ID strings.


Parameters

p__PULONG__SystemError - Pointer to system error value (if function would return EN_SYSTEM_CALL_FAILED).

p__PULONG__Version - Pointer to the variable to receive ASPI layer version number.

p__PCHAR__VersionText - Pointer to the buffer to receive ASPI layer version text.

p__ULONG__VersionTextSizeInUCHARs - Version text buffer size in UCHARs.


Result

Execution status.


Remarks

This one is for Rocket Division Software ASPI layer only.


Example

Please see FindDevice sample as example how to use StarBurn_GetId API call.


See Also

There are no companion API calls for this one.

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_GetId(
    OUT PULONG p__PULONG__SystemError,
	OUT PULONG p__PULONG__Version,
	OUT PCHAR p__PCHAR__VersionText,
	IN ULONG p__ULONG__VersionTextSizeInUCHARs
    );


/*

This function gets volume ID from ISO9660/Joliet volume name.


Parameters

p__PCHAR__VolumeName - ISO9660/Joliet name we'd like to query.

p__PCHAR__VolumeID - Pointer to destination buffer volume ID would be copied to.


Result

Execution status.


Remarks

This one is for ISO9660/Joliet volumes only.


Example

Please see BuildImageWithImportFromFile sample as example how to use StarBurn_GetVolumeIDs API call.


See Also

There are no companion API calls for this one.

*/

STARBURN_IMPEX_API
ULONG
__stdcall
StarBurn_GetVolumeIDs(
	IN PCHAR p__PCHAR__VolumeName,
	OUT PCHAR p__PCHAR__VolumeID
    );


/*

This function returns device letter (device root path) for a device name, like the one used in StarBurn_CdvdBurnerGrabber_CreateEx(...) API call.


Parameters

p__PCHAR__DeviceName - Device name to return the letter for.

p__PCHAR__DeviceLetter - Buffer to receive device root path. 

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Example

Please see GUI samples as example how to use StarBurn_GetDeviceLetter API call.


See Also

StarBurn_CdvdBurnerGrabber_CreateEx.

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_GetDeviceLetter(
	IN PCHAR p__PCHAR__DeviceName,
	OUT PCHAR p__PCHAR__DeviceLetter,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function detects recorded optical disc file system.


Parameters

p__PVOID__CdvdBurnerGrabber - Pointer to the CdvdBurnerGrabber object that toolkit allocated before.

p__PCHAR__ExceptionText - Pointer to array of CHARs that will be used to store formatted exception description message.

p__ULONG__ExceptionTextSizeInUCHARs - Size of the array of CHARs used to be formatted exception message storage.

p__PULONG__SystemError - Pointer to ULONG that will contain the system error (if some will occur).

p__PCDB_FAILURE_INFORMATION - Pointer to CDB_FAILURE_INFORMATION that will be filled with appropriate values.

p__PDISC_FILESYSTEM - Pointer to structure to receive disc file system flags.


Result

Execution status.


Example

Please see GUI DataBurner sample as example how to use StarBurn_GetDiscFileSystem API call.

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_GetDiscFileSystem(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
	OUT PDISC_FILESYSTEM p__PDISC_FILESYSTEM
	);


/*

This function adds local device (RAM disk, hard disk or DVD-ROM emulation) to StarPort virtual storage controller. 
StarPort acts like RAM disk, hard disk and DVD emulator, AoE (ATA-over-Ethernet) and iSCSI (SCSI-over-IP) initiator driver.


Parameters

p__STARPORT_DEVICE_TYPE - StarPort device type (See STARPORT_DEVICE_TYPE enum for more information).

p__PCHAR__StarPortDeviceName - Pointer to device name we want to add.

p__PLONG__StarPortDeviceTargetId - Pointer to the variable to receive StarPort device TargetId after device object creation.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Remarks

This one is for Enterprise or Network license holders only.


Example

Please see StarPort sample as example how to use StarBurn_StarPort_DeviceAddLocal API call.


See Also

StarBurn_StarPort_DeviceAddLocalEx, StarBurn_StarPort_DeviceRemove, StarBurn_StarPort_DeviceListQueryLocal, 
StarBurn_StarPort_DeviceListQueryRemote, StarBurn_StarPort_DeviceAddRemote, StarBurn_StarPort_DeviceAddRemoteEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarPort_DeviceAddLocal(
	IN STARPORT_DEVICE_TYPE p__STARPORT_DEVICE_TYPE,
	IN PCHAR p__PCHAR__StarPortDeviceName,
	OUT PLONG p__PLONG__StarPortDeviceTargetId,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function adds local device (RAM disk, hard disk or DVD-ROM emulation) to StarPort virtual storage controller. 
StarPort acts like RAM disk, hard disk and DVD emulator, AoE (ATA-over-Ethernet) and iSCSI (SCSI-over-IP) initiator 
driver. Device can be added persistent.


Parameters

p__STARPORT_DEVICE_TYPE - StarPort device type (See STARPORT_DEVICE_TYPE enum for more information).

p__PCHAR__StarPortDeviceName - Pointer to device name we want to add.

p__PLONG__StarPortDeviceTargetId - Pointer to the variable to receive StarPort device TargetId after device object creation.

p__BOOLEAN__Persistent - Is device will be added persistent.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Remarks

This one is for Enterprise or Network license holders only.


Example

Please see StarPort sample as example how to use StarBurn_StarPort_DeviceAddLocal API call.


See Also

StarBurn_StarPort_DeviceAddLocal,StarBurn_StarPort_DeviceRemove, StarBurn_StarPort_DeviceListQueryLocal, 
StarBurn_StarPort_DeviceListQueryRemote, StarBurn_StarPort_DeviceAddRemote, StarBurn_StarPort_DeviceAddRemoteEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarPort_DeviceAddLocalEx(
	IN STARPORT_DEVICE_TYPE p__STARPORT_DEVICE_TYPE,
	IN PCHAR p__PCHAR__StarPortDeviceName,
	OUT PLONG p__PLONG__StarPortDeviceTargetId,
	IN BOOLEAN p__BOOLEAN__Persistent,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function adds remote device (RAM disk, hard disk or DVD-ROM emulation) to StarPort virtual storage controller. 
StarPort acts like RAM disk, hard disk and DVD emulator, AoE (ATA-over-Ethernet) and iSCSI (SCSI-over-IP) initiator 
driver. Device can be mount persistent.


Parameters

p__PCHAR__TargetAddress - Pointer to the IP:port string corresponding to iSCSI target we'd like to add.

p__STARPORT_DEVICE_TYPE - StarPort device type (See STARPORT_DEVICE_TYPE enum for more information).

p__PCHAR__StarPortDeviceName - Pointer to iSCSI target device name we want to add.

p__PLONG__StarPortDeviceTargetId - Pointer to the variable to receive StarPort device TargetId after device object creation.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Remarks

This one is for Network license holders only.


Example

Please see StarPort sample as example how to use StarBurn_StarPort_DeviceAddRemote API call.


See Also

StarBurn_StarPort_DeviceAddRemoteEx, StarBurn_StarPort_DeviceRemove, StarBurn_StarPort_DeviceListQueryLocal, 
StarBurn_StarPort_DeviceListQueryRemote, StarBurn_StarPort_DeviceAddLocal, StarBurn_StarPort_DeviceAddLocalEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarPort_DeviceAddRemote(
	IN PCHAR p__PCHAR__TargetAddress,
	IN STARPORT_DEVICE_TYPE p__STARPORT_DEVICE_TYPE,
	IN PCHAR p__PCHAR__StarPortDeviceName,
	OUT PLONG p__PLONG__StarPortDeviceTargetId,								
	OUT PULONG p__PULONG__SystemError
	);


/*

This function adds remote device (RAM disk, hard disk or DVD-ROM emulation) to StarPort virtual storage controller. 
StarPort acts like RAM disk, hard disk and DVD emulator, AoE (ATA-over-Ethernet) and iSCSI (SCSI-over-IP) initiator driver.


Parameters

p__PCHAR__TargetAddress - Pointer to the IP:port string corresponding to iSCSI target we'd like to add.

p__STARPORT_DEVICE_TYPE - StarPort device type (See STARPORT_DEVICE_TYPE enum for more information).

p__PCHAR__StarPortDeviceName - Pointer to iSCSI target device name we want to add.

p__PLONG__StarPortDeviceTargetId - Pointer to the variable to receive StarPort device TargetId after device object creation.

p__BOOLEAN__Persistent - Is device will be mount persistent.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Remarks

This one is for Network license holders only.


Example

Please see StarPort sample as example how to use StarBurn_StarPort_DeviceAddRemote API call.


See Also

StarBurn_StarPort_DeviceAddRemote, StarBurn_StarPort_DeviceRemove, StarBurn_StarPort_DeviceListQueryLocal, 
StarBurn_StarPort_DeviceListQueryRemote, StarBurn_StarPort_DeviceAddLocal, StarBurn_StarPort_DeviceAddLocalEx

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarPort_DeviceAddRemoteEx(
	IN PCHAR p__PCHAR__TargetAddress,
	IN STARPORT_DEVICE_TYPE p__STARPORT_DEVICE_TYPE,
	IN PCHAR p__PCHAR__StarPortDeviceName,
	OUT PLONG p__PLONG__StarPortDeviceTargetId,
	IN BOOLEAN p__BOOLEAN__Persistent,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function removes device from StarPort virtual storage controller. StarPort acts like RAM disk, hard disk and 
DVD-ROM emulator, AoE (ATA-over-Ethernet) and iSCSI (SCSI-over-IP) initiator driver.


Parameters

p__LONG__StarPortDeviceTargetId - StarPort device TargetId we want to remove from the system.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Remarks

This one is for Enterprise or Network license holders only.


Example

Please see StarPort sample as example how to use StarBurn_StarPort_DeviceRemove API call.


See Also

StarBurn_StarPort_DeviceAddRemote, StarBurn_StarPort_DeviceListQueryLocal, StarBurn_StarPort_DeviceListQueryRemote, 
StarBurn_StarPort_DeviceAddLocal

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarPort_DeviceRemove(
	IN LONG p__LONG__StarPortDeviceTargetId,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function gets device list from StarPort virtual storage controller. StarPort acts like RAM disk, hard disk 
and DVD-ROM emulator, AoE (ATA-over-Ethernet) and iSCSI (SCSI-over-IP) initiator driver. Unlike 
StarBurn_StarPort_DeviceListQueryRemote API call which retrieves information about REMOTE device list this call 
gets information about LOCAL device list.


Parameters

p__PSTARPORT_DEVICE_LIST - Pointer to the STARPORT_DEVICE_LIST structure drive would fill with StarPort device list information.

p__ULONG__StarPortDeviceListSizeInUCHARs - True STARPORT_DEVICE_LIST structure size in UCHARs.

p__PLONG__NumberOfTargets - Pointer to the variable to receive number of targets StarPort would enumerate during this call.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Remarks

This one is for Enterprise or Network license holders only.


Example

Please see StarPort sample as example how to use StarBurn_StarPort_DeviceListQueryLocal API call.


See Also

StarBurn_StarPort_DeviceAddLocal, StarBurn_StarPort_DeviceRemove, StarBurn_StarPort_DeviceListQueryRemote, StarBurn_StarPort_DeviceAddRemote

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarPort_DeviceListQueryLocal(
	OUT PSTARPORT_DEVICE_LIST p__PSTARPORT_DEVICE_LIST,
	IN ULONG p__ULONG__StarPortDeviceListSizeInUCHARs,
	OUT PLONG p__PLONG__NumberOfTargets,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function gets device list from remote StarWind iSCSI target. StarWind exports RAM disk, hard disk and DVD-ROM 
emulator, AoE (ATA-over-Ethernet) and iSCSI (SCSI-over-IP) targets. Unlike StarBurn_StarPort_DeviceListQueryLocal
API call which retreives information about LOCAL device list this call gets information about REMOTE device list.


Parameters

p__PCHAR__TargetAddress - Pointer to IP:port string which corresponds to the iSCSI target we'd like to query.

p__PSTARPORT_DEVICE_LIST - Pointer to the STARPORT_DEVICE_LIST structure drive would fill with StarPort device list information.

p__ULONG__StarPortDeviceListSizeInUCHARs - True STARPORT_DEVICE_LIST structure size in UCHARs.

p__PLONG__NumberOfTargets - Pointer to the variable to receive number of targets StarPort would enumerate during this call.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Remarks

This one is for Network license holders only.


Example

Please see StarPort sample as example how to use StarBurn_StarPort_DeviceListQueryRemote API call.


See Also

StarBurn_StarPort_DeviceAddLocal, StarBurn_StarPort_DeviceRemove, StarBurn_StarPort_DeviceListQueryLocal, StarBurn_StarPort_DeviceAddRemote

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarPort_DeviceListQueryRemote(
	IN PCHAR p__PCHAR__TargetAddress,
	OUT PSTARPORT_DEVICE_LIST p__PSTARPORT_DEVICE_LIST,
	IN ULONG p__ULONG__StarPortDeviceListSizeInUCHARs,
	OUT PLONG p__PLONG__NumberOfTargets,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function retrieves device letter (symbolic link) for StarPort device by its target ID.


Parameters

p__LONG__StarPortDeviceTargetId - StarPort device TargetId we want to get device letter for.

p__PCHAR__DeviceLetter - Pointer to the CHAR variable to store the device letter.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Remarks

This one is for Network license holders only.


Example

Please see StarPort GUI sample as example how to use StarBurn_StarPort_GetDeviceLetter API call.


See Also

StarBurn_StarPort_DeviceAddLocal, StarBurn_StarPort_DeviceRemove, StarBurn_StarPort_DeviceListQueryLocal,
StarBurn_StarPort_DeviceAddRemote, StarBurn_StarPort_DeviceListQueryRemote

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarPort_GetDeviceLetter(
	IN LONG p__LONG__StarPortDeviceTargetId,
	OUT PCHAR p__PCHAR__DeviceLetter,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function checks if the StarPortLite driver is installed and that its API version is equal to the one StarBurn was built with.


Parameters

p__PULONG__BuildVersion - StarPortLite driver build version.

p__PULONG__ApiVersion - StarPortLite driver API version.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Remarks

This one is for Network license holders only.


Example

Please see StarPort GUI sample as example how to use StarBurn_StarPort_GetVersion API call.


See Also

StarBurn_StarPort_DeviceAddLocal, StarBurn_StarPort_DeviceRemove, StarBurn_StarPort_DeviceListQueryLocal,
StarBurn_StarPort_DeviceAddRemote, StarBurn_StarPort_DeviceListQueryRemote, StarBurn_StarPort_GetDeviceLetter

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarPort_GetVersion(
	OUT PULONG p__PULONG__BuildVersion,
	OUT PULONG p__PULONG__ApiVersion,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function retrieves device type, vendor ID, product ID and revision for StarPort device by its target ID.


Parameters

p__LONG__StarPortDeviceTargetId - StarPort device TargetId we want to get device letter for.

p__PSTARPORT_DEVICE_TYPE - Pointer to the STARPORT_DEVICE_TYPE variable to store the device type.

p__PCHAR__VendorID - Pointer to the buffer to receive vendor ID.

p__ULONG__VendorIDSizeInUCHARs - The size of the buffer to receive vendor ID.

p__PCHAR__ProductID - Pointer to the buffer to receive product ID.

p__ULONG__ProductIDSizeInUCHARs - The size of the buffer to receive product ID.

p__PCHAR__Revision - Pointer to the buffer to receive revision.

p__ULONG__RevisionSizeInUCHARs - The size of the buffer to receive revision.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Remarks

This one is for Network license holders only.


Example

Please see StarPort GUI sample as example how to use StarBurn_StarPort_GetDeviceInformation API call.


See Also

StarBurn_StarPort_DeviceAddLocal, StarBurn_StarPort_DeviceRemove, StarBurn_StarPort_DeviceListQueryLocal,
StarBurn_StarPort_DeviceAddRemote, StarBurn_StarPort_DeviceListQueryRemote, StarBurn_StarPort_GetDeviceLetter,
StarBurn_StarPort_GetVersion.

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarPort_GetDeviceInformation(	
	IN LONG p__LONG__StarPortDeviceTargetId,
	OUT PSTARPORT_DEVICE_TYPE p__PSTARPORT_DEVICE_TYPE,
	OUT PCHAR p__PCHAR__VendorID,
	IN ULONG p__ULONG__VendorIDSizeInUCHARs,
	OUT PCHAR p__PCHAR__ProductID,
	IN ULONG p__ULONG__ProductIDSizeInUCHARs,
	OUT PCHAR p__PCHAR__Revision,
	IN ULONG p__ULONG__RevisionSizeInUCHARs,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function retrieves device SCSI address for StarPort device by its target ID.


Parameters

p__LONG__StarPortDeviceTargetId - StarPort device TargetId we want to get device letter for.

p__PSCSI_DEVICE_ADDRESS - Pointer to the variable to receive device SCSI address.

p__PULONG__SystemError - Pointer to the variable to receive system error if function would return anything except EN_SUCCESS.


Result

Execution status.


Remarks

This one is for Network license holders only.


Example

Please see StarPort GUI sample as example how to use StarBurn_StarPort_GetDeviceSCSIAddress API call.


See Also

StarBurn_StarPort_DeviceAddLocal, StarBurn_StarPort_DeviceRemove, StarBurn_StarPort_DeviceListQueryLocal,
StarBurn_StarPort_DeviceAddRemote, StarBurn_StarPort_DeviceListQueryRemote, StarBurn_StarPort_GetDeviceLetter,
StarBurn_StarPort_GetVersion, StarBurn_StarPort_GetDeviceLetter

*/

STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_StarPort_GetDeviceSCSIAddress(	
	IN LONG p__LONG__StarPortDeviceTargetId,
	OUT PSCSI_DEVICE_ADDRESS p__PSCSI_DEVICE_ADDRESS,
	OUT PULONG p__PULONG__SystemError
	);


/*

This function generates next ISO9660 file name to make it unique.


Parameters

p__PCHAR__Name - Pointer to current name.


Result

Nothing.


Remarks

N/A


Example

N/A


See Also

StarBurn_CorrectJolietName_Default

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_CorrectISO9660Name_Default(
	IN OUT PCHAR p__PCHAR__Name
	);


/*

This function generates next Joliet file name to make it unique.


Parameters

p__PWCHAR__Name - Pointer to current name.


Result

Nothing.


Remarks

N/A


Example

N/A


See Also

StarBurn_CorrectISO9660Name_Default

*/

STARBURN_IMPEX_API
VOID 
__stdcall
StarBurn_CorrectJolietName_Default(
	IN OUT PWCHAR p__PWCHAR__Name
	);


/*

This function returns is so-called "64KB I/O" (when StarBurn issues 64KB I/O packets instead of the 32KB ones) currently 
enabled (TRUE) or disabled (FALSE).


Parameters

Nothing.


Result

Is "64KB I/O" mode enabled (TRUE) or disabled (FALSE).


Remarks

There's no need to play with this parameter unless you really have broken device you will to force 32KB I/O requests for.


Example

There are no examples for StarBurn_GetIs64KBIO(...) API call.


See Also

StarBurn_SetIs64KBIO

*/

STARBURN_IMPEX_API
BOOLEAN
__stdcall
StarBurn_GetIs64KBIO(
    IN VOID
    );


/*

This function sets current so-called "64KB I/O" (when StarBurn issues 64KB I/O packets instead of the 32KB ones) to
enabled (TRUE) or disabled (FALSE) state.


Parameters

p__BOOLEAN__NewIs64KBIO - Current "64KB I/O" enabled (TRUE) or disabled (FALSE).


Result

Nothing.


Remarks

There's no need to play with this parameter unless you really have broken device you will to force 32KB I/O requests for.


Example

There are no examples for StarBurn_SetIs64KBIO(...) API call.


See Also

StarBurn_GetIs64KBIO

*/

STARBURN_IMPEX_API
VOID
__stdcall
StarBurn_SetIs64KBIO(
    IN BOOLEAN p__BOOLEAN__NewIs64KBIO
    );


//
// Experimental code (begin)
//


STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_TrackAtOnceFromFileAudioUnicode(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PWCHAR p__PWCHAR__SoundImagePathAndFileName,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


STARBURN_IMPEX_API
EXCEPTION_NUMBER
__stdcall
StarBurn_CdvdBurnerGrabber_DiscAtOnceRawPWFromFileAudioUnicode(
    IN PVOID p__PVOID__CdvdBurnerGrabber,
    OUT PCHAR p__PCHAR__ExceptionText,
    IN ULONG p__ULONG__ExceptionTextSizeInUCHARs,
    OUT PULONG p__PULONG__SystemError,
    OUT PCDB_FAILURE_INFORMATION p__PCDB_FAILURE_INFORMATION,
    IN PDAO_DISC_LAYOUT p__PDAO_DISC_LAYOUT,
    IN BOOLEAN p__BOOLEAN__IsXA,
    IN BOOLEAN p__BOOLEAN__IsTestWrite,
    IN BOOLEAN p__BOOLEAN__IsNextSessionAllowed,
	IN BOOLEAN p__BOOLEAN__IsSubChannelRepairRequired,
    IN ULONG p__ULONG__WriteReportDelayInSeconds,
    IN ULONG p__ULONG__BufferStatusReportDelayInSeconds
    );


//
// Experimental code (end)
//


//
// UDF2 (begin)
//


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_ISO9660FileTreeCreate(
	void **ISO9660FileTree,
	void *UdfVolume
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_DirectoryCreate(
	void **Directory,
	const char *Name,
	unsigned long *GUID,
	void *Parent
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_DirectoryUnicodeCreate(
	void **Directory,
	const unsigned short *UnicodeName,
	unsigned long *GUID,
	void *Parent
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_DirectoryRootCreate(
	void **Directory,
	unsigned long *GUID
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_FileCreate(
	void **File,
	const char *Name,
	const char *PathName,
	unsigned long *GUID,
	void *Parent
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_FileUnicodeCreate(
	void **File,
	const unsigned short *UnicodeName,
	const unsigned short *UnicodePathName,
	unsigned long *GUID,
	void *Parent
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_FileMemoryCreate(
	void **File,
	const char *Name,
	const void *MemoryRegion,
	unsigned long MemoryRegionSizeInUCHARs,
	unsigned long *GUID,
	void *Parent
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_FileMemoryUnicodeCreate(
	void **File,
	const unsigned short *UnicodeName,
	const void *MemoryRegion,
	unsigned long MemoryRegionSizeInUCHARs,
	unsigned long *GUID,
	void *Parent
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_VolumeCreate(
	void **Volume,
	void *Root,
	const char *Name,
	BOOL IsUnicode,
	BOOL IsGlobalDateTime,
	const STARBURN_UDF2_FILE_DATE_TIME *DateTime
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_VolumeUnicodeCreate(
	void **Volume,
	void *Root,
	const unsigned short *UnicodeName,
	BOOL IsUnicode,
	BOOL IsGlobalDateTime,
	const STARBURN_UDF2_FILE_DATE_TIME *DateTime,
	unsigned char OSClass
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_VolumeStore(
	void *Volume,
	const char *Name
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_VolumeSizeInUCHARsGet(
	void *Volume,
	unsigned __int64 *SizeInUCHARs
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_VolumeSeekRead(
	void *Volume,
	void *Buffer,
	unsigned long BufferSizeInLogicalBlocks,	
	unsigned long OffsetInLogicalBlocks
	);


STARBURN_IMPEX_API
void
__stdcall
StarBurn_UDF2_DirectoryDestroy(
	void *Directory
	);


STARBURN_IMPEX_API
void
__stdcall
StarBurn_UDF2_FileDestroy(
	void *File
	);


STARBURN_IMPEX_API
void
__stdcall
StarBurn_UDF2_VolumeDestroy(
	void *Volume
	);


STARBURN_IMPEX_API
void
__stdcall
StarBurn_UDF2_FileDirectoryDateTimeSet(
	void *FileDirectory,
	STARBURN_UDF2_FILE_DATE_TIME *DateTime	
	);


STARBURN_IMPEX_API
void
__stdcall
StarBurn_UDF2_FileDirectoryDateTimeGet(
	void *FileDirectory,
	STARBURN_UDF2_FILE_DATE_TIME *DateTime	
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_DirectoryProcess(
	const char *Name,
	const char *PathName,
	unsigned long *GUID,
	void *Parent
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_DirectoryUnicodeProcess(
	const unsigned short *UnicodeName,
	const unsigned short *UnicodePathName,
	unsigned long *GUID,
	void *Parent
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_DirectoryProcessEx(
	const char *Name,
	const char *PathName,
	unsigned long *GUID,
	void *Parent,
	PSTARBURN_UDF2_PROGRESS_CALLBACK Callback,
	const void *Context,
	STARBURN_UDF2_FILE_DATE_TIME *DateTime
	);


STARBURN_IMPEX_API
long
__stdcall
StarBurn_UDF2_DirectoryUnicodeProcessEx(
	const unsigned short *UnicodeName,
	const unsigned short *UnicodePathName,
	unsigned long *GUID,
	void *Parent,
	PSTARBURN_UDF2_UNICODE_PROGRESS_CALLBACK Callback,
	const void *Context,
	STARBURN_UDF2_FILE_DATE_TIME *DateTime
	);


//
// UDF2 (end)
//


#endif // __STARBURN_CORE_HPP__


#ifdef __cplusplus

}

#endif


//
// Own data types, global function bodies, classes and methods (end)
//


#endif // Define this file __STARBURN_H__ (end)

#ifndef WINDOWS_EX_FILE_SYSTEM_H
#define WINDOWS_EX_FILE_SYSTEM_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

BOOL WINAPI ResizeFile(HANDLE hFile, LARGE_INTEGER liFileSize);

BOOL WINAPI SetFileSparse(HANDLE hFile);

BOOL WINAPI SetFileZeroData(/*IN*/ HANDLE hFile,
                            /*IN*/ PFILE_ZERO_DATA_INFORMATION lpFzdi);

BOOL WINAPI QueryFileAllocatedRanges(
        /*IN    */ HANDLE hFile,
        /*IN    */ PFILE_ALLOCATED_RANGE_BUFFER lpQueryRange,
        /*OUT   */ PFILE_ALLOCATED_RANGE_BUFFER lpRanges,
        /*IN OUT*/ PDWORD lpNumberOrRanges);


BOOL WINAPI GetFileAllocationBlockSizeA(/*IN */ LPCSTR lpRootPath,
                                        /*OUT*/ LPDWORD lpBytesPerBlock);

BOOL WINAPI GetFileAllocationBlockSizeW(/*IN */ LPCWSTR lpRootPath,
                                        /*OUT*/ LPDWORD lpBytesPerBlock);

BOOL WINAPI LockVolume(HANDLE hVolume);

BOOL WINAPI UnlockVolume(HANDLE hVolume);

BOOL WINAPI DismountVolume(HANDLE hVolume);

BOOL WINAPI GetNtfsVolumeData(
        /*IN */ HANDLE hVolume,
        /*OUT*/ PNTFS_VOLUME_DATA_BUFFER lpNtfsVolumeData);

BOOL WINAPI GetVolumeBitmap(
        /*IN    */ HANDLE hVolume,
        /*IN    */ PSTARTING_LCN_INPUT_BUFFER lpStartingLcn,
        /*OUT   */ PVOLUME_BITMAP_BUFFER lpBitmap,
        /*IN OUT*/ PDWORD lpBitmapSize);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* WINDOWS_EX_FILE_SYSTEM_H */

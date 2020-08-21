#include "FileSystem.h"

BOOL WINAPI ResizeFile(HANDLE hFile, LARGE_INTEGER liFileSize)
{
    LARGE_INTEGER liUnused;
    if (!SetFilePointerEx(hFile, liFileSize, &liUnused, FILE_BEGIN))
        return FALSE;
    return SetEndOfFile(hFile);
}

BOOL WINAPI SetFileSparse(HANDLE hFile)
{
    DWORD dwUnused;
    return DeviceIoControl(
                hFile, FSCTL_SET_SPARSE, NULL, 0, NULL, 0, &dwUnused, NULL);
}

BOOL WINAPI SetFileZeroData(HANDLE hFile, PFILE_ZERO_DATA_INFORMATION lpFzdi)
{
    DWORD dwUnused;
    return DeviceIoControl(
                hFile, FSCTL_SET_ZERO_DATA,
                lpFzdi, sizeof(FILE_ZERO_DATA_INFORMATION),
                NULL, 0, &dwUnused, NULL);
}

BOOL WINAPI QueryFileAllocatedRanges(
        HANDLE hFile,
        PFILE_ALLOCATED_RANGE_BUFFER lpQueryRange,
        PFILE_ALLOCATED_RANGE_BUFFER lpRanges,
        PDWORD lpNumberOrRanges)
{
    if (lpNumberOrRanges == NULL)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    DWORD nSizeOfRanges =
            (DWORD)(*lpNumberOrRanges * sizeof(FILE_ALLOCATED_RANGE_BUFFER));
    DWORD nBytesReturned;
    BOOL bResult = DeviceIoControl(
                       hFile, FSCTL_QUERY_ALLOCATED_RANGES,
                       lpQueryRange, sizeof(FILE_ALLOCATED_RANGE_BUFFER),
                       lpRanges, nSizeOfRanges, &nBytesReturned, NULL);
    if (bResult)
    {
        *lpNumberOrRanges =
                nBytesReturned / sizeof(FILE_ALLOCATED_RANGE_BUFFER);
    }
    return bResult;
}

BOOL WINAPI GetFileAllocationBlockSizeA(
        LPCSTR lpRootPath, LPDWORD lpBytesPerBlock)
{
    if (lpBytesPerBlock == NULL)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    DWORD nSectorsPerCluster = 0;
    DWORD nBytesPerSector = 0;
    DWORD dwUnused;
    BOOL bResult = GetDiskFreeSpaceA(
                       lpRootPath, &nSectorsPerCluster, &nBytesPerSector,
                       &dwUnused, &dwUnused);
    if (bResult)
        *lpBytesPerBlock = 16 * nBytesPerSector * nSectorsPerCluster;
    return bResult;
}

BOOL WINAPI GetFileAllocationBlockSizeW(
        LPCWSTR lpRootPath, LPDWORD lpBytesPerBlock)
{
    if (lpBytesPerBlock == NULL)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    DWORD nSectorsPerCluster = 0;
    DWORD nBytesPerSector = 0;
    DWORD dwUnused;
    BOOL bResult = GetDiskFreeSpaceW(
                       lpRootPath, &nSectorsPerCluster, &nBytesPerSector,
                       &dwUnused, &dwUnused);
    if (bResult)
        *lpBytesPerBlock = 16 * nBytesPerSector * nSectorsPerCluster;
    return bResult;
}

BOOL WINAPI LockVolume(HANDLE hVolume)
{
    DWORD dwUnused;
    return DeviceIoControl(
                hVolume, FSCTL_LOCK_VOLUME,
                NULL, 0, NULL, 0, &dwUnused, NULL);
}

BOOL WINAPI UnlockVolume(HANDLE hVolume)
{
    DWORD dwUnused;
    return DeviceIoControl(
                hVolume, FSCTL_UNLOCK_VOLUME,
                NULL, 0, NULL, 0, &dwUnused, NULL);
}

BOOL WINAPI DismountVolume(HANDLE hVolume)
{
    DWORD dwUnused;
    return DeviceIoControl(
                hVolume, FSCTL_DISMOUNT_VOLUME,
                NULL, 0, NULL, 0, &dwUnused, NULL);
}

BOOL WINAPI GetNtfsVolumeData(
        HANDLE hVolume,
        PNTFS_VOLUME_DATA_BUFFER lpNtfsVolumeData)
{
    DWORD dwUnused;
    return DeviceIoControl(
                hVolume, FSCTL_GET_NTFS_VOLUME_DATA,
                NULL, 0, lpNtfsVolumeData, sizeof(NTFS_VOLUME_DATA_BUFFER),
                &dwUnused, NULL);
}

BOOL WINAPI GetVolumeBitmap(HANDLE hVolume,
                            PSTARTING_LCN_INPUT_BUFFER lpStartingLcn,
                            PVOLUME_BITMAP_BUFFER lpBitmap,
                            PDWORD lpBitmapSize)
{
    if (lpBitmapSize == NULL)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    DWORD nInBufferSize = (DWORD)(*lpBitmapSize + 2 * sizeof(LARGE_INTEGER));
    DWORD nBytesReturned;
    BOOL bResult = DeviceIoControl(
                hVolume, FSCTL_GET_VOLUME_BITMAP,
                lpStartingLcn, sizeof(STARTING_LCN_INPUT_BUFFER),
                lpBitmap, nInBufferSize, &nBytesReturned, NULL);
    if (bResult == FALSE && GetLastError() != ERROR_MORE_DATA)
        return FALSE;

    if (nBytesReturned < 2 * sizeof(LARGE_INTEGER))
    {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return FALSE;
    }

    *lpBitmapSize = (DWORD)(nBytesReturned - 2 * sizeof(LARGE_INTEGER));
    return bResult;
}

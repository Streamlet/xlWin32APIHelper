//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   FileOP.h
//    Author:      Streamlet
//    Create Time: 2016-09-20
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __FILEOP_H_8DB99F9D_F271_4988_80A8_6EE0C3A9C69F_INCLUDED__
#define __FILEOP_H_8DB99F9D_F271_4988_80A8_6EE0C3A9C69F_INCLUDED__


#include <Windows.h>
#include <string>
#include <assert.h>
#include "External/stdex/string.h"
#include "FileScanner.h"

namespace xl
{
    namespace Win32
    {
        namespace File
        {
            bool MakeDir(LPCWSTR lpszPath)
            {
                assert(lpszPath);
                std::wstring strPath(lpszPath);
                std::vector<stdex::shadow_wstring> vecDir = stdex::str_split(strPath, L'\\');
                for each (auto ss in vecDir)
                {
                    if (ss.length() == 0)
                        continue;
                    size_t i = (ss.c_str() - strPath.c_str()) + ss.length();
                    strPath[i] = L'\0';
                    if (!::CreateDirectoryW(strPath.c_str(), NULL))
                        return false;
                    strPath[i] = L'\\';
                }
                return true;
            }

            bool RMDir(LPCWSTR lpszPath)
            {
                assert(lpszPath && lpszPath[0] != L'\\');
                if (!EnumFiles(lpszPath, L"*", ENUM_RECURSIVELY | ENUM_DIRECTORY | ENUM_EXCLUDE_FILES, [](LPCWSTR lpszFile, LPVOID lpParam)
                    {
                        return RMDir(lpszFile);
                    }, NULL))
                {
                    return false;
                }

                if (!EnumFiles(lpszPath, L"*", 0, [](LPCWSTR lpszFile, LPVOID lpParam)
                    {
                        return !!::DeleteFileW(lpszFile);
                    }, NULL))
                {
                    return false;
                }

                return !!::RemoveDirectoryW(lpszPath);
            }
        }
    }
}

#endif // #ifndef __FILEOP_H_8DB99F9D_F271_4988_80A8_6EE0C3A9C69F_INCLUDED__

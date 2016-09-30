//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   FileScanner.h
//    Author:      Streamlet
//    Create Time: 2016-09-09
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __FILESCANNER_H_6B3FBD9E_9870_4C5F_88B5_673C082192A7_INCLUDED__
#define __FILESCANNER_H_6B3FBD9E_9870_4C5F_88B5_673C082192A7_INCLUDED__


#include <Windows.h>
#include <string>
#include <vector>

namespace xl
{
    namespace Win32
    {
        namespace File
        {
            enum
            {
                ENUM_RECURSIVELY    = 0x01,
                ENUM_SUB_FIRST      = 0x08,
                ENUM_NO_DIRECTORIES = 0x02,
                ENUM_NO_FILES       = 0x04,
            };

            typedef bool (*ENUM_FILE_PROC)(LPCWSTR, DWORD, LPVOID);
            template <typename Callback>
            bool EnumFiles(LPCWSTR lpszDir, LPCWSTR lpszFile, DWORD dwFlags, Callback callback, LPVOID lpParam)
            {
                std::wstring strPath;
                strPath.reserve(MAX_PATH);
                strPath.append(lpszDir);
                if (!strPath.empty() && *strPath.rbegin() != L'\\')
                    strPath.append(1, L'\\');
                size_t nLen = strPath.length();

                WIN32_FIND_DATAW wfd = {};

                strPath.append(lpszFile);
                HANDLE hFind = ::FindFirstFileW(strPath.c_str(), &wfd);
                if (hFind == INVALID_HANDLE_VALUE)
                    return false;
                strPath.resize(nLen);

                do
                {
                    if (wcscmp(wfd.cFileName, L".") == 0 || wcscmp(wfd.cFileName, L"..") == 0)
                        continue;

                    strPath.append(wfd.cFileName);

                    if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
                    {
                        if (!(dwFlags & ENUM_NO_DIRECTORIES) && !(dwFlags & ENUM_SUB_FIRST))
                        {
                            if (!callback(strPath.c_str(), wfd.dwFileAttributes, lpParam))
                                break;
                        }

                        if (dwFlags & ENUM_RECURSIVELY)
                        {
                            if (!EnumFiles(strPath.c_str(), lpszFile, dwFlags, callback, lpParam))
                                break;
                        }

                        if (!(dwFlags & ENUM_NO_DIRECTORIES) && (dwFlags & ENUM_SUB_FIRST))
                        {
                            if (!callback(strPath.c_str(), wfd.dwFileAttributes,  lpParam))
                                break;
                        }
                    }
                    else
                    {
                        if (!(dwFlags & ENUM_NO_FILES))
                        {
                            if (!callback(strPath.c_str(), wfd.dwFileAttributes, lpParam))
                                break;
                        }
                    }

                    strPath.resize(nLen);

                } while (::FindNextFileW(hFind, &wfd));

                ::FindClose(hFind);
                return true;
            }

            std::vector<std::wstring> GetFileList(LPCWSTR lpszDir, LPCWSTR lpszFile, DWORD dwFlags)
            {
                std::vector<std::wstring> vecFiles;
                EnumFiles(lpszDir, lpszFile, dwFlags, [&vecFiles](LPCWSTR lpszFile, DWORD dwAttr, LPVOID lpParam)
                {
                    vecFiles.push_back(lpszFile);
                    return true;
                }, nullptr);
                return vecFiles;
            }
        }
    }
}


#endif // #ifndef __FILESCANNER_H_6B3FBD9E_9870_4C5F_88B5_673C082192A7_INCLUDED__

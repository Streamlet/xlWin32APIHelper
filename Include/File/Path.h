//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Path.h
//    Author:      Streamlet
//    Create Time: 2016-09-15
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __PATH_H_1400E3A8_4978_4AEF_909F_643C06218D08_INCLUDED__
#define __PATH_H_1400E3A8_4978_4AEF_909F_643C06218D08_INCLUDED__


#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include <string>

namespace xl
{
    namespace Win32
    {
        namespace File
        {
            std::wstring PathNormalize(LPCWSTR lpszPath)
            {
                std::wstring s;
                s.resize(MAX_PATH);
                if (!PathCanonicalize(&s[0], lpszPath))
                    return L"";
                s.resize(wcslen(s.c_str()));
                return s;
            }
        }
    }
}

#endif // #ifndef __PATH_H_1400E3A8_4978_4AEF_909F_643C06218D08_INCLUDED__

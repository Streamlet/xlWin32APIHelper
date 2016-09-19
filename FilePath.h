//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   FilePath.h
//    Author:      Streamlet
//    Create Time: 2016-09-20
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __FILEPATH_H_398A9DC3_D0A4_466A_9FC5_A9094ECC1DE1_INCLUDED__
#define __FILEPATH_H_398A9DC3_D0A4_466A_9FC5_A9094ECC1DE1_INCLUDED__


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
                if (!PathCanonicalizeW(&s[0], lpszPath))
                    return L"";
                s.resize(wcslen(s.c_str()));
                return s;
            }
        }
    }
}

#endif // #ifndef __FILEPATH_H_398A9DC3_D0A4_466A_9FC5_A9094ECC1DE1_INCLUDED__

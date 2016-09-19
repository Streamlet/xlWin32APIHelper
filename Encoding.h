//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Encoding.h
//    Author:      Streamlet
//    Create Time: 2010-09-15
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __ENCODING_H_B23F48D1_9E5C_435B_9BDA_B6370F9BAD62_INCLUDED__
#define __ENCODING_H_B23F48D1_9E5C_435B_9BDA_B6370F9BAD62_INCLUDED__


#include <Windows.h>
#include <string>

namespace Win32
{
    namespace String
    {
        inline std::wstring ANSIToUCS2(LPCSTR lpszANSI, UINT uCodePage = CP_ACP)
        {
            std::wstring strUCS2;
            int size = MultiByteToWideChar(uCodePage, 0, lpszANSI, -1, NULL, 0);
            if (size == 0)
                return strUCS2;
            strUCS2.resize(size);
            MultiByteToWideChar(uCodePage, 0, lpszANSI, -1, &strUCS2[0], size);
            return strUCS2;
        }

        inline std::string UCS2ToANSI(LPCWSTR lpszUCS2, UINT uCodePage = CP_ACP)
        {
            std::string strANSI;
            int size = WideCharToMultiByte(uCodePage, 0, lpszUCS2, -1, NULL, 0, NULL, NULL);
            if (size == 0)
                return strANSI;
            strANSI.reserve(size);
            WideCharToMultiByte(uCodePage, 0, lpszUCS2, -1, &strANSI[0], size, NULL, NULL);
            return strANSI;
        }

        inline std::wstring UTF8ToUCS2(LPCSTR lpszANSI)
        {
            return ANSIToUCS2(lpszANSI, CP_UTF8);
        }

        inline std::string UCS2ToUTF8(LPCWSTR lpszUCS2)
        {
            return UCS2ToANSI(lpszUCS2, CP_UTF8)
        }
    }
}

#endif // #ifndef __ENCODING_H_B23F48D1_9E5C_435B_9BDA_B6370F9BAD62_INCLUDED__

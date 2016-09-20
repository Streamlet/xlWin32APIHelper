#include "../External/xlUnitTest/UnitTest.h"
#include "../FilePath.h"
#include "../FileScanner.h"
#include "../FileOP.h"
#include <functional>

XL_NAMED_TEST_CASE(PathNormalize)
{
    using namespace xl::Win32::File;

    XL_TEST_ASSERT(PathNormalize(L"C:\\a\\b\\") == L"C:\\a\\b\\");
    XL_TEST_ASSERT(PathNormalize(L"C:\\a\\b") == L"C:\\a\\b");
    XL_TEST_ASSERT(PathNormalize(L"C:\\a\\") == L"C:\\a\\");
    XL_TEST_ASSERT(PathNormalize(L"C:\\a") == L"C:\\a");
    XL_TEST_ASSERT(PathNormalize(L"C:\\") == L"C:\\");
    XL_TEST_ASSERT(PathNormalize(L"C:") == L"C:\\");
    XL_TEST_ASSERT(PathNormalize(L"C") == L"C");

    XL_TEST_ASSERT(PathNormalize(L"C:\\a\\b\\..\\") == L"C:\\a\\");
    XL_TEST_ASSERT(PathNormalize(L"C:\\a\\b\\..") == L"C:\\a");
    XL_TEST_ASSERT(PathNormalize(L"C:\\a\\..\\") == L"C:\\");
    XL_TEST_ASSERT(PathNormalize(L"C:\\a\\..") == L"C:\\");
    XL_TEST_ASSERT(PathNormalize(L"C:\\..\\") == L"C:\\");
    XL_TEST_ASSERT(PathNormalize(L"C:\\..") == L"C:\\");

    XL_TEST_ASSERT(PathNormalize(L"C:\\a\\.\\") == L"C:\\a\\");
    XL_TEST_ASSERT(PathNormalize(L"C:\\a\\.") == L"C:\\a");
    XL_TEST_ASSERT(PathNormalize(L"C:\\.\\") == L"C:\\");
    XL_TEST_ASSERT(PathNormalize(L"C:\\.") == L"C:\\");
}

XL_TEST_CASE()
{
    using namespace xl::Win32::File;

}

int main()
{
    xl::Win32::File::MakeDir(L"a\\b\\\\c");
    xl::Win32::File::RMDir(L"a");
    std::string s = "123";
    xl::Win32::File::SetContent(L"a.txt", s);
    std::string t = xl::Win32::File::GetContent(L"a.txt");
    s = "abc";
    xl::Win32::File::SetContent(L"a.txt", s);
    t = xl::Win32::File::GetContent(L"a.txt");
    s = "xyz";
    xl::Win32::File::SetContent(L"a.txt", s, true);
    t = xl::Win32::File::GetContent(L"a.txt");
    return 0;
}

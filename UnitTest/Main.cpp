#include "../External/xlUnitTest/UnitTest.h"
#include "../FilePath.h"
#include "../FileScanner.h"
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

    //CreateDirectory(L"a", NULL);
    //EnumFiles();
}

int main()
{
    CreateDirectoryW(L"a\\b\\c", NULL);
    return 0;
}

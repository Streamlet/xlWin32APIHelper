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

XL_NAMED_TEST_CASE(DirOps)
{
    using namespace xl::Win32::File;

    std::vector<std::wstring> files = GetFileList(L"a", L"*", 0);
    XL_TEST_ASSERT(files == std::vector<std::wstring>());

    MakeDir(L"a\\b1\\c1");
    MakeDir(L"a\\b1\\c2");
    MakeDir(L"a\\b2\\c3");
    SetContent(L"a\\b1\\c1\\d1.txt", "");

    files = GetFileList(L"a", L"*", 0);
    XL_TEST_ASSERT(files == std::vector<std::wstring>(
    {
        L"a\\b1",
        L"a\\b2",
    }));
    files = GetFileList(L"a", L"*", ENUM_RECURSIVELY);
    XL_TEST_ASSERT(files == std::vector<std::wstring>(
    {
        L"a\\b1",
        L"a\\b1\\c1",
        L"a\\b1\\c1\\d1.txt",
        L"a\\b1\\c2",
        L"a\\b2",
        L"a\\b2\\c3",
    }));
    files = GetFileList(L"a", L"*", ENUM_RECURSIVELY | ENUM_SUB_FIRST);
    XL_TEST_ASSERT(files == std::vector<std::wstring>(
    {
        L"a\\b1\\c1\\d1.txt",
        L"a\\b1\\c1",
        L"a\\b1\\c2",
        L"a\\b1",
        L"a\\b2\\c3",
        L"a\\b2",
    }));
    files = GetFileList(L"a", L"*", ENUM_RECURSIVELY | ENUM_NO_DIRECTORIES);
    XL_TEST_ASSERT(files == std::vector<std::wstring>(
    {
        L"a\\b1\\c1\\d1.txt",
    }));
    files = GetFileList(L"a", L"*", ENUM_RECURSIVELY | ENUM_NO_FILES);
    XL_TEST_ASSERT(files == std::vector<std::wstring>(
    {
        L"a\\b1",
        L"a\\b1\\c1",
        L"a\\b1\\c2",
        L"a\\b2",
        L"a\\b2\\c3",
    }));

    RMDir(L"a");

    files = GetFileList(L"a", L"*", 0);
    XL_TEST_ASSERT(files == std::vector<std::wstring>());
}

XL_NAMED_TEST_CASE(FileContent)
{
    using namespace xl::Win32::File;

    SetContent(L"a.txt", "123");
    XL_TEST_ASSERT(GetContent(L"a.txt") == "123");
    SetContent(L"a.txt", "abc");
    XL_TEST_ASSERT(GetContent(L"a.txt") == "abc");
    SetContent(L"a.txt", "xyz", true);
    XL_TEST_ASSERT(GetContent(L"a.txt") == "abcxyz");
    RMFile(L"a.txt");
    XL_TEST_ASSERT(GetContent(L"a.txt") == "");
}

int main()
{
    return 0;
}

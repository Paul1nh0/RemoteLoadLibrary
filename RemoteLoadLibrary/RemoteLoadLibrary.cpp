// RemoteLoadLibrary.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "RemoteLoadLibrary.h"

HMODULE LoadLibraryByRemoteServer(LPCWSTR lpLibPath, LPCWSTR lpUsername, LPCWSTR lpPassword)
{
    std::wstring strUserName;
    std::wstring strPassword;
    std::wstring strAddress;
    std::wstring strFile;

    strUserName = lpUsername;
    strPassword = lpPassword;
    strAddress = lpLibPath;
    strFile = lpLibPath;
    LPWSTR lpLocalName = (LPWSTR)TEXT("");
    LPWSTR lpComment = (LPWSTR)TEXT("");

    //The hwndOwner parameter can be NULL. 
    //If it is, a call to WNetAddConnection3 is equivalent
    //to calling the WNetAddConnection2 function.


    //The WNetUseConnection function is similar to the WNetAddConnection3 function.
    //The main difference is that WNetUseConnection can automatically select
    //an unused local device to redirect to the network resource.
    NETRESOURCE nr = {};
    nr.dwUsage = RESOURCE_CONNECTED;
    nr.dwType = RESOURCETYPE_ANY;
    nr.dwDisplayType = RESOURCEDISPLAYTYPE_DIRECTORY;
    nr.dwUsage = 0;
    nr.lpComment = lpComment;
    nr.lpLocalName = lpLocalName;  //映射成本地驱动器
    nr.lpProvider = NULL;
    nr.lpRemoteName = (LPWSTR)strAddress.c_str(); 

    DWORD dwFlag = CONNECT_UPDATE_PROFILE;
    WNetAddConnection3(NULL, &nr, strPassword.c_str(), strUserName.c_str(), dwFlag);

    /*KernelOpenFile(strFile.c_str());*/
    HANDLE hFile = CreateFile(strFile.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return NULL;
    }

    CloseHandle(hFile);

    return LoadLibrary(strFile.c_str());
}

BOOL FreeLibraryByRemoteServer(HMODULE hRemoteLib)
{
    return FreeLibrary(hRemoteLib);
}

#ifdef One
void main()
{
    HMODULE hMod = LoadLibraryByRemoteServer(L"\\\\192.168.138.128\\Winobj\\test.dll", L"Test", L"123456");
}
#endif

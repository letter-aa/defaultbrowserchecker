#include <Windows.h>
#include <iostream>

using namespace std;

LSTATUS RegViewKeyData(HKEY hKey, string key, LPCWSTR lpSubKey, TCHAR * &result) {
    HKEY phkey;
    LONG regKeyParent = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &phkey);
    if (regKeyParent == ERROR_SUCCESS) {
        wstring wideKey = L"" + wstring(key.begin(), key.end()); //hmmmmmmm ok
        TCHAR lpb[255];
        DWORD lpd = sizeof(lpb);
        LONG regKey = RegQueryValueEx(phkey, wideKey.c_str(), NULL, NULL, (LPBYTE)lpb, &lpd);
        result = new TCHAR[lpd];
        memcpy(result, lpb, lpd);
        RegCloseKey(phkey);
        return 0 && ERROR_SUCCESS;
    }
    else {
        //ERROR_FILE_NOT_FOUND
        return 1 && ERROR_FILE_NOT_FOUND;
    }
}
int main()
{
    TCHAR * result;
    int ok = RegViewKeyData(HKEY_CURRENT_USER,"ProgID",L"Software\\Microsoft\\Windows\\Shell\\Associations\\UrlAssociations\\https\\UserChoice", result);
    wstring preRes;
    //string * resultConv = reinterpret_cast<string *>(result);
    if (wcscmp(result, L"MSEdgeHTM") == 0) {
        preRes = L"Microsoft Edge";
    }
    else if (wcscmp(result, L"ChromeHTML") == 0) {
        preRes = L"Google Chrome";
    }
    else if (wcscmp(result, L"FirefoxHTML") == 0) {
        preRes = L"Firefox";
    }
    else if (wcscmp(wstring(result).substr(0, 8).c_str(), L"Opera GX") == 0) {
        preRes = L"Opera GX";
    }
    else {
        preRes = L"idk lol";
    }    
    wstring result2 = L"Your default browser is " + preRes;
    MessageBox(NULL, result2.c_str(), TEXT("the default browser checker"), NULL);
}


#include <Windows.h>
#include <ShObjIdl.h>

#include <atlbase.h>
#include <string>

#include "FileManager.h"

std::wstring openDialog() {
    std::wstring filePath;
    //std::wstring filePath;
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr)) {
        IFileOpenDialog *pFileOpen;

        // Create the FileOpenDialog object
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
        if (SUCCEEDED(hr)) {
            LPCWSTR title = L"Select game";
            pFileOpen->SetTitle(title);
            COMDLG_FILTERSPEC rgSpec[] =
            {
                { L"All GameBoy types", L"*.gb; *.gbc" },
                { L"GameBoy", L"*.gb" },
                { L"GameBoy Color", L"*.gbc" },
                { L"All Files", L"*.*" }
            };

            pFileOpen->SetFileTypes(4, rgSpec);

            // Show the Open dialog box
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box
            if (SUCCEEDED(hr)) {
                IShellItem *pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr)) {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    // Display the file name to the user
                    if (SUCCEEDED(hr)) {
                        //MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
                        //USES_CONVERSION;
                        //filePath = T2CA(pszFilePath);
                        filePath = pszFilePath;
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }

    return filePath;
}

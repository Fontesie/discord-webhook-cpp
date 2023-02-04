#include <Windows.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")

int main() {
    HINTERNET hSession = WinHttpOpen(L"Fontesie/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    HINTERNET hConnect = WinHttpConnect(hSession,
        L"discordapp.com",
        INTERNET_DEFAULT_HTTPS_PORT,
        0);

    HINTERNET hRequest = WinHttpOpenRequest(hConnect,
        L"POST",
        L"/api/webhooks/webhook-id/webhook-token",
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE);

    std::string title = "Title";
    std::string desc = "Description";
    std::string color = "16711680"; // Decimal color
    std::string founderid = "854037287716651108";
    std::string request_body = "{\"username\": \"github.com/Fontesie\",\"content\": null,\"embeds\": [{\"title\": \"" + title + "\",\"description\": \"" + desc + "\",\"footer\": {\"text\": \"github.com/fontesie\"},\"color\": " + color + " }], \"attachments\": []}";

    BOOL bResults = WinHttpSendRequest(hRequest,
        L"Content-Type: application/json\r\n",
        (DWORD)-1L,
        (LPVOID)request_body.c_str(),
        (DWORD)request_body.length(),
        (DWORD)request_body.length(),
        0);

    if (bResults) {
        WinHttpReceiveResponse(hRequest, NULL);
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return 0;
}

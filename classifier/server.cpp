#include<bits/stdc++.h>
#include<Windows.h>
#define BUF_SIZE 65535
#define EXAMP_PIPE   "\\\\.\\pipe\\AlbumPipe"
// 定义管道名 , 如果是跨网络通信 , 则在圆点处指定服务器端程序所在的主机名
using namespace std;
int main(){
    HANDLE hPipe = NULL;
    hPipe = CreateNamedPipe(
        EXAMP_PIPE,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE |
        PIPE_READMODE_MESSAGE |
        PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        BUF_SIZE,
        BUF_SIZE,
        0,
        NULL);

    if (hPipe==INVALID_HANDLE_VALUE)
    {
        cout<<"Create Read Pipe Error";
        return FALSE;
    }

    if (!ConnectNamedPipe(hPipe, NULL))
    {
        cout<<"Connect Failed";
        return FALSE;
    }





    DWORD dwReturn = 0;
    char szBuffer[BUF_SIZE] = {0};
    for(int i=0;i<200;++i){
        // printf("sended");
        // 读取客户端数据
        memset(szBuffer, 0, BUF_SIZE);
        if (ReadFile(hPipe,szBuffer,BUF_SIZE,&dwReturn,NULL))
        {
            szBuffer[dwReturn] = '\0';
            cout<<"receive msg:"<<szBuffer<<endl;
        }
        else
        {
            cout<<"Read Failed";
        }

    }
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    return 0;
}
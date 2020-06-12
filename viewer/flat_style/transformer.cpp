#include "transformer.h"
#include "widget.h"
#include "ui_widget.h"
#include "Python.h"
#include<QKeyEvent>
#include<QImage>
#include<QDebug>
#include<iostream>
#include<Windows.h>


Transformer::Transformer()
{

}
int Transformer::classifier(){
    clock_t beg=clock();

    PyObject* classifierModule=PyImport_ImportModule("classifier");
    PyObject* classifyFunction=PyObject_GetAttrString(classifierModule,"eval");
    PyObject* args=Py_BuildValue("({s:i,s:s,s:s})","batch_size",1,"test_data_root","D:/magicAlbum/sharePool/poster","load_model_path","D:/magicAlbum/classifier/checkpoints/SimpleNet_0609_23_48_04.ckpt");
    PyObject* pTag=PyObject_CallObject(classifyFunction,args);
    long tag=PyLong_AsLong(pTag);
    Py_DecRef(pTag);
    Py_DecRef(args);
    //classify

    qDebug()<<tag<<"classify img"<<clock()-beg;
    beg=clock();

    return static_cast<int>(tag);
}
TCHAR *CharToWchar(const QString &str)
{
QByteArray ba = str.toUtf8();
char *data = ba.data(); //以上两步不能直接简化为“char *data = str.toUtf8().data();”
int charLen = strlen(data);
int len = MultiByteToWideChar(CP_ACP, 0, data, charLen, NULL, 0);
TCHAR *buf = new TCHAR[len + 1];
MultiByteToWideChar(CP_ACP, 0, data, charLen, buf, len);
buf[len] = '\0';
return buf;
}
void Transformer::transform(QString path){
    info.setFile(path);
    QString baseName=info.baseName();
    QString fileName=info.fileName();
    QString dirName="D:/magicAlbum/warehouse";

    STARTUPINFO stStartUpInfo;
    ::memset(&stStartUpInfo, 0 ,sizeof(stStartUpInfo));
    stStartUpInfo.cb = sizeof(stStartUpInfo);

    PROCESS_INFORMATION stProcessInfo;
    ::memset(&stProcessInfo, 0 ,sizeof(stProcessInfo));

    TCHAR szPath[]=L"D:/anaconda/envs/t031/pythonw.exe";
    QString cmd=" D:/magicAlbum/transformer/main.py ";
    cmd = cmd + dirName +" ";
    cmd = cmd + baseName + " ";
    cmd = cmd + fileName + " ";
    cmd = cmd + "6" + " ";

    TCHAR* szCmd=CharToWchar(cmd);   //lpCommandLine的内容中开头需要一个空格，不然就和lpApplicationName连在一起去了

    bool bRet = ::CreateProcess(
        szPath,
        szCmd,
        NULL,
        NULL,
        false,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &stStartUpInfo,
        &stProcessInfo);

    if (bRet)
    {
        ::CloseHandle(stProcessInfo.hProcess);
        ::CloseHandle(stProcessInfo.hThread);
        stProcessInfo.hProcess = NULL;
        stProcessInfo.hThread = NULL;
        stProcessInfo.dwProcessId = 0;
        stProcessInfo.dwThreadId = 0;
    }
    else
    {
        //如果创建进程失败，查看错误码
        DWORD dwErrCode = GetLastError();
        printf_s("ErrCode : %d\n",dwErrCode);

    }
}

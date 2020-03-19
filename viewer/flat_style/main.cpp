#include <QApplication>
#include "widget.h"
#include <Python.h>

int main(int argc, char *argv[])
{
    ////初始化Python环境
    Py_SetPythonHome((const wchar_t *)(L"D:/anaconda/envs/t031"));
    Py_Initialize();
    PyRun_SimpleString("import sys");
    //加入python文件路径
    PyRun_SimpleString("sys.path.append('D:/magicAlbum/classifier')");

    QApplication a(argc, argv);
    Widget w;
    a.exec();


    Py_Finalize();
    return 0;
}

#include <QApplication>
#include "widget.h"
#include <Python.h>
#define PYTHONENV L"D:/anaconda/envs/t031"
#define CLASSIFIERPATH "sys.path.append('D:/magicAlbum/classifier')"

int main(int argc, char *argv[])
{
    ////初始化Python环境
    Py_SetPythonHome(static_cast<const wchar_t*>(PYTHONENV));
    Py_Initialize();
    PyRun_SimpleString("import sys");
    //加入python文件路径
    PyRun_SimpleString(CLASSIFIERPATH);

    QApplication a(argc, argv);
    Widget w;
    a.exec();


    Py_Finalize();
    return 0;
}

#include "transformer.h"
#include "widget.h"
#include "ui_widget.h"
#include "Python.h"
#include<QKeyEvent>
#include<QImage>
#include<QDebug>
#include<iostream>


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
void Transformer::transform(QString path){
    info.setFile(path);
    QString dirName=info.dir().path();
    QString baseName=info.baseName();
    QString fileName=info.fileName();
    QString srcName=dirName+"/src";
    QString targetName=dirName+"/target";
    QString resultName=dirName+"/result.gif";
    dir.setPath(dirName);
    QString headName=dir.absoluteFilePath("head.png");

    clock_t beg=clock();
    PyObject* cutterModule=PyImport_ImportModule("cutter");
    PyObject* cutFunction=PyObject_GetAttrString(cutterModule,"cut");
    PyObject* args=Py_BuildValue("(ss)",path.toStdString().c_str(),headName.toStdString().c_str());
    PyObject* pTuple=PyObject_CallObject(cutFunction,args);
    int left,top;
    PyArg_ParseTuple(pTuple,"ii",&left,&top);
    Py_DecRef(args);
    Py_DecRef(pTuple);
    //cutter

    qDebug()<<"cut img"<<clock()-beg;
    beg=clock();

    PyObject* transformerModule=PyImport_ImportModule("transformer");
    PyObject* transformeFunction=PyObject_GetAttrString(transformerModule,"transform");
    dir.mkdir(srcName);
    qDebug()<<srcName<<" "<<headName;
    args=Py_BuildValue("(ss)",headName.toStdString().c_str(),srcName.toStdString().c_str());
    PyObject_CallObject(transformeFunction,args);
    Py_DecRef(args);
    //transformer

    qDebug()<<"transform img"<<clock()-beg;
    beg=clock();

    int num=6;
    dir.mkdir(targetName);
    PyObject* rebuilderModule=PyImport_ImportModule("rebuilder");
    PyObject* rebuildFunction=PyObject_GetAttrString(rebuilderModule,"rebuild");
    args=Py_BuildValue("(iiisss)",num,left,top,path.toStdString().c_str(),srcName.toStdString().c_str(),targetName.toStdString().c_str());
    PyObject_CallObject(rebuildFunction,args);
    Py_DecRef(args);
    //rebuilder

    qDebug()<<"rebuild img"<<clock()-beg;
    beg=clock();

    PyObject* combinerModule=PyImport_ImportModule("combiner");
    PyObject* combineFunction=PyObject_GetAttrString(combinerModule,"combine");
    args=Py_BuildValue("(iss)",num,targetName.toStdString().c_str(),resultName.toStdString().c_str());
    PyObject* pRet=PyObject_CallObject(combineFunction,args);
    Py_DecRef(args);
    int ret=PyLong_AsLong(pRet);
    qDebug()<<ret;
    Py_DecRef(pRet);
    //combiner
    qDebug()<<"combine img"<<clock()-beg;
    beg=clock();
}

﻿#include <QCoreApplication>
#include <server.h>
//#include <Windows.h>
//#include <DbgHelp.h>

//static LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
//{
//    //And output crash information
//    EXCEPTION_RECORD *record = pException->ExceptionRecord;
//    QString errCode(QString::number(record->ExceptionCode, 16));
//    QString errAddr(QString::number((uint)record->ExceptionAddress, 16));
//    QString errFlag(QString::number(record->ExceptionFlags, 16));
//    QString errPara(QString::number(record->NumberParameters, 16));
//    qDebug()<<"errCode: "<<errCode;
//    qDebug()<<"errAddr: "<<errAddr;
//    qDebug()<<"errFlag: "<<errFlag;
//    qDebug()<<"errPara: "<<errPara;
//    //Create the dump file
//    HANDLE hDumpFile = CreateFile((LPCWSTR)QString("crash.dmp").utf16(),
//             GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//    if(hDumpFile != INVALID_HANDLE_VALUE) {
//        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
//        dumpInfo.ExceptionPointers = pException;
//        dumpInfo.ThreadId = GetCurrentThreadId();
//        dumpInfo.ClientPointers = TRUE;
//        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
//        CloseHandle(hDumpFile);
//    }
//    return EXCEPTION_EXECUTE_HANDLER;
//}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    Server* server = new Server();
    if(server->StartServer() == false)
        delete server;
    return a.exec();
}

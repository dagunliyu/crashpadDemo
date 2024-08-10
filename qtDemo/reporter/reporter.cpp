/*
 *  Copyright (C) 2016 Alexander Makarov
 *
 * This file is a part of Breakpad-qt library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#include "reporter.h"
#include "ui_reporter.h"

#include <QTimer>
#include <QDir>
#include <QDateTime>
//#include "QBreakpadHandler.h"
#include "../program/TestThread.h"

#include "client/crash_report_database.h"
#include "client/crashpad_client.h"
#include "client/settings.h"
#include "base/files/file_path.h" //! mini_chromium
#include "../../crashpadLocalHandler.h"
#include <crashpadHandler.h>
#include "qlogging.h"



bool checkPath(const QString& path, QString& absPath)
{
	absPath = path;
	if (!QDir::isAbsolutePath(absPath))
	{
		absPath = QDir::cleanPath(qApp->applicationDirPath() + "/" + path);
	}
	Q_ASSERT(QDir::isAbsolutePath(absPath));

	QDir().mkpath(absPath);
	if (!QDir().exists(absPath))
	{
		qDebug("Failed to set dump path which not exists: %s", qPrintable(absPath));
		return false;
	}
	return true;
}

QStringList dumpFileList()
{
	//if (!d->dumpPath.isNull() && !d->dumpPath.isEmpty())
	//{
	//	QDir dumpDir(d->dumpPath);
	//	dumpDir.setNameFilters(QStringList() << "*.dmp");
	//	return dumpDir.entryList();
	//}

	return QStringList();
}

int main (int argc, char *argv[])
{
    QApplication app (argc, argv);

    QCoreApplication::setApplicationName("crashpad-ReporterExample");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCoreApplication::setOrganizationName("OrgName");
    QCoreApplication::setOrganizationDomain("name.org");

//    // Set directory to store dumps and url to upload
//    //QBreakpadInstance.setDumpPath("crashes");
//	QBreakpadInstance.setCrashGenClient("C:\\dumps\\");
//
//    // Set server type for uploading
//#if defined(SOCORRO)
//    QBreakpadInstance.setUploadUrl(QUrl("http://[your.site.com]/submit"));
//#elif defined(CALIPER)
//    QBreakpadInstance.setUploadUrl(QUrl("http://[your.site.com]/crash_upload"));
//#else
//    QBreakpadInstance.setUploadUrl(QUrl("http://110.242.68.3/"));
//#endif

#if 1
	QString appDirPath = QCoreApplication::applicationDirPath();
	QString dbPath = appDirPath + "/database";
	QString dmpPath = appDirPath + "/database/reports";//+ "/database/reports";
	QString handlerPath = "D:/Projects/Proj_Basic_proj/build_cp/cp_cxx14/crashpad/x64/release/crashpad_handler.exe";
	std::string appDir = appDirPath.toStdString();
	std::string dmpDir = appDir + "/database/reports";
	std::wstring dbDir = dbPath.toStdWString(); 
	std::wstring handlerDir = handlerPath.toStdWString();


	crashpadInstance.setDBPath(dbDir)
		->setHandlerPath(handlerDir)
		->setDumpPath(dmpDir)
		->setUploadUrl("http://192.168.24.32:18080/upload_mini_dump")
		->initCrashpad();

#else
    crashpadHandlerBuilder cphBuilder;

	QString appDirPath = QCoreApplication::applicationDirPath();
	//qDebug() << appDirPath;
    QString dbPath = appDirPath+ "/database";
	QString dmpPath = appDirPath + "/database/reports";//+ "/database/reports";
    //QString handlerPath = appDirPath + "/crashpad_handler.exe";
    QString handlerPath = "D:/Projects/Proj_Basic_proj/build_cp/cp_cxx14/crashpad/x64/release/crashpad_handler.exe";
        //"D:/Projects/Proj_Coding_Alog_Interview_Recruit/Proj_Basic_proj/build_crashpad/crashpad_depot2/crashpad/x64/debug/crashpad_handler.exe";

    //! gen reports dir through CrashReportDatabase::Init
    cphBuilder.setDBPath(dbPath)->setHandlerPath(handlerPath)
        ->setDumpPath(dmpPath)->setUploadUrl(QUrl("http://192.168.24.32:18080/upload_mini_dump"));
    
    //http://192.168.24.32:18080/submit
    //"http://localhost:18080/submit"
    //crashpadInstance.setDBPath(dbPath);
    //crashpadInstance.setHandlerPath(handlerPath);
    //crashpadInstance.setDumpPath(dbPath);
    //crashpadInstance.setUploadUrl(QUrl("http://127.0.0.1:8000"));

    crashpadLocalInstance.initCrashpad();

#endif

    // Create the dialog and show it
    crashPadReporterExample example;
    example.show();

    // Run the app
    return app.exec();
}

crashPadReporterExample::crashPadReporterExample (QWidget *parent) :
    QDialog (parent),
    ui (new Ui::crashPadReporterExample)
{
    // Create and configure the user interface
    ui->setupUi (this);
    this->setWindowTitle("crashpad_client_Test (crashpad v."+ crashpadLocalHandler::version()+")");
    ui->urlLineEdit->setText(crashpadLocalInstance.uploadUrl());

    ui->dumpFilesTextEdit->appendPlainText(crashpadLocalInstance.dumpFileList().join("\n"));

    // Force crash app when the close button is clicked
    connect (ui->crashButton, SIGNAL (clicked()),
             this,              SLOT (crash()));

	connect(ui->crashInThreadButton, SIGNAL(clicked()),
		this, SLOT(crashInThread()));
    
    // upload dumps when the updates button is clicked
    connect (ui->uploadButton, SIGNAL (clicked()),
             this,               SLOT (uploadDumps()));
}

crashPadReporterExample::~crashPadReporterExample()
{
    delete ui;
}

void DerefZeroCrash() {
	int* x = 0;
	*x = 1;
}

void crashPadReporterExample::crash()
{
#if 0
	qsrand(QDateTime::currentDateTime().toTime_t());
	TestThread t1(false, qrand());
	TestThread t2(true, qrand());

	t1.start();
	t2.start();

	QTimer::singleShot(3000, qApp, SLOT(quit()));
#else
	DerefZeroCrash();
#endif

}

void crashPadReporterExample::crashInThread()
{
	qsrand(QDateTime::currentDateTime().toTime_t());
	TestThread t1(false, qrand());
	TestThread t2(true, qrand());

	t1.start();
	t2.start();

	QTimer::singleShot(3000, qApp, SLOT(quit()));
}

void crashPadReporterExample::uploadDumps()
{
    //QUrl url;
    //url.setUrl("http://127.0.0.1:8000/crash_upload/");
	//QBreakpadInstance.setUploadUrl(url);

	//QBreakpadInstance.setUploadUrl(QUrl("http://110.242.68.3/"));
	//QBreakpadInstance.setUploadUrl(QUrl("http://127.0.0.1:8000/"));
 //   QBreakpadInstance.sendDumps();
}

//! ftp autotest@172.30.100.34
//! /ÁÙÊ±Ä¿Â¼/lhc
//172.30.100.34:21
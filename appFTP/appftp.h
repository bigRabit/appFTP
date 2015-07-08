#ifndef APPFTP_H
#define APPFTP_H

#include <QtGui/QWidget>
#include "ui_appftp.h"
#include <QLabel>
#include <QLineEdit>
#include <QTreeWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QtGui>
#include <QFtp>
#include <QUrlInfo>
#include <QDebug>


class appFTP : public QWidget
{
	Q_OBJECT

public:
	appFTP(QWidget *parent = 0, Qt::WFlags flags = 0);
	~appFTP();

private:
	Ui::appFTPClass ui;
	QLabel *serverLabel;
	QLineEdit *lineEdit;
	QPushButton *connectButton;
	QTreeWidget *treeWidget;
	QLabel *statusLabel;
	QProgressBar *progressBar;
	QPushButton	*downloadButton;
	QPushButton *quitButton;
	QPushButton *refreshButton;
	
	QHash<QString,bool> isDirectory;
	QString currentPath;
	QFile *file;
	QFtp *ftp;

private slots:
	void quitButtonClicked();
	void downloadButtonClicked();
	void connectButtonClicked();
	void ftpCommandFinished(int,bool);
	void ftpCommandStarted(int);
	void updateDataTransferProgress(qint64,qint64);
	void addToList(const QUrlInfo &urlInfo);
	void processItem(QTreeWidgetItem *item, int column);
	void refreshButtonClicked();
	//void processItem(QTreeWidgetItem*,int);
};

#endif // APPFTP_H

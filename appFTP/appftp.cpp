#include "appftp.h"

//test add a feature

appFTP::appFTP(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	serverLabel = new QLabel(tr("Ftp server IP : "));
	lineEdit = new QLineEdit();
	connectButton = new QPushButton(tr("Connect"));
	
	treeWidget = new QTreeWidget(this);
    treeWidget->setEnabled(false);
    treeWidget->setRootIsDecorated(false);
    treeWidget->setHeaderLabels(QStringList() << tr("Name") << tr("Size") << tr("Owner") << tr("Group") << tr("Time"));
    //treeWidget->header()->setStretchLastSection(false);

	statusLabel = new QLabel(this);
	
	progressBar = new QProgressBar(this);
	progressBar->setValue(0);

	downloadButton = new QPushButton(tr("Download"));
	quitButton = new QPushButton(tr("Quit"));
	refreshButton = new QPushButton(tr("Refresh"));

	QHBoxLayout *hBox1 = new QHBoxLayout();
	QHBoxLayout *hBox2 = new QHBoxLayout();
	QVBoxLayout *vBox = new QVBoxLayout();

	hBox1->addWidget(serverLabel);
	hBox1->addWidget(lineEdit);
	hBox1->addWidget(connectButton);
	hBox1->addWidget(refreshButton);

	hBox2->addWidget(progressBar);
	hBox2->addWidget(downloadButton);
	hBox2->addWidget(quitButton);

	vBox->addLayout(hBox1);
	vBox->addWidget(treeWidget);
	vBox->addWidget(statusLabel);
	vBox->addLayout(hBox2);

	setLayout(vBox);

	connect(quitButton,SIGNAL(clicked()),this,SLOT(quitButtonClicked()));
	connect(connectButton,SIGNAL(clicked()),this,SLOT(connectButtonClicked()));
	//connect(treeWidget,SIGNAL(itemActivated(QTreeWidgetItem*,int)),this,SLOT(processItem(QTreeWidget*,int)))
	connect(downloadButton,SIGNAL(clicked()),this,SLOT(downloadButtonClicked()));
	connect(treeWidget,SIGNAL(itemActivated(QTreeWidgetItem *, int)),this, SLOT(processItem(QTreeWidgetItem *, int)));
	connect(refreshButton,SIGNAL(clicked()),this,SLOT(refreshButtonClicked()));
}

appFTP::~appFTP()
{

}

void appFTP::quitButtonClicked()
{
	close();
}

void appFTP::connectButtonClicked()
{
	treeWidget->clear();
	currentPath.clear();
	isDirectory.clear();
	
	ftp = new QFtp(this);

	//QString ftpServer = lineEdit->text();
	QString ftpServer = QString("192.168.1.119");
	QString userName = QString("Root");
	QString passWord = QString("toor");

	//ftp->connectToHost(ftpServer,21);
	//ftp->login(userName,passWord);

	QUrl url("192.168.1.119");
    if (!url.isValid() || url.scheme().toLower() != QLatin1String("ftp")) {
         ftp->connectToHost(ftpServer, 21);
         ftp->login(userName,passWord);
     } else {
         ftp->connectToHost(url.host(), url.port(21));

         if (!url.userName().isEmpty())
             ftp->login(QUrl::fromPercentEncoding(url.userName().toLatin1()), url.password());
         else
             ftp->login(userName,passWord);
         if (!url.path().isEmpty())
             ftp->cd(url.path());
     }


	connect(ftp,SIGNAL(commandStarted(int,bool)),this,SLOT(ftpCommandStarted(int)));
	connect(ftp,SIGNAL(commandFinished(int,bool)),this,SLOT(ftpCommandFinished(int,bool)));
    connect(ftp,SIGNAL(listInfo(const QUrlInfo &)),this,SLOT(addToList(const QUrlInfo &)));
	connect(ftp,SIGNAL(dataTransferProgress(qint64,qint64)),this,SLOT(updateDataTransferProgress(qint64,qint64)));
}

void appFTP::ftpCommandStarted(int)
{
	if(ftp->currentCommand() == QFtp::ConnectToHost)
	{
		statusLabel->setText(tr("Connecting to the server..."));
	}
	if(ftp->currentCommand() == QFtp::Login)
	{
		statusLabel->setText(tr("Logining Now..."));
	}
	if(ftp->currentCommand() == QFtp::Get)
	{
		statusLabel->setText(tr("Downloading Now..."));		
	}
	if(ftp->currentCommand() == QFtp::Close)
	{
		statusLabel->setText(tr("Closing the connection..."));
	}
}	

void appFTP::ftpCommandFinished(int,bool error)
{
    if(ftp->currentCommand() == QFtp::ConnectToHost)
    {
       if(error)
           statusLabel->setText(tr("Connecting error:")
                               .arg(ftp->errorString()));
       else statusLabel->setText(tr("Connecting successful !"));
    }
    
    if (ftp->currentCommand() == QFtp::Login)
    {
       if(error)
		   statusLabel->setText(tr("Logining error:")
                               .arg(ftp->errorString()));
       else 
       	{
       		statusLabel->setText(tr("Login succsessful !"));
       		ftp->list();
       	}
    }
    
    if (ftp->currentCommand() == QFtp::Get)
    {
       if(error)
		   statusLabel->setText(tr("Downloading error:")
                               .arg(ftp->errorString()));
       else {
           statusLabel->setText(tr("Download succsessful !"));
           //ui->textBrowser->setText(ftp->readAll());
           downloadButton->setEnabled(true);
           file->close();
           delete file;
       }
    }
    else if (ftp->currentCommand() == QFtp::Close){
       statusLabel->setText(tr("Close the connection ."));
    }
    
    if(ftp->currentCommand() == QFtp::List)
    {
    	if(isDirectory.isEmpty())
    	{
    		treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList()<< tr("<empty>")));
    		treeWidget->setEnabled(false);
    		statusLabel->setText(tr("the directory is empty ."));
    	}
    }
}

void appFTP::addToList(const QUrlInfo& urlInfo)
{
	QTreeWidgetItem *item = new QTreeWidgetItem;
	item->setText(0,urlInfo.name());
	item->setText(1,QString::number(urlInfo.size()));
	item->setText(2,urlInfo.owner());
	item->setText(3,urlInfo.group());
	item->setText(4,urlInfo.lastModified().toString("MMM dd yyyy"));

	isDirectory[urlInfo.name()] = urlInfo.isDir();

	treeWidget->addTopLevelItem(item);

	if(!treeWidget->currentItem())
	{
		treeWidget->setCurrentItem(treeWidget->topLevelItem(0));
		treeWidget->setEnabled(true);
	}
}

void appFTP::downloadButtonClicked()
{
	QString fileName = treeWidget->currentItem()->text(0);
	file = new QFile(fileName);
	
	if(!file->open(QIODevice::WriteOnly))
	{
		delete file;
		return;
	}

	downloadButton->setEnabled(false);
	ftp->get(treeWidget->currentItem()->text(0),file);
}

void appFTP::updateDataTransferProgress(qint64 readBytes,qint64 totalBytes)
{
	progressBar->setMaximum(totalBytes);
	progressBar->setValue(readBytes);
}

 void appFTP::processItem(QTreeWidgetItem *item, int /*column*/)
 {
     QString name = item->text(0);
     if (isDirectory.value(name)) {
         treeWidget->clear();
         isDirectory.clear();
         currentPath += "/" + name;
         ftp->cd(name);
         ftp->list();
         //cdToParentButton->setEnabled(true);
 #ifndef QT_NO_CURSOR
         setCursor(Qt::WaitCursor);
 #endif
         return;
     }
 }

 void appFTP::refreshButtonClicked()
 {
 	treeWidget->clear();
 	ftp->list();
 	//connect(ftp,SIGNAL(listInfo(const QUrlInfo &)),this,SLOT(addToList(const QUrlInfo &)));
 }
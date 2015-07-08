#include <QtGui/QApplication>
#include "appftp.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	appFTP w;
	w.show();
	return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget mainshow;
    mainshow.setWindowFlags(Qt::FramelessWindowHint );
    mainshow.setObjectName("mainshow");

    TitleBar *pTitleBar = new TitleBar(&mainshow);

    mainshow.installEventFilter(pTitleBar);

    MainWindow w;
    w.setParent(&mainshow);

    QVBoxLayout *pLayout = new QVBoxLayout(&mainshow);
    pLayout->addWidget(pTitleBar);
    pLayout->addWidget(&w);
    //pLayout->addStretch();//伸缩器
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    mainshow.setLayout(pLayout);

    mainshow.setWindowTitle("<h3><font color=gray>File Locker</font></h3>");//使用html格式
    QIcon icon(":/new/pic/mainicon.ico");
    mainshow.setWindowIcon(icon);
    //zhu.setGeometry(QApplication::desktop()->width()/2-260,QApplication::desktop()->height()/2-195,520,390);
    mainshow.show();
    //w.show();

    return a.exec();
}

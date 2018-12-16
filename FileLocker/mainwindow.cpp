#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Setupshowmodel(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Setupshowmodel(int i)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//自定义标题栏 挡菜单
    this->setWindowFlags(Qt::Widget);
    //ui->mainToolBar->setStyleSheet("background-color: rgb(170, 255, 255);border-color: rgb(170, 255, 255)");
    QFile qssFile;
    switch(i)
    {
        case 1://white
        {
            qssFile.setFileName(":new/qssf/firstqss.qss");
            break;
        }
        case 2:
        {
            qssFile.setFileName(":new/qssf/secondqss.qss");
            break;
        }
        case 3:
        {
            qssFile.setFileName(":new/qssf/thirdqss.qss");
            break;
        }
        case 4:
        {
            qssFile.setFileName(":new/qssf/forthqss.qss");
            break;
        }
        case 5:
        {
            qssFile.setFileName(":new/qssf/fifthqss.qss");
            break;
        }
        default:
        {
            qssFile.setFileName(":new/qssf/firstqss.qss");
            break;
        }
    }

    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        QString aqss = QString(qssFile.readAll());
        qApp->setStyleSheet(aqss);
        qssFile.close();
    }
}

void MainWindow::on_pushButton_3_clicked()//生成随机密钥，hex 显示
{
    QString input = ui->textEdit_3->toPlainText();
    bool flag;
    int sum = input.toInt(&flag,10);
    if(flag)//成功获取输入的 十进制数字
    {
        QByteArray key;
        key.resize(sum);
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);//srand设定rand要用的种子
        for (int i = 0;i < sum;i++)
        {
            int n = qrand() % 255;
            key[i] = n;
        }
        QString res = key.toHex().data();
        res = res.toUpper();
        ui->textEdit_3->setText(res);
    }
    else
    {
        QMessageBox::critical(0, QStringLiteral("输入有误"),QStringLiteral("输入的文本不是合法的十进制数字！ "), QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_5_clicked()//读取key文件 以十六进制看待
{
    QString path = QFileDialog::getOpenFileName(this,QStringLiteral("导入key文件"),"","KEY(*.zkey);;ALL(*.*)");
    if(path.isEmpty())
    {
        return;
    }
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(0, QStringLiteral("出错"),QStringLiteral("读取key文件出错。 "), QMessageBox::Ok);
        return;
    }

    QByteArray resl = file.readAll();
    file.close();
    QString hextmp = resl.toHex().data();
    hextmp = hextmp.toUpper();
    //qDebug()<<"set text start"<<QDateTime::currentDateTime().toString("yyyyMMddhhmmss")<<endl;
    ui->textEdit_3->setText(hextmp);//显示文本 太费时  大文本时太慢 是阻塞的。
    //qDebug()<<"set test over"<<QDateTime::currentDateTime().toString("yyyyMMddhhmmss")<<endl;
}

void MainWindow::on_pushButton_4_clicked()//存储key文件
{
    QString path = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("存为key文件"),"","KEY(*.zkey);;ALL(*.*)");
    if(path.isEmpty())
    {
        return;
    }
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(0, QStringLiteral("出错"),QStringLiteral("写入key文件出错。 "), QMessageBox::Ok);
        return;
    }

    QString str = ui->textEdit_3->toPlainText();
    if(str.isEmpty())
    {
        file.close();
        QMessageBox::critical(0, QStringLiteral("出错"),QStringLiteral("key内容为空。 "), QMessageBox::Ok);
        return;
    }
    str.remove(QRegExp("\\s"));//移除所有分隔字节的空格

    QByteArray resl = QByteArray::fromHex(str.toLocal8Bit());
    if(resl.isEmpty())
    {
        file.close();
        QMessageBox::critical(0, QStringLiteral("出错"),QStringLiteral("输入有误，输入的可能不是16进制数据。 "), QMessageBox::Ok);
        return;
    }

    file.write(resl);
    file.close();
}

void MainWindow::on_pushButton_11_clicked()//原文存储结果
{
    QString path = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("存储结果文件"),"","ENCRYPT(*.zencrypt);;ALL(*.*)");
    if(path.isEmpty())
    {
        return;
    }
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(0, QStringLiteral("出错"),QStringLiteral("写入文件出错。 "), QMessageBox::Ok);
        return;
    }

    QByteArray source;//可能hex 可能文本
    if(ui->radioButton_2->isChecked())
    {
        QString sortmp = ui->textEdit->toPlainText();//hex空格分 string
        sortmp.remove(QRegExp("\\s"));//移除所有空格
        source = QByteArray::fromHex(sortmp.toLocal8Bit());
    }
    else
    {
        source = ui->textEdit->toPlainText().toLocal8Bit();
    }

    if(source.isEmpty())
    {
        file.close();
        QMessageBox::critical(0, QStringLiteral("出错"),QStringLiteral("数据有误，数据可能不是16进制数据。 "), QMessageBox::Ok);
        return;
    }
    file.write(source);
    file.close();
}

void MainWindow::on_pushButton_8_clicked()//原文 打开文件 皆以16进制表示
{
    QString sourcefile = QFileDialog::getOpenFileName(this,QStringLiteral("打开源文件"),"","ALL(*.*)");
    if(sourcefile.isEmpty())
    {
        return;
    }
    QFile file(sourcefile);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(0, QStringLiteral("出错"),QStringLiteral("读取文件出错。 "), QMessageBox::Ok);
        return;
    }
    QByteArray res = file.readAll();
    file.close();

    QString hextmp = res.toHex().data();
    hextmp = hextmp.toUpper();

    ui->textEdit->setText(hextmp);
    ui->radioButton_2->setChecked(true);
}

void MainWindow::on_pushButton_9_clicked()//密文 存为文件
{
    QString result = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("存储结果文件"),"","ENCRYPT(*.zencrypt);;ALL(*.*)");
    if(result.isEmpty())
    {
        return;
    }
    QFile file(result);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(0, QStringLiteral("出错"),QStringLiteral("写入文件出错。 "), QMessageBox::Ok);
        return;
    }

    QString sor = ui->textEdit_2->toPlainText();//hex空格分 string
    sor.remove(QRegExp("\\s"));//移除所有空格

    QByteArray res = QByteArray::fromHex(sor.toLocal8Bit());
    if(res.isEmpty())
    {
        file.close();
        QMessageBox::critical(0, QStringLiteral("出错"),QStringLiteral("数据有误，数据可能不是16进制数据。 "), QMessageBox::Ok);
        return;
    }
    file.write(res);
    file.close();
}
void MainWindow::on_pushButton_12_clicked()//密文打开文件
{
    QString path = QFileDialog::getOpenFileName(this,QStringLiteral("打开加密文件"),"","ENCRYPT(*.zencrypt);;ALL(*.*)");
    if(path.isEmpty())
    {
        return;
    }
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(0, QStringLiteral("出错"),QStringLiteral("读取加密文件出错。 "), QMessageBox::Ok);
        return;
    }
    QByteArray res = file.readAll();
    file.close();
    QString hextmp = res.toHex().data();
    hextmp = hextmp.toUpper();
    ui->textEdit_2->setText(hextmp);//显示文本 太费时  大文本时太慢 是阻塞的。
}

void MainWindow::on_pushButton_2_clicked()//解密  固定为减 key
{
    QByteArray key;
    QString tmp1 = ui->textEdit_3->toPlainText();//hex空格分 string
    if(tmp1.isEmpty())
    {
        QMessageBox::critical(0, QStringLiteral("解密出错"),QStringLiteral("key为空！ "), QMessageBox::Ok);
        return;
    }
    tmp1.remove(QRegExp("\\s"));//移除所有空格
    key = QByteArray::fromHex(tmp1.toLocal8Bit());

    QByteArray source;
    QString sortmp = ui->textEdit_2->toPlainText();//hex空格分 string
    if(sortmp.isEmpty())
    {
        QMessageBox::critical(0, QStringLiteral("解密出错"),QStringLiteral("密文为空！ "), QMessageBox::Ok);
        return;
    }
    sortmp.remove(QRegExp("\\s"));//移除所有空格
    source = QByteArray::fromHex(sortmp.toLocal8Bit());

    QByteArray result;
    result.resize(source.length());
    int keyseq = 0;
    for(int i = 0;i<source.length ();i++)//
    {
           result[i] = source[i] - key[keyseq];
           if(0 > result[i])
           {
               result[i] = 255 + result[i]+1;
           }
           keyseq = keyseq +1;
           if(!(keyseq<key.length()))
           {
               keyseq = 0;
           }
    }

    QString hextmp = result.toHex().data();
    hextmp = hextmp.toUpper();
    ui->textEdit->setText(hextmp);
    ui->radioButton_2->setChecked(true);
}

void MainWindow::on_pushButton_clicked()//加密  约定固定为加 key
{
    QByteArray key;//key固定16进制
    QString keytmp = ui->textEdit_3->toPlainText();//hex空格分 string
    if(keytmp.isEmpty())
    {
        QMessageBox::critical(0, QStringLiteral("加密出错"),QStringLiteral("key为空！ "), QMessageBox::Ok);
        return;
    }
    keytmp.remove(QRegExp("\\s"));//移除所有空格
    key = QByteArray::fromHex(keytmp.toLocal8Bit());

    QByteArray source;//可能hex 可能文本
    if(ui->radioButton_2->isChecked())
    {
        QString sortmp = ui->textEdit->toPlainText();//hex空格分 string
        if(sortmp.isEmpty())
        {
            QMessageBox::critical(0, QStringLiteral("加密出错"),QStringLiteral("原文为空！ "), QMessageBox::Ok);
            return;
        }
        sortmp.remove(QRegExp("\\s"));//移除所有空格
        source = QByteArray::fromHex(sortmp.toLocal8Bit());
    }
    else
    {
        source = ui->textEdit->toPlainText().toLocal8Bit();
        if(source.isEmpty())
        {
            QMessageBox::critical(0, QStringLiteral("加密出错"),QStringLiteral("原文为空！ "), QMessageBox::Ok);
            return;
        }
    }


    QByteArray result;//固定hex
    result.resize(source.length());
    int keyseq = 0;
    for(int i = 0;i<source.length ();i++)//
    {
           result[i] = source[i] + key[keyseq];
           if(255 < result[i])
           {
               result[i] = result[i]%255;
           }
           keyseq = keyseq +1;
           if(!(keyseq<key.length()))
           {
               keyseq = 0;
           }
    }

    QString hextmp = result.toHex().data();
    hextmp = hextmp.toUpper();
    ui->textEdit_2->setText(hextmp);
}



void MainWindow::on_actionwhite_triggered()
{
    Setupshowmodel(1);
}

void MainWindow::on_actiongray_triggered()
{
    Setupshowmodel(2);
}

void MainWindow::on_actionblue_triggered()
{
    Setupshowmodel(3);
}

void MainWindow::on_actionred_triggered()
{
    Setupshowmodel(4);
}

void MainWindow::on_actionblack_triggered()
{
    Setupshowmodel(5);
}

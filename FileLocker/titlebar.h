#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>


class TitleBar : public QWidget//自定义控件  标题栏控件
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

    protected:

        // 双击标题栏进行界面的最大化/还原
        virtual void mouseDoubleClickEvent(QMouseEvent *event);

        // 进行鼠界面的拖动
        virtual void mousePressEvent(QMouseEvent *event);

        // 设置界面标题与图标
        virtual bool eventFilter(QObject *obj, QEvent *event);

    private slots:

        // 进行最小化、最大化/还原、关闭操作
        void onClicked();

    private:

        // 最大化/还原
        void updateMaximize();

    private:
        QLabel *m_pIconLabel;//程序图标
        QLabel *m_pTitleLabel;//程序名
        QPushButton *m_pMinimizeButton;//最小化按钮
        QPushButton *m_pMaximizeButton;//还原按钮
        QPushButton *m_pCloseButton;//关闭按钮
};

#endif // TITLEBAR_H

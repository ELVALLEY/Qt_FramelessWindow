/*
 * MIT License
 *
 * Copyright (C) 2021 by EL_Valley (el.valley@foxmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "FramelessWindow.h"
#include "ui_FramelessWindow.h"
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QScreen>
#include <QDesktopWidget>
#include <QDebug>
#include <QApplication>

FramelessWindow::FramelessWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FramelessWindow),
    m_bMousePressed(false),
    m_bDragTop(false),
    m_bDragLeft(false),
    m_bDragRight(false),
    m_bDragBottom(false)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);

    // append minimize button flag in case of windows,
    // for correct windows native handling of minimize function
#if defined(Q_OS_WIN)
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
#endif

    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground);

    setMouseTracking(true);
    QApplication::instance()->installEventFilter(this);

    // window shadow 窗口阴影
    QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
    if(windowShadow){
        windowShadow->setBlurRadius(9.0);
        windowShadow->setColor(QColor(0,0,0));
        windowShadow->setOffset(0.0);
        ui->windowFrame->setGraphicsEffect(windowShadow);
    }

    QObject::connect(qApp, &QGuiApplication::applicationStateChanged, this, &FramelessWindow::on_ApplicationstateChanged);
    QObject::connect(ui->windowTitleBar, &WindowDragger::doubleClicked, this, &FramelessWindow::on_windowTitleBarDoubleClicked);

    ui->restoreBtn->setVisible(false);
    ui->maximizeBtn->setVisible(true);

    resize(500, 500);
}

FramelessWindow::~FramelessWindow()
{
    delete ui;
}
void FramelessWindow::setWindowTitle(const QString &str)
{
    ui->windowTitleText->setText(str);
}
void FramelessWindow::setWindowIcon(const QIcon &icon)
{
    ui->windowIcon->setPixmap(icon.pixmap(16,16));
}
void FramelessWindow::setContentWidget(QWidget* w)
{
    ui->windowContent->layout()->addWidget(w);
}

bool FramelessWindow::leftBorderHit(const QPoint &pos)
{
    const QRect &rect = this->geometry();

    if(rect.x() <= pos.x() && pos.x() <= rect.x() + CONST_DRAG_BORDER_SIZE){
        return true;
    }else {
        return false;
    }
}

bool FramelessWindow::rightBorderHit(const QPoint &pos)
{
    const QRect &rect = this->geometry();
    int len = rect.x() + rect.width();

    if(len-CONST_DRAG_BORDER_SIZE <= pos.x() && pos.x() <= len){
        return true;
    }else {
        return false;
    }
}

bool FramelessWindow::topBorderHit(const QPoint &pos)
{
    const QRect &rect = this->geometry();

    if(rect.y() <= pos.y() && pos.y() <= rect.y() + CONST_DRAG_BORDER_SIZE){
        return true;
    }else {
        return false;
    }
}

bool FramelessWindow::bottomBorderHit(const QPoint &pos)
{
    const QRect &rect = this->geometry();
    int len = rect.y() + height();

    if(len-CONST_DRAG_BORDER_SIZE <= pos.y() && pos.y() <= len){
        return true;
    }else {
        return false;
    }
}

void FramelessWindow::changeCursorState(QPoint& globalMousePos)
{
    if (leftBorderHit(globalMousePos) && topBorderHit(globalMousePos)) {
        setCursor(Qt::SizeFDiagCursor);
    } else if (rightBorderHit(globalMousePos) && topBorderHit(globalMousePos)) {
        setCursor(Qt::SizeBDiagCursor);
    } else if (leftBorderHit(globalMousePos) && bottomBorderHit(globalMousePos)) {
        setCursor(Qt::SizeBDiagCursor);
    } else if(rightBorderHit(globalMousePos) && bottomBorderHit(globalMousePos)){
        setCursor(Qt::SizeFDiagCursor);
    }

    else {
        if (topBorderHit(globalMousePos)) {
            setCursor(Qt::SizeVerCursor);
        } else if (leftBorderHit(globalMousePos)) {
            setCursor(Qt::SizeHorCursor);
        } else if (rightBorderHit(globalMousePos)) {
            setCursor(Qt::SizeHorCursor);
        } else if (bottomBorderHit(globalMousePos)) {
            setCursor(Qt::SizeVerCursor);
        } else {
            m_bDragTop = false;
            m_bDragLeft = false;
            m_bDragRight = false;
            m_bDragBottom = false;
            setCursor(Qt::ArrowCursor);
        }
    }
}


void FramelessWindow::changeWindowGeometry(const QPoint &globalMousePos)
{
    //获取程序所在的主屏幕
    QScreen* screen = QGuiApplication::primaryScreen();
    //excludes taskbar去掉任务栏等无用空间的几何
    QRect availGeometry = screen->availableGeometry();
    int h = availGeometry.height();
    int w = availGeometry.width();

    QList<QScreen*> screenList = screen->virtualSiblings();
    if(screenList.contains(screen)){
        QSize sz = QApplication::desktop()->size();
        h = sz.height();
        w = sz.width();
    }

    //top right corner
    if (m_bDragTop && m_bDragRight) {
        int oldX = m_StartGeometry.x() + m_StartGeometry.width();
        int oldY = m_StartGeometry.y();

        int diffWidth = globalMousePos.x() - oldX;
        //Note: 高度增加时y减小
        int diffHeight = oldY - globalMousePos.y();

        int newWidth = m_StartGeometry.width() + diffWidth;
        int newHeight = m_StartGeometry.height() + diffHeight;

        int newY = m_StartGeometry.y() - diffHeight;

        if(newY > 0 && newY < (h - 50) && newWidth > 0 && newHeight > 0){
            QRect newRect(m_StartGeometry.x(), newY, newWidth, newHeight);

            setGeometry(newRect);
        }
        //Note: 这样的实现还是不够完美, 在进行缩放时窗口会产生抖动;
    }
    //right bottom corner 四个角中只有右下角的缩放效果没有抖动产生
    else if (m_bDragRight && m_bDragBottom){
        int oldX = m_StartGeometry.x() + m_StartGeometry.width();
        int oldY = m_StartGeometry.y() + m_StartGeometry.height();

        int diffWidth = globalMousePos.x() - oldX;

        int diffHeight = globalMousePos.y() - oldY;

        int newWidth = m_StartGeometry.width() + diffWidth;
        int newHeight = m_StartGeometry.height() + diffHeight;


        if(newWidth > 0 && newHeight > 0){
            QRect newRect(m_StartGeometry.x(), m_StartGeometry.y(), newWidth, newHeight);

            setGeometry(newRect);
        }
    }
    //left botton corner
    else if (m_bDragBottom && m_bDragLeft){
        int oldX = m_StartGeometry.x();
        int oldY = m_StartGeometry.y() + m_StartGeometry.height();

        int diffWidth = oldX - globalMousePos.x();
        int diffHeight = globalMousePos.y() - oldY;

        int newWidth = m_StartGeometry.width() + diffWidth;
        int newHeight = m_StartGeometry.height() + diffHeight;

        int newX = m_StartGeometry.x() - diffWidth;

        if(newX < oldX + m_StartGeometry.width() && (newWidth > 0 && newHeight > 0)){

            QRect newRect(newX, m_StartGeometry.y(), newWidth, newHeight);

            setGeometry(newRect);
        }
    }
    //top left corner
    else if (m_bDragLeft && m_bDragTop) {
        int oldX = m_StartGeometry.x();
        int oldY = m_StartGeometry.y();

        int diffWidth = oldX - globalMousePos.x();
        int diffHeight = oldY - globalMousePos.y();

        int newWidth = m_StartGeometry.width() + diffWidth;
        int newHeight = m_StartGeometry.height() + diffHeight;

        int newX = m_StartGeometry.x() - diffWidth;
        int newY = m_StartGeometry.y() - diffHeight;

        if(newX < oldX + m_StartGeometry.width() && newY < oldY + m_StartGeometry.height() && newY > 0 && (newWidth > 0 && newHeight > 0)){

            QRect newRect(newX, newY, newWidth, newHeight);

            setGeometry(newRect);
        }
    }
    else {
        if(m_bDragBottom){
            int oldX = m_StartGeometry.x();
            int oldY = m_StartGeometry.y();

            int diffHeight = globalMousePos.y() - oldY - m_StartGeometry.height();

            int newHeight = m_StartGeometry.height() + diffHeight;

            if(newHeight > 0){

                QRect newRect(oldX, oldY, m_StartGeometry.width(), newHeight);

                setGeometry(newRect);
            }
        }
        else if (m_bDragLeft) {
            int oldX = m_StartGeometry.x();
            int oldY = m_StartGeometry.y();

            int diffWidth = oldX - globalMousePos.x();

            int newX = oldX - diffWidth;

            int newWidth = m_StartGeometry.width() + diffWidth;

            if(newWidth > 0){

                QRect newRect(newX, oldY, newWidth, m_StartGeometry.height());

                setGeometry(newRect);
            }
        }
        else if (m_bDragTop) {
            int oldX = m_StartGeometry.x();
            int oldY = m_StartGeometry.y();

            int diffHeight = oldY - globalMousePos.y();

            int newY = oldY - diffHeight;

            int newHeight = m_StartGeometry.height() + diffHeight;

            if(newHeight > 0){

                QRect newRect(oldX, newY, m_StartGeometry.width(), newHeight);

                setGeometry(newRect);
            }
        }
        else if (m_bDragRight){
            int oldX = m_StartGeometry.x();
            int oldY = m_StartGeometry.y();

            int diffWidth = globalMousePos.x() - oldX - m_StartGeometry.width();

            int newWidth = m_StartGeometry.width() + diffWidth;

            if(newWidth > 0){

                QRect newRect(oldX, oldY, newWidth, m_StartGeometry.height());

                setGeometry(newRect);
            }
        }
    }

}
/**
 * @brief FramelessWindow::eventFilter
 * qApp安装此事件过滤, 对该应用程序接收的事件进行过滤处理
 */
bool FramelessWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(isMaximized()){
        // no change cursor state when window is maximized;
        return QWidget::eventFilter(watched, event);
    }

    if(event->type() == QEvent::MouseMove){
        //过滤所有的鼠标移动事件 filter all of mouse move event
        QMouseEvent* pMouse = dynamic_cast<QMouseEvent*>(event);
        if(pMouse){
            checkBorderDragging(pMouse);
        }
    }

    return QWidget::eventFilter(watched, event);
}

void FramelessWindow::mousePressEvent(QMouseEvent *event)
{
    if(isMaximized()){
        return;
    }

    m_bMousePressed = true;
    m_StartGeometry = this->geometry();
    QPoint globalMousePos = mapToGlobal(QPoint(event->x(), event->y()));

    if(leftBorderHit(globalMousePos) && topBorderHit(globalMousePos)){
        m_bDragLeft = true;
        m_bDragTop = true;
        return;
    } else if(rightBorderHit(globalMousePos) && topBorderHit(globalMousePos)){
        m_bDragRight = true;
        m_bDragTop = true;
        return;
    } else if(leftBorderHit(globalMousePos) && bottomBorderHit(globalMousePos)){
        m_bDragLeft = true;
        m_bDragBottom = true;
        return;
    } else if(rightBorderHit(globalMousePos) && bottomBorderHit(globalMousePos)){
        m_bDragRight = true;
        m_bDragBottom = true;
        return;
    } else if(rightBorderHit(globalMousePos)){
        m_bDragRight = true;
        return;
    } else if(bottomBorderHit(globalMousePos)){
        m_bDragBottom = true;
        return;
    } else if(leftBorderHit(globalMousePos)){
        m_bDragLeft = true;
        return;
    } else if(topBorderHit(globalMousePos)){
        m_bDragTop = true;
        return;
    }
}

void FramelessWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (isMaximized()) {
        return;
    }

    m_bMousePressed = false;
    bool bSwitchBackCursorNeeded =
            m_bDragTop || m_bDragLeft || m_bDragRight || m_bDragBottom;
    m_bDragTop = false;
    m_bDragLeft = false;
    m_bDragRight = false;
    m_bDragBottom = false;
    if (bSwitchBackCursorNeeded) {
        setCursor(Qt::ArrowCursor);
    }

}

void FramelessWindow::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::WindowStateChange){
        if(windowState().testFlag(Qt::WindowNoState)){
            setWindowStyle(true, true);
        }
        else if(windowState().testFlag(Qt::WindowMaximized)){
            setWindowStyle(false, true);
        }

        QWidget::changeEvent(event);

    } else {
        QWidget::changeEvent(event);
    }
}

/**
 * @brief FramelessWindow::checkBorderDragging
 * 鼠标移动时确定鼠标位置是否处于范围内, 并改变光标形态
 * 移动时若鼠标按下, 那么进行窗体大小改变
 */
void FramelessWindow::checkBorderDragging(QMouseEvent *event)
{
    if(isMinimized()){
        return;
    }
    //全局位置
    QPoint globalMousePos = event->globalPos();

    if(!m_bMousePressed){
        // no mouse pressed

        changeCursorState(globalMousePos);
    }else {
        // mouse pressed

        changeWindowGeometry(globalMousePos);
    }
}


void FramelessWindow::setWindowStyle(bool isNoState, bool isActive)
{
    if(isActive){
        if(isNoState){
            this->layout()->setMargin(5);
            QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
            if (oldShadow) delete oldShadow;
            QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
            windowShadow->setBlurRadius(9.0);
            windowShadow->setColor(QColor(0,0,0));
            windowShadow->setOffset(0.0);
            ui->windowFrame->setGraphicsEffect(windowShadow);

            ui->windowTitleBar->setStyleSheet(QStringLiteral(
                                                  "#windowTitleBar{border: 0px none palette(shadow); "
                                                  "border-top-left-radius:5px; border-top-right-radius:5px; "
                                                  "background-color:rgb(255, 255, 255);}"));
            ui->windowFrame->setStyleSheet(QStringLiteral(
                                               "#windowFrame{border:1px solid rgb(0,0,0); "
                                               "border-radius:5px 5px 0px 0px; "
                                               "background-color:palette(Window);}"));
        }else {
            layout()->setMargin(0);
            QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
            if (oldShadow) delete oldShadow;
            ui->windowFrame->setGraphicsEffect(nullptr);

            ui->windowTitleBar->setStyleSheet(QStringLiteral(
                                                  "#windowTitleBar{border: 0px none red; "
                                                  "border-top-left-radius:0px; border-top-right-radius:0px;"
                                                  "background-color:rgb(255, 255, 255);}"));
            ui->windowFrame->setStyleSheet(QStringLiteral(
                                               "#windowFrame{border:1px solid rgb(0,0,0); "
                                               "border-radius:0px 0px 0px 0px; "
                                               "background-color:palette(Window);}"));
        }
    }else {
        if(isNoState){

            QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
            if (oldShadow) delete oldShadow;
            QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
            windowShadow->setBlurRadius(10.0);
            windowShadow->setColor(QColor(255,255,255));
            windowShadow->setOffset(0.0);
            ui->windowFrame->setGraphicsEffect(windowShadow);

            ui->windowTitleBar->setStyleSheet(QStringLiteral(
                                                  "#windowTitleBar{border: 0px none red; "
                                                  "border-top-left-radius:5px; border-top-right-radius:5px; "
                                                  "background-color:rgb(240,240,240);}"));

        }else {
            layout()->setMargin(0);
            QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
            if (oldShadow) delete oldShadow;
            ui->windowFrame->setGraphicsEffect(nullptr);
            ui->windowTitleBar->setStyleSheet(QStringLiteral(
                                                  "#windowTitleBar{border: 0px none red; "
                                                  "border-top-left-radius:0px; border-top-right-radius:0px;"
                                                  "background-color:rgb(240,240,240);}"));
            ui->windowFrame->setStyleSheet(QStringLiteral(
                                               "#windowFrame{border:1px solid color(0,0,0); "
                                               "border-radius:0px 0px 0px 0px; "
                                               "background-color:palette(Window);}"));
        }
    }
}
/**
 * @brief FramelessWindow::on_ApplicationstateChanged
 * 当应用程序状态发生改变时, 窗口阴影和标题栏颜色相应发生改变
 * 应用程序状态 : 激活, 未激活
 * 窗口状态: max, min, nostate;
 */
void FramelessWindow::on_ApplicationstateChanged(Qt::ApplicationState state)
{
    if(state == Qt::ApplicationActive){
        if(windowState().testFlag(Qt::WindowNoState)){
            setWindowStyle(true, true);
        }else if(windowState().testFlag(Qt::WindowMaximized)){
            setWindowStyle(false, true);
        }
    }else if(state == Qt::ApplicationInactive){
        if(windowState().testFlag(Qt::WindowNoState)){
            setWindowStyle(true, false);
        }else if(windowState().testFlag(Qt::WindowMaximized)){
            setWindowStyle(false, false);
        }
    }
}

void FramelessWindow::on_closeBtn_clicked()
{
    this->close();
}

void FramelessWindow::on_maximizeBtn_clicked()
{

    ui->restoreBtn->setVisible(true);
    ui->maximizeBtn->setVisible(false);

    //设置窗口状态, 事件传入changeEvent
    setWindowState(Qt::WindowMaximized);
    //setWindowStyle(false, true);

    //this->showMaximized();和setWindowState效果相同
    //以上方式由于没有与平台完美融合, 实现的效果不太完美,
    //缺点: 最大化时, 多屏幕状态, 覆盖了windows任务栏
}

void FramelessWindow::on_restoreBtn_clicked()
{

    ui->restoreBtn->setVisible(false);
    ui->maximizeBtn->setVisible(true);

    //设置窗口状态, 事件传入changeEvent
    setWindowState(Qt::WindowNoState);
   // setWindowStyle(true, true);

    //showNormal();和setWindowState效果相同

#if defined(Q_OS_MACOS)
    // on MacOS this hack makes sure the
    // background window is repaint correctly
    hide();
    show();
#endif
}
void FramelessWindow::on_minimizeBtn_clicked()
{
    setWindowState(Qt::WindowMinimized);
}

void FramelessWindow::on_windowTitleBarDoubleClicked()
{
    if(windowState().testFlag(Qt::WindowMaximized)){
        on_restoreBtn_clicked();
    }else if (windowState().testFlag(Qt::WindowNoState)){
        on_maximizeBtn_clicked();
    }
}


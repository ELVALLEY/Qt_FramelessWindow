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

#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QWidget>

namespace Ui {
class FramelessWindow;
}

QT_BEGIN_NAMESPACE
class QGraphicsDropShadowEffect;
QT_END_NAMESPACE

class FramelessWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FramelessWindow(QWidget *parent = nullptr);
    ~FramelessWindow();
    void setContentWidget(QWidget* w);

public slots:
    void setWindowTitle(const QString &str);
    void setWindowIcon(const QIcon &icon);

private:
    bool leftBorderHit(const QPoint &pos);
    bool rightBorderHit(const QPoint &pos);
    bool topBorderHit(const QPoint &pos);
    bool bottomBorderHit(const QPoint &pos);
    void changeCursorState(QPoint& globalMousePos);
    void changeWindowGeometry(const QPoint& globalMousePos);
    void checkBorderDragging(QMouseEvent* event);
    void setWindowStyle(bool isNoState, bool isActive);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void changeEvent(QEvent *event);

private slots:
    void on_closeBtn_clicked();
    void on_maximizeBtn_clicked();
    void on_restoreBtn_clicked();
    void on_minimizeBtn_clicked();
    void on_windowTitleBarDoubleClicked();
    void on_ApplicationstateChanged(Qt::ApplicationState state);

private:
    Ui::FramelessWindow *ui;
    QRect m_StartGeometry;

    const quint8 CONST_DRAG_BORDER_SIZE = 15;
    bool m_bMousePressed;
    bool m_bDragTop;
    bool m_bDragLeft;
    bool m_bDragRight;
    bool m_bDragBottom;
};

#endif // FRAMELESSWINDOW_H

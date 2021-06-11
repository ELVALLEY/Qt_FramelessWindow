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
#include "WindowDragger.h"
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>

WindowDragger::WindowDragger(QWidget *parent) : QWidget(parent),m_mousePress(false),m_TopWindow(nullptr)
{
    QWidget* parentWindow = this->parentWidget();
    if(parentWindow) parentWindow = parentWindow->parentWidget();
    if(parentWindow) m_TopWindow = parentWindow;
}

void WindowDragger::mousePressEvent(QMouseEvent *event)
{
    m_mousePress = true;
    m_startPos = event->globalPos();

    if(m_TopWindow) m_currentPos = m_TopWindow->pos();

}
void WindowDragger::mouseMoveEvent(QMouseEvent *event)
{
    if (m_mousePress && m_TopWindow) {
        QPoint movePos = event->globalPos();

        m_TopWindow->move(m_currentPos + (movePos - m_startPos));
    }
}
void WindowDragger::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_mousePress = false;
}
void WindowDragger::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit doubleClicked();
}
void WindowDragger::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

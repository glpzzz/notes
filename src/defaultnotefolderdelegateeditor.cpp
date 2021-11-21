#include "defaultnotefolderdelegateeditor.h"
#include <QPainter>
#include <QDebug>
#include <QTreeView>
#include "nodetreemodel.h"

DefaultNoteFolderDelegateEditor::DefaultNoteFolderDelegateEditor(QTreeView *view, const QStyleOptionViewItem &option,
                                                     const QModelIndex &m_index,
                                                     QWidget *parent) :
    QWidget(parent),
    m_option(option),
    m_index(m_index),
    #ifdef __APPLE__
    m_displayFont(QFont(QStringLiteral("SF Pro Text")).exactMatch() ? QStringLiteral("SF Pro Text") : QStringLiteral("Roboto")),
    #elif _WIN32
    m_displayFont(QFont(QStringLiteral("Segoe UI")).exactMatch() ? QStringLiteral("Segoe UI") : QStringLiteral("Roboto")),
    #else
    m_displayFont(QStringLiteral("Roboto")),
    #endif
    #ifdef __APPLE__
    m_titleFont(m_displayFont, 13, 65),
    #else
    m_titleFont(m_displayFont, 10, 60),
    #endif
    m_titleColor(26, 26, 26),
    m_titleSelectedColor(255, 255, 255),
    m_activeColor(68, 138, 201),
    m_hoverColor(207, 207, 207),
    m_view(view)
{
    setContentsMargins(0, 0, 0, 0);
}


void DefaultNoteFolderDelegateEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    auto iconRect = QRect(rect().x() + 5, rect().y() + (rect().height() - 20) / 2, 20, 20);
    QRect nameRect(rect());
    nameRect.setLeft(iconRect.x() + iconRect.width() + 5);
    auto displayName = m_index.data(NodeItem::Roles::DisplayText).toString();
    if (m_view->currentIndex() == m_index) {
        painter.fillRect(rect(), QBrush(m_activeColor));
        painter.setPen(m_titleSelectedColor);
    } else {
        painter.fillRect(rect(), QBrush(m_hoverColor));
        painter.setPen(m_titleColor);
    }
    painter.setFont(m_titleFont);
    painter.drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, displayName);
    QWidget::paintEvent(event);
}

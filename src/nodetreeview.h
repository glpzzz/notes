#ifndef NODETREEVIEW_H
#define NODETREEVIEW_H

#include <QTreeView>
#include <QTimer>

class QMenu;
class QAction;

class NodeTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit NodeTreeView(QWidget* parent = Q_NULLPTR);

    void setTreeSeparator(const QVector<QModelIndex> &newTreeSeparator);
    void setIsEditing(bool newIsEditing);
    void onRenameFolderFinished(const QString& newName);
    void onRenameTagFinished(const QString& newName);
    void setCurrentIndexC(const QModelIndex& index);
public slots:
    void onCustomContextMenu(const QPoint& point);
    void onChangeTagColorAction();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

signals:
    void addFolderRequested();
    void renameFolderRequested();
    void renameFolderInDatabase(const QModelIndex& index, const QString& newName);
    void renameTagInDatabase(const QModelIndex& index, const QString& newName);
    void deleteNodeRequested(const QModelIndex& index);
    void loadNotesInFolderRequested(int folderID, bool isRecursive);
    void loadNotesInTagsRequested(const QSet<int>& tagIds);
    void moveNodeRequested(int node, int target);
    void renameTagRequested();
    void changeTagColorRequested(const QModelIndex& index);
    void deleteTagRequested(const QModelIndex& index);
    void addNoteToTag(int noteId, int tagId);

private slots:
    void onClicked(const QModelIndex& index);
    void onDeleteNodeAction();
    void onExpanded(const QModelIndex& index);
    void onCollapsed(const QModelIndex& index);
private:
    QMenu* contextMenu;
    QAction* renameFolderAction;
    QAction* deleteFolderAction;
    QAction* addSubfolderAction;
    QAction* renameTagAction;
    QAction* changeTagColorAction;
    QAction* deleteTagAction;
    QAction* clearSelectionAction;
    QTimer contextMenuTimer;
    QVector<QModelIndex> m_treeSeparator;
    QModelIndex m_currentEditingIndex;
    bool m_isContextMenuOpened;
    bool m_isEditing;
    QVector<QString> m_expanded;
    void updateEditingIndex(const QPoint &pos);
    void closeCurrentEditor();

    // QAbstractItemView interface
protected slots:
    virtual void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;
    virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

    // QWidget interface
protected:
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;

    // QAbstractItemView interface
public slots:
    virtual void reset() override;
};

#endif // NODETREEVIEW_H

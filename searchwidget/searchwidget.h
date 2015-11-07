#ifndef SEARCHWIDGET_COMMON_DLLSPEC
#define SEARCHWIDGET_COMMON_DLLSPEC  Q_DECL_EXPORT

#include <QWidget>
#include <QItemSelectionModel>
#include <QAbstractItemView>
#include <QLineEdit>

#include "qtaglabelbutton.h"
#include "tagcustomcompleter.h"
#include "tagcompleteritemdelegate.h"
#include "tageventfilter.h"
#include "flowlayout.h"
//#include "graphproxymodel.h"


class SEARCHWIDGET_COMMON_DLLSPEC SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = 0, bool defaultFont = true);
    ~SearchWidget();
//! [1] QWidget public methods
//! [1]
//! [2] Custom public methods
    QAbstractItemModel *model();
    void setModel(QAbstractItemModel *model);
    QItemSelectionModel *selectionModel(void) const;
    void setSelectionModel(QItemSelectionModel *selectionModel);
    QAbstractItemView::SelectionMode selectionMode(void) const;
    void setSelectionMode(QAbstractItemView::SelectionMode mode);
    QString getSearchString(void);
//! [2]
    void setMainFont(QFont mfont){font = mfont;}

signals:

public slots:
    void insertSelection(QModelIndex curIndex);
    void insertCompletion(QModelIndex curIndex);
    void removeBtn(QTagLabelButton *btn);
    void clearAllBtn();
    void clearSelectionBtn();
    void onItemSelected(const QItemSelection & selected, const QItemSelection & deselected );

private:
    //params
    int buttonPadding;
    int padding;
    int fontHeight;
    int height;
    int width;
    QFont font;
public:
    //setters params

    int getButtonPadding() const;
    void setButtonPadding(int value);

    int getPadding() const;
    void setPadding(int value);

    int getFontHeight() const;
    void setFontHeight(int value);

    int getHeight() const;
    void setHeight(int value);

    int getWidth() const;
    void setWidth(int value);
    //setter styles
    void setSearchlineStyle(QString style);
    void setFrameStyle(QString style);
    void setTagButtonStyle(QString style);
    void setClosebtnVisible(bool closebtnVisible);

private:
    QAbstractItemModel *itemModel;
    QItemSelectionModel *selModel;
    QAbstractItemView::SelectionMode selMode;
    //
    QLineEdit *searchLine;
    TagCustomCompleter *completer;
    TagCompleterItemDelegate *tagCompleterItemDelegate;
    FlowLayout *flowLayout;
    QMap<QString,QModelIndex> itemMap;
    int lentag;
    QFrame *frame;
    QTagLabelButton *close_btn;
    bool closebtnVisible;
    bool defaultFont;
    QString buttonStyle;
};

#endif // SEARCHWIDGET_H

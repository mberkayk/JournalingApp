#ifndef LISTPANEL_H
#define LISTPANEL_H

#include <QWidget>
#include <QBoxLayout>
#include <QDate>


class ListCard : public QWidget {
    Q_OBJECT
private:
    QHBoxLayout mainLayout;
    QVBoxLayout dateLayout;
    QDate date;
    QString contents;

public:
    ListCard();
};


class ListPanel  : public QWidget {

    Q_OBJECT

private:
    QVBoxLayout layout;
    QVector<ListCard> cards;

public:
    ListPanel();
};

#endif // LISTPANEL_H

#ifndef FDNODE_H
#define FDNODE_H

#include <QObject>
#include<QString>

class fdnode : public QObject
{
    Q_OBJECT
private:
    QString word;
    int count=0;

public:
    explicit fdnode(QObject *parent = nullptr, QString s="");
    fdnode(const fdnode &f)
    {
        this->word=f.get_word();
        this->count=f.get_count();
    }
    fdnode& operator =(const fdnode &f)
    {
        this->word=f.get_word();
        this->count=f.get_count();
        return *this;
    }
    int get_count() const
    {
        return count;
    }
    QString get_word() const
    {
        return word;
    }
    void inc_count()
    {
        count++;
    }
    friend QDataStream& operator>>( QDataStream& d, fdnode& f );

signals:

public slots:
};

#endif // FDNODE_H

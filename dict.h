#ifndef DICT_H
#define DICT_H

#include <QObject>
#include"fdnode.h"
#include<QList>
#include<QDataStream>
#include<QTextStream>
#include<QRegularExpression>
#include<QMessageBox>
#include<QFileDialog>
#define Not_in_List -1
#include<QDebug>
//end serialization.......................................
class dict : public QObject
{
    Q_OBJECT
private:
    QList<fdnode> dictionary;

public:
    explicit dict(QObject *parent = nullptr);
    fdnode get_el(int i)
    {
        return dictionary[i];
    }
    bool in(QString el)
    {
        QList<fdnode>::iterator it;
        for(it=dictionary.begin();it!=dictionary.end();it++)
            if(it->get_word()==el)
                return true;

        return false;

    }
    int get_id(QString el)
    {

        for(int i=0;i<dictionary.size();i++)
            if(dictionary[i].get_word()==el)
                return i;

       return Not_in_List;

    }
    void add(QString el)
    {
        el=el.toLower();
        //qDebug()<<el;

        if(dictionary.isEmpty())
        {
            fdnode* nod=new fdnode(nullptr,el);
            dictionary.push_back(*nod);
            return;
        }
        int id=this->get_id(el);
            if(id>Not_in_List)
            {

                //qDebug()<<id;
                dictionary[id].inc_count();
                return;
            }
            else
            {
                if(el<dictionary[0].get_word())
                {
                    fdnode* node=new fdnode(nullptr,el);
                    dictionary.insert(0,*node);

                    return;
                }

               else
                {
                    for(QList<fdnode>::iterator it=dictionary.end()-1;it>=dictionary.begin();it--)
                    {
                        if(el>it->get_word())
                        {
                            fdnode* node=new fdnode(nullptr,el);
                            //qDebug()<<node->get_count();
                            dictionary.insert(((it-dictionary.begin())+1),*node);
                            return;
                        }
                    }


                }
            }



    }

    QStringList get_dict()
    {

        QStringList str_list;
        QString str;
        QTextStream stream(&str);
        for(int i=0;i<dictionary.length();i++)
        {
            QString Test=dictionary[i].get_word();
            str="";
            stream<<(dictionary[i].get_word())<<" - "<<QString::number(dictionary[i].get_count());
            str_list.push_back(str);
        }
        return str_list;
    }
    bool is_empty()
    {
        return dictionary.isEmpty();
    }








signals:
void load_data_complit(bool);

public slots:
   void parce_from_file();
   void load_from_file();
   void save_to_file();
   void clear();
};

#endif // DICT_H

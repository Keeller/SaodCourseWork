#include "dict.h"
QDataStream& operator>>( QDataStream& d, fdnode& f )
{
    d >>f.word>>f.count;
    return d;
}

QDataStream& operator<<( QDataStream& d, const fdnode &f )
{

    d << f.get_word() << f.get_count();
    return d;
}

dict::dict(QObject *parent) : QObject(parent)
{

}

void dict::load_from_file()
{
     QString path=QFileDialog::getOpenFileName();
    if(!dictionary.isEmpty())
    {
        dictionary.clear();
    }

    QFile f(path);
    if(f.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&f);
        while(!stream.atEnd())
        {

            fdnode node;
            stream>>node;
            dictionary.push_back(node);

        }

        emit load_data_complit(true);

    }
    else
        emit load_data_complit(false);

}
void dict::parce_from_file()
{
    if(!dictionary.isEmpty())
    {
        dictionary.clear();
    }
     QString path=QFileDialog::getOpenFileName();
     if(path.isEmpty())
     {
         QMessageBox qms;
         qms.setText("Путь не указан");
         qms.exec();
     }
    QString s;
    QStringList str_list;
    QFile f(path);
    if(f.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&f);

        while(!stream.atEnd())
        {

            stream>>s;
            str_list=(s).split(QRegularExpression("\[,;:.!?\\s]+"));
            if(!str_list.isEmpty())
            {
                for(QStringList::iterator it=str_list.begin();it<str_list.end();it++)
                {
                   if(*it!="")
                    this->add(*(it));

                }

                str_list.clear();
            }
            else
            {
                QMessageBox qms;
                qms.setText("Ошибка обработки текста");
                qms.exec();
                emit load_data_complit(false);
                return;
            }
        }

        emit load_data_complit(true);
    }
    else
        emit load_data_complit(false);

}
void dict::save_to_file()
{
    if(dictionary.isEmpty())
    {
        QMessageBox qms;
        qms.setText("Мой повелитель словарь пуст, нечего сохранять");
        qms.exec();
        return;
    }
     QString path=QFileDialog::getSaveFileName();


    QFile f(path+".dict");
    if(f.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&f);
        for(QList<fdnode>::iterator it=dictionary.begin();it<dictionary.end();it++)
        {


            stream<<(*(it));
        }

    }

}

void dict::clear()
{
    dictionary.clear();
    emit load_data_complit(true);
}

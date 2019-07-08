#include "fdnode.h"
fdnode::fdnode(QObject *parent,QString s) : QObject(parent)
{
    this->word=s;
    count++;

}

#ifndef TERMINAL_H
#define TERMINAL_H
#include <QString>

class Terminal
{
public:
    int id;
    QString name;
    int stile;
    bool escalator;
public:
    Terminal(int id, QString name, int stile, bool escalator);
    Terminal();
};


#endif // TERMINAL_H

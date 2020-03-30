#include "terminal.h"

Terminal::Terminal(int id, QString name, int stile, bool escalator)
{
    this->id = id;
    this->name = name;
    this->stile = stile;
    this->escalator = escalator;
}

Terminal::Terminal()
{

}

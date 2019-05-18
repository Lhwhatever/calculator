#include "IOutputtable.h"

IOutputtable::~IOutputtable() {
    
}

void IOutputtable::outputTo(std::ostream& ostream) {
    throw "NotImplementedException: void outputTo(std::ostream&)";
}

std::ostream& operator<<(std::ostream& ostream, IOutputtable obj) {
    obj.outputTo(ostream);
    return ostream;
}
#include "IOutputtable.h"

std::ostream& operator<<(std::ostream& ostream, IOutputtable& obj) {
    obj.outputTo(ostream);
    return ostream;
}
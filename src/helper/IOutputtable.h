#ifndef CALC__HELPER__IOUTPUTTABLE__H_
#define CALC__HELPER__IOUTPUTTABLE__H_

#include <iostream>


class IOutputtable {

    ~IOutputtable();

protected:
    virtual void outputTo(std::ostream& ostream);
    
    friend std::ostream& operator<<(std::ostream&, IOutputtable);
};

#endif
#ifndef FUNCTION4_H_INCLUDED
#define FUNCTION4_H_INCLUDED

#include "../../include/ifunction.h"
#include <wx/string.h>
#include <math.h>

class Function4 : public IDrawableFunction
{
    public:
        virtual double Calculate(double x)
        {
            return 2*x+1;
        }

        virtual wxString GetName(void)
        {
            return wxT("y=2*x+1");
        }
};

#endif // FUNCTION4_H_INCLUDED

#ifndef FUNCTION3_H_INCLUDED
#define FUNCTION3_H_INCLUDED

#include "../../include/ifunction.h"
#include <wx/string.h>
#include <math.h>

class Function3 : public IDrawableFunction
{
    public:
        virtual double Calculate(double x)
        {
            return pow(x, 2);
        }

        virtual wxString GetName(void)
        {
            return wxT("y=x^2");
        }

        virtual wxColour GetColour()
        {
            return *wxBLUE;
        }
};

#endif // FUNCTION3_H_INCLUDED

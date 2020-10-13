#ifndef FUNCTION1_H_INCLUDED
#define FUNCTION1_H_INCLUDED

#include "../../include/ifunction.h"
#include <wx/string.h>
#include <math.h>

class Function1 : public IDrawableFunction
{
    public:
        virtual double Calculate(double x)
        {
            return pow(x, 3);
        }

        virtual wxString GetName(void)
        {
            return wxT("y=x^3");
        }

        virtual wxColour GetColour()
        {
            return *wxGREEN;
        }

    private:
        std::exception e;
};

#endif // FUNCTION1_H_INCLUDED

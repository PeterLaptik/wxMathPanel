#ifndef FUNCTION2_H_INCLUDED
#define FUNCTION2_H_INCLUDED

#include "../../include/ifunction.h"
#include <wx/string.h>
#include <math.h>

class Function2 : public IDrawableFunction
{
    public:
        virtual double Calculate(double x)
        {
            if(x<=0)
                throw e;

            return log10(x);
        }

        virtual wxString GetName(void)
        {
            return wxT("y=log10(x)");
        }

        virtual wxColour GetColour()
        {
            return *wxCYAN;
        }

    private:
        std::exception e;
};

#endif // FUNCTION2_H_INCLUDED

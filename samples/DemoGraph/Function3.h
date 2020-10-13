#ifndef FUNCTION3_H_INCLUDED
#define FUNCTION3_H_INCLUDED

#include "../../include/ifunction.h"
#include <wx/string.h>
#include <math.h>

class Function3 : public IDrawableFunction
{
    public:
        Function3()
        {
            // maximum allowed value of argument to avoid overflow
            max_arg = log(std::numeric_limits<double>::max())/log(2);
        }

        virtual double Calculate(double x)
        {
//            if(fabs(x)>=max_arg)
//                throw e;

            return pow(x/5, 2);
        }

        virtual wxString GetName(void)
        {
            return wxT("y=(x/5)^2");
        }

        virtual wxColour GetColour()
        {
            return *wxBLUE;
        }

    private:
        double max_arg;
        std::exception e;
};

#endif // FUNCTION3_H_INCLUDED

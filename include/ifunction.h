#ifndef IFUNCTION_H_INCLUDED
#define IFUNCTION_H_INCLUDED

#include <wx/string.h>
#include <wx/colour.h>

/** \brief Interface for drawable function.
*
* Each class that would draw function on a wxMathPanelGraph has to implement the interface.
*/
class IDrawableFunction
{
    public:
        /** \brief Returns function value for x-argument.
        *
        * The function can throw std::exception.
        * On x-values where exception occurs the curve will not be drawn.
        */
        virtual double Calculate(double x) = 0;


        /** \brief Returns function name to be output in legend.
        * \returns Function name.
        */
        virtual wxString GetName(void) = 0;


        /** \brief Returns function colour to draw.
        *
        * wxBLACK is set as a default colour value.
        * \return wxColour for drawing
        */
        virtual wxColour GetColour(void)
        {
            return wxColour(0,0,0);
        }

};

#endif // IFUNCTION_H_INCLUDED

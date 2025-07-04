/*********************************************************************
 * Name:      ipointset.h
 * Purpose:
 * Author:    Peter Laptik
 * Created:   2020-10-18
 * Copyright: (c) Peter Laptik
 * Licence:   BSD 2-clause
 ********************************************************************/

#ifndef IPOINTSET_H_INCLUDED
#define IPOINTSET_H_INCLUDED

#include <vector>


/**\brief An entity for a point set.
* \see IPointSet
*/
struct GraphPoint
{
    double x;
    double y;
    GraphPoint(double X, double Y): x(X), y(Y) { }
};


enum PointLabelType
{
    POINT_TYPE_CIRCLE = 0,
    POINT_TYPE_SQUARE = 1,
    POINT_TYPE_TRIANGLE = 2,
    POINT_TYPE_CROSS = 3,
    POINT_TYPE_NOLABEL = 4
};


/** \brief Interface for drawable interpolated function.
*
* Each class that would draw function by interpolated points on a wxMathPanelPointGraph has to implement the interface.
*/
class IPointSet
{
    public:
        /** \brief Returns set of points to be plotted and interpolated.
        *
        * \return Point set (the set is kept in a vector).
        * \see GraphPoint
        */
        virtual std::vector<GraphPoint>& GetPoints(void) = 0;


        /** \brief Returns function name to be output in a legend.
        * \return Function name.
        */
        virtual wxString GetName(void) = 0;


        /** \brief Returns point label for a point set.
        * \return PointLabelType enumeration value
        * (POINT_TYPE_CIRCLE, POINT_TYPE_SQUARE, POINT_TYPE_TRIANGLE, POINT_TYPE_CROSS or POINT_TYPE_NOLABEL)
        */
        virtual PointLabelType GetLabels(void) = 0;


        /** \brief Returns function colour to draw.
        *
        * Black colour is set as a default colour value.
        * \return wxColour for drawing
        */
        virtual wxColour GetColour(void)
        {
            return wxColour(0,0,0);
        }
};

#endif // IPOINTSET_H_INCLUDED

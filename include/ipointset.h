#ifndef IPOINTSET_H_INCLUDED
#define IPOINTSET_H_INCLUDED

#include <vector>

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


class IPointSet
{
    public:

        virtual std::vector<GraphPoint>& GetPoints(void) = 0;

        virtual wxString GetName(void) = 0;

        virtual PointLabelType GetLabels(void) = 0;

        virtual wxColour GetColour(void)
        {
            return wxColour(0,0,0);
        }
};

#endif // IPOINTSET_H_INCLUDED

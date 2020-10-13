#ifndef POINTSET2_H_INCLUDED
#define POINTSET2_H_INCLUDED

#include "../../include/ipointset.h"

class PointSet2: public IPointSet
{
    public:
        PointSet2()
        {
            points.push_back(GraphPoint(-120/5, 20 + 10*cos((-120)*3.14/180)));
            points.push_back(GraphPoint(-90/5, 20 + 10*cos((-90)*3.14/180)));
            points.push_back(GraphPoint(-60/5, 20 + 10*cos((-60)*3.14/180)));
            points.push_back(GraphPoint(0/5, 20 + 10*cos((0)*3.14/180)));
            points.push_back(GraphPoint(120, 40));
        }

        virtual std::vector<GraphPoint>& GetPoints(void)
        {
            return points;
        }

        virtual wxString GetName()
        {
            return _T("set 2");
        }

        virtual PointLabelType GetLabels(void)
        {
            return POINT_TYPE_TRIANGLE;
        }

        virtual wxColour GetColour(void)
        {
            return *wxGREEN;
        }

    private:
        std::vector<GraphPoint> points;
};

#endif // POINTSET2_H_INCLUDED

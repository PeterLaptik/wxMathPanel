/*********************************************************************
 * Name:      pointlabel.h
 * Purpose:
 * Author:    Peter Laptik
 * Created:   2020-10-18
 * Copyright: (c) Peter Laptik
 * Licence:   BSD 2-clause
 ********************************************************************/

#ifndef POINTLABEL_H_INCLUDED
#define POINTLABEL_H_INCLUDED

#include <wx/dcclient.h>

static const int POINT_LABEL_DEFAULT_SIZE = 5;
static const int POINT_LABEL_MAX_SIZE = 15;

// Labels for point interpolated curves
class PointLabel
{
    public:
        PointLabel()
        {
            label_size = POINT_LABEL_DEFAULT_SIZE;
        }

        PointLabel(int lsize)
        {
            label_size = lsize;
            if(label_size>POINT_LABEL_MAX_SIZE)
                label_size = POINT_LABEL_DEFAULT_SIZE;
        }

        virtual ~PointLabel()
        { }

        virtual void Draw(wxDC &dc, int x, int y)
        { }

    protected:
        int label_size;
};


class PointLabelCircle: public PointLabel
{
    public:
        PointLabelCircle(int value) : PointLabel(value) { }

        virtual void Draw(wxDC &dc, int x, int y)
        {
            dc.DrawCircle(x, y, label_size/(static_cast<double>(2)/1.41));
        }
};


class PointLabelSquare: public PointLabel
{
    public:
        PointLabelSquare(int value) : PointLabel(value) { }

        virtual void Draw(wxDC &dc, int x, int y)
        {
            dc.DrawRectangle(x - label_size/2, y - label_size/2, label_size, label_size);
        }
};


class PointLabelTriangle: public PointLabel
{
    public:
        PointLabelTriangle(int value) : PointLabel(value) { }

        virtual void Draw(wxDC &dc, int x, int y)
        {
            int line_size = label_size*(static_cast<double>(2)/1.41);
            wxPoint triangle[3];
            triangle[0] = wxPoint(x, y - line_size/2);
            triangle[1] = wxPoint(x - line_size/2, y + line_size*sin(30*3.14/180));
            triangle[2] = wxPoint(x + line_size/2, y + line_size*sin(30*3.14/180));
            dc.DrawPolygon(3, triangle);
        }
};


class PointLabelCross: public PointLabel
{
    public:
        PointLabelCross(int value) : PointLabel(value) { }

        virtual void Draw(wxDC &dc, int x, int y)
        {
            dc.DrawLine(x - label_size/2, y - label_size/2, x + label_size/2, y + label_size/2);
            dc.DrawLine(x - label_size/2, y + label_size/2, x + label_size/2, y - label_size/2);
        }
};

#endif // POINTLABEL_H_INCLUDED

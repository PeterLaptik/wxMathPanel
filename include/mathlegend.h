#ifndef MATHLEGEND_H
#define MATHLEGEND_H

#include "ifunction.h"
#include <wx/dcclient.h>
#include <vector>


/**\brief Simple self-drawing legend */
class MathLegend
{
    public:
        MathLegend(std::vector<IDrawableFunction*> *functions);
        virtual ~MathLegend();

        virtual void Refresh(wxDC &dc);

        void SetPosition(int x, int y);
        void GetMetrics(int &pos_x, int &pos_y, int &width, int &height) const;

        void SetMovable(bool movable);
        bool GetMovable(void) const;
        void SetVisible(bool visible);
        bool GetVisible(void) const;

        void SetTextColour(wxColour colour);
        void SetBackgroundColour(wxColour colour);
        void SetFrameColour(wxColour colour);
        wxColour GetTextColour(void) const;
        wxColour GetBackgroundColour(void) const;
        wxColour GetFrameColour(void) const;

        void SetShadow(bool shadow = true);
        bool HasShadow(void) const;

    protected:
        // Scaling computing
        virtual int GetMaxWidth(const wxDC &dc) const;
        virtual int GetMaxHeight(const wxDC &dc) const;

    private:
        bool m_is_visible;
        bool m_is_movable;
        bool m_has_shadow;
        std::vector<IDrawableFunction*> *m_functions;   // functions to draw

        struct LegendMetrics
        {
            int x;
            int y;
            int width;
            int height;
        } m_metrics;

        struct LegendColours
        {
            wxColour background;
            wxColour frame;
            wxColour text;
        } m_colours;
};

#endif // MATHLEGEND_H

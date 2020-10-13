#ifndef MATHLEGEND_H
#define MATHLEGEND_H

#include "ifunction.h"
#include "ipointset.h"
#include "pointlabel.h"
#include "wxmathpanel.h"
#include <wx/dcclient.h>
#include <map>


/**\brief Simple self-drawing legend. */
class MathLegend
{
    public:
        MathLegend(wxMathPanel *parent);
        virtual ~MathLegend();

        void AppendItem(wxString name, wxColour colour, PointLabelType ltype);
        void ClearItems(void);

        void Refresh(wxDC &dc);

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


    private:
        // Scaling computing
        inline int GetMaxWidth(const wxDC &dc) const;
        inline int GetMaxHeight(const wxDC &dc) const;
        inline PointLabel* GetPointLabelObject(PointLabelType ptype);

        wxMathPanel *m_parent;
        bool m_is_visible;
        bool m_is_movable;
        bool m_has_shadow;

        std::vector<wxString> m_item_names;
        std::map<int, wxColour> m_item_colours;
        std::map<int, PointLabelType> m_item_labels;

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

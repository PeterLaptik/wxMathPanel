#include "../include/mathlegend.h"

// Default sizes and margins
static const int L_DEFAULT_SIZE = 20;
static const int L_BORDER_MARGIN = 10;
static const int L_TEXT_MARGIN = 5;
static const int L_LINE_MARGIN = 5;
static const int L_DEFAULT_LABEL_SIZE = 8;

// Default colours
static const wxColor DEFAULT_BACKGROUND_COLOUR = *wxWHITE;
static const wxColor DEFAULT_FRAME_COLOUR = *wxBLACK;
static const wxColor DEFAULT_TEXT_COLOUR = *wxBLACK;
static const int DEFAULT_SHADOW_THICKNESS = 3;

// Curve colour line length in pixels
static const int L_LINE_LENGTH = 50;


/** \brief Constructor for the legend.
* \param parent wxMathPanel instance where the legend is to be drawn.
*/
MathLegend::MathLegend(wxMathPanel *parent)
{
    m_parent = parent;
    m_metrics.x = m_metrics.y = 0;
    m_metrics.height = m_metrics.width = L_DEFAULT_SIZE;
    m_colours.background = DEFAULT_BACKGROUND_COLOUR;
    m_colours.frame = DEFAULT_FRAME_COLOUR;
    m_colours.text = DEFAULT_TEXT_COLOUR;
    m_is_visible = m_is_movable = true;
    m_has_shadow = true;
}

MathLegend::~MathLegend()
{ }


/** \brief Append item into the legend.
*
* Output order depends on appending sequence.
* \param num Item number.
* \param name Item name.
* \param colour Item colour.
* \param ltype Point label type.
*/
void MathLegend::AppendItem(wxString name, wxColour colour, PointLabelType ltype)
{
    int num = m_item_names.size();
    m_item_names.push_back(name);
    m_item_colours.insert(std::pair<int, wxColour>(num, colour));
    m_item_labels.insert(std::pair<int, PointLabelType>(num, ltype));
}

/**\brief Clear legend items. */
void MathLegend::ClearItems()
{
    m_item_names.clear();
    m_item_colours.clear();
    m_item_labels.clear();
}

/**\brief Sets the legend position.
*
* A parent panel has to be refreshed to show the legend in a new position.
* \param x X-coordinate value.
* \param y Y-coordinate value.
*/
void MathLegend::SetPosition(int x, int y)
{
    m_metrics.x = x;
    m_metrics.y = y;
    m_parent->Refresh();
}

/**\brief Returns legend size and position.
* \param pos_x Variable to write x-position.
* \param pos_y Variable to write y-position.
* \param width Variable to write legend width.
* \param height Variable to write legend height.
*/
void MathLegend::GetMetrics(int &pos_x, int &pos_y, int &width, int &height) const
{
    pos_x = m_metrics.x;
    pos_y = m_metrics.y;
    width = m_metrics.width;
    height = m_metrics.height;
}

/**\brief Makes legend movable/unmovable.
* @param movable Makes legend movable if true-value is passed.
*/
void MathLegend::SetMovable(bool movable)
{
    m_is_movable = movable;
}

/**\brief Returns is the legend movable.
*@return Movable state of the legend.
*/
bool MathLegend::GetMovable() const
{
    return m_is_movable;
}

/**\brief Shows/hides legend.
*
* A parent panel has to be refreshed to show changes.
* @param visible True if a legend has to be shown / false for hiding the legend.
*/
void MathLegend::SetVisible(bool visible)
{
    m_is_visible = visible;
    m_parent->Refresh();
}

/**\brief Returns visibility of the legend.
*@return True if the legend is visible.
*/
bool MathLegend::GetVisible() const
{
    return m_is_visible;
}

/**\brief Sets legend background colour.
*
* A parent panel has to be refreshed to show changes.
* \param colour Colour to set.
*/
void MathLegend::SetBackgroundColour(wxColour colour)
{
    m_colours.background = colour;
    m_parent->Refresh();
}

/**\brief Sets legend text colour.
*
* A parent panel has to be refreshed to show changes.
* \param colour Colour to set.
*/
void MathLegend::SetTextColour(wxColour colour)
{
    m_colours.text = colour;
    m_parent->Refresh();
}

/**\brief Sets legend frame colour.
*
* A parent panel has to be refreshed to show changes.
* \param colour Colour to set.
*/
void MathLegend::SetFrameColour(wxColour colour)
{
    m_colours.frame = colour;
    m_parent->Refresh();
}

/**\brief Returns legend colour.
* \return Colour value.
*/
wxColour MathLegend::GetTextColour() const
{
    return m_colours.text;
}

/**\brief Returns background colour.
* \return Colour value.
*/
wxColour MathLegend::GetBackgroundColour() const
{
    return m_colours.background;
}

/**\brief Returns frame colour.
* \return Colour value.
*/
wxColour MathLegend::GetFrameColour() const
{
    return m_colours.frame;
}

/**\brief Sets visibility of the legend shadow.
*
* A parent panel has to be refreshed to show changes.
* By default shadow is set to visible.
* \param shadow Visibility value.
*/
void MathLegend::SetShadow(bool shadow)
{
    m_has_shadow = shadow;
    m_parent->Refresh();
}

/**\brief Returns visibility of the legend shadow.
* \return Value of the legend visibility.
*/
bool MathLegend::HasShadow() const
{
    return m_has_shadow;
}

/**\brief Draws legend.
* \param dc Device context for painting.
*/
void MathLegend::Refresh(wxDC &dc)
{
    if((m_item_names.empty())||(!m_is_visible))
        return;

    m_metrics.width = GetMaxWidth(dc);
    m_metrics.height = GetMaxHeight(dc);

    wxPen pen(m_colours.frame);
    wxBrush brush(m_colours.background);
    dc.SetPen(pen);
    dc.SetBrush(brush);
    dc.SetTextForeground(m_colours.text);
    dc.DrawRectangle(m_metrics.x, m_metrics.y, m_metrics.width, m_metrics.height);

    // Create shadow
    if(m_has_shadow)
    {
        for(int i=1; i<DEFAULT_SHADOW_THICKNESS; i++)
        {
            dc.DrawLine(m_metrics.x - i, m_metrics.y - i, m_metrics.x + m_metrics.width - i, m_metrics.y - i);
            dc.DrawLine(m_metrics.x - i, m_metrics.y - i, m_metrics.x - i, m_metrics.y + m_metrics.height - i);
        }
    }

    if(m_metrics.width<1)
        m_metrics.width = L_DEFAULT_SIZE;

    if(m_metrics.height<1)
        m_metrics.height = L_DEFAULT_SIZE;

    // Fill legend
    wxString text;
    wxColour colour;
    int text_height = dc.GetFont().GetPixelSize().GetHeight();
    int pos = text_height/2 + L_LINE_MARGIN;
    int step_size = text_height + L_LINE_MARGIN;
    int value_counter = 0;
    for(std::vector<wxString>::iterator it=m_item_names.begin(); it!=m_item_names.end(); ++it)
    {
        // Function name
//        text = (*it)->GetName();
        dc.DrawText((*it), m_metrics.x + L_BORDER_MARGIN + L_LINE_LENGTH + L_TEXT_MARGIN, m_metrics.y + pos - text_height/2 - L_LINE_MARGIN/2);
        // Function line
        colour = m_item_colours.find(value_counter)->second;
        pen.SetColour(colour);
        dc.SetPen(pen);
        dc.SetBrush(wxBrush(colour));
        dc.DrawLine(m_metrics.x + L_BORDER_MARGIN, m_metrics.y + pos, m_metrics.x + L_BORDER_MARGIN + L_LINE_LENGTH, m_metrics.y + pos);
        // Draw point label
        PointLabel *label = GetPointLabelObject(m_item_labels.find(value_counter++)->second);
        if(label!=NULL)
        {
            label->Draw(dc, m_metrics.x + L_BORDER_MARGIN + L_LINE_LENGTH/2, m_metrics.y + pos);
            delete label;
        }
        pos += step_size;
    }
}

//
// Auto-scale calculations
//
// Get legend width according to text length
int MathLegend::GetMaxWidth(const wxDC &dc) const
{
    int text_length = 0;
    int text_max_length = 0;

    if(m_item_names.size()<1)
        return 0;

    for(std::vector<wxString>::const_iterator it=m_item_names.begin(); it!=m_item_names.end(); ++it)
    {
        text_length = dc.GetTextExtent(*it).GetWidth();
        if(text_length>text_max_length)
            text_max_length = text_length;
    }
    return L_BORDER_MARGIN*2 + L_LINE_LENGTH + L_TEXT_MARGIN + text_max_length;
}

// Get maximum height of the legend according to text height
int MathLegend::GetMaxHeight(const wxDC &dc) const
{
    if(m_item_names.size()<1)
        return 0;

    int text_height = dc.GetFont().GetPixelSize().GetHeight();
    int pos = text_height/2 + L_LINE_MARGIN;
    int step_size = text_height + L_LINE_MARGIN;

    for(std::vector<wxString>::const_iterator it=m_item_names.begin(); it!=m_item_names.end(); ++it)
    {
        pos += step_size;
    }
    return pos - step_size + text_height/2 + L_LINE_MARGIN;
}


PointLabel* MathLegend::GetPointLabelObject(PointLabelType ptype)
{
    PointLabel* label = NULL;

    switch(ptype)
        {
            case POINT_TYPE_CIRCLE:
                label = new PointLabelCircle(L_DEFAULT_LABEL_SIZE);
                break;
            case POINT_TYPE_SQUARE:
                label = new PointLabelSquare(L_DEFAULT_LABEL_SIZE);
                break;
            case POINT_TYPE_TRIANGLE:
                label = new PointLabelTriangle(L_DEFAULT_LABEL_SIZE);
                break;
            case POINT_TYPE_CROSS:
                label = new PointLabelCross(L_DEFAULT_LABEL_SIZE);
                break;
            case POINT_TYPE_NOLABEL:
                label = NULL;
        }
    return label;
}

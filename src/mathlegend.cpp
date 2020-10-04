#include "../include/mathlegend.h"

// Default sizes and margins
static const int L_DEFAULT_SIZE = 20;
static const int L_BORDER_MARGIN = 10;
static const int L_TEXT_MARGIN = 5;
static const int L_LINE_MARGIN = 5;

// Default colours
static const wxColor DEFAULT_BACKGROUND_COLOUR = *wxWHITE;
static const wxColor DEFAULT_FRAME_COLOUR = *wxBLACK;
static const wxColor DEFAULT_TEXT_COLOUR = *wxBLACK;
static const int DEFAULT_SHADOW_THICKNESS = 3;

// Curve colour line length in pixels
static const int L_LINE_LENGTH = 50;


MathLegend::MathLegend(std::vector<IDrawableFunction*> *functions)
{
    m_functions = functions;
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
}

/**\brief Sets legend text colour.
*
* A parent panel has to be refreshed to show changes.
* \param colour Colour to set.
*/
void MathLegend::SetTextColour(wxColour colour)
{
    m_colours.text = colour;
}

/**\brief Sets legend frame colour.
*
* A parent panel has to be refreshed to show changes.
* \param colour Colour to set.
*/
void MathLegend::SetFrameColour(wxColour colour)
{
    m_colours.frame = colour;
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
    if((m_functions->size()<1)||(!m_is_visible))
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

    for(std::vector<IDrawableFunction*>::iterator it=m_functions->begin(); it!=m_functions->end(); ++it)
    {
        // Function name
        text = (*it)->GetName();
        dc.DrawText(text, m_metrics.x + L_BORDER_MARGIN + L_LINE_LENGTH + L_TEXT_MARGIN, m_metrics.y + pos - text_height/2 - L_LINE_MARGIN/2);
        // Function line
        colour = (*it)->GetColour();
        pen.SetColour(colour);
        dc.SetPen(pen);
        dc.DrawLine(m_metrics.x + L_BORDER_MARGIN, m_metrics.y + pos, m_metrics.x + L_BORDER_MARGIN + L_LINE_LENGTH, m_metrics.y + pos);
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

    if(m_functions->size()<1)
        return 0;

    for(std::vector<IDrawableFunction*>::const_iterator it=m_functions->begin(); it!=m_functions->end(); ++it)
    {
        text_length = dc.GetTextExtent((*it)->GetName()).GetWidth();
        if(text_length>text_max_length)
            text_max_length = text_length;
    }
    return L_BORDER_MARGIN*2 + L_LINE_LENGTH + L_TEXT_MARGIN + text_max_length;
}

// Get maximum height of the legend according to text height
int MathLegend::GetMaxHeight(const wxDC &dc) const
{
    if(m_functions->size()<1)
        return 0;

    int text_height = dc.GetFont().GetPixelSize().GetHeight();
    int pos = text_height/2 + L_LINE_MARGIN;
    int step_size = text_height + L_LINE_MARGIN;

    for(std::vector<IDrawableFunction*>::const_iterator it=m_functions->begin(); it!=m_functions->end(); ++it)
    {
        pos += step_size;
    }
    return pos - step_size + text_height/2 + L_LINE_MARGIN;
}


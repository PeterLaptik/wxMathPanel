#include "../include/wxmathpanel.h"
#include <wx/dcbuffer.h>

#define MATH_PANEL_TURN_ON_DOUBLE_BUFFERING

wxDEFINE_EVENT(wxMATHPANEL_MOUSE_MOVE, MouseMoveEvent);

// Default screen position borders
// top left corner:     [- MATH_DEF_POSITION, MATH_DEF_POSITION]
// bottom right corner: [MATH_DEF_POSITION, - MATH_DEF_POSITION]
static const int MATH_DEF_POSITION = 10;

// Minimum numeric value for logarithmic scaled axis
static const double MATH_MIN_VALUE_FOR_LOG = 0.1;

// Maximum and minimum exponent values
// Means edge borders for the canvas
static const int MATH_MAX_EXPONENT = 10;
static const int MATH_MIN_EXPONENT = -10;

// Zero-value
// Any label that is less than zero-value will be shown as zero
static const double MATH_ZERO_NUMBER = 1e-14;

// Minimum margin (in pixels) between net lines on the canvas
// Any net lines will be drawn with a distance not less than this value
static const int MATH_MIN_MIDDLE_LINE_MARGIN = 75;

// Net lines serif size
static const int MATH_NET_SERIF_SIZE = 10;

// Minimum panel size to be drawn (in pixels)
static const int MATH_MIN_ACTUAL_SIZE = 10;

// Default multiplier for the net lines
// Each label will be equal to multiplier*(2*integer)*10^x.
// Where x = -n, -n+1, ..., 0, ..., n+1, n
static const int MATH_MAX_BASE_NUMBER = 5;

// Zoom speed coefficient
static const double SCALE_ZOOM_COEFF = 1.25;

// Axis arrows size in pixels
static const int MATH_ARROW_LENGTH = 10;
static const int MATH_ARROW_WIDTH = 5;

// Arrow lines margin
// Distance from panel borders to axises
// when the axises are drawn at the edge of a panel
static const int MATH_AXIS_MARGIN_H = 2;
static const int MATH_AXIS_MARGIN_V = 0;

// Font-axis / font-line / font-frame margin
static const int MATH_FONT_MARGIN = 2;
static const int MATH_FONT_FRAME_MARGIN = 4;

// Margin between exponent and mantissa for logarithmic axis labels
static const int MATH_FONT_EXP_MARGIN = 2;

// Default value for out-of-canvas coordinates
static const int MATH_OUT_OF_CANVAS_VALUE = 20;

// Label vertical shift
static const int MATH_LABEL_SHIFT = 20;
static const wxString MATH_X_NAME = wxT("x");
static const wxString MATH_Y_NAME = wxT("y");
static const wxString MATH_ZERO_LABEL = wxT("0");
static const wxString MATH_DEC_LABEL = wxT("10");

// Default colours
static const wxColour MATH_DEF_AXIS_COLOUR = *wxBLACK;
static const wxColour MATH_DEF_NET_COLOUR(200,200,200);
static const wxColour MATH_DEF_CURVE_COLOUR = *wxBLACK;
static const wxColour MATH_DEF_LABEL_COLOUR = *wxBLACK;

// Default view and behavior
static const bool MATH_DEFAULT_FRAMED = false;
static const bool MATH_DEFAULT_VISIBLE_NETWORK_LINES = true;
static const bool MATH_DEFAULT_VISIBLE_NETWORK_LABLES = true;
static const bool MATH_DEFAULT_LOG_AXISES = false;
static const bool MATH_DEFAULT_MOVABLE = true;
static const bool MATH_DEFAULT_SCALABLE = true;


/**\brief Default constructor.
* \param parent The parent window.
* \param winid An identifier for the panel. wxID_ANY is taken to mean a default.
* \param pos The panel position.
* \param size The panel size.
* \param style The window style.
* \param name The window name.
*/
wxMathPanel::wxMathPanel(wxWindow *parent,
                        wxWindowID winid,
                        const wxPoint &pos,
                        const wxSize &size,
                        long style,
                        const wxString &name)
{
    Create(parent, winid, pos, size, style, name);

    // Events handlers
    Bind(wxEVT_PAINT, &wxMathPanel::EventPaint, this);
    Bind(wxEVT_SIZE, &wxMathPanel::EventResize, this);
    Bind(wxEVT_LEFT_DOWN, &wxMathPanel::EventMouseLeftButtonDown, this);
    Bind(wxEVT_LEFT_UP, &wxMathPanel::EventMouseLeftButtonUp, this);
    Bind(wxEVT_MOUSEWHEEL, &wxMathPanel::EventMouseWheel, this);
    Bind(wxEVT_MOTION, &wxMathPanel::EventMouseMove, this);
    Bind(wxEVT_LEAVE_WINDOW, &wxMathPanel::EventMouseLeave, this);

    // Canvas surface dimensions
    m_borders.left = m_last_left_border = -MATH_DEF_POSITION;
    m_borders.right = m_last_right_border = MATH_DEF_POSITION;
    m_borders.bottom = m_last_bottom_border = -MATH_DEF_POSITION;
    m_borders.top = m_last_top_border = MATH_DEF_POSITION;

    // Canvas state
    m_is_framed = MATH_DEFAULT_FRAMED;
    m_is_dragging = false;
    m_is_movable = MATH_DEFAULT_MOVABLE;
    m_scalable.is_scalable_x = m_scalable.is_scalable_y = MATH_DEFAULT_SCALABLE;
    m_is_x_logarithmic = m_is_y_logarithmic = MATH_DEFAULT_LOG_AXISES;

    // Default borders restraints
    m_restraints.right = m_restraints.top = pow(10, MATH_MAX_EXPONENT);
    m_restraints.left = m_restraints.bottom = 0 - pow(10, MATH_MAX_EXPONENT);

    // Default properties
    m_width = this->GetSize().GetWidth();
    m_height = this->GetSize().GetHeight();

    // Default settings
    m_base_number_horizontal = m_base_number_vertical = MATH_MAX_BASE_NUMBER;
    m_minimum_log_value = MATH_MIN_VALUE_FOR_LOG;
    m_min_line_margin = MATH_MIN_MIDDLE_LINE_MARGIN;
    m_xname = MATH_X_NAME;
    m_yname = MATH_Y_NAME;

    // Default network lines visibility
    m_show_x_net_lines = m_show_y_net_lines = MATH_DEFAULT_VISIBLE_NETWORK_LINES;
    m_show_x_middle_lines = m_show_y_middle_lines = MATH_DEFAULT_VISIBLE_NETWORK_LINES;
    m_show_x_labels = m_show_y_labels = MATH_DEFAULT_VISIBLE_NETWORK_LABLES;

    // Colors
    m_colour_net_lines = MATH_DEF_NET_COLOUR;
    m_colour_axis = MATH_DEF_AXIS_COLOUR;
    m_colour_label = MATH_DEF_LABEL_COLOUR;

    #ifdef MATH_PANEL_TURN_ON_DOUBLE_BUFFERING
        this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    #endif // MATH_PANEL_TURN_ON_DOUBLE_BUFFERING
    this->Refresh();
}

/**\brief Destructor. */
wxMathPanel::~wxMathPanel()
{ }


// Events
// Save actual metrics on panel resized
void wxMathPanel::EventResize(wxSizeEvent &event)
{
    m_width = this->GetSize().GetWidth();
    m_height = this->GetSize().GetHeight();
    this->Refresh();
}

// Remember start position for dragging if left mouse button has been pressed
void wxMathPanel::EventMouseLeftButtonDown(wxMouseEvent &event)
{
    if(!m_is_movable)
        return;

    m_is_dragging = true;

    // Save start coordinates
    m_start_x = event.GetX();    // start x-position for dragging
    m_start_y = event.GetY();    // start y-position for dragging
}

// Stop dragging on mouse left button has been released
void wxMathPanel::EventMouseLeftButtonUp(wxMouseEvent &event)
{
    m_is_dragging = false;
}

// Stop dragging on mouse leaves panel
void wxMathPanel::EventMouseLeave(wxMouseEvent &event)
{
    m_is_dragging = false;
}

// Drag screen if left a mouse button is being pressed
void wxMathPanel::EventMouseMove(wxMouseEvent &event)
{
    double dx, dy;
    double real_x, real_y;
    int x, y;

    // Get real coordinates that match to the mouse pointer
    x = m_x = real_x = event.GetX();
    y = m_y = real_y = event.GetY();

    // Send event MouseMoveEvent
    MouseMoveEvent mouse_event(wxMATHPANEL_MOUSE_MOVE, this->GetId());
    ReverseTranslateCoordinates(real_x, real_y);
    mouse_event.X = real_x;
    mouse_event.Y = real_y;
    wxPostEvent(this, mouse_event);

    if((!m_is_dragging)||(!m_is_movable))
        return;

    dx = m_start_x - x;
    dy = m_start_y - y;
    dx /= m_width;
    dx *= (m_borders.right - m_borders.left);
    dy /= m_height;
    dy *= (m_borders.top - m_borders.bottom);

    if(!m_is_x_logarithmic) // logarithmic axises are unmovable
    {
        m_borders.left += dx;
        m_borders.right += dx;
        m_start_x = x;

        // Check restraints
        if(m_restraints.left>m_borders.left)
        {
            dx = m_restraints.left - m_borders.left;
            m_borders.left += dx;
            m_borders.right += dx;
        }

        if(m_restraints.right<m_borders.right)
        {
            dx = m_restraints.right - m_borders.right;
            m_borders.left += dx;
            m_borders.right += dx;
        }
    }

    if(!m_is_y_logarithmic) // logarithmic axises are unmovable
    {
        m_borders.top -= dy;
        m_borders.bottom -= dy;
        m_start_y = y;

        if(m_restraints.top<m_borders.top)
        {
            dy = m_borders.top - m_restraints.top;
            m_borders.top -= dy;
            m_borders.bottom -= dy;
        }

        if(m_restraints.bottom>m_borders.bottom)
        {
            dy = m_borders.bottom - m_restraints.bottom;
            m_borders.top -= dy;
            m_borders.bottom -= dy;
        }
    }

    this->Refresh();
}

// Scale image on mouse wheel event
void wxMathPanel::EventMouseWheel(wxMouseEvent &event)
{
    if((!m_scalable.is_scalable_x)&&(!m_scalable.is_scalable_y))
        return;

    if (event.GetWheelRotation()<0)
        ZoomOut();

    if (event.GetWheelRotation()>0)
        ZoomIn();
}

void wxMathPanel::EventPaint(wxPaintEvent &event)
{
    #ifdef MATH_PANEL_TURN_ON_DOUBLE_BUFFERING
        wxBufferedPaintDC dc(this);
        dc.Clear();
    #else
        wxPaintDC dc(this);
    #endif // MATH_PANEL_TURN_ON_DOUBLE_BUFFERING

    dc.SetTextForeground(m_colour_label);

    if(m_width<MATH_MIN_ACTUAL_SIZE || m_height<MATH_MIN_ACTUAL_SIZE)
        return;

    CheckBorders(dc);

    // Network lines
    if(!m_is_y_logarithmic)
        DrawNetworkHorizontal(dc);
    else
        DrawNetworkLogHorizontal(dc);

    if(!m_is_x_logarithmic)
        DrawNetworkVertical(dc);
    else
        DrawNetworkLogVertical(dc);

    DrawAxises(dc);

    // Draw additions - mock for subclasses
    DrawAfter(dc);
}

// Check borders values to avoid errors
void wxMathPanel::CheckBorders(wxDC &dc)
{
    const int MAX_LOOP = 5;
    double deltaX;
    double deltaY;
    wxString label_start_x, label_end_x;
    wxString label_start_y, label_end_y;

    // Exclude negative values for the logarithmic axises
    if((m_is_x_logarithmic)&&(m_borders.left<=0))
    {
        deltaX = m_minimum_log_value - m_borders.left;
        m_borders.left += deltaX;
        m_borders.right += deltaX;
    }

    if((m_is_y_logarithmic)&&(m_borders.bottom<=0))
    {
        deltaY = m_minimum_log_value - m_borders.bottom;
        m_borders.bottom += deltaY;
        m_borders.top += deltaY;
    }

    // Trying to zoom out the screen if the selected scale is too small
    int loop_flag = 0;
    label_start_x<<m_borders.left;
    label_end_x<<m_borders.right;
    label_start_y<<m_borders.bottom;
    label_end_y<<m_borders.top;
    while((label_start_x==label_end_x)||(label_start_y==label_end_y))
    {
        deltaX = ((m_borders.right - m_borders.left)*SCALE_ZOOM_COEFF);
        deltaX -= m_borders.right - m_borders.left;
        deltaX /= 2;
        m_borders.left -= deltaX;
        m_borders.right += deltaX;

        deltaY = ((m_borders.top - m_borders.bottom)*SCALE_ZOOM_COEFF);
        deltaY -= m_borders.top - m_borders.bottom;
        deltaY /= 2;
        m_borders.top += deltaY;
        m_borders.bottom -= deltaY;

        label_start_x<<m_borders.left;
        label_end_x<<m_borders.right;
        label_start_y<<m_borders.bottom;
        label_end_y<<m_borders.top;

        loop_flag++;
        if(loop_flag>=MAX_LOOP)
            break;
    }

    // Check borders restraints
    if(m_borders.left<m_restraints.left)
        m_borders.left=m_restraints.left;

    if(m_borders.right>m_restraints.right)
        m_borders.right=m_restraints.right;

    if(m_borders.top>m_restraints.top)
        m_borders.top=m_restraints.top;

    if(m_borders.bottom<m_restraints.bottom)
        m_borders.bottom=m_restraints.bottom;
}

/**\brief Calculates real scale difference for the logarithmic X-axis that match to one-pixel step on the panel.
* (for the defined point)
* \param x_point Defined point for a step from.
* \return Pixel step value in real scale.
*/
double wxMathPanel::GetLogStepFor(double x_point)
{
    double a, b, c;
    double x1 = x_point;

    TranslateXCoordinate(x1);
    x1++;

    a = log10(m_borders.left);
    b = log10(m_borders.right);
    c = a + x1/m_width*(b - a);
    x1 = pow(10, c);

    return fabs(x_point - x1);
}

/**\brief Drawing routine that is being called each time after paint event.
* Mock for drawing in subclasses.
* \param dc Device context for painting.
*/
void wxMathPanel::DrawAfter(wxDC &dc)
{
    return;
}

/**\brief Translates real coordinates to the coordinates on the panel
* (real x -> x on panel, real y -> y on panel).
* \param x Real x-coordinate to translate.
* \param y Real y-coordinate to translate.
*/
void wxMathPanel::TranslateCoordinates(double &x, double &y)
{
    double a, b;    // logarithmic borders
    double c;       // logarithmic position

    if (!m_is_x_logarithmic)
    {
        x = m_width*(x - m_borders.left)/(m_borders.right - m_borders.left);
    }
    else if (x!=0)
    {
        a = log10(m_borders.left);
        b = log10(m_borders.right);
        c = log10(x);
        x = m_width*(c - a)/(b - a);
    }
    else {x = 0;}

    if (!m_is_y_logarithmic)
    {
        y = m_height - m_height*(y - m_borders.bottom)/(m_borders.top - m_borders.bottom);
    }
    else if (y!=0)
    {
        a = log10(m_borders.bottom);
        b = log10(m_borders.top);
        if(y<=0)
        {
            y = m_height + MATH_OUT_OF_CANVAS_VALUE;
        }
        else
        {
            c = log10(y);
            y = m_height - m_height*(c - a)/(b - a);
        }
    }
    else { y = m_height /* bottom border */;}

    // Prevent overflows on drawing
    if(x<0)
        x = - MATH_OUT_OF_CANVAS_VALUE;

    if(x>m_width)
        x = m_width + MATH_OUT_OF_CANVAS_VALUE;

    if(y<0)
        y = - MATH_OUT_OF_CANVAS_VALUE;

    if(y>m_height)
        y = m_height + MATH_OUT_OF_CANVAS_VALUE;

    if(m_is_framed)
    {
        x += m_borders.frame_left;
        y -= m_borders.frame_bottom;
    }
}

/**\brief Translates real x-coordinate to the coordinate on the panel
* (real x -> x on panel).
* \param x Real x-coordinate to translate.
*/
void wxMathPanel::TranslateXCoordinate(double &x)
{
    double a, b;    // logarithmic borders
    double c;       // logarithmic position

    if (!m_is_x_logarithmic)
    {
        x = m_width*(x - m_borders.left)/(m_borders.right - m_borders.left);
    }
    else if (x!=0)
        {
            a = log10(m_borders.left);
            b = log10(m_borders.right);
            c = log10(x);
            x = m_width*(c - a)/(b - a);
        }
    else {x = 0;}

    // Prevent overflows on drawing
    if(x<0)
        x = - MATH_OUT_OF_CANVAS_VALUE;

    if(x>m_width)
        x = m_width + MATH_OUT_OF_CANVAS_VALUE;

    if(m_is_framed)
        x += m_borders.frame_left;
}

/**\brief Translates real y-coordinate to the coordinate on the panel
* (real y -> y on panel).
* \param y Real y-coordinate to translate.
*/
void wxMathPanel::TranslateYCoordinate(double &y)
{
    double a, b;    // logarithmic borders
    double c;       // logarithmic position

    if (!m_is_y_logarithmic)
    {
        y = m_height - m_height*(y - m_borders.bottom)/(m_borders.top - m_borders.bottom);
    }
    else if (y!=0)
        {
            a = log10(m_borders.bottom);
            b = log10(m_borders.top);
            c = log10(y);
            y = m_height - m_height*(c - a)/(b - a);
        }
    else { y = m_height /* bottom border */;}

    if(y<0)
        y = - MATH_OUT_OF_CANVAS_VALUE;

    if(y>m_height)
        y = m_height + MATH_OUT_OF_CANVAS_VALUE;

    if(m_is_framed)
        y -= m_borders.frame_bottom;
}

void wxMathPanel::ReverseTranslateCoordinates(double &x, double &y)
{
    double a, b;    // logarithmic borders
    double c;       // logarithmic position

    if(m_is_framed)
    {
        x -= m_borders.frame_left;
        y += m_borders.frame_bottom;
    }

    double left = m_borders.left;
    double right = m_borders.right;
    double top = m_borders.top;
    double bottom = m_borders.bottom;

    if (!m_is_x_logarithmic)
    {
        x = left + (right - left)/(m_width)*x;

    }
    else
    {
        a = log10(left);
        b = log10(right);
        c = a + x/m_width*(b - a);
        x = pow(10, c);
    }

    if (!m_is_y_logarithmic)
    {
        y = top - (top - bottom)/m_height*y;
    }
    else
    {
        a = log10(bottom);
        b = log10(top);
        c = a + (m_height - y)/m_height*(b - a);
        y = pow(10, c);
    }
}

// Assign frame sizes for linear scales
void wxMathPanel::AssignFrames(wxDC &dc, int start, int step)
{
    int result = 0;
    int text_size;
    wxString label_val;

    if(!m_is_framed)
    {
        m_borders.frame_bottom = m_borders.frame_left = 0;
        return;
    }

    while(start<m_borders.top)
    {
        label_val.Clear();
        label_val<<start;
        text_size = dc.GetTextExtent(label_val).GetWidth();
        if(result<text_size)
            result = text_size;

        start += step;
    }

    m_borders.frame_left = result + MATH_FONT_FRAME_MARGIN;
    m_borders.frame_bottom = dc.GetFont().GetPixelSize().GetHeight() + MATH_FONT_FRAME_MARGIN;
}

// Assign frames for logarithmic scales
void wxMathPanel::AssignFrames(wxDC &dc)
{
    wxString txt = MATH_DEC_LABEL;
    txt<<round(log10(m_borders.right));
    m_borders.frame_left = dc.GetTextExtent(txt).GetWidth() + MATH_FONT_FRAME_MARGIN;
    m_borders.frame_bottom = dc.GetFont().GetPixelSize().GetHeight() + MATH_FONT_FRAME_MARGIN;
}

// Draws axises O-x, O-y
void wxMathPanel::DrawAxises(wxDC &dc)
{
    double x_1, y_1;
    double x_2, y_2;
    // Drawing settings
    wxPen pen(m_colour_axis);
    wxBrush brush(m_colour_axis);
    dc.SetPen(pen);
    // Arrows points sets
    wxPoint vert_arrow[3];
    wxPoint hor_arrow[3];

    // Vertical axis
    x_1 = m_borders.right;
    y_1 = 0;
    ReverseTranslateCoordinates(x_1, y_1);
    if((m_borders.left<=0)&&(m_borders.right>=0))
    {
        x_1 = 0;
        x_2 = 0;
        y_1 = m_borders.top;
        y_2 = m_borders.bottom;
        TranslateCoordinates(x_1, y_1);
        TranslateCoordinates(x_2, y_2);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawLine(x_1, y_1, x_2, y_2);
        // Draw arrow
        vert_arrow[0] = wxPoint(x_1, 0);
        vert_arrow[1] = wxPoint(x_1 - MATH_ARROW_WIDTH/2, MATH_ARROW_LENGTH);
        vert_arrow[2] = wxPoint(x_1 + MATH_ARROW_WIDTH/2, MATH_ARROW_LENGTH);
        dc.SetBrush(brush);
        dc.DrawPolygon(3, vert_arrow);
        dc.DrawText(m_yname, x_1 + MATH_ARROW_WIDTH + MATH_FONT_MARGIN, 0);
    }
    else
    {
        // Axis is out of screen
        x_1 = x_2 = m_borders.left;
        y_1 = m_borders.top;
        y_2 = m_borders.bottom;
        TranslateCoordinates(x_1, y_1);
        TranslateCoordinates(x_2, y_2);
        dc.DrawLine(x_1 + MATH_AXIS_MARGIN_V, y_1, x_1 + MATH_AXIS_MARGIN_V, y_2);
        vert_arrow[0] = wxPoint(x_1 + MATH_AXIS_MARGIN_V, 0);
        vert_arrow[1] = wxPoint(x_1 - MATH_ARROW_WIDTH/2 + MATH_AXIS_MARGIN_V, MATH_ARROW_LENGTH);
        vert_arrow[2] = wxPoint(x_1 + MATH_ARROW_WIDTH/2 + MATH_AXIS_MARGIN_V, MATH_ARROW_LENGTH);
        dc.SetBrush(brush);
        dc.DrawPolygon(3, vert_arrow);
        dc.DrawText(m_yname, MATH_FONT_MARGIN + MATH_ARROW_WIDTH, 0);
    }

    // Horizontal axis
    if((m_borders.bottom<=0)&&(m_borders.top>=0))
    {
        x_1 = m_borders.left;
        x_2 = m_borders.right;
        y_1 = y_2 = 0;
        TranslateCoordinates(x_1, y_1);
        TranslateCoordinates(x_2, y_2);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawLine(x_1, y_1, x_2, y_2);
        // Draw arrow
        x_2 = m_width;
        hor_arrow[0] = wxPoint(x_2, y_1);
        hor_arrow[1] = wxPoint(x_2 - MATH_ARROW_LENGTH, y_1 + MATH_ARROW_WIDTH/2);
        hor_arrow[2] = wxPoint(x_2 - MATH_ARROW_LENGTH, y_1 - MATH_ARROW_WIDTH/2);
        dc.SetBrush(brush);
        dc.DrawPolygon(3, hor_arrow);
        dc.DrawText(m_xname,
                    m_width - dc.GetTextExtent(m_xname).GetWidth() - MATH_FONT_MARGIN,
                    y_1 - MATH_ARROW_WIDTH/2 - MATH_FONT_MARGIN - dc.GetFont().GetPixelSize().GetHeight());
    }
    else
    {
        // Axis is out of screen
        x_1 = m_borders.left;
        x_2 = m_borders.right;
        y_1 = y_2 = m_borders.bottom;
        TranslateCoordinates(x_1, y_1);
        TranslateCoordinates(x_2, y_2);
        x_2 = m_width;
        dc.DrawLine(x_1, y_1 - (m_is_y_logarithmic ? 0 : MATH_AXIS_MARGIN_H),
                    x_2, y_1 - (m_is_y_logarithmic ? 0 : MATH_AXIS_MARGIN_H));

        hor_arrow[0] = wxPoint(x_2, y_1 - (m_is_y_logarithmic ? 0 : MATH_AXIS_MARGIN_H));
        hor_arrow[1] = wxPoint(x_2 - MATH_ARROW_LENGTH, y_1 - (m_is_y_logarithmic ? 0 : MATH_AXIS_MARGIN_H) + MATH_ARROW_WIDTH/2);
        hor_arrow[2] = wxPoint(x_2 - MATH_ARROW_LENGTH, y_1 - (m_is_y_logarithmic ? 0 : MATH_AXIS_MARGIN_H) - MATH_ARROW_WIDTH/2);
        dc.SetBrush(brush);
        dc.DrawPolygon(3, hor_arrow);
        dc.DrawText(m_xname,
                    m_width - dc.GetTextExtent(m_xname).GetWidth() - MATH_FONT_MARGIN,
                    m_height - MATH_ARROW_WIDTH/2 - MATH_FONT_MARGIN - dc.GetFont().GetPixelSize().GetHeight());
    }

    // Output zero-value
    if((m_is_x_logarithmic)&&(m_is_y_logarithmic))  // do not show for both logarithmic axises
        return;

    // Draw zero value with respect to intersections
    x_1 = y_1 = 0;
    TranslateCoordinates(x_1, y_1);
    if((m_is_x_logarithmic)&&(y_1 + dc.GetFont().GetPixelSize().GetHeight() + MATH_FONT_MARGIN > m_height))
        return;

    if(x_1 + dc.GetTextExtent(m_xname).GetWidth() + MATH_FONT_MARGIN > m_width - dc.GetTextExtent(MATH_ZERO_LABEL).GetWidth())
        return;

    if(y_1 - dc.GetTextExtent(MATH_ZERO_LABEL).GetHeight() < MATH_ARROW_WIDTH + MATH_FONT_MARGIN*2)
        return;

    if(((m_borders.left<=0)&&(m_borders.right>=0))&&
       ((m_borders.bottom<=0)&&(m_borders.top>=0)))
    {
        dc.DrawText(MATH_ZERO_LABEL,
                    x_1 + MATH_FONT_MARGIN,
                    y_1 - dc.GetFont().GetPixelSize().GetHeight() - MATH_FONT_MARGIN);
    }
    else if((m_borders.left>0)||(m_borders.right<0))
    {
        dc.DrawText(MATH_ZERO_LABEL,
                    MATH_FONT_MARGIN,
                    y_1 - dc.GetFont().GetPixelSize().GetHeight() - MATH_FONT_MARGIN);
    }
    else if((m_borders.bottom>0)||(m_borders.bottom<0))
    {
        dc.DrawText(MATH_ZERO_LABEL,
                    x_1 + MATH_FONT_MARGIN,
                    m_height - MATH_LABEL_SHIFT);
    }
}

// Draws horizontal middle lines
// Calculates best line margins and base points
void wxMathPanel::DrawNetworkHorizontal(wxDC &dc)
{
    double y;
    wxString label_out;
    wxPen pen;

    wxColour net_colour = m_show_x_net_lines ? m_colour_net_lines : m_colour_axis;
    pen.SetColour(net_colour);
    dc.SetPen(pen);

    // Finding appropriate exponent for the screen size values
    int exponent = 0;
    if(m_borders.top - m_borders.bottom>1)
    {
        while ((static_cast<int>(m_borders.top - m_borders.bottom))/static_cast<int>(pow(10,exponent))!=0)
        {
            ++exponent;
            if (exponent>MATH_MAX_EXPONENT)
                break;
        }
        exponent--;
    }
    else
    {
        while (((m_borders.top - m_borders.bottom))/pow(10,exponent)<1)
        {
            --exponent;
            if (exponent<MATH_MIN_EXPONENT)
                break;
        }
    }

    // Align network as per line number
    // Add or remove net lines
    int base_number = m_base_number_vertical;

    // Expand network if current margin is too small
    int middle_lines_margin = m_height/((m_borders.top - m_borders.bottom)/(base_number*pow(10, exponent-1)));  // height / number of lines
    while(middle_lines_margin<m_min_line_margin)
    {
        base_number *= 2;
        middle_lines_margin = m_height/((m_borders.top - m_borders.bottom)/(base_number*pow(10, exponent-1)));
    }

    // Number for incrementing (step value)
    double incrementor = base_number*pow(10, exponent-1);
    // Net lines start position
    double start_y = static_cast<int>(m_borders.bottom/incrementor)*incrementor;

    // Assign frame margins
    // Frame margins depends on labels width
    AssignFrames(dc, start_y, incrementor);

    // Label and net-lines output
    int font_size = dc.GetFont().GetPixelSize().GetHeight();
    int font_shift = MATH_FONT_MARGIN + font_size;

    while(start_y<m_borders.top)
    {
        // Do not show zero
        if(fabs(start_y)<MATH_ZERO_NUMBER)
        {
            start_y += incrementor;
            continue;
        }

        // Net line
        y = start_y;
        TranslateYCoordinate(y);

        if(m_show_x_net_lines)
            dc.DrawLine(0, y, m_width, y);

        // Labels
        if(((start_y > 0)&&(y <= (font_size + MATH_FONT_MARGIN)*2)) // positive values - axis label intersection
           ||((start_y < 0)&&(y <= (font_size + MATH_FONT_MARGIN))) // negative values - axis label intersection
           ||((start_y < 0)&&(y > m_height - 2*(font_size + MATH_FONT_MARGIN)))  // negative values - bottom border intersection
           ||((start_y > 0)&&(y > m_height - (font_size + MATH_FONT_MARGIN)))  // positive values - bottom border intersection
           ||(!m_show_y_labels))
        {
            start_y += incrementor;
            continue;   // do not draw text too close to the border
        }

        if(!m_show_x_net_lines)
            dc.DrawLine(0, y, MATH_NET_SERIF_SIZE, y); // make serif

        label_out.Clear();
        label_out<<start_y;
        font_shift = start_y > 0 ? - MATH_FONT_MARGIN - font_size : 0;
        dc.DrawText(label_out, 0 + MATH_FONT_MARGIN, y + font_shift);

        start_y += incrementor;
    }
}

// Draws horizontal middle lines for the logarithmic scale
void wxMathPanel::DrawNetworkLogHorizontal(wxDC &dc)
{
    wxString label_out;
    int label_width;
    int label_height;
    wxFont default_font = dc.GetFont();
    wxFont small_font = default_font.Smaller();
    wxPen line_pen(m_colour_net_lines);
    wxPen serif_pen(m_colour_axis);
    double x1, x2, y;

    AssignFrames(dc);
    int order = log10(m_borders.bottom);

    x1 = m_borders.left;
    x2 = m_borders.right;
    TranslateXCoordinate(x1);
    TranslateXCoordinate(x2);

    while(pow(10, order)<m_borders.top)
    {
        dc.SetPen(serif_pen);
        y = pow(10, order);
        TranslateYCoordinate(y);

        if (m_show_x_net_lines)
            dc.DrawLine(x1, y, x2, y);

        label_height = dc.GetFont().GetPixelSize().GetHeight();
        y = m_height - m_height*(order - log10(m_borders.bottom))/(log10(m_borders.top) - log10(m_borders.bottom)); // label position
        if((m_show_y_labels)&&(y > label_height + MATH_FONT_MARGIN))
        {
            // Mantissa output
            label_out = MATH_DEC_LABEL;
            label_width = dc.GetTextExtent(label_out).GetWidth();
            dc.DrawText(label_out, 0, y);
            // Exponent output
            label_out = wxString::Format(wxT("%d"), order);
            dc.SetFont(small_font);
            dc.DrawText(label_out, 0 + label_width + MATH_FONT_EXP_MARGIN, y);
            dc.SetFont(default_font);
        }

        if(!m_show_x_middle_lines)
        {
            order++;
            continue;
        }

        dc.SetPen(line_pen);
        for (int i=1; i<10; ++i)
        {
            if (pow(10, order) + (pow(10, order+1) - pow(10, order))/(10-1)*i>m_borders.top)
                break;

            y = pow(10, order) + (pow(10, order+1) - pow(10, order))/(10-1)*i;
            TranslateYCoordinate(y);
            dc.DrawLine(x1, y, x2, y);

        }
        order++;
    }
}

// Draws vertical middle lines
// Calculates best line margins and base points
void wxMathPanel::DrawNetworkVertical(wxDC &dc)
{
    double x;
    wxString label_out;
    wxPen pen;

    wxColour net_colour = m_show_x_net_lines ? m_colour_net_lines : m_colour_axis;
    pen.SetColour(net_colour);
    dc.SetPen(pen);

    // Finding appropriate exponent for the screen size values
    int exponent = 0;
    if(m_borders.right - m_borders.left>1)
    {
        while ((static_cast<int>(m_borders.right - m_borders.left))/static_cast<int>(pow(10,exponent))!=0)
        {
            ++exponent;
            if (exponent>MATH_MAX_EXPONENT)
                break;
        }
        exponent--;
    }
    else
    {
        while (((m_borders.right - m_borders.left))/pow(10,exponent)<1)
        {
            --exponent;
            if (exponent<MATH_MIN_EXPONENT)
                break;
        }
    }

    // Align network as per line number
    // Add or remove net lines
    int base_number = m_base_number_horizontal;

    // Expand network if current margin is too small
    int middle_lines_margin = m_width/((m_borders.right - m_borders.left)/(base_number*pow(10, exponent-1)));  // height / number of lines
    while(middle_lines_margin<m_min_line_margin)
    {
        base_number *= 2;
        middle_lines_margin = m_width/((m_borders.right - m_borders.left)/(base_number*pow(10, exponent-1)));
    }

    // Number for incrementing
    double incrementor = base_number*pow(10, exponent-1);

    // Net lines start position
    double start_x = static_cast<int>(m_borders.left/incrementor)*incrementor;

    // Right margin value
    int axis_label_width = dc.GetTextExtent(m_xname).GetWidth();
    if(axis_label_width<MATH_ARROW_LENGTH)
        axis_label_width = MATH_ARROW_LENGTH;

    // Label and net-lines output
    int text_width;
    int font_shift;
    while(start_x<m_borders.right)
    {
        // Do not show zero
        if(fabs(start_x)<MATH_ZERO_NUMBER)
        {
            start_x += incrementor;
            continue;
        }

        x = start_x;
        TranslateXCoordinate(x);

        if(m_show_y_net_lines)
            dc.DrawLine(x, 0, x, m_height);

        // Output labels
        label_out.Clear();
        label_out<<start_x;

        text_width = dc.GetTextExtent(label_out).GetWidth();
        font_shift = start_x > 0 ? 0 : text_width;
        // Check label position
        if(((start_x > 0)&&(x - text_width < 0))    // left border - label intersection
           ||((start_x < 0)&&(x - font_shift - text_width< 0))
           ||(x + text_width + MATH_FONT_MARGIN > m_width)  // right border - label intersection
           ||(!m_show_x_labels))
        {
            start_x += incrementor;
            continue;   // do not draw text too close to the border
        }

        // Exclude intersections
        if(x + text_width - font_shift > m_width - MATH_FONT_MARGIN - MATH_AXIS_MARGIN_H - axis_label_width) // value - axis label intersections
        {
            start_x += incrementor;
            continue;
        }

        if(!m_show_y_net_lines)
            dc.DrawLine(x, m_height, x, m_height - MATH_NET_SERIF_SIZE); // make serif

        dc.DrawText(label_out, x + MATH_AXIS_MARGIN_H - font_shift, m_height - MATH_LABEL_SHIFT);
        start_x += incrementor;
    }
}

// Draws vertical middle lines for the logarithmic scale
void wxMathPanel::DrawNetworkLogVertical(wxDC &dc)
{
    wxString label_out;
    int label_width;
    wxFont default_font = dc.GetFont();
    wxFont small_font = default_font.Smaller();
    wxPen line_pen(m_colour_net_lines);
    wxPen serif_pen(m_colour_axis);
    double x, y1, y2;    // coordinates to draw

    int order = log10(m_borders.left);

    y1 = m_borders.bottom;
    y2 = m_borders.top;
    TranslateYCoordinate(y1);
    TranslateYCoordinate(y2);

    while(pow(10, order)<m_borders.right)
    {
        dc.SetPen(serif_pen);
        x = pow(10, order);
        TranslateXCoordinate(x);

        if (m_show_y_net_lines)
            dc.DrawLine(x, y1, x, y2);

        label_out = MATH_DEC_LABEL;
        label_out<<order;
        x = m_width*(order - log10(m_borders.left))/(log10(m_borders.right) - log10(m_borders.left)); // label position
        if((m_show_x_labels)
           &&(x + dc.GetTextExtent(label_out).GetWidth() + MATH_FONT_MARGIN < m_width - dc.GetTextExtent(m_xname).GetWidth()))
        {
            // Mantissa output
            label_out = MATH_DEC_LABEL;
            label_width = dc.GetTextExtent(label_out).GetWidth();
            dc.DrawText(label_out, x, m_height - MATH_LABEL_SHIFT);
            // Exponent output
            label_out = wxString::Format(wxT("%d"), order);
            dc.SetFont(small_font);
            dc.DrawText(label_out, x + label_width + MATH_FONT_EXP_MARGIN, m_height - MATH_LABEL_SHIFT);
            dc.SetFont(default_font);
        }

        if(!m_show_y_middle_lines)
        {
            order++;
            continue;
        }

        dc.SetPen(line_pen);
        for (int i=1; i<10; ++i)
        {
            if (pow(10, order) + (pow(10, order+1) - pow(10, order))/(10-1)*i>m_borders.right)
                break;

            x = pow(10, order) + (pow(10, order+1) - pow(10, order))/(10-1)*i;
            TranslateXCoordinate(x);
            dc.DrawLine(x, y1, x, y2);
        }
        order++;
    }
}

/**\brief Zooms in screen. */
void wxMathPanel::ZoomIn()
{
    double deltaX;
    double deltaY;

    if ((m_borders.right - m_borders.left>pow(10, MATH_MIN_EXPONENT))&&(m_scalable.is_scalable_x))
    {
        deltaX = ((m_borders.right - m_borders.left)/SCALE_ZOOM_COEFF);
        deltaX -= m_borders.right - m_borders.left;
        deltaX /= 2;
        m_borders.left -= deltaX;
        m_borders.right += deltaX;
        m_was_resized_x = true; // do not restore linear scale while is switched from the logarithmic
    }

    if ((m_borders.top - m_borders.bottom>pow(10, MATH_MIN_EXPONENT))&&(m_scalable.is_scalable_y))
    {
        deltaY = ((m_borders.top - m_borders.bottom)/SCALE_ZOOM_COEFF);
        deltaY -= m_borders.top - m_borders.bottom;
        deltaY /= 2;
        m_borders.top += deltaY;
        m_borders.bottom -= deltaY;
        m_was_resized_y = true; // do not restore linear scale while is switched from the logarithmic
    }

    // Reset to zero for logarithmic axises
    if(m_is_x_logarithmic)
        m_borders.left = 0;

    if(m_is_y_logarithmic)
        m_borders.bottom = 0;

    this->Refresh();
}

/**\brief Zooms out screen. */
void wxMathPanel::ZoomOut()
{
    double deltaX;
    double deltaY;

    if ((m_borders.right - m_borders.left<pow(10, MATH_MAX_EXPONENT))&&(m_scalable.is_scalable_x))
    {
        deltaX = ((m_borders.right - m_borders.left)*SCALE_ZOOM_COEFF);
        deltaX -= m_borders.right - m_borders.left;
        deltaX /= 2;

        if(!((m_is_x_logarithmic)&&(m_borders.left-deltaX<=0)))
        {
            m_borders.left -= deltaX;
        }
        m_borders.right += deltaX;
        m_was_resized_x = true; // do not restore linear scale while is switched from the logarithmic
    }

    if ((m_borders.top - m_borders.bottom<pow(10,MATH_MAX_EXPONENT))&&(m_scalable.is_scalable_y))
    {
        deltaY = ((m_borders.top - m_borders.bottom)*SCALE_ZOOM_COEFF);
        deltaY -= m_borders.top - m_borders.bottom;
        deltaY /= 2;

        if(!((m_is_y_logarithmic)&&(m_borders.bottom-deltaY<=0)))
        {
            m_borders.bottom -= deltaY;
        }
        m_borders.top += deltaY;
        m_was_resized_y = true; // do not restore linear scale while is switched from the logarithmic
    }

    this->Refresh();
}

/**\brief Sets panel screen borders.
* \param left Left border value.
* \param top Top border value.
* \param right Right border value.
* \param bottom Bottom border value.
*/
void wxMathPanel::SetBorders(const double &left, const double &top, const double &right, const double &bottom)
{
    if((left>=right)||(bottom>=top))
        return;

    m_borders.left = left;
    m_borders.right = right;
    m_borders.bottom = bottom;
    m_borders.top = top;

    if(m_is_x_logarithmic)
        m_borders.left = m_minimum_log_value;

    if(m_is_y_logarithmic)
        m_borders.bottom = m_minimum_log_value;

    this->Refresh();
}

/**\brief Returns panel screen borders.
* \param left Left border value to write.
* \param top Top border value to write.
* \param right Right border value to write.
* \param bottom Bottom border value to write.
*/
void wxMathPanel::GetBorders(double &left, double &top, double &right, double &bottom) const
{
    left = m_borders.left;
    top = m_borders.top;
    right = m_borders.right;
    bottom = m_borders.bottom;
}

/**\brief Sets canvas restraints.
* The screen cannot be scaled or moved to the values outside of restraints.
* \param left_border Left border value.
* \param top_border Top border value.
* \param right_border Right border value.
* \param bottom_border Bottom border value.
*/
void wxMathPanel::SetRestraints(const double &left_border, const double &top_border, const double &right_border, const double &bottom_border)
{
    if(bottom_border>top_border)
        return;

    if(left_border>right_border)
        return;

    m_restraints.top = top_border;
    m_restraints.bottom = bottom_border;
    m_restraints.left = left_border;
    m_restraints.right = right_border;
    this->Refresh();
}

/**\brief Returns restraints values.
* \param left_border Left border value to write.
* \param top_border Top border value to write.
* \param right_border Right border value to write.
* \param bottom_border Bottom border value to write.
*/
void wxMathPanel::GetRestraints(double &left_border, double &top_border, double &right_border, double &bottom_border) const
{
    left_border = m_restraints.left;
    top_border = m_restraints.left;
    right_border = m_restraints.left;
    bottom_border = m_restraints.left;
}

/**\brief  Resets restraints to default values. */
void wxMathPanel::ResetRestraints()
{
    m_restraints.right = m_restraints.top = pow(10, MATH_MAX_EXPONENT);
    m_restraints.left = m_restraints.bottom = 0 - pow(10, MATH_MAX_EXPONENT);
    this->Refresh();
}

/**\brief Returns real scale for the X-axis.
* \return Scale: real value per panel pixel.
*/
double wxMathPanel::GetLinearScaleX() const
{
    return (m_borders.right - m_borders.left)/m_width;
}

/**\brief Returns real scale for the Y-axis.
* \return Scale: real value per panel pixel.
*/
double wxMathPanel::GetLinearScaleY() const
{
    return (m_borders.top - m_borders.bottom)/m_height;
}

/**\brief Returns axis types (logarithmic/linear).
* \param x_axis Is X-axis logarithmic variable.
* \param x_axis Is X-axis logarithmic variable.
*/
void wxMathPanel::GetIsLogarithmic(bool &x_axis, bool &y_axis) const
{
    x_axis = m_is_x_logarithmic;
    y_axis = m_is_y_logarithmic;
}

/**\brief Changes multiplier for the net lines:
* Each label/net-line will be equal to multiplier*(2*integer)*10^x
* where x = -n, -n+1, ..., 0, ..., n+1, n.
* \param base_number Multiplier value.
*/
void wxMathPanel::SetBaseNumber(int base_number)
{
    if((base_number<1)||(base_number>MATH_MAX_BASE_NUMBER))
        base_number = MATH_MAX_BASE_NUMBER;

    m_base_number_horizontal = m_base_number_vertical = base_number;
    this->Refresh();
}

/**\brief Changes multiplier for the net lines:
* Each label/net-line will be equal to multiplier*(2*integer)*10^x
* where x = -n, -n+1, ..., 0, ..., n+1, n.
* \param x_base_number Multiplier value for the X-axis.
* \param y_base_number Multiplier value for the Y-axis.
*/
void wxMathPanel::SetBaseNumber(int x_base_number, int y_base_number)
{
    if((x_base_number<1)||(x_base_number>MATH_MAX_BASE_NUMBER))
        x_base_number = MATH_MAX_BASE_NUMBER;

    if((y_base_number<1)||(y_base_number>MATH_MAX_BASE_NUMBER))
        y_base_number = MATH_MAX_BASE_NUMBER;

    m_base_number_horizontal = x_base_number;
    m_base_number_vertical = y_base_number;
    this->Refresh();
}

/**\brief Returns base number values.
* \param x_base_number Pointer to the X base number.
* \param y_base_number Pointer to the Y base number.
*/
void wxMathPanel::GetBaseNumber(int &x_base_number, int &y_base_number) const
{
    x_base_number = m_base_number_horizontal;
    y_base_number = m_base_number_vertical;
}

/**\brief Sets minimum value for the logarithmic axises.
* \param value Numeric values like ..., 0.001, 0.01, 0.1, ... etc. The value has to be equal to 10^i, where i is an integer number (positive or negative)
*/
void wxMathPanel::SetLogMinValue(double value)
{
    double current_margin = pow(10, MATH_MIN_EXPONENT); // start margin
    double end_margin = pow(10, MATH_MAX_EXPONENT);

    if((value>=end_margin)||(value<=current_margin))
        return;

    int exponent = static_cast<int>(log10(value));
    m_minimum_log_value = pow(10, exponent);

    if(m_is_x_logarithmic)
        m_borders.left = m_minimum_log_value;

    if(m_is_y_logarithmic)
        m_borders.bottom = m_minimum_log_value;

    this->Refresh();
}

/**\brief Returns minimum value for the logarithmic axises.
* \return Minimum value.
* \see SetLogMinValue
*/
double wxMathPanel::GetLogMinValue() const
{
    return m_minimum_log_value;
}

// Behavior settings
/**\brief Sets panel non-movable and non-scalable.
*/
void wxMathPanel::Freeze()
{
    m_is_movable = m_scalable.is_scalable_x = m_scalable.is_scalable_y = false;
}

/**\brief Sets panel movable and scalable.
*/
void wxMathPanel::UnFreeze()
{
    m_is_movable = m_scalable.is_scalable_x = m_scalable.is_scalable_y = true;
}

/**\brief Sets panel screen to be able to be dragging by mouse.
* \param is_movable Can panel screen be dragging by mouse.
*/
void wxMathPanel::SetMovable(bool is_movable)
{
    m_is_movable = is_movable;
}

/**\brief Returns whether panel movable.
* \return Is panel movable.
*/
bool wxMathPanel::GetMovable() const
{
    return m_is_movable;
}


/**\brief Sets panel screen to be able to be scaled by mouse wheel.
* \param is_scalable Can panel screen be scaled.
*/
void wxMathPanel::SetScalable(bool is_scalable)
{
    m_scalable.is_scalable_x = m_scalable.is_scalable_y = is_scalable;
}

/**\brief Sets panel screen to be able to be scaled by mouse wheel.
* \param is_scalable_x Can panel screen be scaled along X-axis.
* \param is_scalable_y Can panel screen be scaled along Y-axis.
*/
void wxMathPanel::SetScalable(bool is_scalable_x, bool is_scalable_y)
{
    m_scalable.is_scalable_x = is_scalable_x;
    m_scalable.is_scalable_y = is_scalable_y;
}

/**\brief Returns panel ability to be scaled by mouse wheel.
* \param is_scalable_x Can panel screen be scaled along X-axis. Value to write.
* \param is_scalable_y Can panel screen be scaled along Y-axis. Value to write.
*/
void wxMathPanel::GetScalable(bool &is_scalable_x, bool &is_scalable_y) const
{
    is_scalable_x = m_scalable.is_scalable_x;
    is_scalable_y = m_scalable.is_scalable_y;
}

// View settings
void wxMathPanel::SetFramed(bool framed)
{
    m_is_framed = framed;
    this->Refresh();
}

/**\brief Makes axises logarithmically scaled.
* \param x_axis Is X-axis logarithmic.
* \param y_axis Is Y-axis logarithmic.
*/
void wxMathPanel::SetLogarithmic(bool x_axis, bool y_axis)
{
    SetLogarithmicX(x_axis);
    SetLogarithmicY(y_axis);
}

// Make X-axis logarithmically scaled.
// is_logarithmic -- true for logarithmic / false for linear
void wxMathPanel::SetLogarithmicX(bool is_logarithmic)
{
    if(m_is_x_logarithmic==is_logarithmic)
        return;

    m_is_x_logarithmic = is_logarithmic;
    // Save last linear borders or restore them
    if(is_logarithmic)
    {
        m_last_left_border = m_borders.left;
        m_last_right_border = m_borders.right;
        m_borders.left = m_minimum_log_value;
        m_was_resized_x = false;
    }
    else
    {
        m_borders.left = m_last_left_border;
        if(!m_was_resized_x)    // restore if screen was not resized only
        {
            m_borders.right = m_last_right_border;
        }
    }
    this->Refresh();
}

// Make Y-axis logarithmically scaled.
// \param is_logarithmic -- true for logarithmic / false for linear
void wxMathPanel::SetLogarithmicY(bool is_logarithmic)
{
    if(m_is_y_logarithmic==is_logarithmic)
        return;

    m_is_y_logarithmic = is_logarithmic;
    // Save last linear borders or restore them
    if(is_logarithmic)
    {
        m_last_top_border = m_borders.top;
        m_last_bottom_border = m_borders.bottom;
        m_borders.bottom = m_minimum_log_value;
        m_was_resized_y = false;
    }
    else
    {
        m_borders.bottom = m_last_bottom_border;
        if(!m_was_resized_y)    // restore if screen was not resized only
        {
            m_borders.top = m_last_top_border;
        }
    }
    this->Refresh();
}

/**\brief Sets network lines visibility.
* \param show_x Show horizontal lines.
* \param show_y Show vertical lines.
*/
void wxMathPanel::ShowNetLines(bool show_x, bool show_y)
{
    m_show_x_net_lines = show_x;
    m_show_y_net_lines = show_y;
    this -> Refresh();
}

/**\brief Returns network lines visibility.
* \param show_x Pointer to visibility of horizontal lines. Value to write.
* \param show_y Pointer to visibility of vertical lines. Value to write.
*/
void wxMathPanel::GetNetLinesVisibility(bool &show_x, bool &show_y) const
{
    show_x = m_show_x_net_lines;
    show_y = m_show_y_net_lines;
}

/**\brief Sets visibility of middle lines for logarithmic axises.
* \param show_x Horizontal lines.
* \param show_y Vertical lines.
*/
void wxMathPanel::ShowMiddleLines(bool show_x, bool show_y)
{
    m_show_x_middle_lines = show_x;
    m_show_y_middle_lines = show_y;
    this->Refresh();
}

/**\brief Returns middle lines visibility.
* \param show_x Pointer to visibility of horizontal lines. Value to write.
* \aram show_y Pointer to visibility of vertical lines. Value to write.
*/
void wxMathPanel::GetMiddleLinesVisibility(bool &show_x, bool &show_y) const
{
    show_x = m_show_x_middle_lines;
    show_y = m_show_y_middle_lines;
}

/**\brief Sets visibility of axises numeric labels.
* \param x_labels Show values for X-axis.
* \param y_labels Show values for Y-axis.
*/
void wxMathPanel::ShowLabels(bool x_labels, bool y_labels)
{
    m_show_x_labels = x_labels;
    m_show_y_labels = x_labels;
    this->Refresh();
}

/**\brief Returns axises labels visibility.
* \param x_labels Pointer to visibility of values for X-axis. Value to write.
* \param y_labels Pointer to visibility of values for Y-axis. Value to write.
*/
void wxMathPanel::GetLabelsVisibility(bool &x_labels, bool &y_labels) const
{
    x_labels = m_show_x_labels;
    y_labels = m_show_y_labels;
}

/**\brief Sets axises names.
* \param xname Name for X-axis.
* \param yname Name for Y-axis.
*/
void wxMathPanel::SetAxisNames(wxString xname, wxString yname)
{
    m_xname = xname;
    m_yname = yname;
    this->Refresh();
}

/**\brief Returns axises names.
* \param xname Pointer to name for X-axis. Value to write.
* \param yname Pointer to name for Y-axis. Value to write.
*/
void wxMathPanel::GetAxisNames(wxString &xname, wxString &yname) const
{
    xname = m_xname;
    yname = m_yname;
}

/**\brief Sets main axises colour.
* \param colour Colour to set.
*/
void wxMathPanel::SetAxisColour(const wxColour &colour)
{
    m_colour_axis = colour;
    this -> Refresh();
}

/**\brief Sets colour for the net lines.
* \param colour Colour to set.
*/
void wxMathPanel::SetNetLinesColour(const wxColour &colour)
{
    m_colour_net_lines = colour;
    this -> Refresh();
}

/**\brief Sets colour for labels.
* \param colour Colour to set.
*/
void wxMathPanel::SetLabelColour(const wxColour &colour)
{
    m_colour_label = colour;
}

/**\brief Returns colour of axises.
* \return wxColour value.
*/
wxColour wxMathPanel::GetAxisColour() const
{
    return m_colour_axis;
}

/**\brief Returns colour of network lines.
* \return wxColour value.
*/
wxColour wxMathPanel::GetNetLinesColour() const
{
    return m_colour_net_lines;
}

/**\brief Returns colour of labels.
* \return wxColour value.
*/
wxColour wxMathPanel::GetLabelColour() const
{
    return m_colour_label;
}


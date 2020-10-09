#ifndef MOUSEEVENT_H_INCLUDED
#define MOUSEEVENT_H_INCLUDED

#include <wx/event.h>

class MouseMoveEvent;
wxDECLARE_EVENT(wxMATHPANEL_MOUSE_MOVE, MouseMoveEvent);

/**\brief Mouse event.
*
* Occurs each time on mouse move over the panel.
* Keeps coordinates of the mouse pointer.
*/
class MouseMoveEvent: public wxCommandEvent
{
    public:
        MouseMoveEvent(wxEventType commandType = wxMATHPANEL_MOUSE_MOVE, int id = 0)
                    :  wxCommandEvent(commandType, id)
        { }

        MouseMoveEvent(const MouseMoveEvent& event)
                    :  wxCommandEvent(event)
        {
            SetEventType(wxMATHPANEL_MOUSE_MOVE);
            this->X = event.X;
            this->Y = event.Y;;
        }

        wxEvent* Clone() const { return new MouseMoveEvent(*this); }

    double X;   /**< Mouse X-coordinate */
    double Y;   /**< Mouse Y-coordinate */
};

#endif // MOUSEEVENT_H_INCLUDED

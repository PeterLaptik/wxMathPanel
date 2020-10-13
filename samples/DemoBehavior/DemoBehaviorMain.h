/***************************************************************
 * Purpose:   MathPanel sample to demonstrate panel behavior
 * Author:    Peter Laptik
 * Created:   2020-09-13
 **************************************************************/

#ifndef DEMOBEHAVIORMAIN_H
#define DEMOBEHAVIORMAIN_H

//(*Headers(DemoBehaviorFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
//*)

#include "../../include/wxMathPanel.h"

class DemoBehaviorFrame: public wxFrame
{
    public:

        DemoBehaviorFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~DemoBehaviorFrame();

    private:

        //(*Handlers(DemoBehaviorFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnMovableChanged(wxCommandEvent& event);
        void OnChangeScalable(wxCommandEvent& event);
        void OnChangeScalableAxis(wxCommandEvent& event);
        void OnChangeMultiplier(wxCommandEvent& event);
        void OnChangeAxisToLog(wxCommandEvent& event);
        void OnChangeLogValue(wxCommandEvent& event);
        void OnChangeColour(wxCommandEvent& event);
        void OnChangeShowNet(wxCommandEvent& event);
        void OnChangeShowMiddleLines(wxCommandEvent& event);
        void OnChangeAxisName(wxCommandEvent& event);
        void OnAddRestraints(wxCommandEvent& event);
        void OnResetBorders(wxCommandEvent& event);
        void OnSetFramed(wxCommandEvent& event);
        void OnMouseMove(wxMouseEvent& event);
        void OnPanel2MouseMove(wxMouseEvent& event);
        //*)

        //(*Identifiers(DemoBehaviorFrame)
        static const long ID_PANEL2;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_CHECKBOX3;
        static const long ID_CHECKBOX4;
        static const long ID_CHECKBOX5;
        static const long ID_CHECKBOX6;
        static const long ID_CHECKBOX7;
        static const long ID_CHECKBOX8;
        static const long ID_CHECKBOX9;
        static const long ID_CHECKBOX10;
        static const long ID_CHECKBOX11;
        static const long ID_CHECKBOX12;
        static const long ID_BUTTON1;
        static const long ID_PANEL3;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(DemoBehaviorFrame)
        wxButton* Button1;
        wxCheckBox* CheckBox10;
        wxCheckBox* CheckBox11;
        wxCheckBox* CheckBox12;
        wxCheckBox* CheckBox1;
        wxCheckBox* CheckBox2;
        wxCheckBox* CheckBox3;
        wxCheckBox* CheckBox4;
        wxCheckBox* CheckBox5;
        wxCheckBox* CheckBox6;
        wxCheckBox* CheckBox7;
        wxCheckBox* CheckBox8;
        wxCheckBox* CheckBox9;
        wxMathPanel* Panel2;
        wxPanel* Panel1;
        wxPanel* Panel3;
        wxStatusBar* StatusBar1;
        //*)

        /** Catching mouse move event for the math panel */
        void OnCustomEvent(MouseMoveEvent &event);

        DECLARE_EVENT_TABLE()
};

#endif // DEMOBEHAVIORMAIN_H

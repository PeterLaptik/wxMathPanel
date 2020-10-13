/***************************************************************
 * Purpose:   MathPanel sample to demonstrate panel behavior
 * Author:    Peter Laptik
 * Created:   2020-09-13
 **************************************************************/

#include "DemoBehaviorApp.h"

//(*AppHeaders
#include "DemoBehaviorMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(DemoBehaviorApp);

bool DemoBehaviorApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	DemoBehaviorFrame* Frame = new DemoBehaviorFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

/*
The contents of this file are subject to the Initial Developer's Public
License Version 1.0 (the "License"); you may not use this file except in
compliance with the License. You may obtain a copy of the License here:
http://www.flamerobin.org/license.html.

Software distributed under the License is distributed on an "AS IS"
basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
License for the specific language governing rights and limitations under
the License.

The Original Code is FlameRobin (TM).

The Initial Developer of the Original Code is Milan Babuskov.

Portions created by the original developer
are Copyright (C) 2004 Milan Babuskov.

All Rights Reserved.

$Id$

Contributor(s): Michael Hieke, Nando Dessena
*/

#ifndef DATABASEREGISTRATIONDIALOG_H
#define DATABASEREGISTRATIONDIALOG_H

#include <wx/wx.h>
#include "BaseDialog.h"
#include "metadata/server.h"
#include "metadata/database.h"

class DatabaseRegistrationDialog: public BaseDialog {
public:
    enum {
        ID_textcontrol_dbpath = 101,
        ID_textcontrol_username,
        ID_button_browse,
        ID_button_ok,
        ID_button_cancel = wxID_CANCEL
    };

    void setDatabase(YDatabase *db);
    void setServer(YServer *s);			// needed to create new db

    // events
    void OnSettingsChange(wxCommandEvent& event);
    void OnOkButtonClick(wxCommandEvent& event);
    void OnBrowseButtonClick(wxCommandEvent& event);

    DatabaseRegistrationDialog(wxWindow* parent, int id, const wxString& title, bool createDB = false, 
        const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, 
        long style=wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);

private:
    YDatabase *databaseM;
    YServer *serverM;
    bool createM;

    void do_layout();
    void set_properties();
    void updateButtons();

protected:
    virtual const std::string getName() const;

protected:
    wxStaticText* label_dbpath;
    wxTextCtrl* text_ctrl_dbpath;
    wxButton* button_browse;
    wxStaticText* label_username;
    wxTextCtrl* text_ctrl_username;
    wxStaticText* label_password;
    wxTextCtrl* text_ctrl_password;
    wxStaticText* label_charset;
    wxComboBox* combo_box_charset;
    wxStaticText* label_role;
    wxTextCtrl* text_ctrl_role;
    wxStaticText* label_pagesize;
    wxComboBox* combo_box_pagesize;
    wxStaticText* label_dialect;
    wxComboBox* combo_box_dialect;
    wxButton* button_ok;
    wxButton* button_cancel;

    DECLARE_EVENT_TABLE()
};

#endif // DATABASEREGISTRATIONDIALOG_H

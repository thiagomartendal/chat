#ifndef LOGIN_H
#define LOGIN_H

#include <wx/wx.h>

class Login : public wxPanel {
 private:
    long id_entrar;
    long id_conta;
	wxTextCtrl *email;
	wxTextCtrl *senha;
	wxBoxSizer *vertical;
	wxBoxSizer *horizontal1;
	wxBoxSizer *horizontal2;
	wxBoxSizer *horizontal3;
	wxButton *entrar;
	wxButton *conta;

	void ids() {
		id_entrar = wxNewId();
		id_conta = wxNewId();
	}

 	wxStaticText *rotulo(wxString titulo) {
 		wxStaticText *rotulo = new wxStaticText(this, wxID_ANY, titulo, wxDefaultPosition, wxDefaultSize, 0, wxStaticTextNameStr);
 		return rotulo;
 	}

 	void ajustadores() {
        vertical = new wxBoxSizer(wxVERTICAL);
        horizontal1 = new wxBoxSizer(wxHORIZONTAL);
		horizontal2 = new wxBoxSizer(wxHORIZONTAL);
		horizontal3 = new wxBoxSizer(wxHORIZONTAL);
 	}

 	void componentes() {
        email = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, wxDefaultValidator, wxTextCtrlNameStr);
		senha = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD|wxFULL_REPAINT_ON_RESIZE, wxDefaultValidator, wxTextCtrlNameStr);
		entrar = new wxButton(this, id_entrar, wxT("Entrar"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
		conta = new wxButton(this, id_conta, wxT("Criar Conta"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
 	}

 	void layout() {
 	    horizontal1->Add(rotulo("Email: "), wxSizerFlags().Center());
		horizontal1->Add(email, 1, wxALL|wxEXPAND, 5);
		horizontal2->Add(rotulo("Senha:"), wxSizerFlags().Center());
		horizontal2->Add(senha, 1, wxALL|wxEXPAND, 5);
		horizontal3->Add(entrar, wxSizerFlags().Center());
		horizontal3->Add(conta, wxSizerFlags().Center());
		vertical->Add(horizontal1, 0, wxALL|wxEXPAND, 5);
		vertical->Add(horizontal2, 0, wxALL|wxEXPAND, 5);
		vertical->Add(horizontal3, wxSizerFlags().Center());
		this->SetSizer(vertical);
 	}
 public:
    Login(wxPanel *pnl) : wxPanel(pnl, wxID_ANY, wxDefaultPosition, pnl->GetSize(), wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, wxT("login")) {
        ids();
        ajustadores();
        componentes();
        layout();
    }

    long getIdConta() {
		return id_conta;
	}

	long getIdEntrar() {
		return id_entrar;
	}

	wxTextCtrl *getEmail() {
		return email;
	}

	wxTextCtrl *getSenha() {
		return senha;
	}
};

#endif

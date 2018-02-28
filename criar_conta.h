#ifndef CRIAR_CONTA_H
#define CRIAR_CONTA_H

#include <wx/wx.h>
#include "usuario.h"

class Criar_Conta : public wxPanel {
 private:
    long id_nome;
 	long id_criar;
	long id_voltar;
 	wxTextCtrl *nome;
 	wxTextCtrl *email;
	wxTextCtrl *senha;
	wxBoxSizer *vertical;
	wxBoxSizer *horizontal1;
	wxBoxSizer *horizontal2;
	wxBoxSizer *horizontal3;
	wxBoxSizer *horizontal4;
	wxButton *criar;
	wxButton *voltar;

	void ids() {
		id_nome = wxNewId();
		id_criar = wxNewId();
		id_voltar = wxNewId();
	}

	wxStaticText *rotulo(wxString titulo) {
 		wxStaticText *rotulo = new wxStaticText(this, wxID_ANY, titulo, wxDefaultPosition, wxDefaultSize, 0, wxStaticTextNameStr);
 		return rotulo;
 	}

 	void criar_conta() {
 		Usuario *usuario = new Usuario(std::string(nome->GetValue()), std::string(email->GetValue()), std::string(senha->GetValue()));
 		usuario->novoUsuario();
 		if (usuario->getConcluir()) {
 			wxMessageDialog *dlg = new wxMessageDialog(nullptr, wxT("Cadastro concluído com sucesso."), wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
		  	dlg->ShowModal();
		  	this->Destroy();
 		}
 	}

    void ajustadores() {
        vertical = new wxBoxSizer(wxVERTICAL);
 		horizontal1 = new wxBoxSizer(wxHORIZONTAL);
		horizontal2 = new wxBoxSizer(wxHORIZONTAL);
		horizontal3 = new wxBoxSizer(wxHORIZONTAL);
		horizontal4 = new wxBoxSizer(wxHORIZONTAL);
    }

    void componentes() {
        nome = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, wxDefaultValidator, wxTextCtrlNameStr);
 		email = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, wxDefaultValidator, wxTextCtrlNameStr);
		senha = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD|wxFULL_REPAINT_ON_RESIZE, wxDefaultValidator, wxTextCtrlNameStr);
        criar = new wxButton(this, id_criar, wxT("Criar Conta"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
		voltar = new wxButton(this, id_voltar, wxT("Voltar"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    }

    void layout() {
        horizontal1->Add(rotulo("Nome: "), wxSizerFlags().Center());
		horizontal1->Add(nome, 1, wxALL|wxEXPAND, 5);
		horizontal2->Add(rotulo("Email: "), wxSizerFlags().Center());
		horizontal2->Add(email, 1, wxALL|wxEXPAND, 5);
		horizontal3->Add(rotulo("Senha:"), wxSizerFlags().Center());
		horizontal3->Add(senha, 1, wxALL|wxEXPAND, 5);
		horizontal4->Add(criar, wxSizerFlags().Center());
		horizontal4->Add(voltar, wxSizerFlags().Center());
		vertical->Add(horizontal1, 0, wxALL|wxEXPAND, 5);
		vertical->Add(horizontal2, 0, wxALL|wxEXPAND, 5);
		vertical->Add(horizontal3, 0, wxALL|wxEXPAND, 5);
		vertical->Add(horizontal4, wxSizerFlags().Center());
		this->SetSizer(vertical);
    }

    void eventos() {
		Connect(id_criar, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&Criar_Conta::criar_conta);
	}
 public:
    Criar_Conta(wxPanel *pnl) : wxPanel(pnl, wxID_ANY, wxDefaultPosition, pnl->GetSize(), wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, wxT("login")) {
        ids();
        ajustadores();
        componentes();
        layout();
        eventos();
    }

    long getIdVoltar() {
 		return id_voltar;
 	}
};

#endif

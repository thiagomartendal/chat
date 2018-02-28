#ifndef JANELA_H
#define JANELA_H

#include <wx/wx.h>
#include "conexao.h"
#include "login.h"
#include "criar_conta.h"
#include "usuario.h"
#include "dashboard.h"

class Janela : public wxFrame {
 private:
    bool ofline;
    wxBoxSizer *vertical;
    wxPanel *painel;
    Login *login;
    Criar_Conta *conta;
    Dashboard *dash;

    void entrar() {
		std::string email = std::string(login->getEmail()->GetValue());
 		std::string senha = std::string(login->getSenha()->GetValue());
 		Usuario *usuario = new Usuario("vazio", email, senha);
 		usuario->login();
 		if (usuario->getEmail() != "") {
			vertical->Clear(true);
			dash = new Dashboard(painel, usuario->getEmail());
			vertical->Add(dash, 1, wxALL|wxEXPAND, 5);
			Connect(dash->getIdSair(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&Janela::sair);
		}
 	}

    void criar_conta() {
        //login->Destroy();
        //vertical->Clear(true);
        conta = new Criar_Conta(painel);
        vertical->Add(conta, 1, wxALL|wxEXPAND, 5);
        Connect(conta->getIdVoltar(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&Janela::voltar);
    }

    void voltar() {
        conta->Destroy();
        vertical->Clear(true);
        login = new Login(painel);
        vertical->Add(login, 1, wxALL|wxEXPAND, 5);
        eventos();
    }

    void sair() {
 		alterar_status();
 		dash->Destroy();
 		vertical->Clear(true);
 		login = new Login(painel);
 		vertical->Add(login, wxSizerFlags().Center());
 		ofline = true;
 		eventos();
 	}

 	void fechar(wxCloseEvent& evento) {
 		if (evento.CanVeto()) {
 			if (!ofline && dash) {
 				alterar_status();
			}
 			evento.Veto();
 		}
 		this->Destroy();
 		exit(0);
 	}

 	void alterar_status() {
 		Conexao *conn = new Conexao();
	 	try {
			sql::Statement *stmt = conn->getCon()->createStatement();
			stmt->executeUpdate("UPDATE usuario SET status='0' WHERE email='"+dash->getEmail()+"';");
			conn->getCon()->close();
			delete stmt;
			delete conn->getCon();
	 	} catch (sql::SQLException &e) {
			wxString msg = "# Erro: "+std::string(e.what())+" (Codigo de erro MySQL: "+std::to_string(e.getErrorCode())+". "+"Status SQL: "+std::string(e.getSQLState())+").";
			wxMessageDialog *dlg = new wxMessageDialog(nullptr, msg, wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
			dlg->ShowModal();
		}
 	}

    void eventos() {
        Connect(login->getIdConta(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&Janela::criar_conta);
        Connect(login->getIdEntrar(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&Janela::entrar);
    }

    DECLARE_EVENT_TABLE()
 public:
    Janela(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxFULL_REPAINT_ON_RESIZE, wxT("janela")) {
        vertical = new wxBoxSizer(wxVERTICAL);
        painel = new wxPanel(this, wxID_ANY, wxDefaultPosition, this->GetSize(), wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, wxT("painel_principal"));
        login = new Login(painel);
        vertical->Add(login, 1, wxALL|wxEXPAND, 5);
        painel->SetSizer(vertical);
        eventos();
    }
};

#endif

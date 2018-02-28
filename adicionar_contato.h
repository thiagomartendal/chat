#ifndef ADICIONAR_CONTATO_H
#define ADICIONAR_CONTATO_H

#include <wx/wx.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "mysql_connection.h"
#include "conexao.h"

class AdicionarContato : public wxDialog {
 private:
 	long id_add;
 	long id_fechar;
 	std::string seu_email;
 	wxTextCtrl *email;
 	wxPanel *dashboard;
 	wxBoxSizer *vertical;
 	wxBoxSizer *horizontal;
 	wxBoxSizer *horizontal2;
 	wxButton *add;
 	wxButton *fechar_;
 	Conexao *conn;

 	void ids() {
        id_add = wxNewId();
 		id_fechar = wxNewId();
 	}

 	wxStaticText *rotulo(wxString titulo) {
 		wxStaticText *rotulo =new wxStaticText(this, wxID_ANY, titulo, wxDefaultPosition, wxDefaultSize, 0, wxStaticTextNameStr);
 		return rotulo;
 	}

 	void err(sql::SQLException &e) {
 		wxString msg = "# Erro: "+std::string(e.what())+" (Codigo de erro MySQL: "+std::to_string(e.getErrorCode())+". "+"Status SQL: "+std::string(e.getSQLState())+").";
		wxMessageDialog *dlg = new wxMessageDialog(nullptr, msg, wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
		dlg->ShowModal();
 	}

 	bool verificarContato(std::string email_contato) {
		bool existeContato = false;
		conn = new Conexao();
 		try {
			sql::Connection *con = conn->getCon();
			sql::Statement *stmt = con->createStatement();
			sql::ResultSet *res = stmt->executeQuery("SELECT * FROM contato WHERE email='"+email_contato+"' AND seu_email='"+seu_email+"';");
			while (res->next()) {
				existeContato = true;
			}
			delete res;
			delete stmt;
			delete con;
		} catch (sql::SQLException &e) {
			err(e);
		}
		return existeContato;
 	}

 	void adicionar() {
 		Conexao *conn = new Conexao();
 		std::string email_contato = std::string(email->GetValue());
 		if (verificarContato(email_contato)) {
 			wxMessageDialog *dlg = new wxMessageDialog(nullptr, _("O contato já foi adicionado."), wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
			dlg->ShowModal();
 		} else {
	 		bool contatoAdicionado = false;
            consulta(email_contato, contatoAdicionado);
			if (!contatoAdicionado) {
				wxMessageDialog *dlg = new wxMessageDialog(nullptr, _("Email inválido."), wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
				dlg->ShowModal();
			}
		}
 	}

    void consulta(std::string email_contato, bool contatoAdicionado) {
        try {
			sql::Statement *stmt = conn->getCon()->createStatement();
			sql::ResultSet *res = stmt->executeQuery("SELECT * FROM usuario WHERE email='"+email_contato+"';");
			if (email_contato != seu_email) {
				while (res->next()) {
					sql::PreparedStatement *pstmt = conn->getCon()->prepareStatement("INSERT INTO contato(nome, email, seu_email) VALUES (?, ?, ?);");
					pstmt->setString(1, res->getString("nome"));
					pstmt->setString(2, res->getString("email"));
					pstmt->setString(3, seu_email);
					pstmt->executeUpdate();
					wxMessageDialog *dlg = new wxMessageDialog(nullptr, wxT("Contato adicionado."), wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
					dlg->ShowModal();
					dashboard->Refresh();
					dashboard->Update();
					contatoAdicionado = true;
					delete pstmt;
				}
			} else {
				contatoAdicionado = false;
			}
			conn->getCon()->close();
			delete stmt;
			delete conn->getCon();
		} catch (sql::SQLException &e) {
			err(e);
		}
    }

 	void fechar() {
 		this->Destroy();
 	}

    void ajustadores() {
        vertical = new wxBoxSizer(wxVERTICAL);
 		horizontal = new wxBoxSizer(wxHORIZONTAL);
 		horizontal2 = new wxBoxSizer(wxHORIZONTAL);
    }

    void componentes() {
        email = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, wxDefaultValidator, wxTextCtrlNameStr);
 		add = new wxButton(this, id_add, wxT("Adicionar"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
 		fechar_ = new wxButton(this, id_fechar, wxT("Fechar"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
    }

    void layout() {
        horizontal->Add(rotulo("Email: "), wxSizerFlags().Center());
 		horizontal->Add(email, 1, wxALL|wxEXPAND, 5);
 		horizontal->Add(add, wxSizerFlags().Center());
 		horizontal2->Add(fechar_, wxSizerFlags().Center());
 		vertical->Add(horizontal, 0, wxALL|wxEXPAND, 5);
 		vertical->Add(horizontal2, wxSizerFlags().Center());
 		this->SetSizer(vertical);
    }

 	void eventos() {
        Connect(id_add, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&AdicionarContato::adicionar);
 		Connect(id_fechar, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&AdicionarContato::fechar);
 	}
 public:
 	AdicionarContato(std::string seu_email, wxPanel *dash) : wxDialog(NULL, wxID_ANY, wxT("Adicionar Contato"), wxDefaultPosition, wxSize(400, 100), wxDEFAULT_DIALOG_STYLE, wxT("addContato")), seu_email{seu_email}, dashboard{dash} {
 		ids();
        ajustadores();
 		componentes();
 		layout();
 		eventos();
 	}
};

#endif

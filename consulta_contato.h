#ifndef CONSULTA_CONTATO_H
#define CONSULTA_CONTATO_H

#include <string>
#include <vector>
#include <wx/wx.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "conexao.h"

class ConsultaContato : public wxPanel {
 private:
 	long id_remover;
 	std::string etiqueta;
 	std::vector<std::string> nomes;
 	std::vector<std::string> emails;
 	std::vector<std::string> nomes_contatos;
 	std::vector<std::string> emails_contatos;
 	wxBoxSizer *horizontal;

 	void err(sql::SQLException &e) {
 		wxString msg = "# Erro: "+std::string(e.what())+" (Codigo de erro MySQL: "+std::to_string(e.getErrorCode())+". "+"Status SQL: "+std::string(e.getSQLState())+").";
		wxMessageDialog *dlg = new wxMessageDialog(nullptr, msg, wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
		dlg->ShowModal();
 	}
 public:
 	ConsultaContato(std::string email) {
 		Conexao *conn = new Conexao();
 		try {
			sql::Statement *stmt = conn->getCon()->createStatement();
			sql::ResultSet *res = stmt->executeQuery("SELECT * FROM contato WHERE seu_email = '"+email+"' ORDER BY nome;");
			while (res->next()) {
				nomes_contatos.push_back(res->getString("nome"));
				emails_contatos.push_back(res->getString("email"));
				sql::Statement *stmt2 = conn->getCon()->createStatement();
				sql::ResultSet *res2 = stmt->executeQuery("SELECT * FROM usuario WHERE email = '"+res->getString("email")+"' AND status='1';");
				while (res2->next()) {
					etiqueta += res2->getString("nome")+" - "+res2->getString("email")+"\n";
					nomes.push_back(res2->getString("nome"));
					emails.push_back(res2->getString("email"));
				}
				delete res2;
	  			delete stmt2;
	  		}
	  		conn->getCon()->close();
	  		delete res;
	  		delete stmt;
	  		delete conn->getCon();
		} catch (sql::SQLException &e) {
			err(e);
		}
 	}

 	std::vector<std::string> getNomes() {
 		return nomes;
 	}

 	std::vector<std::string> getEmails() {
 		return emails;
 	}

 	std::vector<std::string> getNomesContatos() {
 		return nomes_contatos;
 	}

 	std::vector<std::string> getEmailsContatos() {
 		return emails_contatos;
 	}
};

#endif

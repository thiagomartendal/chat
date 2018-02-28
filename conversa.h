#ifndef CONVERSA_H
#define CONVERSA_H

#include <string>
#include <vector>
#include <locale.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "conexao.h"

class Conversa {
 private:
 	std::string email_contato;
 	std::string seu_email;
 	std::vector<std::string> mensagens;
 	std::vector<std::string> direcao;
 	Conexao *conn;

 	void err(sql::SQLException &e) {
 		wxString msg = "# Erro: "+std::string(e.what())+" (Codigo de erro MySQL: "+std::to_string(e.getErrorCode())+". "+"Status SQL: "+std::string(e.getSQLState())+").";
		wxMessageDialog *dlg = new wxMessageDialog(nullptr, msg, wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
		dlg->ShowModal();
 	}

 public:
 	Conversa(std::string email_contato_, std::string seu_email_) : email_contato{email_contato_}, seu_email{seu_email_} {
 		setlocale(LC_ALL, "Portuguese");
 		conn = new Conexao();
 		try {
			sql::Statement *stmt = conn->getCon()->createStatement();
			sql::ResultSet *res = stmt->executeQuery("SELECT * FROM conversa WHERE seu_email='"+seu_email+"' AND email_contato='"+email_contato+"' OR seu_email='"+email_contato+"' AND email_contato='"+seu_email+"' ORDER BY id;");
			while (res->next()) {
				mensagens.push_back(res->getString("mensagem"));
				if (res->getString("seu_email") == seu_email) {
					direcao.push_back("esq");
				} else {
					direcao.push_back("dir");
				}
			}
			conn->getCon()->close();
			delete stmt;
			delete conn->getCon();
		} catch (sql::SQLException &e) {
			err(e);
		}
 	}

 	void enviarMensagem(std::string mensagem) {
		Conexao *c = new Conexao();
		try {
			sql::PreparedStatement *pstmt = c->getCon()->prepareStatement("INSERT INTO conversa(seu_email, email_contato, mensagem) VALUES (?, ?, ?);");
			pstmt->setString(1, seu_email);
			pstmt->setString(2, email_contato);
			pstmt->setString(3, mensagem);
			pstmt->executeUpdate();
			c->getCon()->close();
			delete pstmt;
			delete c->getCon();
		} catch (sql::SQLException &e) {
			err(e);
		}
 	}

 	std::vector<std::string> getMensagens() {
 		return mensagens;
 	}

 	std::vector<std::string> getDirecao() {
 		return direcao;
 	}
};

#endif

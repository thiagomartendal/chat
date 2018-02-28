#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <wx/wx.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset_metadata.h>
#include "conexao.h"
#include "criptografia.h"
#include "validar_email.h"

class Usuario {
 private:
 	std::string nome;
 	std::string email;
 	std::string senha;
 	Conexao *conn;
 	Criptografia *crip;
 	bool erro;
 	bool tamanhoSenha;
 	bool concluir;
 	bool log;
 	bool valid_email;

 	void err(sql::SQLException &e) {
 		wxString msg = "# Erro: "+std::string(e.what())+" (Codigo de erro MySQL: "+std::to_string(e.getErrorCode())+". "+"Status SQL: "+std::string(e.getSQLState())+").";
		wxMessageDialog *dlg = new wxMessageDialog(nullptr, msg, wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
		dlg->ShowModal();
 	}
 public:
	Usuario(std::string nome, std::string email, std::string senha) : nome{nome}, email{email}, senha{senha} {
		erro = false;
		concluir = false;
		tamanhoSenha = false;
		log = false;
		ValidarEmail *val = new ValidarEmail(email);
		if (nome == "" || email == "" || senha == "") {
			erro = true;
			wxMessageDialog *dlg = new wxMessageDialog(nullptr, wxT("Preencha todos os campos."), wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
			dlg->ShowModal();
		} else if (senha.size() < 6) {
			tamanhoSenha = true;
			wxMessageDialog *dlg = new wxMessageDialog(nullptr, wxT("A senha deve ter ao menos seis caracteres."), wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
			dlg->ShowModal();
		} else if (!val->valido()) {
			valid_email = true;
			wxMessageDialog *dlg = new wxMessageDialog(nullptr, _("Email inválido."), wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
			dlg->ShowModal();
		} else {
			erro = false;
			conn = new Conexao();
			crip = new Criptografia(this->senha);
		}
	}

	void novoUsuario() {
		if (!erro && !tamanhoSenha && !valid_email) {
			try {
				sql::PreparedStatement *pstmt = conn->getCon()->prepareStatement("INSERT INTO usuario(nome, email, senha) VALUES (?, ?, ?);");
				pstmt->setString(1, nome);
				pstmt->setString(2, email);
				pstmt->setString(3, std::to_string(crip->getCriptografado()));
				pstmt->executeUpdate();
				concluir = true;
				conn->getCon()->close();
				delete pstmt;
				delete conn->getCon();
			} catch (sql::SQLException &e) {
				err(e);
			}
		}
	}

	void login() {
		if (!erro && !tamanhoSenha && !valid_email) {
			try {
				sql::Statement *stmt = conn->getCon()->createStatement();
				sql::ResultSet *res = stmt->executeQuery("SELECT * FROM usuario;");
				sql::ResultSetMetaData *res_meta = res->getMetaData();
  				int col = res_meta->getColumnCount();
  				bool erro_log = false;
				while (res->next()) {
					for (int i = 1; i <= col; i++) {
						if ((this->email == res->getString("email")) && (std::to_string(crip->getCriptografado()) == res->getString("senha"))) {
							log = true;
							sql::Statement *stmt2 = conn->getCon()->createStatement();
							stmt2->executeUpdate("UPDATE usuario SET status='1' WHERE email='"+this->email+"';");
							delete stmt2;
							break;
						}
					}
			  	}
			  	if (!log) {
			  		wxMessageDialog *dlg = new wxMessageDialog(nullptr, wxT("Email ou senha incorretos."), wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
					dlg->ShowModal();
				}
				conn->getCon()->close();
		  		delete res;
		  		delete stmt;
		  		delete conn->getCon();
			} catch (sql::SQLException &e) {
				err(e);
			}
		}
	}

	bool getConcluir() {
		return concluir;
	}

	std::string getEmail() {
		if (log) {
			return this->email;
		}
		return "";
	}
};

#endif

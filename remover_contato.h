#ifndef REMOVER_CONTATO_H
#define REMOVER_CONTATO_H

#include <string>
#include <wx/wx.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset_metadata.h>
#include "conexao.h"

class RemoverContato  : public wxButton {
 private:
	long id_remover;
	std::string email;
	std::string seu_email;

	void remover() {
		Conexao *conn = new Conexao();
		sql::PreparedStatement *pstmt = conn->getCon()->prepareStatement("DELETE FROM contato WHERE email='"+email+"' AND seu_email='"+seu_email+"';");
		pstmt->executeUpdate();
		conn->getCon()->close();
		delete pstmt;
		delete conn->getCon();
	}
 public:
 	RemoverContato(wxScrolledWindow *painelScroll, std::string email, std::string seu_email) : wxButton(painelScroll, wxID_ANY, wxT("Remover Contato"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr), email{email}, seu_email{seu_email} {
		Connect(wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&RemoverContato::remover);
 	}
};

#endif

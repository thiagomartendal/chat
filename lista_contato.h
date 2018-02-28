#ifndef LIISTA_CONTATO_H
#define LIISTA_CONTATO_H

#include <string>
#include <wx/wx.h>
#include "chat.h"

class ListaContato : public wxStaticText {
 private:
 	std::string email_contato;
 	std::string nome_contato;
 	std::string seu_email;

 	void clique() {
 		Chat *chat = new Chat(nome_contato, email_contato, seu_email);
 		chat->Centre();
	    chat->Show();
 	}

 	void enter() {
 		this->SetCursor(6);
 	}
 public:
 	ListaContato(wxScrolledWindow *pnl, std::string nome, std::string email, std::string seu_email) : wxStaticText(pnl, wxID_ANY, _(nome+" - "+email), wxDefaultPosition, wxDefaultSize, 0, wxStaticTextNameStr), email_contato{email}, nome_contato{nome}, seu_email{seu_email} {
 		this->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&ListaContato::clique, NULL, this);
 		this->Connect(wxEVT_MOTION, (wxObjectEventFunction)&ListaContato::enter, NULL, this);
 	}
};

#endif

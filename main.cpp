#include <iostream>
#include <wx/wx.h>
#include "janela.h"
#include "conexao.h"

BEGIN_EVENT_TABLE(Janela, wxFrame)
    EVT_CLOSE(Janela::fechar)
END_EVENT_TABLE()

class Main : public wxApp {
 private:
    Janela *janela;
 public:
	bool OnInit() {
		janela = new Janela(wxT("Chat"));
	    janela->SetSize(800, 600);
	    janela->Maximize();
	    janela->Centre();
	    janela->Show();
		return true;
	}
};

IMPLEMENT_APP(Main);

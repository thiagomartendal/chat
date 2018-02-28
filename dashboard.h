#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <wx/wx.h>
#include <wx/notebook.h>
#include "adicionar_contato.h"
#include "consulta_contato.h"
#include "lista_contato.h"
#include "painel_contato.h"

class Dashboard : public wxPanel {
 private:
    long id_contato;
 	long id_contatos;
 	long id_sair;
 	long id_temp;
 	long id_scroll;
 	long id_abas;
 	std::string email;
 	Conexao *conn;
 	PainelContato *painelc;
 	wxBoxSizer *vertical;
 	wxBoxSizer *vertical2;
 	wxTimer temporizador;
 	wxScrolledWindow *painelScroll;
 	wxNotebook *abas;

 	void ids() {
 		id_contato = wxNewId();
 		id_contatos = wxNewId();
 		id_sair = wxNewId();
 		id_temp = wxNewId();
 		id_scroll = wxNewId();
 		id_abas = wxNewId();
 	}

    void navegacao() {
 		wxBoxSizer *horizontal1 = new wxBoxSizer(wxHORIZONTAL);
 		wxButton *contato = new wxButton(this, id_contato, wxT("Novo Contato"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
 		wxButton *sair = new wxButton(this, id_sair, wxT("Sair"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
 		horizontal1->Add(contato, wxSizerFlags().Center());
 		horizontal1->Add(sair, wxSizerFlags().Center());
 		vertical->Add(horizontal1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
 	}

 	void ajustadores() {
        vertical = new wxBoxSizer(wxVERTICAL);
 		vertical2 = new wxBoxSizer(wxVERTICAL);
 	}

 	void componentes() {
        conn = new Conexao();
        abas = new wxNotebook(this, id_abas, wxDefaultPosition, this->GetSize(), wxVSCROLL, _T("abas"));
 		painelc = new PainelContato(abas, email);
 		painelScroll = new wxScrolledWindow(abas, id_scroll, wxDefaultPosition, abas->GetSize(), wxVSCROLL, _T("scroll"));
 		painelScroll->ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_DEFAULT);
 		temporizador.SetOwner(this, id_temp);
 		temporizador.Start(1000, wxTIMER_CONTINUOUS);
 		navegacao();
 		resultadoConsulta();
 		painelScroll->SetSizer(vertical2);
    }

    void layout() {
        abas->AddPage(painelScroll, _("Contatos Online"), false);
 		abas->AddPage(painelc, _("Todos os Contatos"), false);
 		vertical->Add(abas, 1, wxALL|wxEXPAND, 5);
 		this->SetSizer(vertical);
    }

    void atualizar(wxTimerEvent& evento) {
 		resultadoConsulta();
 	}

 	void addContato() {
 		AdicionarContato *add = new AdicionarContato(email, this);
 		add->Centre();
 		add->ShowModal();
 	}

 	void resultadoConsulta() {
 		vertical2->Clear(true);
 		ConsultaContato *consulta = new ConsultaContato(this->email);
		if (consulta->getNomes().size() == 0) {
			wxStaticText *rot = new wxStaticText(painelScroll, wxID_ANY, _("Nenhum contato online."), wxDefaultPosition, wxDefaultSize, 0, wxStaticTextNameStr);
			vertical2->Add(rot, wxSizerFlags().Center());
		} else {
			wxFont fonte(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _T("Sans"), wxFONTENCODING_DEFAULT);
			for (int i = 0; i < consulta->getNomes().size(); i++) {
				std::string label = consulta->getNomes().at(i)+" - "+consulta->getEmails().at(i);
				ListaContato *lista = new ListaContato(painelScroll, consulta->getNomes().at(i), consulta->getEmails().at(i), this->email);
		 		lista->SetFont(fonte);
		 		vertical2->Add(lista, wxSizerFlags().Center());
			}
		}
		painelScroll->SetCursor(1);
		painelScroll->SetScrollRate(5, 5);
 		painelScroll->Layout();
 	}

    void eventos() {
 		Connect(id_contato, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&Dashboard::addContato);
 		Connect(id_temp, wxEVT_TIMER, wxTimerEventHandler(Dashboard::atualizar), NULL, this);
 	}
 public:
    Dashboard(wxPanel *pnl, std::string email_) : wxPanel(pnl, wxID_ANY, wxDefaultPosition, pnl->GetSize(), wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, wxT("dashboard")), email{email_} {
        ids();
        ajustadores();
        componentes();
        layout();
        eventos();
    }

    long getIdSair() {
 		return id_sair;
 	}

 	std::string getEmail() {
 		return email;
 	}
};

#endif

#ifndef PAINEL_CONTATO_H
#define PAINEL_CONTATO_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "consulta_contato.h"
#include "lista_contato.h"
#include "remover_contato.h"

class PainelContato : public wxPanel {
 private:
 	long id_scroll;
 	long id_temp;
 	std::string email;
 	wxScrolledWindow *painelScroll;
 	wxTimer temporizador;
 	wxBoxSizer *vertical;
 	wxBoxSizer *vertical2;

 	void ids() {
 		id_scroll = wxNewId();
 		id_temp = wxNewId();
 	}

 	void atualizar(wxTimerEvent& evento) {
 		resultadoConsulta();
 	}

 	void resultadoConsulta() {
 		vertical2->Clear(true);
 		ConsultaContato *consulta = new ConsultaContato(this->email);
		if (consulta->getNomesContatos().size() == 0) {
			wxStaticText *rot = new wxStaticText(painelScroll, wxID_ANY, _("Nenhum contato adicionado."), wxDefaultPosition, wxDefaultSize, 0, wxStaticTextNameStr);
			vertical2->Add(rot, wxSizerFlags().Center());
		} else {
			wxFont fonte(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _T("Sans"), wxFONTENCODING_DEFAULT);
			for (int i = 0; i < consulta->getNomesContatos().size(); i++) {
				ListaContato *lista = new ListaContato(painelScroll, consulta->getNomesContatos().at(i), consulta->getEmailsContatos().at(i), this->email);
		 		lista->SetFont(fonte);
		 		wxBoxSizer *horizontal = new wxBoxSizer(wxHORIZONTAL);
		 		RemoverContato *remover = new RemoverContato(painelScroll, consulta->getEmailsContatos().at(i), this->email);
		 		horizontal->Add(lista, wxSizerFlags().Center());
		 		horizontal->Add(remover, wxSizerFlags().Center());
		 		vertical2->Add(horizontal, wxSizerFlags().Center());
			}
		}
		painelScroll->SetCursor(1);
		painelScroll->SetScrollRate(5, 5);
 		this->Layout();
 	}

 	void ajustadores() {
        vertical = new wxBoxSizer(wxVERTICAL);
 		vertical2 = new wxBoxSizer(wxVERTICAL);
 	}

 	void componentes() {
        temporizador.SetOwner(this, id_temp);
 		temporizador.Start(1000, wxTIMER_CONTINUOUS);
 		painelScroll = new wxScrolledWindow(this, id_scroll, wxDefaultPosition, this->GetSize(), wxVSCROLL, _T("scroll"));
 	}

 	void layout() {
        painelScroll->ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_DEFAULT);
 		painelScroll->SetSizer(vertical2);
 		vertical->Add(painelScroll, wxSizerFlags().Center());
 		this->SetSizer(vertical);
 	}

 	void eventos() {
 		Connect(id_temp, wxEVT_TIMER, wxTimerEventHandler(PainelContato::atualizar), NULL, this);
 	}
 public:
 	PainelContato(wxNotebook *pnl, std::string email) : wxPanel(pnl, wxID_ANY, wxDefaultPosition, pnl->GetSize(), wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, wxT("painel_contato")), email{email} {
 		ids();
        ajustadores();
 		componentes();
 		layout();
 		resultadoConsulta();
 		eventos();
 	}
};

#endif

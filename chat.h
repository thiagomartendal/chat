#ifndef CHAT_H
#define CHAT_H

#include <string>
#include <wx/wx.h>
#include "conversa.h"

class Chat : public wxFrame {
 private:
 	long id_scroll;
 	long id_msg;
 	long id_enviar;
 	long id_temp;
 	std::string email;
 	std::string seu_email;
 	wxBoxSizer *vertical, *vertical2;
 	wxTextCtrl *msg;
 	wxScrolledWindow *painelScroll;
    wxButton *enviar;
 	wxTimer temporizador;

 	void ids() {
 		id_scroll = wxNewId();
 		id_msg = wxNewId();
 		id_enviar = wxNewId();
 		id_temp = wxNewId();
 	}

 	void enviarMensagem() {
 		std::string mensagem = std::string(msg->GetValue());
 		wxMessageDialog *dlg = new wxMessageDialog(nullptr, _(mensagem), wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
		dlg->ShowModal();
 		Conversa *conversa = new Conversa(email, seu_email);
 		conversa->enviarMensagem(mensagem);
 		msg->SetValue("");
 	}

 	void atualizar(wxTimerEvent& evento) {
 		exibirMensagem();
 	}

 	void exibirMensagem() {
 		vertical2->Clear(true);
 		Conversa *conversa = new Conversa(email, seu_email);
 		int tam = conversa->getMensagens().size();
 		if (tam != 0) {
 			for (int i = 0; i < tam; i++) {
	 			wxStaticText *mensagem = new wxStaticText(painelScroll, wxID_ANY, _(conversa->getMensagens().at(i)), wxDefaultPosition, wxDefaultSize, 0, wxStaticTextNameStr);
	 			if (conversa->getDirecao().at(i) == "esq") {
	 				vertical2->Add(mensagem, wxSizerFlags().Left());
	 			} else {
	 				vertical2->Add(mensagem, wxSizerFlags().Right());
	 			}
 			}
 		}
 		this->Layout();
 	}

 	void ajustadores() {
 	    vertical = new wxBoxSizer(wxVERTICAL);
 		vertical2 = new wxBoxSizer(wxVERTICAL);
 	}

 	void componentes() {
        int altura1 = this->GetSize().GetHeight()*0.65;
 		int altura2 = this->GetSize().GetHeight()*0.35;
 		painelScroll = new wxScrolledWindow(this, id_scroll, wxDefaultPosition, wxSize(this->GetSize().GetWidth(), altura1), wxVSCROLL, _T("scroll"));
		painelScroll->ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_DEFAULT);
 		painelScroll->Layout();
 		painelScroll->SetScrollRate(5, 5);
 		painelScroll->SetSizer(vertical2);
 		enviar = new wxButton(this, id_enviar, wxT("Enviar"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxButtonNameStr);
 		msg = new wxTextCtrl(this, id_msg, _(""), wxDefaultPosition, wxSize(this->GetSize().GetWidth(), altura2), wxTE_MULTILINE|wxFONTENCODING_ISO8859_1, wxDefaultValidator, _T("msg"));
 	}

 	void layout() {
        vertical->Add(painelScroll, 1, wxALL|wxEXPAND, 5);
 		vertical->Add(enviar, wxSizerFlags().Right());
 		vertical->Add(msg, 1, wxALL|wxEXPAND, 5);
 		temporizador.SetOwner(this, id_temp);
 		temporizador.Start(1000, wxTIMER_CONTINUOUS);
 		this->SetSizer(vertical);
 	}

 	void eventos() {
 		Connect(id_enviar, wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&Chat::enviarMensagem);
 		Connect(id_temp, wxEVT_TIMER, wxTimerEventHandler(Chat::atualizar), NULL, this);
 	}
 public:
 	Chat(std::string nome, std::string email, std::string seu_email) : wxFrame(NULL, wxID_ANY, _(nome), wxDefaultPosition, wxSize(800, 600), wxDEFAULT_FRAME_STYLE|wxFULL_REPAINT_ON_RESIZE, wxT("chat")), email{email}, seu_email{seu_email} {
 		ids();
 		ajustadores();
 		componentes();
 		layout();
 		exibirMensagem();
 		eventos();
 		painelScroll->Scroll(this->GetSize().GetWidth(), this->GetSize().GetWidth());
 	}
};

#endif

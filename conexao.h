#ifndef CONEXAO_H
#define CONEXAO_H

#include <string>
#include <wx/wx.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include "mysql_connection.h"

class Conexao {
 private:
    sql::Driver *driver;
	sql::Connection *con;
 public:
    Conexao() {
 		try {
			driver = get_driver_instance();
			con = driver->connect("tcp://127.0.0.1:3306", "root", "admin");
			con->setSchema("chat2");
		} catch (sql::SQLException &e) {
			wxString msg = "# Erro: "+std::string(e.what())+" (Codigo de erro MySQL: "+std::to_string(e.getErrorCode())+". "+"Status SQL: "+std::string(e.getSQLState())+").";
            wxMessageDialog *dlg = new wxMessageDialog(nullptr, msg, wxMessageBoxCaptionStr, wxOK|wxCENTRE, wxDefaultPosition);
            dlg->ShowModal();
		}
 	}

 	sql::Connection *getCon() {
 		return con;
 	}
};

#endif

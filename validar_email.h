#ifndef VALIDAR_EMAIL_H
#define VALIDAR_EMAIL_H

#include <string>
#include <regex>

class ValidarEmail {
 private:
 	bool emailCorreto;

 	bool validar(const std::string& email) {
   		const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
		return std::regex_match(email, pattern);
	}
 public:
 	ValidarEmail(std::string email) {
 		if (validar(email)) {
 			emailCorreto = true;
 		} else {
 			emailCorreto = false;
 		}
 	}

 	bool valido() {
 		return this->emailCorreto;
 	}
};

#endif

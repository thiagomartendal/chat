#ifndef CRIPTOGRAFIA_H
#define CRIPTOGRAFIA_H

#include <string>
#include <bitset>

class Criptografia {
 private:
 	int resultado;
 	int fator;

 public:
	Criptografia(std::string senha) {
 		int bin = 0;
 		for (std::size_t i = 0; i < senha.size(); i++) {
 			bin += std::stoi(std::bitset<8ul>(senha.c_str()[i]).to_string());
		}
		resultado = bin;
		fator = senha.size();
 	}

 	int getCriptografado() {
 		return (resultado*fator)*2;
 	}
};

#endif

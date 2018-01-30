#include <cstdlib>
#include <string>
#include <cstring>

std::string ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top;

void configure(const std::string& ct, const std::string& df, const std::string& of, const std::string& lf, const std::string& em, const std::string& dt) { 
	ciphertext = ct;
	dictionary_file = df;
	outfile = of;
	logfile = lf;
	encryption_method = em;
	displayed_top = dt;
}

void load_cfg(std::string& ct, std::string& df, std::string& of, std::string& lf, std::string& em, std::string& dt) { 
	ct = ciphertext;
	df = dictionary_file;
	of = outfile;
	lf = logfile;
	em = encryption_method;
	dt = displayed_top;
}


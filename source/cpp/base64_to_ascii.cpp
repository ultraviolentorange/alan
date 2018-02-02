#include "base64.h"

#include "candidate_handler.h"
#include "cfg_handler.h"

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void run_base64() {
    std::string ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top, cipher_key;
    load_cfg(ciphertext, dictionary_file, outfile, logfile, encryption_method, displayed_top, cipher_key);

    std::ofstream log(logfile);

    if (!logfile.empty()) {
        log << "Trying to decrypt Base64...\n";
    } else {
        std::cout << "Trying to decrypt Base64...\n"; 
    }

    int len = (int)ciphertext.size();
    unsigned char a3[3];
    unsigned char a4[4];
    int i = 0, p = 0;
    
    std::string candidate;
    while (len-- && (ciphertext[p] != '=') && alphabet.find(ciphertext[p]) != std::string::npos) {
        a4[i++] = ciphertext[p]; 
        p++;
        if (i == 4) {
            for (int q = 0; q < 4; q++) a4[q] = alphabet.find(a4[q]);
            a3[0] = (a4[0] << 2) + ((a4[1] & 0x30) >> 4);
            a3[1] = ((a4[1] & 0xf) << 4) + ((a4[2] & 0x3c) >> 2);
            a3[2] = ((a4[2] & 0x3) << 6) + a4[3];
            for (int q = 0; q < 3; q++) candidate += a3[q];
            i = 0;
        } 
    }
    if (i) {
        for (int q = i; q < 4; q++) a4[q] = 0;
        for (int q = 0; q < 4; q++) a4[q] = alphabet.find(a4[q]);
        a3[0] = (a4[0] << 2) + ((a4[1] & 0x30) >> 4);
        a3[1] = ((a4[1] & 0xf) << 4) + ((a4[2] & 0x3c) >> 2);
        a3[2] = ((a4[2] & 0x3) << 6) + a4[3];
        for (int q = 0; q < i - 1; q++) candidate += a3[q];
    }
    
    add_candidate(candidate);
}


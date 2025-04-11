#include <iostream>
using std::cout, std::endl, std::cerr, std::cin, std::getline;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <fstream>
using std::ifstream, std::ofstream;
#include <random>
using std::mt19937;

map <char, vector<int>> ecoliProbMap = {
    {'F', {57, 100}},
    {'L', {15, 27, 39, 49, 54, 100}},
    {'I', {58, 93, 100}},
    {'M', {100}},
    {'V', {25, 43, 60, 100}},
    {'S', {11, 22, 37, 53, 67, 100}},
    {'P', {17, 30, 44, 100}},
    {'T', {16, 63, 76, 100}},
    {'A', {11, 42, 63, 100}},
    {'Y', {53, 100}},
    {'H', {55, 100}},
    {'Q', {30, 100}},
    {'N', {47, 100}},
    {'K', {73, 100}},
    {'D', {65, 100}},
    {'E', {70, 100}},
    {'C', {42, 100}},
    {'W', {100}},
    {'R', {36, 80, 87, 94, 96, 100}},
    {'G', {29, 75, 88, 100}},
    {'*', {0, 64, 100}},
};

map <char, vector<string>> codonMap = {
    {'F', {"TTT", "TTC"}},
    {'L', {"TTA", "TTG", "CTT", "CTC", "CTA", "CTG"}},
    {'I', {"ATT", "ATC", "ATA"}},
    {'M', {"ATG"}},
    {'V', {"GTT", "GTC", "GTA", "GTG"}},
    {'S', {"TCT", "TCC", "TCA", "TCG", "AGT", "AGC"}},
    {'P', {"CCT", "CCC", "CCA", "CCG"}},
    {'T', {"ACT", "ACC", "ACA", "ACG"}},
    {'A', {"GCT", "GCC", "GCA", "GCG"}},
    {'Y', {"TAT", "TAC"}},
    {'H', {"CAT", "CAC"}},
    {'Q', {"CAA", "CAG"}},
    {'N', {"AAT", "AAC"}},
    {'K', {"AAA", "AAG"}},
    {'D', {"GAT", "GAC"}},
    {'E', {"GAA", "GAG"}},
    {'C', {"TGT", "TGC"}},
    {'W', {"TGG"}},
    {'R', {"CGT", "CGC", "CGA", "CGG", "AGA", "AGG"}},
    {'G', {"GGT", "GGC", "GGA", "GGG"}},
    {'*', {"TAG", "TAA", "TGA"}},
};


string readFasta(ifstream& inputstream){
    cout << "inside readFasta function" << endl;
    if (!inputstream){
        throw std::invalid_argument("could not open file");
    }
    string line;
    while (getline(inputstream, line)) {
        if (!line.empty() && line[0] != '>') {
            break;
        }
    }
    return line;
}

bool requestHisTag(){
    string response;
    cout << "No His-Tag detected. Do you want to add one? [Y/N]" << endl;
    getline(cin, response);
    if(response == "Y" || response == "y"){
        return true;
    }
    return false;
}

void prepSequence(string& sequence){
    for (char& c : sequence){
        c = toupper(c);
        if (codonMap.find(c) == codonMap.end()){
            cerr << "found invalid sequence character: " << c << endl;
            throw std::invalid_argument("invalid amino acid");
        }
    }
    
    if(sequence.substr(0,6) != "HHHHHH" && requestHisTag()){
        cout << "Adding a 10x His-tag" << endl;
        sequence = "HHHHHHHHHH" + sequence;
    }
    if(sequence.front() != 'M'){
        cout << "Adding a start codon" << endl;
        sequence = "M" + sequence;
    }
    if(sequence.back() != '*'){
        cout << "Adding stop codon" << endl;
        sequence = sequence + "*";
    }
}

int seed = 100;
mt19937 gen(seed);
std::uniform_int_distribution<> dist(1,100);

string selectCodon(char AA){
    int index = 0;
    int rand_selector = dist(gen); 
    vector<int> list = ecoliProbMap[AA];
    while(index < list.size() && list.at(index) < rand_selector){
        index++;
    }
    return codonMap[AA].at(index);
}

string reverseTranslate(string AAseq){
    string DNAseq = "";
    for (char c : AAseq){
        DNAseq = DNAseq + selectCodon(c);
    }
    return DNAseq;
}

int main(){
    cout << "Welcome to the gene design protocol! This program takes an amino acid seqence, and returns a complex probability based reverse translation" << endl;

    //Okay, first we need to read in the file
    cout << "Do you have a .fasta or do you want to copy and paste the amino acid sequence?" << endl;
    cout << "Type 'f' for .fasta or 'c' for copy and paste" << endl;

    string inputType;
    getline(cin, inputType);
    string inputSequence;

    if (inputType == "f"){
        cout << "You've selected .fasta \nPlease type the name of your .fasta file" << endl;
        string filename;
        getline(cin, filename);
        ifstream infile(filename);
        inputSequence=readFasta(infile);
        infile.close();
    }else if (inputType == "c"){
        cout << "You've selected copy and paste \nPlease paste your sequence" << endl;
        getline(cin, inputSequence);
    }else{
        cout << "I am so sorry but I don't want to code every possible input. The only allowed inputs are 'f' or 'c' :)" << endl;
        cout << "Restart the program please!" << endl;
        return 1;
    }

    // Now we need to check the sequence and prepare it for reverse translation
    if(inputSequence==""){return -1;}

    cout << "This is the input sequence being used:" <<endl;
    cout << inputSequence << endl;

    prepSequence(inputSequence);

    cout << inputSequence << endl;

    // Now we reverse translate
    string outputSequence = reverseTranslate(inputSequence);

        cout << outputSequence << endl;
  

    cout << "DONE! " << endl;
    return 0;
    

}
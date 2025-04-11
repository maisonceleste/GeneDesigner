# GeneDesigner
This is a program that does probability based reverse translation of amino acid sequences and some sequence prep

This Program is designed for my lab members, so it prompts for all inputs. 
If the .exe file works, use that, otherwise you will need to compile it yourself.
## Compilation instructions:
If you have a mac, linux, or WSL, use that. Otherwise you will have to put in an IT ticket to get a compiler installed (you can do it yourself, but it's easier to ask IT)
Figure out which compiler you have by typing `g++ --version` or `clang++ --version` into a terminal. Either one or both of those will print out which version you have. I use clang++, so if you have g++, just replace anytime I type `clang++` with `g++`
1. To compile you will need do download the .cpp file in this repository
2. In a terminal, navigate to the folder where the .cpp file is
3. Paste this command into the terminal:
   ```
   clang++ designer.cpp -o designer
   ```
   This works on my computer, however, sometimes I run into dependency problems and have to specify my C++ version so I type
   ```
   clang++ -std=c++17 designer.cpp -o designer
   ```
4. The terminal line should return without throwing any errors or warnings.
5. Compiling the code should have made an executable (.exe) file

## Running the code
You should be able to double click on the executable (which will pull up a terminal window and start the program) or type  ```./designer``` into a terminal that you already have open.
The program will then print out progress updates and ask for prompts as needed. 

## How this program works
I've used an E. coli codon probability chart to have the program select a codon for each amino acid in the sequence randomly, but with physiological probabilities. This increases sequence complexity which reduces the risk of the gene forming secondary structures that inhibit expression. The program will check for and add start codons, add a 10xHis-tag if requested, and check for and add stop codons. 

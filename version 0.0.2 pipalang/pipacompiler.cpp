#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>



using namespace std;

class PipaCompiler {
    public:
        void PipaToExe(string PipaName, string PipaExename){
            ifstream Pipafile(PipaName);
            if (!Pipafile.is_open()){
                cout << "Compiler [Error][[No file to run]] " << PipaName <<"\n";
                return;
            }
            ofstream filecpp("PipaLang.cpp");

            filecpp << "#include <iostream>\n";
            filecpp << "#include <string>\n";
            filecpp << "#include <cstdlib>\n"; 
            filecpp << "#include <ctime>\n";   
            filecpp << "#include <chrono>\n";  
            filecpp << "#include <vector>\n";  
            filecpp << "using namespace std;\n\n";
            
            filecpp << "class PipaBase {\n";
            filecpp << "private:\n";
            filecpp << "    chrono::steady_clock::time_point start_time;\n";
            filecpp << "public:\n";
            filecpp << "    PipaBase() { srand(time(0)); }\n"; 
            filecpp << "    void scr(string text) { cout << text; }\n";
            filecpp << "    void scr(int number) { cout << number; }\n";
            filecpp << "    void scr_nextl(string text) { cout << text << endl; }\n";
            filecpp << "    void scr_nextl(int number) { cout << number << endl; }\n";
            filecpp << "    void in(int &var) { cin >> var; }\n";
            filecpp << "    void in(string &var) { cin >> var; }\n";
            filecpp << "    string replace(string text, string findtext, string changetext){\n";
            filecpp << "        size_t pos = text.find(findtext);\n";
            filecpp << "        while(pos != string::npos){\n";
            filecpp << "            text.replace(pos, findtext.length(), changetext);\n";
            filecpp << "            pos = text.find(findtext, pos + changetext.length());\n";
            filecpp << "        }\n";
            filecpp << "        return text;\n";
            filecpp << "    }\n";

            filecpp << "    void measure_start() { start_time = chrono::steady_clock::now(); }\n";
            filecpp << "    void measure_end() {\n";
            filecpp << "        auto end_time = chrono::steady_clock::now();\n";
            filecpp << "        auto diff = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();\n";
            filecpp << "        cout << \"\\n[run time: \" << diff << \" ms]\\n\";\n";
            filecpp << "    }\n";

            //filecpp << "    int random(int min, int max) { return min + rand() % (max - min + 1); }\n";
            filecpp << "};\n";
            filecpp << "PipaBase value;\n";
            filecpp << "#define str string\n\n";
            filecpp << "#define elif else if\n";
            filecpp << "#define dbl double\n";
            filecpp << "#define array_str vector<string>\n";
            filecpp << "#define array_int vector<int>\n";
            filecpp << "#define pushitem push_back\n";

            string linecode;
            while (getline(Pipafile, linecode)){filecpp << linecode <<"\n";}

            Pipafile.close();
            filecpp.close();

            cout << "Compiler [Running][[Compiling]]\n";
            string CompileCommand = "g++ PipaLang.cpp -o" + PipaExename;
            int status = system(CompileCommand.c_str());

            system("del PipaLang.cpp");

            if (status == 0){
                cout << "Compiler [Finish][[successfully create " << PipaExename << ".exe ]]\n";
            } else {cout << "Compiler [Fail][[Can't run your project please check your code]]";}
        }
};
#include <iostream>
#include <vector>
#include <fstream>
#include <string>


// Tokenizing  string using stringstream 

using namespace std;

void getDir(const char* d, vector<string>& f)
{
    FILE* pipe = NULL;
    string pCmd = "dir /B /S " + string(d);
    char buf[256];

    if (NULL == (pipe = _popen(pCmd.c_str(), "rt")))
    {
        cout << "Shit" << endl;
        return;
    }

    while (!feof(pipe))
    {
        if (fgets(buf, 256, pipe) != NULL)
        {
            f.push_back(string(buf));
        }

    }
    _pclose(pipe);
}

void eraseSubStr(std::string& mainStr, const std::string& toErase)
{
    // Search for the substring in string
    size_t pos = mainStr.find(toErase);

    if (pos != std::string::npos)
    {
        // If found then erase it from string
        mainStr.erase(pos, toErase.length());
    }
}

vector<string> tokenizer(const string& str, const string& delimiters)
{
    vector<string> tokens;

    // Skip delimiters at beginning.

    string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // Find first "non-delimiter".

    string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters. Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
    return tokens;
}

int main()
{
    char dir[50] = "sm_doc_set";
    char dir_out[50] = "sm_doc_set_out";
    vector<string> files;
    getDir(dir, files);

    for (int i = 0; i < files.size(); i++)
    {
        string filename = files[i];

        // Remove directory if present.
        // Do this before extension removal incase directory has a period character.
        const size_t last_slash_idx = filename.find_last_of("\\/");
        if (std::string::npos != last_slash_idx)
        {
            filename.erase(0, last_slash_idx + 1);
        }

        // Remove extension if present.
        const size_t period_idx = filename.rfind('.');
        if (std::string::npos != period_idx)
        {
            filename.erase(period_idx);
        }
        files[i] = filename + ".txt";
    }

    cout << string(dir) + "/" + files[0] << endl;
    cout << "sm_doc_set/abf0704.txt";
    
    fstream f;
    f.open(string(dir) + "/" + files[0], ios::in);
    string data;
    string line;
    while (!f.eof())
    {
        getline(f, line);
        data += line;
    }
    f.close();
    

    vector<string> token = tokenizer(data, ".,:;`/\+-(){}[]<>*&^%$#@!?~/\\\=1234567890 ");

    fstream fout;
    fout.open(string(dir_out) + "/" + files[0], ios::out);
    for (int i = 0; i < token.size(); i++)
    {
        fout << token[i] << endl;
    }
    fout.close();
    

    /*
    for (int i = 0; i < files.size(); i++)
    {
        fstream f;
        f.open(string(dir)+"/"+files[i], ios::in);
        string data;
        string line;
        while (!f.eof())
        {
            getline(f, line);
            data += line;
        }
        f.close();

        vector<string> token = tokenizer(data, ".,:;`/\+-(){}[]<>*&^%$#@!?~/\\\=1234567890 ");

        fstream fout;
        fout.open(string(dir_out) + "/" + files[i], ios::out);
        for (int i = 0; i < token.size(); i++)
        {
            fout << token[i] << endl;
        }
        fout.close();
    }
    */
    /*
    fstream f;
    f.open("sm_doc_set/abf0704.shtml.txt", ios::in);

    string data;

    string line;
    while (!f.eof())
    {
        getline(f, line);
        data += line;
    }
    f.close();

    vector<string> token = tokenizer(data, ".,:;`/\+-(){}[]<>*&^%$#@!?~/\\\=1234567890 ");

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < token.size(); i++)
    {
        fout << token[i] << endl;
    }
    fout.close();
    */ 
}


#if !defined STORABLE_H
#define STORABLE_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Reader;
class writer;

class Storable
{
public:
    Storable(){}
    Storable(Reader&){}
    virtual ~Storable(){}
    virtual void Write(Writer&) const = 0;

};

class Reader
{
public:
    Reader(char * filename):fin(filename,ios::binary){}
    virtual ~Reader(){fin.close();}
    virtual Reader& operator >> (int&);
    virtual Reader& operator >> (const int&);
    virtual Reader& operator >> (char&);
    virtual Reader& operator >> (char*&);
    virtual Reader& operator >> (bool&);
    virtual Reader& operator >> (vector<char>&);

private:
    ifstream fin;

};

class Writer
{
public:
    Writer(char * filename):fout(filename,ios::binary){}
    virtual ~Reader(){fout.close();}
    virtual Writer& operator << (int&);
    virtual Writer& operator << (const int&);
    virtual Writer& operator << (char&);
    virtual Writer& operator << (char*&);
    virtual Writer& operator << (bool&);
    virtual Writer& operator << (vector<char>&);

private:
    ofstream fout;

};

#endif

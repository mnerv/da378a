#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

#include "PersonReg.hpp"
#include <iostream>
using namespace std;

#if 1
#define PN(x) cout << x
#define DN(x) x
#define PD(x) cout << x
#else
#define PN(x)
#define DN(x)
#define PD(x) (x)
#endif

void Init(PersonReg& tr) {
    tr.Tom();
    PD(tr.LaggTillTest("olle", "0703955123"));
    PD(tr.LaggTillTest("olle", "123"));
    PD(tr.LaggTillTest("kurtåke", "12345"));
    PD(tr.LaggTillTest("olle", "456"));
    PD(tr.LaggTillTest("sven", "456"));
    PD(tr.LaggTillTest("kurt", "95815"));
    PN(endl);
    PN(("fullt reg "));
    PN((endl));
    DN((tr.Print()));
}

#include <fstream>
bool ReadReg(PersonReg& reg, string fileName) {
    string line;
    ifstream myfile(fileName);

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            while (line.length() == 0 && getline(myfile, line));
            string name(line);
            string adress;
            getline(myfile, adress);
            auto p = Person(name, adress);
            reg.LaggTill(&p);
        }
        myfile.close();
        return true;
    }
    else {
        cout << "Unable to open file";
        return false;
    }
}

void Test1() {
    PersonReg reg(10);
    ReadReg(reg, "PersonExempel.txt");
    reg.Print(); cout << "\n\n";
    reg.Tom();
    reg.Print();
}

void Test2() {
    PersonReg reg(10);
    Init(reg);
    string namn, adress;
    Person te, *tep;

    tep = reg.SokNamn("olle");
    if (tep) {
        cout << tep->adress << endl;
        reg.TaBortEntry(tep);
    }
    else
        cout << "not found \n";

    tep = reg.SokNamn("olle");
    if (tep) {
        cout << tep->adress << endl;
        reg.TaBortEntry(tep);
    }
    else
        cout << "not found \n";

    tep = reg.SokNamn("olle");
    if (tep) {
        cout << tep->adress << endl;
        reg.TaBortEntry(tep);
    }
    else
        cout << "not found \n";

    tep = reg.SokNamn("olle");
    if (tep) {
        cout << tep->adress << endl;
        reg.TaBortEntry(tep);
    }
    else
        cout << "not found \n";

    tep = reg.SokNamn("olle");
    if (tep) {
        cout << tep->adress << endl;
        reg.TaBortEntry(tep);
    }
    else
        cout << "not found \n";

    reg.Print();

    reg.Tom();
    reg.Print();
}

void Test3() {
    PersonReg reg(10);

    Init(reg);
    reg.Print();
    string namn, adress;
    Person te, *tep;

    tep = nullptr;
    while ((tep = reg.SokFritt("olle", tep))) {
        tep->Print();
        //        cout << tep->adress << endl;
    }
    cout << "not found \n";

    cout << "blandade sökningar \n";
    Person* ptr1 = nullptr, *ptr2 = nullptr;
    bool first = true;
    while (first || ptr1 || ptr2) {
        if (ptr1 || first) {
            ptr1 = reg.SokFritt("olle", ptr1);
            if (ptr1)
                ptr1->Print();
        }
        if (ptr2 || first) {
            ptr2 = reg.SokFritt("581", ptr2);
            if (ptr2)
                ptr2->Print();
        }
        first = false;
    }
}

int main() {
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //locale::global(locale("swedish"));
    PersonReg pr(5);
    Init(pr);
    Test1();
    Test2();
    Test3();
    cin.get();
}

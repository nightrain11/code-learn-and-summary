#include <iostream>
#include <getopt.h>
#include "parsingargs.h"
#include <string.h>


using namespace std;


int main(int argc, char * argv[])
{

    //string tmpPara = "-p \"4567\" --out 1.log "; //ok
    //string tmpPara = "xxxx -p \"4567\" --out 1.log ";//ok
    //string tmpPara = "-p \"4567\" --out 1.log 2.log"; //ok
    string tmpPara = "";
    for(int i=1;i <argc; i++)
    {
        cout << i << "=" << argv[i] <<"---"<< endl;
        if(strlen(argv[i]) == 0) //处理空字符串
        {
            cout << "find NULL" << endl;
            tmpPara += char(31);
        }
        else
        {
            tmpPara += argv[i];
        }
        tmpPara += " ";
    }
    std::map<std::string, std::vector<std::string> > result;
    ParsingArgs pa;
    pa.AddArgType('l',"getlist", ParsingArgs::NO_VALUE);
    pa.AddArgType('p',"getuser", ParsingArgs::MAYBE_VALUE);
    pa.AddArgType('o',"outFile", ParsingArgs::MUST_VALUE);
    bool bExit = false;
    do
    {
        result.clear();
        cout << "input is:" << tmpPara << "---size = " << tmpPara.size()<< endl;
        std::string errPos;
        int iRet = pa.Parse(tmpPara,result, errPos);
        if(0>iRet)
        {
            cout << "参数错误" << iRet << errPos << endl;
        }
        else
        {
            map<std::string, std::vector<std::string> >::iterator it = result.begin();
            for(; it != result.end(); ++it)
            {
                cout << "key=" << it->first<<endl;
                for(int i=0; i<it->second.size(); ++i)
                {
                    cout << "   value =" << it->second[i] << "------" << endl;
                }
            }
        }
        string str;
        cout << ">>> ";
        getline(cin, tmpPara);
        if(0 == tmpPara.compare("exit"))
        {
            bExit = true;
        }

    }while(!bExit);
    return 0;
}



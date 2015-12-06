#include <bits/stdc++.h>

using namespace std;

int main()
{
    string Reserved[8] ={"if", "then", "else", "end", "repeat", "until", "read", "write"};
    string special[9] = {"+", "-", "*", "/", "=", "<", "()", ";",":="};
    string line;
    bool ifnum = 0;

    int start = 1, comment = 2, num = 3, id = 4, nassign = 5, done = 6;
    int current_state = start;
    char other;

    ifstream myfile ("tiny_sample_code.txt");
    ofstream another ("scanner_output.txt");
    if (myfile.is_open() && another.is_open())
    {
        while ( getline (myfile,line) )
        {
            string check="";
            current_state=start;
            for(int i=0; i<=line.length();i++)
            {
                switch (current_state)
                {
                    // start
                    case 1:
                    {
                        if(line[i] == ' ')
                            current_state = start;
                        else if(isdigit(line[i]))
                        {
                            current_state = num;
                            check = check + line[i];
                        }
                        else if(isalpha(line[i]))
                        {
                            check = check + line[i];
                            current_state = id;
                        }
                        else if (line[i]==':')
                        {
                            current_state = nassign;
                            check = check + line[i];
                        }
                        else if (line[i] == '{')
                         {
                            current_state = comment;
                            check = check + line[i];
                         }
                        else
                        {
                            current_state = done;
                            check = check + line[i];
                        }
                        break;
                    }
                    //comment
                    case 2:
                    {
                        if(line[i]=='}')
                            current_state = start;
                        else
                            current_state = comment;
                        break;
                    }
                    //num
                    case 3:
                    {
                        if(isdigit(line[i]))
                        {
                            check = check + line[i];
                            current_state = num;
                        }
                        else
                        {
                            i--;
                            ifnum = 1;
                            current_state = done;
                        }
                        break;
                    }
                    //id
                    case 4:
                    {
                        if(isalpha(line[i]))
                        {
                            current_state = id;
                            check = check + line[i];
                        }
                        else
                        {
                            i--;
                            current_state = done;
                        }
                        break;
                    }
                    //assign
                    case 5:
                    {
                        if(line[i] == '=')
                        {
                            check = check + line[i];
                            current_state = done;
                        }
                        else
                        {
                            i--;
                            current_state = done;
                        }
                        break;
                    }
                    //done
                    case 6:
                    {
                        if(isalpha(check[0]))
                        {
                            for(int j =0; j<8; j++)
                            {
                                if(check == Reserved[j])
                                {
                                    another <<check  << setw(30 - check.length())<<"\n";
                                    current_state=start;
                                    i--;
                                    check ="";
                                }
                                if(check == "")
                                    break;
                            }
                            if(check.length()>0)
                            {
                                another << setw(30 - check.length()) << "identifier"<<"\n";
                                current_state=start;
                                check = "";
                                i--;
                                break;
                            }
                        }
                        for(int j=0; j<9; j++)
                        {
                            if(check == special[j])
                             {
                                another << check << setw(30 - check.length())<<"\n";
                                current_state=start;
                                i--;
                                check = "";
                             }
                              if(check == "")
                                break;
                        }
                        if (ifnum == 1)
                        {
                            another << setw(30 - check.length()) << "number"<<"\n";
                            current_state=start;
                            i--;
                            check = "";
                            ifnum = 0;
                            break;
                        }
                    }
                }
            }
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    return 0;
}

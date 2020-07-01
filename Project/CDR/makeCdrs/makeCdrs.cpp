#include <iostream>
#include <fstream>  
#include <string>
#include <vector>
#include <utility>
#include <cstring>
#include <string>

void MakeRandomImsi(char* a_imsi)
{
    for (size_t i = 0; i < 15; ++i)
    {
        a_imsi[i] = rand() % 10 + 48;
    }
    a_imsi[15] = '\0';
}

void MakeRandommsisdn(char* a_imsi)
{
    std::string temp;
    for (size_t i = 0; i < 15; ++i)
    {
        a_imsi[i] = rand() % 10 + 48;
    }
    a_imsi[15] = '\0';
}


void MakeRandomimei(char* a_imsi)
{
    std::string temp;
    for (size_t i = 0; i < 15; ++i)
    {
        a_imsi[i] = rand() % 10 + 48;
    }
    a_imsi[15] = '\0';
}

void MakeRandomDate(char* a_imsi)
{
    std::string temp;

    size_t i = 0;
    
    a_imsi[i] = rand() % 2 + 48;
    ++i;

    if (a_imsi[i] == '1')
    {
        a_imsi[i] = rand() % 3 + 48;
        ++i;
    }
    else
    {
       a_imsi[i] = rand() % 10 + 48;
        ++i;
    }
    

    a_imsi[i] = '/';
    ++i;

    a_imsi[i] = rand() % 3 + 48;
    ++i;

     a_imsi[i] = rand() % 10 + 48;
    ++i;
    

    a_imsi[i] = '/';
    ++i;

    a_imsi[i] = rand() % 10 + 48;
    ++i;

     a_imsi[i] = rand() % 10 + 48;
    ++i;

    a_imsi[i] = rand() % 10 + 48;
    ++i;

     a_imsi[i] = rand() % 10 + 48;
    ++i;

    a_imsi[i] = '\0';
    
}

void MakeRandomTime(char* a_imsi)
{
    std::string temp;

    size_t i = 0;
    
    a_imsi[i] = rand() % 2 + 48;
    ++i;

     a_imsi[i] = rand() % 4 + 48;
    ++i;
    

    a_imsi[i] = '/';
    ++i;

    a_imsi[i] = rand() % 6 + 48;
    ++i;

     a_imsi[i] = rand() % 10 + 48;
    ++i;
    

    a_imsi[i] = '/';
    ++i;

    a_imsi[i] = rand() % 6 + 48;
    ++i;

     a_imsi[i] = rand() % 10 + 48;
    ++i;    

    a_imsi[i] = '\0';
}

void MakeRandomDuration(char* a_imsi)
{
    for (size_t i = 0; i < 3; ++i)
    {
        a_imsi[i] = rand() % 10 + 48;
    }
    a_imsi[3] = '\0';
}


void MakeRandomdownload(char* a_imsi)
{
    for (size_t i = 0; i < 3; ++i)
    {
        a_imsi[i] = rand() % 10 + 48;
    }
    a_imsi[3] = '\0';
}

void MakeRandomUpload(char* a_imsi)
{
    for (size_t i = 0; i < 3; ++i)
    {
        a_imsi[i] = rand() % 10 + 48;
    }
    a_imsi[3] = '\0';
}


void Makerandomoperator(char* a_operator, char* a_mccMnc, std::vector<std::pair<std::string, std::string> >& a_operatorVec)
{
    int randoma = rand() % 5;
    strcpy(a_operator, &(a_operatorVec[randoma].first[0]));
    strcpy(a_mccMnc, &(a_operatorVec[randoma].second[0]));

}
void Makerandomparty(char* a_mccMnc, std::vector<std::pair<std::string, std::string> >& a_operatorVec)
{
    int randoma = rand() % 5;

    strcpy(a_mccMnc, &a_operatorVec[randoma].second[0]);
}




void MakeType(char* a_operator)
{
    int randoma = rand() % 5;

    std::cout << randoma << '\n';
    if(randoma == 0)
    {
        strcpy(a_operator, "moc");
    }
    else if(randoma == 1)
    {
        strcpy(a_operator, "mtc");
    }
    else if(randoma == 2)
    {
        strcpy(a_operator, "sms-mo");
    }
    else if(randoma == 3)
    {
        strcpy(a_operator, "sms-mt");
    }
    else if(randoma == 4)
    {
        strcpy(a_operator, "gprs");
    }
}


int main()
{
    std::vector<std::pair<std::string, std::string> > g_operatorVec;

    std::pair<std::string, std::string> operator1;
    operator1.first = "cellcom bee";
    operator1.second = "048051";

    std::pair<std::string, std::string> operator2;
    operator2.first = "orange man";
    operator2.second = "048052";

    std::pair<std::string, std::string> operator3;
    operator3.first = "partner house";
    operator3.second = "048053";

    std::pair<std::string, std::string> operator4;
    operator4.first = "cellcom inc";
    operator4.second = "048054";

    std::pair<std::string, std::string> operator5;
    operator5.first = "sergio Telecom";
    operator5.second = "999998";

    g_operatorVec.push_back(operator1);
    g_operatorVec.push_back(operator2);
    g_operatorVec.push_back(operator3);
    g_operatorVec.push_back(operator4);
    g_operatorVec.push_back(operator5);

    srand (time(NULL));
    std::ofstream outfile ("test3.txt");

    char imsi[16];
    char msisdn[16];
    char imei[16];
    char operatorName[64];
    char mccMnc[7];
    char type[7];
    char date[11];
    char time[9];
    char duration[4];
    char download[4];
    char upload[4];
    char partyMsisbn[16];
    char partyMccMnc[7];

    outfile << "imsi | msisdn  | imei  | operatorName  | mccMnc  |   type  |  date  |  time  |   duration  |  download   |   upload   |   partyMsisbn  |  partyMccMnc" << std::endl;


    for (size_t i = 0 ;i < 40000; ++i)
    {
        MakeRandomImsi(imsi);
        MakeRandommsisdn(msisdn);
        MakeRandomimei(imei);
        MakeRandomDate(date);
        MakeRandomTime(time);
        MakeRandomDuration(duration);
        MakeRandomdownload(download);
        MakeRandomUpload(upload );
        Makerandomoperator(operatorName, mccMnc, g_operatorVec);
        Makerandomparty(partyMccMnc, g_operatorVec);
        MakeRandommsisdn(partyMsisbn);
        MakeType(type);


       outfile << imsi << '|' << msisdn << '|' << imei << '|' << operatorName << '|' << mccMnc << '|' << type << '|' << date << '|' << time << '|' << duration << '|' << download << '|' << upload << '|' << partyMsisbn << '|' << partyMccMnc << std::endl;
    }
    outfile.close(); 

    return 1;
} 
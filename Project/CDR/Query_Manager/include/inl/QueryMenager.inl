namespace advcpp
{


size_t RequestClientMSG::CreateMsg(char* a_buffer)
{
    RequestClient Request;
    Request.m_type = ONE_CLIENT_REQ;
    bool flag = true;
    while(flag)
        {
            std::cout<<"enter imsi \n";
            std::cin>>Request.m_imsi;
            if(strlen(Request.m_imsi) > 0)
            {
                flag = false;
                break;
            }
        }
            
    Request.m_length = strlen(Request.m_imsi);

    size_t size;

    try 
    {
        size = Translator::ClientRequestEncode(&Request, a_buffer); 
    }

    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return size; 
}

size_t RequestOperotorMSG::CreateMsg(char* a_buffer)
{
    RequestOperator Request;
    Request.m_type = ONE_OPERATOR_REQ;
    bool flag = true;
    while(flag)
        {
            std::cout<<"enter Mcc_Mnc \n";
            std::cin>>Request.m_value;
            if(strlen(Request.m_value) > 0)
            {
                flag = false;
                break;
            }
        }
            
    Request.m_length = strlen(Request.m_value);

    size_t size;

    try 
    {
        size  = Translator::RequestOperatorEncode(&Request, a_buffer); 
    }

    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return size;
}


template <typename App>
QueryMenager<App>::QueryMenager(size_t a_port, char a_ip[MAX_IP_LENGTH], size_t a_buffer)
:   m_queryRequest(a_port, a_ip, a_buffer)
{
}

template <typename App>
int QueryMenager<App>::displayMenu()
{
    int i=0;
    int flag = 999;
    while(flag)
    {
        std::cout << "Choice the request:\n";
        std::cout << "1. Request client \n";
        std::cout << "2. Request operator \n";
        std::cin >>i;
        if(i==1 || i == 2)
        {
            flag = 0;
        }
    }
    return i; 
}

template <typename App>
void QueryMenager<App>::Menu()
{
    int choice;
    while(1)
    {
        choice = displayMenu();
        switch (choice)
        {

            case CLIENT_REQUEST:
            {
                char buffer[20];
                RequestClientMSG req;
                req.CreateMsg(buffer);
                m_queryRequest.SendMSG(buffer);
                break;
            }

            case OPERATOR_REQUEST:
            {
                char buffer[100];
                RequestOperotorMSG req;
                req.CreateMsg(buffer);
                m_queryRequest.SendMSG(buffer);
                break;
            }
            default:
            {
                std::cout<<"wrong choice\n";  //TODO exception
                break;
            } 
        }
    }

}

}


#include "data_storage.hpp"

namespace advcpp
{
 
DataStorage::DataStorage()
: m_clients(CLIENT_INDX_SIZE, HashingClient())
, m_operators(OPERATOR_INDX_SIZE, HashingOperator())
{
}

bool DataStorage::GetOne(IMSI const& a_imsi, Client& a_client) const
{
    return m_clients.Find(a_imsi, a_client);
}

bool DataStorage::GetAll(std::vector<Client>& a_target) const
{
    m_clients.GetAll(a_target);
    return true;
}

void DataStorage::Drain(std::vector<Client>& a_target)
{
    m_clients.Drain(a_target);
}


bool DataStorage::GetOne(MCCMNC const& a_mccMnc, Operator& a_operator) const
{
    return m_operators.Find(a_mccMnc, a_operator);
}

bool DataStorage::GetAll(std::vector<Operator>& a_target) const
{
    m_operators.GetAll(a_target);
    return true;
}

void DataStorage::Drain(std::vector<Operator>& a_target)
{
    m_operators.Drain(a_target);
}

void DataStorage::Upsert(Cdr const& a_cdr)
{
    upsertClient(a_cdr);
    upsertOperator(a_cdr); 
}

void DataStorage::upsertClient(Cdr const& a_cdr)
{
    Client client;
    Client::CdrToClientOut(a_cdr, client);
    Upsert(client);
    if(Client::CdrToClientIn(a_cdr, client))
    {
        Upsert(client);
    }
}

void DataStorage::upsertOperator(Cdr const& a_cdr)
{
    Operator op;
    if(Operator::CdrToOperatorOut(a_cdr, op))
    { 
        Upsert(op);  
        Operator::CdrToOperatorIn(a_cdr, op);
        Upsert(op);
    }
}

void DataStorage::Upsert(Client const& a_client)
{
    m_clients.Upsert(a_client.Imsi(), a_client, UpdateClient());
}

void DataStorage::Upsert(Operator const& a_operator)
{
    m_operators.Upsert(a_operator.MccMnc(), a_operator, UpdateOperator());    
}



}//namespace advcpp

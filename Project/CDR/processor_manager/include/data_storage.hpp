#ifndef DATA_STORAGE_HPP
#define DATA_STORAGE_HPP

#include "protocol_handler_ui.hpp"
#include "commons.hpp"
#include "client.hpp"
#include "operator.hpp"
#include "index.hpp"


namespace advcpp
{

class DataStorage: private UnCopyable
{
public:
    DataStorage();

    template<typename Value, typename Key>
    static bool Find(DataStorage const& a_ds, std::vector<Value>& a_vec, Key const* a_key = 0);

    void Upsert(Cdr const& a_cdr);



    bool GetOne(IMSI const& a_imsi, Client& a_client) const;
    bool GetAll(std::vector<Client>& a_target) const;
    void Drain(std::vector<Client>& a_target);

    bool GetOne(MCCMNC const& a_mccMnc, Operator& a_operator) const;
    bool GetAll(std::vector<Operator>& a_target) const;
    void Drain(std::vector<Operator>& a_target);

    void Upsert(Client const& a_client);
    void Upsert(Operator const& a_operator);

private:
    void upsertClient(Cdr const& a_cdr);
    void upsertOperator(Cdr const& a_cdr);

private:
    const static size_t CLIENT_INDX_SIZE = 1000;
    const static size_t OPERATOR_INDX_SIZE = 100;
    Index<IMSI, Client, HashingClient> m_clients;
    Index<MCCMNC, Operator, HashingOperator> m_operators;
};


} //namespace advcpp

#include "data_storage.inl"

#endif //DATA_STORAGE_HPP

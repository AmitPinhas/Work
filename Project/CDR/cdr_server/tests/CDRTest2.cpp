#include "mu_test.h"

#include <iostream> // std::cout
#include "tcp_server.hpp"
#include "safe_hash_table.hpp"
#include "tcp_client.hpp"
#include "socket.hpp"

UNIT(client)
    advcpp::TCPClient client(2300, "127.0.0.1");

    char msgSend[] = "hello";

    client.Send(msgSend, sizeof(msgSend));

    char buffer[4096];

    client.Recv(buffer, sizeof(buffer));

    std::cout << buffer << '\n';

    ASSERT_PASS();

END_UNIT

TEST_SUITE(test the cdr on fire)

    TEST(client)

END_SUITE

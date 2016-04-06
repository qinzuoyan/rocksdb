# pragma once
# include "rrdb.client.perf.h"

namespace dsn { namespace apps {  

class rrdb_perf_test_client_impl : public rrdb_perf_test_client
{
public:
    using rrdb_perf_test_client::rrdb_perf_test_client;

    virtual void send_one_put(int payload_bytes, int key_space_size) override
    {
        update_request req;

        auto rs = random64(0, 10000000) % key_space_size;
        std::stringstream oss;
        oss << "key." << rs;
        req.key = oss.str();
        req.value = req.key;

        put(
            req,
            [this, context = prepare_send_one()](error_code err, int&& resp)
            {
                end_send_one(context, err);
            },
            _timeout
            );
    }

    virtual void send_one_remove(int payload_bytes, int key_space_size) override
    {
        auto rs = random64(0, 10000000) % key_space_size;
        std::stringstream oss;
        oss << "key." << rs;
        std::string req = oss.str();

        remove(
            req,
            [this, context = prepare_send_one()](error_code err, int32_t&& resp)
            {
                end_send_one(context, err);
            },
            _timeout
            );
    }

    virtual void send_one_merge(int payload_bytes, int key_space_size) override
    {
        update_request req;

        auto rs = random64(0, 10000000) % key_space_size;
        std::stringstream oss;
        oss << "key." << rs;
        req.key = oss.str();
        req.value = req.key;

        merge(
            req,
            [this, context = prepare_send_one()](error_code err, int32_t&& resp)
            {
                end_send_one(context, err);
            },
            _timeout
            );
    }

    virtual void send_one_get(int payload_bytes, int key_space_size) override
    {
        auto rs = random64(0, 10000000) % key_space_size;
        std::stringstream oss;
        oss << "key." << rs;
        std::string req = oss.str();
        
        get(
            req,
            [this, context = prepare_send_one()](error_code err, read_response&& resp)
            {
                end_send_one(context, err);
            },
            _timeout
            );
    }
};

} } 

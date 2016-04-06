# pragma once
# include <dsn/dist/replication.h>
# include "rrdb.code.definition.h"
# include <iostream>

namespace dsn { namespace apps { 

class rrdb_client 
    : public ::dsn::replication::replication_app_client_base
{
public:
    using replication_app_client_base::replication_app_client_base;
    virtual ~rrdb_client() {}

    // from requests to partition index
    // PLEASE DO RE-DEFINE THEM IN A SUB CLASS!!!
    virtual uint64_t get_key_hash(const update_request& key) { return 0; }
    virtual uint64_t get_key_hash(const std::string& key) { return 0; }

    // ---------- call RPC_RRDB_RRDB_PUT ------------
    // - synchronous  
    std::pair< ::dsn::error_code, int32_t> put_sync(
        const update_request& update,
        std::chrono::milliseconds timeout = std::chrono::milliseconds(0)
        )
    {
        return dsn::rpc::wait_and_unwrap<int32_t>(
            ::dsn::replication::replication_app_client_base::write(
                get_key_hash(update),
                RPC_RRDB_RRDB_PUT,
                update,
                this,
                empty_callback,
                timeout,
                0
                )
            );
    }
 
    // - asynchronous with on-stack update_request and int32_t 
    template<typename TCallback>
    ::dsn::task_ptr put(
        const update_request& update,
        TCallback&& callback,
        std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
        int reply_hash = 0
        )
    {
        return ::dsn::replication::replication_app_client_base::write(
            get_key_hash(update),
            RPC_RRDB_RRDB_PUT,
            update,
            this,
            std::forward<TCallback>(callback),
            timeout,
            reply_hash
            );
    }

    // ---------- call RPC_RRDB_RRDB_REMOVE ------------
    // - synchronous  
    std::pair< ::dsn::error_code, int32_t> remove_sync(
        const std::string& key,
        std::chrono::milliseconds timeout = std::chrono::milliseconds(0)
        )
    {
        return dsn::rpc::wait_and_unwrap<int32_t>(
            ::dsn::replication::replication_app_client_base::write(
                get_key_hash(key),
                RPC_RRDB_RRDB_REMOVE,
                key,
                this,
                empty_callback,
                timeout,
                0
                )
            );
    }
 
    // - asynchronous with on-stack std::string and int32_t 
    template<typename TCallback>
    ::dsn::task_ptr remove(
        const std::string& key,
        TCallback&& callback,
        std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
        int reply_hash = 0
        )
    {
        return ::dsn::replication::replication_app_client_base::write(
            get_key_hash(key),
            RPC_RRDB_RRDB_REMOVE,
            key,
            this,
            std::forward<TCallback>(callback),
            timeout,
            reply_hash
            );
    }

    // ---------- call RPC_RRDB_RRDB_MERGE ------------
    // - synchronous  
    std::pair< ::dsn::error_code, int32_t> merge_sync(
        const update_request& update,
        std::chrono::milliseconds timeout = std::chrono::milliseconds(0)
        )
    {
        return dsn::rpc::wait_and_unwrap<int32_t>(
            ::dsn::replication::replication_app_client_base::write(
                get_key_hash(update),
                RPC_RRDB_RRDB_MERGE,
                update,
                this,
                empty_callback,
                timeout,
                0
                )
            );
    }
 
    // - asynchronous with on-stack update_request and int32_t 
    template<typename TCallback>
    ::dsn::task_ptr merge(
        const update_request& update,
        TCallback&& callback,
        std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
        int reply_hash = 0
        )
    {
        return ::dsn::replication::replication_app_client_base::write(
            get_key_hash(update),
            RPC_RRDB_RRDB_MERGE,
            update,
            this,
            std::forward<TCallback>(callback),
            timeout,
            reply_hash
            );
    }

    // ---------- call RPC_RRDB_RRDB_GET ------------
    // - synchronous  
    std::pair< ::dsn::error_code, read_response> get_sync(
        const std::string& key,
        std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
        ::dsn::replication::read_semantic semantic = ::dsn::replication::read_semantic::ReadLastUpdate
        )
    {
        return dsn::rpc::wait_and_unwrap<read_response>(
            ::dsn::replication::replication_app_client_base::read(
                get_key_hash(key),
                RPC_RRDB_RRDB_GET,
                key,
                this,
                empty_callback,
                timeout,
                0,
                semantic
                )
            );
    }
 
    // - asynchronous with on-stack std::string and read_response 
    template<typename TCallback>
    ::dsn::task_ptr get(
        const std::string& key,
        TCallback&& callback,
        std::chrono::milliseconds timeout = std::chrono::milliseconds(0),
        int reply_hash = 0,
        ::dsn::replication::read_semantic semantic = ::dsn::replication::read_semantic::ReadLastUpdate
        )
    {
        return ::dsn::replication::replication_app_client_base::read(
            get_key_hash(key),
            RPC_RRDB_RRDB_GET,
            key,
            this,
            std::forward<TCallback>(callback),
            timeout,
            reply_hash,
            semantic
            );
    }
};
} } 

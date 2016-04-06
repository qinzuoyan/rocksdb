# pragma once
# include <dsn/service_api_cpp.h>

//
// uncomment the following line if you want to use 
// data encoding/decoding from the original tool instead of rDSN
// in this case, you need to use these tools to generate
// type files with --gen=cpp etc. options
//
// !!! WARNING: not feasible for replicated service yet!!! 
//
// # define DSN_USE_THRIFT_SERIALIZATION

# ifdef DSN_USE_THRIFT_SERIALIZATION


# include "rrdb_types.h" 


# else // use rDSN's data encoding/decoding

namespace dsn { namespace apps { 
    // ---------- update_request -------------
    struct update_request
    {
        std::string key;
        std::string value;
    };

    inline void marshall(::dsn::binary_writer& writer, const update_request& val)
    {
        marshall(writer, val.key);
        marshall(writer, val.value);
    }

    inline void unmarshall(::dsn::binary_reader& reader, /*out*/ update_request& val)
    {
        unmarshall(reader, val.key);
        unmarshall(reader, val.value);
    }

    // ---------- read_response -------------
    struct read_response
    {
        int32_t error;
        std::string value;
    };

    inline void marshall(::dsn::binary_writer& writer, const read_response& val)
    {
        marshall(writer, val.error);
        marshall(writer, val.value);
    }

    inline void unmarshall(::dsn::binary_reader& reader, /*out*/ read_response& val)
    {
        unmarshall(reader, val.error);
        unmarshall(reader, val.value);
    }

} } 

#endif 

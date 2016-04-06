namespace cpp dsn.apps

struct update_request
{
    1:binary key;
    2:binary value;
}

struct read_response
{
    1:i32    error;
    2:binary value;
}

service rrdb
{
    i32 put(1:update_request update);
    i32 remove(1:binary key);
    i32 merge(1:update_request update);
    read_response get(1:binary key);
}


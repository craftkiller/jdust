/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#include "result_store.h"
#include <sstream>

void result_store::store_result(const std::string & val)
{
    results.push_back(val);
}

void result_store::store_error(const std::string & val)
{
    errors.push_back(val);
}

void result_store::store_log(const std::string & val)
{
    logs.push_back(val);
}

std::string result_store::get_result() const
{
    bool first = true;
    std::stringstream combined;
    for (const std::string & val : results)
    {
        if (!first)
        {
            combined << '\n';
        } else {
            first = false;
        }
        combined << val;
    }
    return combined.str();
}

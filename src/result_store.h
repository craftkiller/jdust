/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#pragma once

#include <string>
#include <list>
#include "v8.h"
#include "out_streams.h"

using namespace v8;

class result_store : public out_streams
{
  public:
    virtual void store_result(const std::string & val);
    virtual void store_error(const std::string & val);
    virtual void store_log(const std::string & val);

    std::string get_result() const;
    
  private:
    std::list<std::string> results;
    std::list<std::string> errors;
    std::list<std::string> logs;
};


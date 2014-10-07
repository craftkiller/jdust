/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#pragma once
#include <string>
#include <v8.h>

class out_streams
{
  public:
    virtual ~out_streams() { }
    virtual void store_result(const std::string & val) = 0;
    virtual void store_error(const std::string & val) = 0;
    virtual void store_log(const std::string & val) = 0;
};

v8::Handle<v8::Object> wrap_out_streams(v8::Isolate* isolate, out_streams* store);

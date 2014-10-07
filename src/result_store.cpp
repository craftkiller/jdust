/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#include "result_store.h"
#include <iostream>
#include <sstream>

namespace
{
    Handle<ObjectTemplate> make_result_store_template(Isolate* isolate)
    {
        EscapableHandleScope handle_scope(isolate);
    
        Local<ObjectTemplate> result = ObjectTemplate::New(isolate);
        result->SetInternalFieldCount(1);

        // Return the result through the current handle scope.
        return handle_scope.Escape(result);
    }

    void set_error(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::HandleScope handle_scope(args.GetIsolate());
        Local<Object> self = args.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
        void* ptr = wrap->Value();
        result_store* state = static_cast<result_store*>(ptr);

        for (int i = 0; i < args.Length(); i++)
        {
            v8::String::Utf8Value str(args[i]);
            std::string error = std::string(*str);
            std::cerr << error << "\n";
            state->store_error(error);
        }
    }

    void set_result(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::HandleScope handle_scope(args.GetIsolate());
        Local<Object> self = args.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
        void* ptr = wrap->Value();
        result_store* state = static_cast<result_store*>(ptr);

        for (int i = 0; i < args.Length(); i++)
        {
            v8::String::Utf8Value str(args[i]);
            std::string result = std::string(*str);
            state->store_result(result);
        }
    }
}

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

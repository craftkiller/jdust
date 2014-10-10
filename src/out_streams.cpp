/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#include "out_streams.h"
#include <iostream>

using namespace v8;

namespace
{
    Handle<ObjectTemplate> make_out_streams_template(Isolate* isolate)
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
        out_streams* state = static_cast<out_streams*>(ptr);

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
        out_streams* state = static_cast<out_streams*>(ptr);

        for (int i = 0; i < args.Length(); i++)
        {
            v8::String::Utf8Value str(args[i]);
            std::string result = std::string(*str);
            state->store_result(result);
        }
    }

    void set_log(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        v8::HandleScope handle_scope(args.GetIsolate());
        Local<Object> self = args.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
        void* ptr = wrap->Value();
        out_streams* state = static_cast<out_streams*>(ptr);

        for (int i = 0; i < args.Length(); i++)
        {
            v8::String::Utf8Value str(args[i]);
            std::string result = std::string(*str);
            state->store_log(result);
        }
    }
}

Handle<Object> wrap_out_streams(Isolate* isolate, out_streams* store)
{
    // Handle scope for temporary handles.
    EscapableHandleScope handle_scope(isolate);

    Handle<ObjectTemplate> templ = make_out_streams_template(isolate);
    templ->Set(String::NewFromUtf8(isolate, "error"), FunctionTemplate::New(isolate, set_error));
    templ->Set(String::NewFromUtf8(isolate, "store"), FunctionTemplate::New(isolate, set_result));
    templ->Set(String::NewFromUtf8(isolate, "log"), FunctionTemplate::New(isolate, set_error));

    Local<Object> result = templ->NewInstance();

    // Wrap the raw C++ pointer in an External so it can be referenced
    // from within JavaScript.
    Handle<External> request_ptr = External::New(isolate, store);

    // Store the request pointer in the JavaScript wrapper.
    result->SetInternalField(0, request_ptr);

    // Raise result to the parent scope
    return handle_scope.Escape(result);
}


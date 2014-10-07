/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#include "dust_renderer.h"

#include <iostream>
#include <string>
#include "v8.h"
#include "result_store.h"
#include "return_codes.h"

using namespace v8;

int execute_js(out_streams & out, const char* raw_source)
{
    // Create a new Isolate and make it the current one.
    Isolate* isolate = Isolate::New();
    Isolate::Scope isolate_scope(isolate);

    // Create a stack-allocated handle scope.
    HandleScope handle_scope(isolate);

    // Create a template for the global object.
    v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);

    // Create a new context.
    Local<Context> context = Context::New(isolate, nullptr, global);

    // Enter the context for compiling and running the hello world script.
    Context::Scope context_scope(context);

    Handle<Object> v8_state = wrap_out_streams(isolate, &out);
    context->Global()->Set(String::NewFromUtf8(isolate, "console"), v8_state);

    // Create a string containing the JavaScript source code.
    Local<String> source = String::NewFromUtf8(isolate, raw_source);

    // Compile the source code.
    Local<Script> script = Script::Compile(source);

    // Run the script to get the result.
    Local<Value> result = script->Run();

    return SUCCESS;
}


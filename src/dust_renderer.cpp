/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#include "dust_renderer.h"

#include <string>
#include <sstream>
#include "v8.h"
#include "result_store.h"
#include "return_codes.h"

#include <iostream>

using namespace v8;

namespace
{
    int execute_js(out_streams & out, const char* raw_source)
    {
        std::cerr << raw_source << "\n";
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
}

int compile_template(out_streams & out, const char* full_dust, const char* tmpl, const char* template_name)
{
    std::stringstream full_js;

    full_js << full_dust <<                                             \
        "dust.debugLevel = 'DEBUG';"                                    \
        "console.store(dust.compile(\"" << tmpl << "\", '" << template_name << "'));";

    std::string final_js = full_js.str();
    return execute_js(out, final_js.c_str());
}

int render_compiled_template(out_streams & out, const char* core_dust, const char* compiled_template, const char* dust_context, const char* template_name)
{
    std::stringstream full_js;
    
    full_js << core_dust <<                              \
        "dust.loadSource(\"" << compiled_template << "\");"              \
        "dust.render('" << template_name << "', " << dust_context << ", function(err, out) {" \
        "    if (err) {"                                                \
        "        console.error(err);"                                   \
        "    }"                                                         \
        "    if (out) {"                                                \
        "        console.store(out);"                                   \
        "    }"                                                         \
        "});";
    
    std::string final_js = full_js.str();
    return execute_js(out, final_js.c_str());
}

int render_template(out_streams & out, const char* full_dust, const char* tmpl, const char* dust_context)
{
    std::stringstream full_js;

    full_js << full_dust <<                                             \
        "dust.debugLevel = 'DEBUG';"                                    \
        "var compiled = dust.compile(\"" << tmpl << ", 'compiledtmpl');" \
        "dust.loadSource(compiled);"                                    \
        "dust.render('compiledtmpl', " << dust_context << ", function(err, out) {" \
        "    if (err) {"                                                \
        "        console.error(err);"                                   \
        "    }"                                                         \
        "    if (out) {"                                                \
        "        console.store(out);"                                   \
        "    }"                                                         \
        "});";

    std::string final_js = full_js.str();
    return execute_js(out, final_js.c_str());
}


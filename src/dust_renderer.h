/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#pragma once
#include "out_streams.h"

/**
 * Take a dust template and generate the compiled javascript
 * code. Upon success a 0 will be returned and the compiled template
 * will be passed into the stdout stream.
 * 
 * @param out Interface to out/error/log streams
 * @param full_dust The javascript source to a full dust distribution. The full distribution is required for compilation
 * @param tmpl The text of the dust template to compile
 * @param template_name Name the template should have in the dust engine
 */
int compile_template(out_streams & out, const char* full_dust, const char* tmpl, const char* template_name = "compiledtmpl");

/**
 * Take a compiled javascript form of a dust template and render it
 * with the given dust context.
 * 
 * @param out Interface to out/error/log streams
 * @param core_dust The javascript source to a core dust distribution. The full distribution will also work here but only the core distribution is necessary for rendering
 * @param compiled_template A compiled copy of a dust template in javascript form
 * @param dust_context A JSON blob of the context data to use in rendering the template
 * @param template_name Name the template has in the dust engine
 */
int render_compiled_template(out_streams & out, const char* core_dust, const char* compiled_template, const char* dust_context, const char* template_name = "compiledtmpl");

/**
 * Take a raw uncompiled dust template and render it with the given
 * dust context.
 * 
 * @param out Interface to out/error/log streams
 * @param full_dust The javascript source to a full dust distribution. The full distribution is required for compilation
 * @param tmpl The text of the dust template to compile and render
 * @param dust_context A JSON blob of the context data to use in rendering the template
 */
int render_template(out_streams & out, const char* full_dust, const char* tmpl, const char* dust_context);

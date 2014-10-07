/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#pragma once

#include "out_streams.h"
#include <jni.h>

class JStore : public out_streams
{
  public:
    JStore(JNIEnv* _env, jobject _state);
    virtual ~JStore() { }
    virtual void store_result(const std::string & val);
    virtual void store_error(const std::string & val);
    virtual void store_log(const std::string & val);

  private:
    JNIEnv* env;
    jobject state;
    jclass state_class;
    jmethodID state_stdout;
    jmethodID state_stderr;
    jmethodID state_log;
};


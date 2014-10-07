/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#include "JStore.h"

JStore::JStore(JNIEnv* _env, jobject _state):
    env(_env),
    state(_state)
{
    state_class = env->GetObjectClass(state);
    state_stdout = env->GetMethodID(state_class, "out", "(Ljava/lang/String;)V");
    state_stderr = env->GetMethodID(state_class, "error", "(Ljava/lang/String;)V");
    state_log = env->GetMethodID(state_class, "log", "(Ljava/lang/String;)V");
}

void JStore::store_result(const std::string & val)
{
    jstring jval = env->NewStringUTF(val.c_str());
    env->CallVoidMethod(state, state_stdout, jval);
    env->DeleteLocalRef(jval);
}

void JStore::store_error(const std::string & val)
{
    jstring jval = env->NewStringUTF(val.c_str());
    env->CallVoidMethod(state, state_stderr, jval);
    env->DeleteLocalRef(jval);
}

void JStore::store_log(const std::string & val)
{
    jstring jval = env->NewStringUTF(val.c_str());
    env->CallVoidMethod(state, state_log, jval);
    env->DeleteLocalRef(jval);
}

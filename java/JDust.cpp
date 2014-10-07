/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#include "buzz_fizz_jdust_JDust.h"
#include "JStore.h"
#include "dust_renderer.h"

extern "C"
JNIEXPORT jint JNICALL
Java_buzz_fizz_jdust_JDust_executeJs(JNIEnv* env, jobject callingObject, jobject state, jstring js)
{
    const char *native_js = env->GetStringUTFChars(js, 0);

    JStore jstore(env, state);
    int ret = execute_js(jstore, native_js);

    env->ReleaseStringUTFChars(js, native_js);
    return ret;
}

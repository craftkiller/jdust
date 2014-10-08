/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
#include "buzz_fizz_jdust_JDust.h"
#include "JStore.h"
#include "dust_renderer.h"

extern "C"
JNIEXPORT jint JNICALL
Java_buzz_fizz_jdust_JDust_compileTemplate(JNIEnv* env, jobject callingObject, jobject state, jstring fullDust, jstring dustTemplate, jstring templateName)
{
    const char* cFullDust = env->GetStringUTFChars(fullDust, 0);
    const char* cDustTemplate = env->GetStringUTFChars(dustTemplate, 0);
    const char* cTemplateName = env->GetStringUTFChars(templateName, 0);


    JStore jstore(env, state);
    int ret = compile_template(jstore, cFullDust, cDustTemplate, cTemplateName);

    env->ReleaseStringUTFChars(fullDust, cFullDust);
    env->ReleaseStringUTFChars(dustTemplate, cDustTemplate);
    env->ReleaseStringUTFChars(templateName, cTemplateName);
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_buzz_fizz_jdust_JDust_renderCompiledTemplate(JNIEnv* env, jobject callingObject, jobject state, jstring coreDust, jstring compiledTemplate, jstring dustContext, jstring templateName)
{
    const char* cCoreDust = env->GetStringUTFChars(coreDust, 0);
    const char* cCompiledTemplate = env->GetStringUTFChars(compiledTemplate, 0);
    const char* cDustContext = env->GetStringUTFChars(dustContext, 0);
    const char* cTemplateName = env->GetStringUTFChars(templateName, 0);


    JStore jstore(env, state);
    int ret = render_compiled_template(jstore, cCoreDust, cCompiledTemplate, cDustContext, cTemplateName);

    env->ReleaseStringUTFChars(coreDust, cCoreDust);
    env->ReleaseStringUTFChars(compiledTemplate, cCompiledTemplate);
    env->ReleaseStringUTFChars(templateName, cTemplateName);
    env->ReleaseStringUTFChars(dustContext, cDustContext);
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_buzz_fizz_jdust_JDust_renderTemplate(JNIEnv* env, jobject callingObject, jobject state, jstring fullDust, jstring dustTemplate, jstring dustContext)
{
    const char* cFullDust = env->GetStringUTFChars(fullDust, 0);
    const char* cDustTemplate = env->GetStringUTFChars(dustTemplate, 0);
    const char* cDustContext = env->GetStringUTFChars(dustContext, 0);


    JStore jstore(env, state);
    int ret = render_template(jstore, cFullDust, cDustTemplate, cDustContext);

    env->ReleaseStringUTFChars(fullDust, cFullDust);
    env->ReleaseStringUTFChars(dustTemplate, cDustTemplate);
    env->ReleaseStringUTFChars(dustContext, cDustContext);
    return ret;
}

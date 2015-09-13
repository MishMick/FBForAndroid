/*
 * FBHelper_Android.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: Mickey
 */

/* STEPS:
 *  Files create for these use cases in Java ; save in package: com.fb.integrate.login etc.
 * 1) Create a new session
 * 2) Open a session
 * 3) Login process
 * 4) Fetch user details
 */
#include "FBHelper_Android.h"
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include "cocos2d.h"
#include <string>
#include <iostream>
using namespace std;
#define  LOG_TAG    "cocos2d-x debug info"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  CLASS_NAME_FBLOGIN "com/facebook/android/FBLogin"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
typedef struct JniMethodInfo_
{
    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
} JniMethodInfo;


extern "C" {

    // get env and cache it
    static JNIEnv* getJNIEnv(void)
    {

        JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
        if (NULL == jvm) {
            // -- LOGD("Failed to get JNIEnv. JniHelper::getJavaVM() is NULL");
            return NULL;
        }

        JNIEnv *env = NULL;
        // get jni environment
        jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);

        switch (ret) {
            case JNI_OK :
            // Success!
            return env;

            case JNI_EDETACHED :
            // Thread not attached

            // TODO : If calling AttachCurrentThread() on a native thread
            // must call DetachCurrentThread() in future.
            // see: http://developer.android.com/guide/practices/design/jni.html

         /*   if (jvm->AttachCurrentThread(&env, NULL) < 0)
            {
                // -- LOGD("Failed to get the environment using AttachCurrentThread()");
                return NULL;
            } else {
                // Success : Attached and obtained JNIEnv!
                return env;
            }
            */
            case JNI_EVERSION :
            // Cannot recover from this error
            // -- LOGD("JNI interface version 1.4 not supported");
            return NULL;
            default :
            // -- LOGD("Failed to get the environment using GetEnv()");
            return NULL;
        }
    }

    // get class and make it a global reference, release it at endJni().
    static jclass getClassID(JNIEnv *pEnv, const char *class_name)
    {
        jclass ret = pEnv->FindClass(class_name);
        if (! ret)
        {
            LOGD("Failed to find class of %s", class_name);
        }

        return ret;
    }

    static bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *methodName, const char *paramCode, const char *class_name)
    {
        jmethodID methodID = 0;
        JNIEnv *pEnv = 0;
        bool bRet = false;

        do
        {
            pEnv = getJNIEnv();
            if (! pEnv)
            {
                break;
            }

            jclass classID = getClassID(pEnv, class_name);

            methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
                LOGD("Failed to find static method id of %s", methodName);
                break;
            }

            methodinfo.classID = classID;
            methodinfo.env = pEnv;
            methodinfo.methodID = methodID;

            bRet = true;
        } while (0);

        return bRet;
    }

    void FBLogin()
    {
        LOGD("C++ Call FBLogin()");
        JniMethodInfo methodInfo;

      /*  if(!getStaticMethodInfo(methodInfo, "FBLogin", "(V)V", CLASS_NAME_FBLOGIN))
        {
            LOGD("C++ Failed Call FBLogin()");
            return;
        } */
        LOGD("C++ Found Call FBLogin()");
        jmethodID midCallBack = methodInfo.env->GetMethodID(methodInfo.env, method, "performFacebookLogin", "()V");
        if (NULL == midCallBack) return;

        // Call back the method (which returns void), based on the Method ID
        (*env)->CallVoidMethod(env, thisObj, midCallBack);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

}

#endif











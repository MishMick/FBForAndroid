//
//  JNIHelper.cpp
//  JavaCPPCall
//
//  Created by Mishal Hemant Shah on 4/2/15.
//
//

#include "JNIHelper.h"
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include "cocos2d.h"
#include <string>
#include <iostream>

using namespace std;

#define  LOG_TAG    "cocos2d-x debug info"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  CLASS_NAME_CJNIHELPER "com/test/first"
#define CLASS_NAME_JNICALL "com/test/second"
#define CLASS_NAME_FBCALL "com/FB/android/FBLogin"

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
    
    void CallMyJavaSideJNI(int num)
    {
        LOGD("C++ Call CallMyJavaSideJNI()");
        JniMethodInfo methodInfo;
        
        if(!getStaticMethodInfo(methodInfo, "CallMyJavaSideJNI", "(I)V", CLASS_NAME_CJNIHELPER))
        {
            LOGD("C++ Failed Call CallMyJavaSideJNI()");
            return;
        }
        LOGD("C++ Found Call CallMyJavaSideJNI()");
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, num );
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    void CallMyFBMethod(int num2)
    {
    	 LOGD("C++ Call CallMyFBMethod()");
    	 JniMethodInfo methodInfo;

    	 if(!getStaticMethodInfo(methodInfo, "CallMyJavaSideJNI", "(I)V", CLASS_NAME_CJNIHELPER))
    	        {
    	            LOGD("C++ Failed Call CallMyFBMethod()");
    	            return;
    	        }
    	        LOGD("C++ Found Call CallMyFBMETHOD()");
    	        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,num2);

    	 methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    const char* CallMyJavaMethod(const char* Str)
    {
    	LOGD("C++ call CallMyJavaMethod()");
    	JniMethodInfo methodInfo;
        const char *err = "Error";
    	        if(!getStaticMethodInfo(methodInfo, "CallMyJavaMethod", "(Ljava/lang/String;)Ljava/lang/String;", CLASS_NAME_JNICALL))
    	        {
    	            LOGD("C++ Failed Call CallMyJavaMethod()");
    	            return "wrong";
    	        }
    	        LOGD("C++ Found Call CallMyJavaMethod()");
    	        jobject obj;
                LOGD("Static method ID found!");
    	        jstring jstrBuf = methodInfo.env->NewStringUTF(Str);

                jmethodID mid = methodInfo.env->GetStaticMethodID(methodInfo.classID, "CallMyJavaMethod", "(Ljava/lang/String;)Ljava/lang/String;");

                jstring var  = (jstring) methodInfo.env->CallStaticObjectMethod(methodInfo.classID , methodInfo.methodID , jstrBuf);
                LOGD("Static method ID found!");

    	       // jstring var = methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID , jstrBuf);
                if (mid == 0)
                {
                  return err ;
                }
    	        const char *nativeString = methodInfo.env->GetStringUTFChars(var,NULL);
    	        if(nativeString!=NULL)
    	        {
    	        	LOGD("Not null");
    	        	__android_log_print(ANDROID_LOG_INFO, "sometag", "test char* = %s", nativeString);
    	        }
    	        methodInfo.env->DeleteLocalRef(methodInfo.classID);
                return nativeString;
    }
    
    void Java_org_cocos2dx_cpp_CJNIHelper_CallCPPLayer(JNIEnv *env, jobject obj) 
    {
        LOGD("Hello World!\n");
        return;
    }


}

#endif






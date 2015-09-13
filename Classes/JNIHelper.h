//
//  JNIHelper.h
//  JavaCPPCall
//
//  Created by Mishal Hemant Shah on 4/2/15.
//
//

#ifndef __JavaCPPCall__JNIHelper__
#define __JavaCPPCall__JNIHelper__


#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <jni.h>
#endif

extern "C"
{
    extern void CallMyJavaSideJNI(int num);
    extern const char* CallMyJavaMethod(const char*);
    extern void CallMyFBMethod(int);
    extern void Java_org_cocos2dx_cpp_CJNIHelper_CallCPPLayer(JNIEnv *env, jobject obj);

}



#endif /* defined(__JavaCPPCall__JNIHelper__) */

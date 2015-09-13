/*
 * FBHelper_Android.h
 *
 *  Created on: Apr 4, 2015
 *      Author: Mickey
 */

#ifndef FBHELPER_ANDROID_H_
#define FBHELPER_ANDROID_H_

/* STEPS:
 *  Files create for these use cases in Java ; save in package: com.fb.integrate.login etc.
 * 1) Create a new session
 * 2) Open a session
 * 3) Login process
 * 4) Fetch user details
 */
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <jni.h>
#endif
#include <stdio.h>

extern "C"
{
  extern void FBLogin();
}

#endif /* FBHELPER_ANDROID_H_ */

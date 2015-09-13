package com.test;
import java.lang.*;
import java.util.Arrays;
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.FB.android.FBLogin;
import com.facebook.android.DialogError;
import com.facebook.android.Facebook;
import com.facebook.android.FacebookError;
import com.facebook.android.Facebook.DialogListener;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

import org.cocos2dx.lib.Cocos2dxActivity;
//import org.cocos2dx.cpp.AppActivity;

public class first extends Activity 
{
	public static String APP_ID = "1063187567030782";
	private final static String TAG = "cocos2d-x debug info JAVA";
	private static first mParentInstance = null;
	public static String permissions_list = "email,basic_info";

	first()
    {
      mParentInstance = first.this; 
    }
	public static void CallMyJavaSideJNI(int num)
	{	     

		List<String> list = Arrays.asList(permissions_list.split(","));

		Log.d(TAG,"CallMyJavaSideJNI() called in Java with"+num);
		
	}
}

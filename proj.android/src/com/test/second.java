package com.test;
import android.util.Log;
public class second
{
    private final static String TAG = "cocos2d-x debug info JAVA";
    public static String CallMyJavaMethod(String strTarget)
	{
		Log.d(TAG,"CallMyJavaMethod() called in Java with"+strTarget);
		
		return strTarget;
	}
}
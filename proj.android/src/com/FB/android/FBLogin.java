package com.FB.android;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.location.Location;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import com.facebook.*;
import com.facebook.android.DialogError;
import com.facebook.android.Facebook;
import com.facebook.android.Facebook.DialogListener;
import com.facebook.android.FacebookError;
import com.facebook.model.GraphObject;
import com.facebook.model.GraphPlace;
import com.facebook.model.GraphUser;
import com.facebook.widget.*;

import java.io.IOException;
import java.net.MalformedURLException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;


public class FBLogin extends FragmentActivity 
{
	private static FBLogin mParentInstance = null;
	public String APP_ID = "1063187567030782";

     public  Facebook fb;
     public Activity b;
     FBLogin()
     {
       mParentInstance = FBLogin.this; 
     }

     Activity  instanceMethod1()
     {
    	 if(b.getParent()!=null)
    	 {
    		 Log.d("DEBUG_ACTIVITY_OBJECT","Not null");
    	 }
    	 else
    	 {
    		 Log.d("DEBUG_ACTIVITY_OBJECT","NULL");
    	 }
        return b.getParent();
     }
     Facebook instanceMethod2()
     {
  		fb = new Facebook(APP_ID);

    	 if(fb!=null)
    	 {
    		 Log.d("DEBUG_FB_OBJECT","Not null");
    	 }
    	 else
    	 {
    		 Log.d("DEBUG_FB_OBJECT","NULL");
    	 }

    	 return fb;
     }
     static Facebook staticMethod2()
     {
    	 return mParentInstance.instanceMethod2();
     }
     static Activity staticMethod1()
     {        
         return mParentInstance.instanceMethod1(); 
     }

	@SuppressWarnings({ "deprecation", "null" })
	public static void checkSession()
	{
		if(staticMethod2().isSessionValid())
		{
			Log.d("Facebook","Session opened");	
		}
		else
		{ 
			//login to facebook
			staticMethod2().authorize(staticMethod1(),new String[]{"email"},new  DialogListener() {
				@Override
				public void onFacebookError(FacebookError e)
				{
					//Toast.makeText(ac.getParent(), "fbError" , Toast.LENGTH_SHORT).show();

				}

				@Override
				public void onComplete(Bundle values)
				{
					// TODO Auto-generated method stub

				}

				@Override
				public void onError(DialogError e) 
				{
					// TODO Auto-generated method stub
					//Toast.makeText(FBLogin.this, "OnError" , Toast.LENGTH_SHORT).show();

				}

				@Override
				public void onCancel() 
				{
					// TODO Auto-generated method stub
					//Toast.makeText(FBLogin.this, "OnCancel" , Toast.LENGTH_SHORT).show();
				}
			});
			Log.d("Facebook","Session not running!");
		}
    }
}

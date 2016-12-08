package com.sjp.sjplab.sjplabandroidot;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.CollapsingToolbarLayout;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.FrameLayout;

public class FirstActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_first);

        ((CollapsingToolbarLayout) findViewById(R.id.collapsing_toolbar_layout)).setTitle("SJPLab Object Tracking");
        ((CollapsingToolbarLayout) findViewById(R.id.collapsing_toolbar_layout)).setExpandedTitleTextAppearance(R.style.ExpandedAppBar);
        ((CollapsingToolbarLayout) findViewById(R.id.collapsing_toolbar_layout)).setCollapsedTitleTextAppearance(R.style.CollapsedAppBar);

        FrameLayout flLogin = (FrameLayout) findViewById(R.id.frame_login);
        flLogin.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub

                Intent i = new Intent(FirstActivity.this, LoginActivity.class);
                startActivity(i);
            }
        });

        FrameLayout flTracking = (FrameLayout) findViewById(R.id.frame_tracking);
        flTracking.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub

                Intent i = new Intent(FirstActivity.this, MainActivity.class);
                startActivity(i);

            }
        });

//        ScrollView view = (ScrollView) findViewById(R.id.scroll_first_parent);
//
//        view.setOnTouchListener(new ListView.OnTouchListener() {
//            @Override
//            public boolean onTouch(View v, MotionEvent event) {
//                int action = event.getAction();
//                switch (action) {
//                    case MotionEvent.ACTION_DOWN:
//                        // Disallow ScrollView to intercept touch events.
//                        v.getParent().requestDisallowInterceptTouchEvent(true);
//                        break;
//
//                    case MotionEvent.ACTION_UP:
//                        // Allow ScrollView to intercept touch events.
//                        v.getParent().requestDisallowInterceptTouchEvent(false);
//                        break;
//                }
//
//                // Handle ListView touch events.
//                v.onTouchEvent(event);
//                return true;
//            }
//        });

    }
}

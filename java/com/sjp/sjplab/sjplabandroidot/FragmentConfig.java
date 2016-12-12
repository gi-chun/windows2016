package com.sjp.sjplab.sjplabandroidot;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.RadioGroup;

public class FragmentConfig extends Fragment implements RadioGroup.OnCheckedChangeListener {

    private static final int VIEW_MODE_RGBA = 0;
    private static final int VIEW_MODE_FEATURES = 5;
    private static final int VIEW_MODE_CMT = 8;
    private static final int START_TLD = 6;
    private static final int START_CMT = 7;

    private boolean tracking_ready = false;
    private int current_startViewMode = START_CMT;

    public FragmentConfig() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.fragment_config, container, false);

        RadioGroup rd = (RadioGroup) view.findViewById(R.id.radioGroup);
        rd.setOnCheckedChangeListener(this);

        final ImageButton button = (ImageButton) view.findViewById(R.id.imageButton2);
        button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                // do something
                if(tracking_ready){
                    tracking_ready = false;
                    ((MainActivity) getActivity()).setTracking_ready(tracking_ready);
                    ((MainActivity) getActivity()).setmSetViewMode(current_startViewMode);
                    button.setImageResource(R.drawable.tracking_normal);

                }else{
                    tracking_ready = true;
                    ((MainActivity) getActivity()).setTracking_ready(tracking_ready);
                    button.setImageResource(R.drawable.tracking_pressed);
                }

            }
        });
        return view;
    }

    public void onCheckedChanged(RadioGroup arg0, int arg1) {

        switch (arg1) {
            case R.id.radioNormal:
                ((MainActivity) getActivity()).setmSetViewMode(START_CMT);
                current_startViewMode = START_CMT;
                break;
            case R.id.radioOther:
                ((MainActivity) getActivity()).setmSetViewMode(START_TLD);
                current_startViewMode = START_TLD;
                break;

        }
    }
}
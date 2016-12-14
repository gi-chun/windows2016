package com.sjp.sjplab.sjplabandroidot;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.GestureDetector.OnGestureListener;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Toast;

import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.JavaCameraView;
import org.opencv.android.OpenCVLoader;
import org.opencv.android.Utils;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Rect;
import org.opencv.core.Scalar;
import org.opencv.imgproc.Imgproc;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;

public class MainActivity extends AppCompatActivity
        implements CameraBridgeViewBase.CvCameraViewListener2, OnGestureListener {

    private static final int SWIPE_MIN_DISTANCE = 120;
    private static final int SWIPE_MAX_OFF_PATH = 250;
    private static final int SWIPE_THRESHOLD_VELOCITY = 200;

    private static final String TAG = "OcvTest2";
    private static final int VIEW_MODE_RGBA = 0;
    private static final int VIEW_MODE_FEATURES = 5;
    private static final int VIEW_MODE_CMT = 8;
    private static final int START_TLD = 6;
    private static final int START_CMT = 7;

    static final int WIDTH = 400 ;//240;// 320;
    static final int HEIGHT =240;// 135;// ;//240;0;
    static final int TLD_WIDTH = 640 ;//240;// 320;
    static final int TLD_HEIGHT = 480;// 135;// ;//240;0;

    private JavaCameraView mJavaCameraView;
    private Mat mRgba;
    private Mat mGray;
    private Mat mRgba2;
    //private Mat mRoiRgba;

    private int mViewMode;
    private int mSetViewMode = START_CMT;
    private int _canvasImgYOffset;
    private int _canvasImgXOffset;
    private MenuItem mItemPreviewRGBA;
    private MenuItem mItemPreviewCMT;
    private MenuItem mItemPreviewFeatures;
    private Menu mainMenu;

    private Rect _trackedBox = null;
    SurfaceHolder _holder;
    static boolean uno = true;

    private Fragment fragment_control;
    private boolean tracking_ready = false;
    private boolean isViewControl = true;

    private static final long TIMEOUT = 1000L;
    private BlockingQueue<Mat> frames = new LinkedBlockingQueue<Mat>();
    private Thread worker;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");

        if (OpenCVLoader.initDebug()) {
            Log.d(TAG, "OpenCVLoader successfully loaded!");
        } else {
            Log.e(TAG, "Error: OpenCVLoader load failed!");
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        Bitmap myicon= BitmapFactory.decodeResource(getResources(),R.drawable.target_point_1); //target_point_small_1
//        mRoiRgba = new Mat();
//        Utils.bitmapToMat(myicon, mRoiRgba);

        mViewMode = VIEW_MODE_RGBA;

        mJavaCameraView = (JavaCameraView) findViewById(R.id.java_camera_view);
        if (mJavaCameraView != null) {
            mJavaCameraView.setVisibility(SurfaceView.VISIBLE);
            mJavaCameraView.setCvCameraViewListener(this);
            //mJavaCameraView.disableFpsMeter();
        } else {
            Log.e(TAG, "onCreate: mJavaCameraView is null!");
        }

        ///////////////////////////////////////////////////
        final AtomicReference<Point> trackedBox1stCorner = new AtomicReference<Point>();
        final Paint rectPaint = new Paint();
        rectPaint.setColor(Color.rgb(0, 255, 0));
        rectPaint.setStrokeWidth(5);
        rectPaint.setStyle(Paint.Style.STROKE);
        _holder = mJavaCameraView.getHolder();

        mJavaCameraView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                // re-init

//                if (mainMenu !=null) {
//                    this.openOptionsMenu(); // activity's onCreateOptionsMenu gets called
//                    optionsMenu.performIdentifierAction(R.id.miSubMenu1, 0);
//
//                    mainMenu.performIdentifierAction(R.id.menu_overflow, 0);
//                }

                //showPopup(getWindow().getDecorView().getRootView());

                if (event.getPointerCount() > 1){
//                    if (mainMenu !=null) {
//                        mainMenu.performIdentifierAction(R.id.menu_overflow, 0);
//                    }

                }else{
                    final Point corner = new Point(event.getX() - _canvasImgXOffset, event.getY() - _canvasImgYOffset);
                    switch (event.getAction()) {
                        case MotionEvent.ACTION_DOWN:
                            trackedBox1stCorner.set(corner);
                            Log.i("TAG", "1st corner: " + corner);
                            break;
                        case MotionEvent.ACTION_UP:
                            _trackedBox = new Rect(trackedBox1stCorner.get(), corner);

                            // view control pannel
                            if(tracking_ready == false){

//                                getWindow().setFlags(WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE, WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE);
//
//                                FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
//
//                                if(!isViewControl){
//                                    ft.setCustomAnimations(R.anim.enter_from_left, R.anim.exit_to_right);
//                                    isViewControl = true;
//                                    ft.show(fragment_control);
//                                    ft.commit();
//                                }else{
//                                    ft.setCustomAnimations(R.anim.enter_from_right, R.anim.exit_to_left);
//                                    isViewControl = false;
//                                    ft.hide(fragment_control);
//                                    ft.commit();
//                                }
//
//                                getWindow().clearFlags(WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE);

                                return true;
                            }else{
                                if (_trackedBox.area() > 100) {
                                    Log.i("TAG", "Tracked box DEFINED: " + _trackedBox);
//                                    if (mViewMode == VIEW_MODE_FEATURES) {
//                                        mViewMode = START_CMT;
//                                        //_trackedBox = null;
//                                        uno = true;
//                                    }else {
//                                        mViewMode = START_TLD;
//                                        //_trackedBox = null;
//                                        uno = true;
//                                    }
                                    mViewMode = mSetViewMode;
                                } else
                                    _trackedBox = null;
                            }

                            break;
                        case MotionEvent.ACTION_MOVE:
                            if(tracking_ready) {
                                final android.graphics.Rect rect = new android.graphics.Rect(
                                        (int) trackedBox1stCorner.get().x
                                                + _canvasImgXOffset,
                                        (int) trackedBox1stCorner.get().y
                                                + _canvasImgYOffset, (int) corner.x
                                        + _canvasImgXOffset, (int) corner.y
                                        + _canvasImgYOffset);
                                final Canvas canvas = _holder.lockCanvas(rect);
                                canvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR); // remove
                                // old
                                // rectangle
                                canvas.drawRect(rect, rectPaint);
                                _holder.unlockCanvasAndPost(canvas);
                            }

                            break;
                    }
                }

                return true;
            }
        });

        //////////////////////////////////////////////////////////////////////
        fragment_control = new FragmentConfig();
        FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
        ft.add(R.id.overlay_fragment_container, fragment_control);
        ft.commit();
        //////////////////////////////////////////////////////////////////////

        worker = new Thread() {
            @Override
            public void run() {
                while (true) { //running

                    Mat inputFrame = null;

                    try {
                        inputFrame = frames.poll(TIMEOUT, TimeUnit.MILLISECONDS);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                    if (inputFrame == null) {
                        // timeout. Also, with a try {} catch block poll can be interrupted via Thread.interrupt() so not to wait for the timeout.
                        continue;
                    }

//                    cropToCenter(inputFrame);
//                    String result = doImgProcessing(inputFrame);
                }
            }
        };

//        ImageButton button = (ImageButton) fragment_control.getView().findViewById(R.id.imageButton2);
//        button.setOnClickListener(new View.OnClickListener()
//        {
//            @Override
//            public void onClick(View v) {
//                Context context = getApplicationContext();
//                CharSequence text = "Hello toast!";
//                int duration = Toast.LENGTH_SHORT;
//
//                Toast toast = Toast.makeText(context, text, duration);
//                toast.show();
//            }
//
//        });


    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        Log.i(TAG, "called onCreateOptionsMenu");
//        mItemPreviewRGBA = menu.add("RGBA");
//        mItemPreviewFeatures = menu.add("TLD");
//        mItemPreviewCMT = menu.add("CMT");

//        MenuInflater inflater = getMenuInflater();
//        inflater.inflate(R.menu.menu, menu);
//        mainMenu = menu;
//        return true;

        return true;

    }

    public boolean onOptionsItemSelected(MenuItem item) {
        Log.i(TAG, "called onOptionsItemSelected; selected item: " + item);

        if (item == mItemPreviewRGBA) {
            mViewMode = VIEW_MODE_RGBA;
        } else if (item == mItemPreviewFeatures) {
            mViewMode = START_TLD;
            _trackedBox = null;
            uno = true;
        } else if (item == mItemPreviewCMT) {
            mViewMode = START_CMT;
            _trackedBox = null;
            uno = true;
        }

        return true;
    }

//    public void showPopup(View v) {
//        PopupMenu popup = new PopupMenu(this, v);
//        MenuInflater inflater = popup.getMenuInflater();
//        inflater.inflate(R.menu.menu, popup.getMenu());
//        popup.show();
//    }

    @Override
    public void onCameraViewStarted(int width, int height) {
        Log.d(TAG, "onCameraViewStarted: width = " + width + ", height = " + height);
        mRgba = new Mat();
    }

    @Override
    public void onCameraViewStopped() {
        Log.d(TAG, "onCameraViewStopped:");
        mRgba.release();
    }

    @Override
    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {
//        mRgba = inputFrame.rgba();
//        nativeDetectAndDisplay(mRgba.getNativeObjAddr());
//        return mRgba;

        final int viewMode = mViewMode;

        switch (viewMode) {
            case VIEW_MODE_RGBA:
                // input frame has RBGA format
                mRgba = inputFrame.rgba();
                break;
            case START_TLD: {
                mRgba = inputFrame.rgba();
                mGray = TLD_Reduce(inputFrame.gray());
                double w = mGray.width();
                double h = mGray.height();
                if (_trackedBox == null)
                    OpenTLD(mGray.getNativeObjAddr(), mRgba.getNativeObjAddr(),
                            (long) (w / 2 - 10), (long) (h / 2 - 10),
                            (long) 10, (long) 10);
                else {

                    Log.i("TAG", "START DEFINED: " + _trackedBox.x / 2 + " "
                            + _trackedBox.y / 2 + " " + _trackedBox.width / 2 + " "
                            + _trackedBox.height / 2);

                    double px = (w) / (double) (mJavaCameraView.getWidth());
                    double py = (h) / (double) (mJavaCameraView.getHeight());
                    //
                    long tx, ty, twidth, theight = 0;
                    tx =  (long) (_trackedBox.x * px);
                    ty =  (long) (_trackedBox.y * py);
                    twidth = (long) (_trackedBox.width * px);
                    theight = (long) (_trackedBox.height * py);

//                    if(tx >= twidth || ty >= theight){
//                        tx =  (long) (w / 2 - 10);
//                        ty =  (long) (h / 2 - 10);
//                        twidth = (long) (10);
//                        theight = (long) (10);
//                    }

                    OpenTLD(mGray.getNativeObjAddr(), mRgba.getNativeObjAddr(),
                            tx,
                            ty,
                            twidth,
                            theight);
                }
                uno = false;
                mViewMode = VIEW_MODE_FEATURES;
            }
            break;
            case START_CMT: {
                mRgba = inputFrame.rgba();
                mGray = Reduce(inputFrame.gray());

//                try {
//                    frames.put(mGray);
//                } catch (InterruptedException e) {
//                    e.printStackTrace();
//                }

                double w = mGray.width();
                double h = mGray.height();
                if (_trackedBox == null)
                    // OpenTLD(mGray.getNativeObjAddr(),
                    // mRgba.getNativeObjAddr(),(long)(w/2-w/4),(long)(
                    // h/2-h/4),(long)w/2,(long)h/2);
                    OpenCMT(mGray.getNativeObjAddr(), mRgba.getNativeObjAddr(),
                            (long) (w / 2 - 10), (long) (h / 2 - 10),
                            (long) 10, (long) 10);
                else {

                    Log.i("TAG", "START DEFINED: " + _trackedBox.x / 2 + " "
                            + _trackedBox.y / 2 + " " + _trackedBox.width / 2 + " "
                            + _trackedBox.height / 2);

                    double px = (w) / (double) (mJavaCameraView.getWidth());
                    double py = (h) / (double) (mJavaCameraView.getHeight());
                    //
                    OpenCMT(mGray.getNativeObjAddr(), mRgba.getNativeObjAddr(),
                            (long) (_trackedBox.x * px),
                            (long) (_trackedBox.y * py),
                            (long) (_trackedBox.width * px),
                            (long) (_trackedBox.height * py));
                }
                uno = false;
                mViewMode = VIEW_MODE_CMT;
            }
            break;

            case VIEW_MODE_FEATURES:
                // input frame has RGBA format
                mRgba = inputFrame.rgba();
                mGray = inputFrame.gray();
                mGray = TLD_Reduce(mGray);
                mRgba2 = TLD_ReduceColor(mRgba);

                // FindFeatures(mGray.getNativeObjAddr(), mRgba.getNativeObjAddr());
                if (uno) {
                    int w = mGray.width();
                    int h = mGray.height();
                    OpenTLD(mGray.getNativeObjAddr(), mRgba2.getNativeObjAddr(),
                            (long) w - w / 4, (long) h / 2 - h / 4, (long) w / 2,
                            (long) h / 2);
                    uno = false;
                } else {

                    ProcessTLD(mGray.getNativeObjAddr(), mRgba2.getNativeObjAddr());
                    double px = (double) mRgba.width() / (double) mRgba2.width();
                    double py = (double) mRgba.height() / (double) mRgba2.height();
                    int[] l = getRect();
                    if (l != null) {
                        Rect r = new Rect();
                        r.x = (int) (l[0] * px);
                        r.y = (int) (l[1] * py);
                        r.width = (int) (l[2] * px);
                        r.height = (int) (l[3] * py);

                        Imgproc.rectangle(mRgba, r.tl(), r.br(), new Scalar(0, 0, 255, 0), 5);
                    }
                    uno = false;

                    // Mat mTemp=mRgba;

                    // mRgba=UnReduceColor(mRgba2,mTemp.width(),mTemp.height());
                    // mTemp.release();

                }

                // mRgba2.release();
                // mGray.release();
                break;

            case VIEW_MODE_CMT:
                // input frame has RGBA format
            {
                mRgba = inputFrame.rgba();
                mGray = inputFrame.gray();
                mGray = Reduce(mGray);
                mRgba2 = ReduceColor(mRgba);

                try {
                    frames.put(mGray);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                worker.start();

                // FindFeatures(mGray.getNativeObjAddr(), mRgba.getNativeObjAddr());
                if (uno) {
                    int w = mGray.width();
                    int h = mGray.height();
                    OpenCMT(mGray.getNativeObjAddr(), mRgba2.getNativeObjAddr(),
                            (long) w - w / 4, (long) h / 2 - h / 4, (long) w / 2,
                            (long) h / 2);
                    uno = false;
                } else {

//                    AsyncTask.execute(new Runnable(){
//                        public void run() {
//                            Mat grayTemp = new Mat(mGray.height(), mGray.width(), mGray.type());
//                            mGray.copyTo(grayTemp);
//                            ProcessCMT(grayTemp.getNativeObjAddr(), grayTemp.getNativeObjAddr());
//                        }
//                    });

                    ProcessCMT(mGray.getNativeObjAddr(), mRgba.getNativeObjAddr());

//                    double px = (double) mRgba.width() / (double) mRgba2.width();
//                    double py = (double) mRgba.height() / (double) mRgba2.height();

//                    int[] l = CMTgetRect();
//                    if (l != null) {
//                        Point topLeft = new Point(l[0] * px, l[1] * py);
//                        Point topRight = new Point(l[2] * px, l[3] * py);
//                        Point bottomLeft = new Point(l[4] * px, l[5] * py);
//                        Point bottomRight = new Point(l[6] * px, l[7] * py);
//
////                        Imgproc.line(mRgba, topLeft, topRight, new Scalar(255, 255,
////                                255), 3);
////                        Imgproc.line(mRgba, topRight, bottomRight, new Scalar(255,
////                                255, 255), 3);
////                        Imgproc.line(mRgba, bottomRight, bottomLeft, new Scalar(255,
////                                255, 255), 3);
////                        Imgproc.line(mRgba, bottomLeft, topLeft, new Scalar(255, 255,
////                                255), 3);
//                    }
                    uno = false;

                    // Mat mTemp=mRgba;

                    // mRgba=UnReduceColor(mRgba2,mTemp.width(),mTemp.height());
                    // mTemp.release();

                }
            }
            // mRgba2.release();
            // mGray.release();
            break;

        }

        return mRgba;

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        if (mJavaCameraView != null)
            mJavaCameraView.disableView();
    }

    @Override
    protected void onPause() {
        super.onPause();

        if (mJavaCameraView != null)
            mJavaCameraView.disableView();
    }

    @Override
    protected void onResume() {
        super.onResume();

        mJavaCameraView.enableView();
    }

    Mat Reduce(Mat m) {
        // return m;
        Mat dst = new Mat();
        Imgproc.resize(m, dst, new org.opencv.core.Size(WIDTH, HEIGHT));
        return dst;
    }

    Mat TLD_Reduce(Mat m) {
        // return m;
        Mat dst = new Mat();
        Imgproc.resize(m, dst, new org.opencv.core.Size(TLD_WIDTH, TLD_HEIGHT));
        return dst;
    }

    Mat ReduceColor(Mat m) {
        Mat dst = new Mat();
        Bitmap bmp = Bitmap.createBitmap(m.width(), m.height(),
                Bitmap.Config.ARGB_8888);
        Utils.matToBitmap(m, bmp);
        Bitmap bmp2 = Bitmap.createScaledBitmap(bmp, WIDTH, HEIGHT, false);

        Utils.bitmapToMat(bmp2, dst);
        // Imgproc.resize(m, dst, new Size(WIDTH,HEIGHT), 0, 0,
        // Imgproc.INTER_CUBIC);
        return dst;
    }

    Mat TLD_ReduceColor(Mat m) {
        Mat dst = new Mat();
        Bitmap bmp = Bitmap.createBitmap(m.width(), m.height(),
                Bitmap.Config.ARGB_8888);
        Utils.matToBitmap(m, bmp);
        Bitmap bmp2 = Bitmap.createScaledBitmap(bmp, TLD_WIDTH, TLD_HEIGHT, false);

        Utils.bitmapToMat(bmp2, dst);
        // Imgproc.resize(m, dst, new Size(WIDTH,HEIGHT), 0, 0,
        // Imgproc.INTER_CUBIC);
        return dst;
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native void nativeDetectAndDisplay(long addrMat);

    public native void OpenTLD(long matAddrGr, long matAddrRgba, long x, long y, long w, long h);
    public native void ProcessTLD(long matAddrGr, long matAddrRgba);
    public native void OpenCMT(long matAddrGr, long matAddrRgba, long x, long y, long w, long h);
    public native void ProcessCMT(long matAddrGr, long matAddrRgba);
    private static native int[] getRect();
    private static native int[] CMTgetRect();

    @Override
    public boolean onDown(MotionEvent motionEvent) {
        return false;
    }

    @Override
    public void onShowPress(MotionEvent motionEvent) {

    }

    @Override
    public boolean onScroll(MotionEvent motionEvent, MotionEvent motionEvent1, float v, float v1) {
        return false;
    }

    @Override
    public void onLongPress(MotionEvent motionEvent) {

    }

    @Override
    public boolean onFling(MotionEvent motionEvent, MotionEvent motionEvent1, float v, float v1) {
        try {
                if (Math.abs(motionEvent.getY() - motionEvent1.getY()) > SWIPE_MAX_OFF_PATH)
                    return false;

                // right to left swipe
                if (motionEvent.getX() - motionEvent1.getX() > SWIPE_MIN_DISTANCE && Math.abs(v) > SWIPE_THRESHOLD_VELOCITY) {
                    Toast.makeText(getApplicationContext(), "Left Swipe", Toast.LENGTH_SHORT).show();
                }
                // left to right swipe
                else if (motionEvent1.getX() - motionEvent.getX() > SWIPE_MIN_DISTANCE && Math.abs(v) > SWIPE_THRESHOLD_VELOCITY) {
                    Toast.makeText(getApplicationContext(), "Right Swipe", Toast.LENGTH_SHORT).show();
                }
                // down to up swipe
                else if (motionEvent.getY() - motionEvent1.getY() > SWIPE_MIN_DISTANCE && Math.abs(v) > SWIPE_THRESHOLD_VELOCITY) {
                    Toast.makeText(getApplicationContext(), "Swipe up", Toast.LENGTH_SHORT).show();
                }
                // up to down swipe
                else if (motionEvent1.getY() - motionEvent.getY() > SWIPE_MIN_DISTANCE && Math.abs(v) > SWIPE_THRESHOLD_VELOCITY) {
                    Toast.makeText(getApplicationContext(), "Swipe down", Toast.LENGTH_SHORT).show();
                }
            } catch (Exception e) {

            }
        return true;
    }

    public boolean onSingleTapUp(MotionEvent e) {
        Toast mToast = Toast.makeText(getApplicationContext(), "Single Tap", Toast.LENGTH_SHORT);
        mToast.show();
        return true;
    }

    // public function
    public void setTracking_ready(boolean bFlag){
        tracking_ready = bFlag;
    }

    public void setmSetViewMode(int pViewMode){
        mSetViewMode = pViewMode;
        mViewMode = VIEW_MODE_RGBA;
    }

}


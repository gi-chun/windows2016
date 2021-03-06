package com.sjp.sjplab.ocvtest2;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.JavaCameraView;
import org.opencv.android.OpenCVLoader;
import org.opencv.android.Utils;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Rect;
import org.opencv.core.Scalar;
import org.opencv.imgproc.Imgproc;

import java.util.concurrent.atomic.AtomicReference;

public class MainActivity extends AppCompatActivity
        implements CameraBridgeViewBase.CvCameraViewListener2 {

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

    private int mViewMode;
    private int _canvasImgYOffset;
    private int _canvasImgXOffset;
    private MenuItem mItemPreviewRGBA;
    private MenuItem mItemPreviewCMT;
    private MenuItem mItemPreviewFeatures;
    private Menu mainMenu;

    private Rect _trackedBox = null;
    SurfaceHolder _holder;
    static boolean uno = true;

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

        mViewMode = VIEW_MODE_RGBA;

        mJavaCameraView = (JavaCameraView) findViewById(R.id.java_camera_view);
        if (mJavaCameraView != null) {
            mJavaCameraView.setVisibility(SurfaceView.VISIBLE);
            mJavaCameraView.setCvCameraViewListener(this);
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
                            if (_trackedBox.area() > 100) {
                                Log.i("TAG", "Tracked box DEFINED: " + _trackedBox);
//                                if (mViewMode == VIEW_MODE_FEATURES)
//                                    mViewMode = START_TLD;
//                                else
//                                    mViewMode = START_CMT;
                                if (mViewMode == VIEW_MODE_FEATURES) {
                                    mViewMode = START_CMT;
                                    //_trackedBox = null;
                                    uno = true;
                                }
                                else {
                                    mViewMode = START_TLD;
                                   // _trackedBox = null;
                                    uno = true;
                                }

                            } else
                                _trackedBox = null;
                            break;
                        case MotionEvent.ACTION_MOVE:
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

                            break;
                    }
                }

                return true;
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        Log.i(TAG, "called onCreateOptionsMenu");
        mItemPreviewRGBA = menu.add("RGBA");
        mItemPreviewFeatures = menu.add("TLD");
        mItemPreviewCMT = menu.add("CMT");

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
                    OpenTLD(mGray.getNativeObjAddr(), mRgba.getNativeObjAddr(),
                            (long) (_trackedBox.x * px),
                            (long) (_trackedBox.y * py),
                            (long) (_trackedBox.width * px),
                            (long) (_trackedBox.height * py));
                }
                uno = false;
                mViewMode = VIEW_MODE_FEATURES;
            }
            break;
            case START_CMT: {
                mRgba = inputFrame.rgba();
                mGray = Reduce(inputFrame.gray());
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

                // FindFeatures(mGray.getNativeObjAddr(), mRgba.getNativeObjAddr());
                if (uno) {
                    int w = mGray.width();
                    int h = mGray.height();
                    OpenCMT(mGray.getNativeObjAddr(), mRgba2.getNativeObjAddr(),
                            (long) w - w / 4, (long) h / 2 - h / 4, (long) w / 2,
                            (long) h / 2);
                    uno = false;
                } else {

                    ProcessCMT(mGray.getNativeObjAddr(), mRgba2.getNativeObjAddr());
                    double px = (double) mRgba.width() / (double) mRgba2.width();
                    double py = (double) mRgba.height() / (double) mRgba2.height();

                    int[] l = CMTgetRect();
                    if (l != null) {
                        Point topLeft = new Point(l[0] * px, l[1] * py);
                        Point topRight = new Point(l[2] * px, l[3] * py);
                        Point bottomLeft = new Point(l[4] * px, l[5] * py);
                        Point bottomRight = new Point(l[6] * px, l[7] * py);

                        Imgproc.line(mRgba, topLeft, topRight, new Scalar(255, 255,
                                255), 3);
                        Imgproc.line(mRgba, topRight, bottomRight, new Scalar(255,
                                255, 255), 3);
                        Imgproc.line(mRgba, bottomRight, bottomLeft, new Scalar(255,
                                255, 255), 3);
                        Imgproc.line(mRgba, bottomLeft, topLeft, new Scalar(255, 255,
                                255), 3);

                    }
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
}

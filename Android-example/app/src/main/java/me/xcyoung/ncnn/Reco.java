package me.xcyoung.ncnn;

import android.graphics.Bitmap;

public class Reco {
    Reco() {
        System.loadLibrary("example");
    }

    void init(String paramPath, String binPath) {
        nativeInit(paramPath, binPath);
    }

    int reco(Bitmap bitmap) {
        return nativeInterface(bitmap);
    }

    native void nativeInit(String paramPath, String binPath);
    native int nativeInterface(Bitmap bitmap);
}

package com.aliucord.libzip;

@SuppressWarnings("unused")
public class Zip {
    static {
        System.loadLibrary("zip");
    }

    private static native long open(String path, int compression, char mode);

    @SuppressWarnings("FieldCanBeLocal")
    private final long ptr;
    public Zip(String path, int compression, char mode) {
        ptr = open(path, compression, mode);
    }

    public native void close();

    public native boolean openEntry(String entry);

    public native boolean openEntryByIndex(int i);

    public native boolean closeEntry();

    public native String getEntryName();

    public native int getEntryIndex();

    public native boolean isEntryDir();

    public native long getEntrySize();

    public native int getEntryCRC32();

    public native boolean writeEntry(byte[] buf, long bufSize);

    public native boolean compressFile(String path);

    public native byte[] readEntry();

    public native boolean extractEntry(String path);

    public native int getTotalEntries();

    public native boolean deleteEntry(String entry);
}

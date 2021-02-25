#include <jni.h>
#include <string>
#include "zip/src/zip.c"

zip_t* getZip(JNIEnv* env, jobject thisObj) {
    jclass cls = env->GetObjectClass(thisObj);
    jfieldID ptrid = env->GetFieldID(cls, "ptr", "J");
    return (zip_t*) env->GetLongField(thisObj, ptrid);
}

unsigned char* toNativeByteArray(JNIEnv* env, jbyteArray array) {
    int len = env->GetArrayLength (array);
    auto* buf = new unsigned char[len];
    env->GetByteArrayRegion (array, 0, len, reinterpret_cast<jbyte*>(buf));
    return buf;
}

extern "C" {

jlong Java_com_aliucord_libzip_Zip_open(JNIEnv* env, jclass, jstring path, jint compression, jchar mode) {
    const char* nativePath = env->GetStringUTFChars(path, nullptr);
    auto ptr = (jlong) zip_open(nativePath, compression, mode);
    env->ReleaseStringUTFChars(path, nativePath);
    return ptr;
}

void Java_com_aliucord_libzip_Zip_close(JNIEnv* env, jobject thisObj) {
    zip_close(getZip(env, thisObj));
}

jboolean Java_com_aliucord_libzip_Zip_openEntry(JNIEnv* env, jobject thisObj, jstring entry) {
    const char* nativeEntry = env->GetStringUTFChars(entry, nullptr);
    int status = zip_entry_open(getZip(env, thisObj), nativeEntry);
    env->ReleaseStringUTFChars(entry, nativeEntry);
    return status == 0 ? JNI_TRUE : JNI_FALSE;
}

jboolean Java_com_aliucord_libzip_Zip_openEntryByIndex(JNIEnv* env, jobject thisObj, jint i) {
    int status = zip_entry_openbyindex(getZip(env, thisObj), i);
    return status == 0 ? JNI_TRUE : JNI_FALSE;
}

jboolean Java_com_aliucord_libzip_Zip_closeEntry(JNIEnv* env, jobject thisObj) {
    int status = zip_entry_close(getZip(env, thisObj));
    return status == 0 ? JNI_TRUE : JNI_FALSE;
}

jstring Java_com_aliucord_libzip_Zip_getEntryName(JNIEnv* env, jobject thisObj) {
    return env->NewStringUTF(zip_entry_name(getZip(env, thisObj)));
}

jint Java_com_aliucord_libzip_Zip_getEntryIndex(JNIEnv* env, jobject thisObj) {
    return zip_entry_index(getZip(env, thisObj));
}

jboolean Java_com_aliucord_libzip_Zip_isEntryDir(JNIEnv* env, jobject thisObj) {
    return zip_entry_isdir(getZip(env, thisObj));
}

jlong Java_com_aliucord_libzip_Zip_getEntrySize(JNIEnv* env, jobject thisObj) {
    return zip_entry_size(getZip(env, thisObj));
}

jint Java_com_aliucord_libzip_Zip_getEntryCRC32(JNIEnv* env, jobject thisObj) {
    return zip_entry_crc32(getZip(env, thisObj));
}

jboolean Java_com_aliucord_libzip_Zip_writeEntry(JNIEnv* env, jobject thisObj, jbyteArray buf, jlong bufSize) {
    int status = zip_entry_write(getZip(env, thisObj), toNativeByteArray(env, buf), bufSize);
    return status == 0 ? JNI_TRUE : JNI_FALSE;
}

jboolean Java_com_aliucord_libzip_Zip_compressFile(JNIEnv* env, jobject thisObj, jstring path) {
    const char* nativePath = env->GetStringUTFChars(path, nullptr);
    int status = zip_entry_fwrite(getZip(env, thisObj), nativePath);
    env->ReleaseStringUTFChars(path, nativePath);
    return status == 0 ? JNI_TRUE : JNI_FALSE;
}

jbyteArray Java_com_aliucord_libzip_Zip_readEntry(JNIEnv* env, jobject thisObj) {
    jbyte* buf;
    int len = zip_entry_read(getZip(env, thisObj), (void**) &buf, nullptr);
    jbyteArray bytes = env->NewByteArray(len);
    env->SetByteArrayRegion(bytes, 0, len, buf);
    return bytes;
}

jboolean Java_com_aliucord_libzip_Zip_extractEntry(JNIEnv* env, jobject thisObj, jstring path) {
    const char* nativePath = env->GetStringUTFChars(path, nullptr);
    int status = zip_entry_fread(getZip(env, thisObj), nativePath);
    env->ReleaseStringUTFChars(path, nativePath);
    return status == 0 ? JNI_TRUE : JNI_FALSE;
}

jint Java_com_aliucord_libzip_Zip_getTotalEntries(JNIEnv* env, jobject thisObj) {
    return zip_total_entries(getZip(env, thisObj));
}

jboolean Java_com_aliucord_libzip_Zip_deleteEntry(JNIEnv* env, jobject thisObj, jstring entry) {
    char* nativeEntry[] = { (char *) env->GetStringUTFChars(entry, nullptr) };
    int status = zip_entries_delete(getZip(env, thisObj), nativeEntry, 1);
    env->ReleaseStringUTFChars(entry, nativeEntry[0]);
    return status == 1 ? JNI_TRUE : JNI_FALSE;
}

}

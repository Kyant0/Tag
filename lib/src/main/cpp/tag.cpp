#include <jni.h>
#include "fileref.h"
#include "tfilestream.h"
#include "tpropertymap.h"
#include "fd.h"
#include "picture.h"
#include "lyrics.h"
#include "save_lyrics.h"

jmethodID metadataConstructor = nullptr;

// Helper function to convert C++ StringList to JNI String array
jobjectArray StringListToJniStringArray(JNIEnv *env, const TagLib::StringList &stringList) {
    jclass stringCls = env->FindClass("java/lang/String");
    jobjectArray array = env->NewObjectArray(stringList.size(), stringCls, nullptr);
    int i = 0;
    for (const auto &str: stringList) {
        env->SetObjectArrayElement(array, i, env->NewStringUTF(str.toCString(true)));
        i++;
    }
    return array;
}

// Helper function to convert C++ PropertyMap to JNI HashMap
jobject PropertyMapToJniHashMap(JNIEnv *env, const TagLib::PropertyMap &propertyMap) {
    jclass hashMapClass = env->FindClass("java/util/HashMap");
    jmethodID hashMapInit = env->GetMethodID(hashMapClass, "<init>", "(I)V");
    jmethodID hashMapPut = env->GetMethodID(hashMapClass, "put",
                                            "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    jobject hashMap = env->NewObject(hashMapClass, hashMapInit, static_cast<jint>(propertyMap.size()));

    for (const auto &it: propertyMap) {
        const std::string key = it.first.toCString(true);
        const TagLib::StringList &valueList = it.second;

        jobjectArray valueArray = StringListToJniStringArray(env, valueList);

        jstring jKey = env->NewStringUTF(key.c_str());
        env->CallObjectMethod(hashMap, hashMapPut, jKey, valueArray);

        env->DeleteLocalRef(jKey);
        env->DeleteLocalRef(valueArray);
    }

    return hashMap;
}

jobject getMetadata(JNIEnv *env, const TagLib::FileRef &fileRef) {
    if (fileRef.isNull()) {
        return nullptr;
    }

    jclass metadataClass = env->FindClass("com/kyant/tag/Metadata");

    if (metadataConstructor == nullptr) {
        metadataConstructor = env->GetMethodID(
                metadataClass,
                "<init>",
                "(JIIILjava/util/Map;)V"
        );
    }

    TagLib::AudioProperties *audioProperties = fileRef.audioProperties();
    jlong lengthInMilliseconds = static_cast<jint>(audioProperties->lengthInMilliseconds());
    jint bitrate = static_cast<jint>(audioProperties->bitrate());
    jint sampleRate = static_cast<jint>(audioProperties->sampleRate());
    jint channels = static_cast<jint>(audioProperties->channels());

    TagLib::PropertyMap properties = fileRef.tag()->properties();

    return env->NewObject(
            metadataClass, metadataConstructor, lengthInMilliseconds, bitrate, sampleRate, channels,
            PropertyMapToJniHashMap(env, properties)
    );
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_kyant_tag_Metadata_00024Companion_getMetadata(JNIEnv *env, jobject /* this */, jstring path) {
    const char *file_path = env->GetStringUTFChars(path, nullptr);
    TagLib::FileRef fileRef(file_path, true, TagLib::AudioProperties::Fast);
    env->ReleaseStringUTFChars(path, file_path);
    return getMetadata(env, fileRef);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_kyant_tag_Metadata_00024Companion_getFdMetadata(JNIEnv *env, jobject /* this */, jint fd) {
    UniqueFileDescriptor uniqueFd(dup(fd));
    TagLib::FileStream stream(uniqueFd.get(), true);
    TagLib::FileRef fileRef(&stream, true, TagLib::AudioProperties::Fast);
    return getMetadata(env, fileRef);
}

extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_kyant_tag_Metadata_00024Companion_getPicture(JNIEnv *env,
                                                      jobject /* this */,
                                                      jstring path) {
    auto picture = get_picture(env->GetStringUTFChars(path, nullptr));
    if (picture.isEmpty())
        return nullptr;

    jbyteArray bytes = env->NewByteArray(static_cast<jint>(picture.size()));
    env->SetByteArrayRegion(
            bytes,
            0,
            static_cast<jint>(picture.size()),
            reinterpret_cast<const jbyte *>(picture.data())
    );
    return bytes;
}

extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_kyant_tag_Metadata_00024Companion_getFdPicture(JNIEnv *env,
                                                        jobject /* this */,
                                                        jint fd) {
    auto picture = get_picture(dup(fd));
    if (picture.isEmpty())
        return nullptr;

    jbyteArray bytes = env->NewByteArray(static_cast<jint>(picture.size()));
    env->SetByteArrayRegion(
            bytes,
            0,
            static_cast<jint>(picture.size()),
            reinterpret_cast<const jbyte *>(picture.data())
    );
    return bytes;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_kyant_tag_Metadata_00024Companion_getLyrics(JNIEnv *env,
                                                     jobject /* this */,
                                                     jstring path) {
    auto lyrics = get_lyrics(env->GetStringUTFChars(path, nullptr));
    if (lyrics.empty())
        return nullptr;

    return env->NewStringUTF(lyrics.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_kyant_tag_Metadata_00024Companion_getFdLyrics(JNIEnv *env,
                                                       jobject /* this */,
                                                       jint fd) {
    auto lyrics = get_lyrics(dup(fd));
    if (lyrics.empty())
        return nullptr;

    return env->NewStringUTF(lyrics.c_str());
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_kyant_tag_Metadata_00024Companion_saveLyrics(JNIEnv *env,
                                                      jobject /* this */,
                                                      jstring path,
                                                      jstring lyrics) {
    return save_lyrics(
            env->GetStringUTFChars(path, nullptr),
            env->GetStringUTFChars(lyrics, nullptr)
    );
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_kyant_tag_Metadata_00024Companion_saveFdLyrics(JNIEnv *env,
                                                        jobject /* this */,
                                                        jint fd,
                                                        jstring lyrics) {
    return save_lyrics(
            dup(fd),
            env->GetStringUTFChars(lyrics, nullptr)
    );
}

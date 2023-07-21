#include <filesystem>
#include <jni.h>
#include <sys/stat.h>
#include "fileref.h"
#include "tfilestream.h"
#include "fd.h"
#include "picture.h"
#include "lyrics.h"
#include "save_lyrics.h"

jmethodID tagConstructor = nullptr;

extern "C"
JNIEXPORT jobject JNICALL Java_com_kyant_tag_Tag_00024Companion_getTag(JNIEnv *env, jobject /* this */, jstring path) {
    try {
        jclass tagClass = env->FindClass("com/kyant/tag/Tag");

        if (tagConstructor == nullptr)
            tagConstructor = env->GetMethodID(
                    tagClass,
                    "<init>",
                    "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IIIJIIILjava/lang/String;JJ)V"
            );

        const char *pathStr = env->GetStringUTFChars(path, nullptr);
        TagLib::FileRef f(pathStr, true, TagLib::AudioProperties::Fast);
        auto properties = f.audioProperties();
        auto tag = f.tag();

        if (!f.isNull() && properties && tag) {
            std::__fs::filesystem::path filePath(pathStr);
            auto fileSize = static_cast<jlong>(std::__fs::filesystem::file_size(filePath));
            auto lastWriteTime = std::__fs::filesystem::last_write_time(filePath);
            auto timePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                    lastWriteTime - std::__fs::filesystem::file_time_type::clock::now() +
                    std::chrono::system_clock::now());
            auto lastWriteTimeT = std::chrono::system_clock::to_time_t(timePoint) * 1000;

            jlong length = static_cast<jint>(properties->lengthInMilliseconds());
            jint bitrate = static_cast<jint>(properties->bitrate());
            jint sampleRate = static_cast<jint>(properties->sampleRate());
            jint channels = static_cast<jint>(properties->channels());

            jstring title = env->NewStringUTF(tag->title().toCString(true));
            jstring artist = env->NewStringUTF(tag->artist().toCString(true));
            jstring album = env->NewStringUTF(tag->album().toCString(true));
            jstring albumArtist = env->NewStringUTF(tag->albumArtist().toCString(true));
            jstring comment = env->NewStringUTF(tag->comment().toCString(true));
            jstring genre = env->NewStringUTF(tag->genre().toCString(true));
            jint year = static_cast<jint>(tag->year());
            jint disc = static_cast<jint>(tag->disc());
            jint track = static_cast<jint>(tag->track());

            jobject tagObj = env->NewObject(
                    tagClass, tagConstructor, title, artist, album, albumArtist, comment, genre, year, disc, track,
                    length, bitrate, sampleRate, channels, path, fileSize, lastWriteTimeT
            );
            return tagObj;
        }
        return nullptr;
    } catch (...) {
        return nullptr;
    }
}

extern "C"
JNIEXPORT jobject JNICALL Java_com_kyant_tag_Tag_00024Companion_getFdTag(JNIEnv *env, jobject /* this */, jint fd) {
    try {
        UniqueFileDescriptor uniqueFd(dup(fd));

        jclass tagClass = env->FindClass("com/kyant/tag/Tag");

        if (tagConstructor == nullptr)
            tagConstructor = env->GetMethodID(
                    tagClass,
                    "<init>",
                    "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IIIJIIILjava/lang/String;JJ)V"
            );

        TagLib::FileStream stream(uniqueFd.get(), true);
        TagLib::FileRef f(&stream, true, TagLib::AudioProperties::Fast);
        auto properties = f.audioProperties();
        auto tag = f.tag();

        if (!f.isNull() && properties && tag) {
            jstring path = env->NewStringUTF(getFilePathFromFd(uniqueFd.get()).c_str());
            struct stat s{};
            fstat(uniqueFd.get(), &s);
            auto fileSize = static_cast<jlong>(s.st_size);
            auto lastWriteTime = s.st_mtime;
            auto lastWriteTimeT = static_cast<jlong>(lastWriteTime) * 1000;

            jlong length = static_cast<jint>(properties->lengthInMilliseconds());
            jint bitrate = static_cast<jint>(properties->bitrate());
            jint sampleRate = static_cast<jint>(properties->sampleRate());
            jint channels = static_cast<jint>(properties->channels());

            jstring title = env->NewStringUTF(tag->title().toCString(true));
            jstring artist = env->NewStringUTF(tag->artist().toCString(true));
            jstring album = env->NewStringUTF(tag->album().toCString(true));
            jstring albumArtist = env->NewStringUTF(tag->albumArtist().toCString(true));
            jstring comment = env->NewStringUTF(tag->comment().toCString(true));
            jstring genre = env->NewStringUTF(tag->genre().toCString(true));
            jint year = static_cast<jint>(tag->year());
            jint disc = static_cast<jint>(tag->disc());
            jint track = static_cast<jint>(tag->track());

            jobject tagObj = env->NewObject(
                    tagClass, tagConstructor, title, artist, album, albumArtist, comment, genre, year, disc, track,
                    length, bitrate, sampleRate, channels, path, fileSize, lastWriteTimeT
            );
            return tagObj;
        }
        return nullptr;
    } catch (...) {
        return nullptr;
    }
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_kyant_tag_Tag_save(JNIEnv *env, jobject tagObj) {
    try {
        jclass tagClass = env->GetObjectClass(tagObj);
        if (tagClass == nullptr)
            return false;

        jfieldID pathField = env->GetFieldID(tagClass, "path", "Ljava/lang/String;");
        if (pathField == nullptr)
            return false;
        auto path = static_cast<jstring>(env->GetObjectField(tagObj, pathField));
        auto pathStr = env->GetStringUTFChars(path, nullptr);

        TagLib::FileRef f(pathStr, false);
        auto tag = f.tag();

        if (!f.isNull() && tag) {
            jfieldID titleField = env->GetFieldID(tagClass, "title", "Ljava/lang/String;");
            auto title = static_cast<jstring>(env->GetObjectField(tagObj, titleField));
            tag->setTitle(TagLib::String(env->GetStringUTFChars(title, nullptr), TagLib::String::UTF8));

            jfieldID artistField = env->GetFieldID(tagClass, "artist", "Ljava/lang/String;");
            auto artist = static_cast<jstring>(env->GetObjectField(tagObj, artistField));
            tag->setArtist(TagLib::String(env->GetStringUTFChars(artist, nullptr), TagLib::String::UTF8));

            jfieldID albumField = env->GetFieldID(tagClass, "album", "Ljava/lang/String;");
            auto album = static_cast<jstring>(env->GetObjectField(tagObj, albumField));
            tag->setAlbum(TagLib::String(env->GetStringUTFChars(album, nullptr), TagLib::String::UTF8));

            jfieldID albumArtistField = env->GetFieldID(tagClass, "albumArtist", "Ljava/lang/String;");
            auto albumArtist = static_cast<jstring>(env->GetObjectField(tagObj, albumArtistField));
            tag->setAlbumArtist(TagLib::String(env->GetStringUTFChars(albumArtist, nullptr), TagLib::String::UTF8));

            jfieldID commentField = env->GetFieldID(tagClass, "comment", "Ljava/lang/String;");
            auto comment = static_cast<jstring>(env->GetObjectField(tagObj, commentField));
            tag->setComment(TagLib::String(env->GetStringUTFChars(comment, nullptr), TagLib::String::UTF8));

            jfieldID genreField = env->GetFieldID(tagClass, "genre", "Ljava/lang/String;");
            auto genre = static_cast<jstring>(env->GetObjectField(tagObj, genreField));
            tag->setGenre(env->GetStringUTFChars(genre, nullptr));

            jfieldID yearField = env->GetFieldID(tagClass, "year", "I");
            auto year = static_cast<jint>(env->GetIntField(tagObj, yearField));
            tag->setYear(static_cast<unsigned int>(year));

            jfieldID discField = env->GetFieldID(tagClass, "disc", "I");
            auto disc = static_cast<jint>(env->GetIntField(tagObj, discField));
            tag->setDisc(static_cast<unsigned int>(disc));

            jfieldID trackField = env->GetFieldID(tagClass, "track", "I");
            auto track = static_cast<jint>(env->GetIntField(tagObj, trackField));
            tag->setTrack(static_cast<unsigned int>(track));

            return f.save();
        }
        return false;
    } catch (...) {
        return false;
    }
}

extern "C" JNIEXPORT jbyteArray JNICALL
Java_com_kyant_tag_Tag_00024Companion_getPicture(JNIEnv *env,
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
Java_com_kyant_tag_Tag_00024Companion_getFdPicture(JNIEnv *env,
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
Java_com_kyant_tag_Tag_00024Companion_getLyrics(JNIEnv *env,
                                                jobject /* this */,
                                                jstring path) {
    auto lyrics = get_lyrics(env->GetStringUTFChars(path, nullptr));
    if (lyrics.empty())
        return nullptr;

    return env->NewStringUTF(lyrics.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_kyant_tag_Tag_00024Companion_getFdLyrics(JNIEnv *env,
                                                  jobject /* this */,
                                                  jint fd) {
    auto lyrics = get_lyrics(dup(fd));
    if (lyrics.empty())
        return nullptr;

    return env->NewStringUTF(lyrics.c_str());
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_kyant_tag_Tag_00024Companion_saveLyrics(JNIEnv *env,
                                                 jobject /* this */,
                                                 jstring path,
                                                 jstring lyrics) {
    return save_lyrics(
            env->GetStringUTFChars(path, nullptr),
            env->GetStringUTFChars(lyrics, nullptr)
    );
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_kyant_tag_Tag_00024Companion_saveFdLyrics(JNIEnv *env,
                                                   jobject /* this */,
                                                   jint fd,
                                                   jstring lyrics) {
    return save_lyrics(
            dup(fd),
            env->GetStringUTFChars(lyrics, nullptr)
    );
}

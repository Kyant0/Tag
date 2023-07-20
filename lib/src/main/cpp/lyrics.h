#ifndef TAG_LYRICS_H
#define TAG_LYRICS_H

#include <string>
#include "apefile.h"
#include "apetag.h"
#include "asffile.h"
#include "flacfile.h"
#include "itfile.h"
#include "modfile.h"
#include "mp4file.h"
#include "mpcfile.h"
#include "unsynchronizedlyricsframe.h"
#include "mpegfile.h"
#include "opusfile.h"
#include "speexfile.h"
#include "vorbisfile.h"
#include "xiphcomment.h"
#include "aifffile.h"
#include "wavfile.h"
#include "s3mfile.h"
#include "tbytevector.h"
#include "trueaudiofile.h"
#include "wavpackfile.h"
#include "xmfile.h"
#include "dsffile.h"
#include "dsdifffile.h"

std::string id3v2_lyrics(TagLib::Tag *tag) {
    auto id3v2Tag = dynamic_cast<TagLib::ID3v2::Tag *>(tag);
    if (id3v2Tag) {
        auto map = id3v2Tag->frameListMap();
        if (map.contains("USLT")) {
            auto *frame = static_cast<TagLib::ID3v2::UnsynchronizedLyricsFrame *>(map["USLT"].front());
            return frame->toString().toCString(true);
        }
    }
    return {};
}

std::string ape_lyrics(TagLib::Tag *tag) {
    auto apeTag = dynamic_cast<TagLib::APE::Tag *>(tag);
    if (apeTag) {
        auto map = apeTag->itemListMap();
        if (map.contains("Lyrics")) {
            return map["Lyrics"].toString().toCString(true);
        }
    }
    return {};
}

std::string asf_lyrics(TagLib::Tag *tag) {
    auto asfTag = dynamic_cast<TagLib::ASF::Tag *>(tag);
    if (asfTag) {
        auto map = asfTag->attributeListMap();
        if (map.contains("WM/Lyrics")) {
            return map["WM/Lyrics"].front().toString().toCString(true);
        }
    }
    return {};
}

std::string xiph_comment_lyrics(TagLib::Tag *tag) {
    auto xiphComment = dynamic_cast<TagLib::Ogg::XiphComment *>(tag);
    if (xiphComment) {
        auto map = xiphComment->fieldListMap();
        if (map.contains("LYRICS")) {
            return map["LYRICS"].front().toCString(true);
        }
    }
    return {};
}

std::string mp4_lyrics(TagLib::Tag *tag) {
    auto mp4Tag = dynamic_cast<TagLib::MP4::Tag *>(tag);
    if (mp4Tag) {
        auto map = mp4Tag->itemMap();
        if (map.contains("\251lyr")) {
            return map["\251lyr"].toStringList().front().toCString(true);
        }
    }
    return {};
}

std::string mod_lyrics(TagLib::Tag *tag) {
    auto modTag = dynamic_cast<TagLib::Mod::Tag *>(tag);
    if (modTag) {
        return modTag->comment().toCString(true);
    }
    return {};
}

std::string get_lyrics(const std::string &path) {
    auto ext = path.substr(path.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    auto pathStr = path.c_str();

    if (ext == "mp3") {
        TagLib::MPEG::File f(pathStr, false);
        auto lyrics = id3v2_lyrics(f.ID3v2Tag());
        if (lyrics.empty()) {
            lyrics = ape_lyrics(f.APETag());
        }
        return lyrics;
    } else if (ext == "ogg") {
        TagLib::Ogg::Vorbis::File f(pathStr, false);
        return xiph_comment_lyrics(f.tag());
    } else if (ext == "flac") {
        TagLib::FLAC::File f(pathStr, false);
        auto lyrics = xiph_comment_lyrics(f.xiphComment());
        if (lyrics.empty()) {
            lyrics = id3v2_lyrics(f.ID3v2Tag());
        }
        return lyrics;
    } else if (ext == "mpc") {
        TagLib::MPC::File f(pathStr, false);
        return ape_lyrics(f.APETag());
    } else if (ext == "wv") {
        TagLib::WavPack::File f(pathStr, false);
        return ape_lyrics(f.APETag());
    } else if (ext == "spx") {
        TagLib::Ogg::Speex::File f(pathStr, false);
        return xiph_comment_lyrics(f.tag());
    } else if (ext == "opus") {
        TagLib::Ogg::Opus::File f(pathStr, false);
        return xiph_comment_lyrics(f.tag());
    } else if (ext == "tta") {
        TagLib::TrueAudio::File f(pathStr, false);
        return id3v2_lyrics(f.tag());
    } else if (ext == "m4a" || ext == "m4r" || ext == "m4b" || ext == "m4p" || ext == "mp4" || ext == "3g2" ||
               ext == "m4v") {
        TagLib::MP4::File f(pathStr, false);
        return mp4_lyrics(f.tag());
    } else if (ext == "wma" || ext == "asf") {
        TagLib::ASF::File f(pathStr, false);
        return asf_lyrics(f.tag());
    } else if (ext == "aif" || ext == "aiff" || ext == "afc" || ext == "aifc") {
        TagLib::RIFF::AIFF::File f(pathStr, false);
        return id3v2_lyrics(f.tag());
    } else if (ext == "wav") {
        TagLib::RIFF::WAV::File f(pathStr, false);
        return id3v2_lyrics(f.tag());
    } else if (ext == "ape") {
        TagLib::APE::File f(pathStr, false);
        return ape_lyrics(f.APETag());
    } else if (ext == "mod" || ext == "module" || ext == "nst" || ext == "wow") {
        TagLib::Mod::File f(pathStr, false);
        return mod_lyrics(f.tag());
    } else if (ext == "s3m") {
        TagLib::S3M::File f(pathStr, false);
        return mod_lyrics(f.tag());
    } else if (ext == "it") {
        TagLib::IT::File f(pathStr, false);
        return mod_lyrics(f.tag());
    } else if (ext == "xm") {
        TagLib::XM::File f(pathStr, false);
        return mod_lyrics(f.tag());
    } else if (ext == "dff" || ext == "dsdiff") {
        TagLib::DSDIFF::File f(pathStr, false);
        return id3v2_lyrics(f.ID3v2Tag());
    } else if (ext == "dsf") {
        TagLib::DSF::File f(pathStr, false);
        return id3v2_lyrics(f.tag());
    }

    return {};
}

std::string get_lyrics(const int &fd) {
    auto path = getFilePathFromFd(fd);
    auto ext = path.substr(path.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    TagLib::FileStream stream(fd, true);

    if (ext == "mp3") {
        auto frameFactory = TagLib::ID3v2::FrameFactory::instance();
        TagLib::MPEG::File f(&stream, frameFactory, false);
        auto lyrics = id3v2_lyrics(f.ID3v2Tag());
        if (lyrics.empty()) {
            lyrics = ape_lyrics(f.APETag());
        }
        return lyrics;
    } else if (ext == "ogg") {
        TagLib::Ogg::Vorbis::File f(&stream, false);
        return xiph_comment_lyrics(f.tag());
    } else if (ext == "flac") {
        auto frameFactory = TagLib::ID3v2::FrameFactory::instance();
        TagLib::FLAC::File f(&stream, frameFactory, false);
        auto lyrics = xiph_comment_lyrics(f.xiphComment());
        if (lyrics.empty()) {
            lyrics = id3v2_lyrics(f.ID3v2Tag());
        }
        return lyrics;
    } else if (ext == "mpc") {
        TagLib::MPC::File f(&stream, false);
        return ape_lyrics(f.APETag());
    } else if (ext == "wv") {
        TagLib::WavPack::File f(&stream, false);
        return ape_lyrics(f.APETag());
    } else if (ext == "spx") {
        TagLib::Ogg::Speex::File f(&stream, false);
        return xiph_comment_lyrics(f.tag());
    } else if (ext == "opus") {
        TagLib::Ogg::Opus::File f(&stream, false);
        return xiph_comment_lyrics(f.tag());
    } else if (ext == "tta") {
        TagLib::TrueAudio::File f(&stream, false);
        return id3v2_lyrics(f.tag());
    } else if (ext == "m4a" || ext == "m4r" || ext == "m4b" || ext == "m4p" || ext == "mp4" || ext == "3g2" ||
               ext == "m4v") {
        TagLib::MP4::File f(&stream, false);
        return mp4_lyrics(f.tag());
    } else if (ext == "wma" || ext == "asf") {
        TagLib::ASF::File f(&stream, false);
        return asf_lyrics(f.tag());
    } else if (ext == "aif" || ext == "aiff" || ext == "afc" || ext == "aifc") {
        TagLib::RIFF::AIFF::File f(&stream, false);
        return id3v2_lyrics(f.tag());
    } else if (ext == "wav") {
        TagLib::RIFF::WAV::File f(&stream, false);
        return id3v2_lyrics(f.tag());
    } else if (ext == "ape") {
        TagLib::APE::File f(&stream, false);
        return ape_lyrics(f.APETag());
    } else if (ext == "mod" || ext == "module" || ext == "nst" || ext == "wow") {
        TagLib::Mod::File f(&stream, false);
        return mod_lyrics(f.tag());
    } else if (ext == "s3m") {
        TagLib::S3M::File f(&stream, false);
        return mod_lyrics(f.tag());
    } else if (ext == "it") {
        TagLib::IT::File f(&stream, false);
        return mod_lyrics(f.tag());
    } else if (ext == "xm") {
        TagLib::XM::File f(&stream, false);
        return mod_lyrics(f.tag());
    } else if (ext == "dff" || ext == "dsdiff") {
        TagLib::DSDIFF::File f(&stream, false);
        return id3v2_lyrics(f.ID3v2Tag());
    } else if (ext == "dsf") {
        TagLib::DSF::File f(&stream, false);
        return id3v2_lyrics(f.tag());
    }

        return {};
}

#endif //TAG_LYRICS_H

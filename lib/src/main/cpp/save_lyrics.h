#ifndef VANILLA_SAVE_LYRICS_H
#define VANILLA_SAVE_LYRICS_H

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

bool save_id3v2_lyrics(TagLib::Tag *tag, const std::string &s) {
    auto id3v2Tag = dynamic_cast<TagLib::ID3v2::Tag *>(tag);
    if (id3v2Tag) {
        if (s.empty()) {
            id3v2Tag->removeFrames("USLT");
            return true;
        }

        auto map = id3v2Tag->frameListMap();
        if (map.contains("USLT")) {
            auto frame = static_cast<TagLib::ID3v2::UnsynchronizedLyricsFrame *>(map["USLT"].front());
            frame->setText(TagLib::String(s, frame->textEncoding()));
            return true;
        }

        auto frame = new TagLib::ID3v2::UnsynchronizedLyricsFrame(TagLib::String::UTF8);
        frame->setTextEncoding(TagLib::String::UTF8);
        frame->setText(TagLib::String(s, TagLib::String::UTF8));
        id3v2Tag->addFrame(frame);
        return true;
    }
    return false;
}

bool save_xiph_comment_lyrics(TagLib::Tag *tag, const std::string &s) {
    auto xiphComment = dynamic_cast<TagLib::Ogg::XiphComment *>(tag);
    if (xiphComment) {
        if (s.empty()) {
            xiphComment->removeFields("LYRICS");
            return true;
        }

        auto map = xiphComment->fieldListMap();
        xiphComment->addField("LYRICS", TagLib::String(s, TagLib::String::UTF8), true);
        return true;
    }
    return false;
}

bool save_lyrics(const std::string &path, const std::string &s) {
    auto ext = path.substr(path.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    auto pathStr = path.c_str();

    if (ext == "mp3") {
        TagLib::MPEG::File f(pathStr, false);
        auto saved = save_id3v2_lyrics(f.ID3v2Tag(), s);
        if (saved) {
            f.save();
        }
        return saved;
    } else if (ext == "ogg") {
        TagLib::Ogg::Vorbis::File f(pathStr, false);
        auto saved = save_xiph_comment_lyrics(f.tag(), s);
        if (saved) {
            f.save();
        }
        return saved;
    } else if (ext == "flac") {
        TagLib::FLAC::File f(pathStr, false);
        auto saved = save_xiph_comment_lyrics(f.xiphComment(), s);
        if (!saved) {
            saved = save_id3v2_lyrics(f.ID3v2Tag(), s);
        }
        if (saved) {
            f.save();
        }
        return saved;
    }

    return false;
}

bool save_lyrics(const int &fd, const std::string &s) {
    auto path = getFilePathFromFd(fd);
    auto ext = path.substr(path.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    TagLib::FileStream stream(fd, true);

    if (ext == "mp3") {
        auto frameFactory = TagLib::ID3v2::FrameFactory::instance();
        TagLib::MPEG::File f(&stream, frameFactory, false);
        auto saved = save_id3v2_lyrics(f.ID3v2Tag(), s);
        if (saved) {
            f.save();
        }
        return saved;
    } else if (ext == "ogg") {
        TagLib::Ogg::Vorbis::File f(&stream, false);
        auto saved = save_xiph_comment_lyrics(f.tag(), s);
        if (saved) {
            f.save();
        }
        return saved;
    } else if (ext == "flac") {
        auto frameFactory = TagLib::ID3v2::FrameFactory::instance();
        TagLib::FLAC::File f(&stream, frameFactory, false);
        auto saved = save_xiph_comment_lyrics(f.xiphComment(), s);
        if (!saved) {
            saved = save_id3v2_lyrics(f.ID3v2Tag(), s);
        }
        if (saved) {
            f.save();
        }
        return saved;
    }

    return false;
}

#endif //VANILLA_SAVE_LYRICS_H

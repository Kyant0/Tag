#ifndef TAG_PICTURE_H
#define TAG_PICTURE_H

#include <string>
#include "apefile.h"
#include "apetag.h"
#include "asffile.h"
#include "flacfile.h"
#include "itfile.h"
#include "modfile.h"
#include "mp4file.h"
#include "mpcfile.h"
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

TagLib::ByteVector id3v2_picture(TagLib::Tag *tag) {
    auto id3v2Tag = dynamic_cast<TagLib::ID3v2::Tag *>(tag);
    if (id3v2Tag) {
        auto frameList = id3v2Tag->frameListMap()["APIC"];
        if (!frameList.isEmpty()) {
            auto *pictureFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frameList.front());
            return pictureFrame->picture();
        }
    }
    return {};
}

TagLib::ByteVector ape_picture(TagLib::Tag *tag) {
    auto apeTag = dynamic_cast<TagLib::APE::Tag *>(tag);
    if (apeTag) {
        auto itemListMap = apeTag->itemListMap();
        auto it = itemListMap.find("COVER ART (FRONT)");
        if (it != itemListMap.end()) {
            return it->second.binaryData();
        }
    }
    return {};
}

TagLib::ByteVector asf_picture(TagLib::Tag *tag) {
    auto asfTag = dynamic_cast<TagLib::ASF::Tag *>(tag);
    if (asfTag) {
        auto attributeListMap = asfTag->attributeListMap();
        auto it = attributeListMap.find("WM/Picture");
        if (it != attributeListMap.end()) {
            auto attributeList = it->second;
            if (!attributeList.isEmpty()) {
                return attributeList.front().toPicture().picture();
            }
        }
    }
    return {};
}

TagLib::ByteVector xiph_comment_picture(TagLib::Tag *tag) {
    auto xiphComment = dynamic_cast<TagLib::Ogg::XiphComment *>(tag);
    if (xiphComment) {
        const auto &pictureList = xiphComment->pictureList();
        if (!pictureList.isEmpty()) {
            return pictureList.front()->data();
        }
    }
    return {};
}

TagLib::ByteVector mp4_picture(TagLib::Tag *tag) {
    auto mp4Tag = dynamic_cast<TagLib::MP4::Tag *>(tag);
    if (mp4Tag) {
        auto itemMap = mp4Tag->itemMap();
        auto it = itemMap.find("covr");
        if (it != itemMap.end()) {
            auto coverArtList = it->second.toCoverArtList();
            if (!coverArtList.isEmpty()) {
                return coverArtList.front().data();
            }
        }
    }
    return {};
}

TagLib::ByteVector mod_picture() {
    return {};
}

TagLib::ByteVector get_picture(const std::string &path) {
    auto ext = path.substr(path.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    auto pathStr = path.c_str();

    if (ext == "mp3") {
        TagLib::MPEG::File f(pathStr, false);
        auto picture = id3v2_picture(f.ID3v2Tag());
        if (picture.isEmpty()) {
            picture = ape_picture(f.APETag());
        }
        return picture;
    } else if (ext == "ogg") {
        TagLib::Ogg::Vorbis::File f(pathStr, false);
        return xiph_comment_picture(f.tag());
    } else if (ext == "flac") {
        TagLib::FLAC::File f(pathStr, false);
        auto pictureList = f.pictureList();
        if (!pictureList.isEmpty()) {
            return pictureList.front()->data();
        }
        auto picture = xiph_comment_picture(f.xiphComment());
        if (picture.isEmpty()) {
            picture = id3v2_picture(f.ID3v2Tag());
        }
        return picture;
    } else if (ext == "mpc") {
        TagLib::MPC::File f(pathStr, false);
        return ape_picture(f.APETag());
    } else if (ext == "wv") {
        TagLib::WavPack::File f(pathStr, false);
        return ape_picture(f.APETag());
    } else if (ext == "spx") {
        TagLib::Ogg::Speex::File f(pathStr, false);
        return xiph_comment_picture(f.tag());
    } else if (ext == "opus") {
        TagLib::Ogg::Opus::File f(pathStr, false);
        return xiph_comment_picture(f.tag());
    } else if (ext == "tta") {
        TagLib::TrueAudio::File f(pathStr, false);
        return id3v2_picture(f.tag());
    } else if (ext == "m4a" || ext == "m4r" || ext == "m4b" || ext == "m4p" || ext == "mp4" || ext == "3g2" ||
               ext == "m4v") {
        TagLib::MP4::File f(pathStr, false);
        return mp4_picture(f.tag());
    } else if (ext == "wma" || ext == "asf") {
        TagLib::ASF::File f(pathStr, false);
        return asf_picture(f.tag());
    } else if (ext == "aif" || ext == "aiff" || ext == "afc" || ext == "aifc") {
        TagLib::RIFF::AIFF::File f(pathStr, false);
        return id3v2_picture(f.tag());
    } else if (ext == "wav") {
        TagLib::RIFF::WAV::File f(pathStr, false);
        return id3v2_picture(f.tag());
    } else if (ext == "ape") {
        TagLib::APE::File f(pathStr, false);
        return ape_picture(f.APETag());
    } else if (ext == "mod" || ext == "module" || ext == "nst" || ext == "wow") {
        return mod_picture();
    } else if (ext == "s3m") {
        return mod_picture();
    } else if (ext == "it") {
        return mod_picture();
    } else if (ext == "xm") {
        return mod_picture();
    } else if (ext == "dff" || ext == "dsdiff") {
        TagLib::DSDIFF::File f(pathStr, false);
        return id3v2_picture(f.ID3v2Tag());
    } else if (ext == "dsf") {
        TagLib::DSF::File f(pathStr, false);
        return id3v2_picture(f.tag());
    }

    return {};
}

TagLib::ByteVector get_picture(const int &fd) {
    auto path = getFilePathFromFd(fd);
    auto ext = path.substr(path.find_last_of(".") + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    TagLib::FileStream stream(fd, true);

    if (ext == "mp3") {
        auto frameFactory = TagLib::ID3v2::FrameFactory::instance();
        TagLib::MPEG::File f(&stream, frameFactory, false);
        auto picture = id3v2_picture(f.ID3v2Tag());
        if (picture.isEmpty()) {
            picture = ape_picture(f.APETag());
        }
        return picture;
    } else if (ext == "ogg") {
        TagLib::Ogg::Vorbis::File f(&stream, false);
        return xiph_comment_picture(f.tag());
    } else if (ext == "flac") {
        auto frameFactory = TagLib::ID3v2::FrameFactory::instance();
        TagLib::FLAC::File f(&stream, frameFactory, false);
        auto pictureList = f.pictureList();
        if (!pictureList.isEmpty()) {
            return pictureList.front()->data();
        }
        auto picture = xiph_comment_picture(f.xiphComment());
        if (picture.isEmpty()) {
            picture = id3v2_picture(f.ID3v2Tag());
        }
        return picture;
    } else if (ext == "mpc") {
        TagLib::MPC::File f(&stream, false);
        return ape_picture(f.APETag());
    } else if (ext == "wv") {
        TagLib::WavPack::File f(&stream, false);
        return ape_picture(f.APETag());
    } else if (ext == "spx") {
        TagLib::Ogg::Speex::File f(&stream, false);
        return xiph_comment_picture(f.tag());
    } else if (ext == "opus") {
        TagLib::Ogg::Opus::File f(&stream, false);
        return xiph_comment_picture(f.tag());
    } else if (ext == "tta") {
        TagLib::TrueAudio::File f(&stream, false);
        return id3v2_picture(f.tag());
    } else if (ext == "m4a" || ext == "m4r" || ext == "m4b" || ext == "m4p" || ext == "mp4" || ext == "3g2" ||
               ext == "m4v") {
        TagLib::MP4::File f(&stream, false);
        return mp4_picture(f.tag());
    } else if (ext == "wma" || ext == "asf") {
        TagLib::ASF::File f(&stream, false);
        return asf_picture(f.tag());
    } else if (ext == "aif" || ext == "aiff" || ext == "afc" || ext == "aifc") {
        TagLib::RIFF::AIFF::File f(&stream, false);
        return id3v2_picture(f.tag());
    } else if (ext == "wav") {
        TagLib::RIFF::WAV::File f(&stream, false);
        return id3v2_picture(f.tag());
    } else if (ext == "ape") {
        TagLib::APE::File f(&stream, false);
        return ape_picture(f.APETag());
    } else if (ext == "mod" || ext == "module" || ext == "nst" || ext == "wow") {
        return mod_picture();
    } else if (ext == "s3m") {
        return mod_picture();
    } else if (ext == "it") {
        return mod_picture();
    } else if (ext == "xm") {
        return mod_picture();
    } else if (ext == "dff" || ext == "dsdiff") {
        TagLib::DSDIFF::File f(&stream, false);
        return id3v2_picture(f.ID3v2Tag());
    } else if (ext == "dsf") {
        TagLib::DSF::File f(&stream, false);
        return id3v2_picture(f.tag());
    }

    return {};
}

#endif //TAG_PICTURE_H

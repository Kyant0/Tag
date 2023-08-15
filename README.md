# Tag

You can read and edit the metadata from a audio file with this library.

The library is based on [the forked version](https://github.com/Kyant0/taglib) of [TagLib](https://taglib.org/).

**Official supported extensions:**
mp3, ogg, flac, mpc, wv, spx, opus, tta, m4a, m4r, m4b, m4p, mp4, 3g2, m4v, wma, asf, aif, aiff, afc, aifc, wav, ape,
mod, module, nst, wow, s3m, it, xm

**Extra supported extensions:**
dff, dsdiff, dsf

## Add to project

[![JitPack Release](https://jitpack.io/v/Kyant0/Tag.svg)](https://jitpack.io/#Kyant0/Tag)

```kotlin
allprojects {
    repositories {
        maven("https://jitpack.io")
    }
}

implementation("com.github.Kyant0:Tag:2023.8.1")
```

## Usage

### Metadata

`Metadata` contains the audio properties and property map (original metadata).

Call `Metadata.getMetadata(path)` to get the metadata of a file.

Unfortunately, you can't edit the metadata of a file yet.

### AudioProperties & Tags

`AudioProperties` holds the audio properties and `Tags` holds the property map (metadata).

To convert from `Metadata` to `AudioProperties`, call `metadata.toAudioProperties()`.

To convert from `Metadata` to `Tags`, call `metadata.toTags()`.

### Album art

**read:** `Metadata.getPicture(path: String)`

**edit:** **TODO**

### Lyrics

**read:** `Metadata.getLyrics(path: String)`

**edit:** `Metadata.saveLyrics(path: String, lyrics: String)` // Only works for mp3, ogg and flac files for now

**remove:** `Metadata.saveLyrics(path: String, lyrics = "")`

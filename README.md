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

implementation("com.github.Kyant0:Tag:2023.7.5")
```

## Usage

### Tag

**read:** `Tag.getTag(path: String)`

**edit:** `tag.save()`

**Supported fields:**

**Tags:** title, artist, album, albumArtist, comment, genre, year, disc, track

**Properties:** duration, bitrate, sampleRate, channels

**File info:** path, size, lastModified

**Planned fields:**

`replayGain`s

### Album art

**read:** `Tag.getPicture(path: String)`

**edit:** **TODO**

### Lyrics

**read:** `Tag.getLyrics(path: String)`

**edit:** `Tag.saveLyrics(path: String, lyrics: String)` (only works for mp3, ogg and flac files for now)

**remove:** `Tag.saveLyrics(path: String, lyrics = "")`

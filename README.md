# Tag

You can get and edit the metadata from a audio file with this library.

The library is using [the forked version](https://github.com/Kyant0/taglib) of [TagLib](https://taglib.org/).

**Supported extensions:**
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

implementation("com.github.Kyant0:Tag:2023.7.3")
```

## Usage

### Tag

**get:** `Tag.getTag(path: String)`

**save:** `tag.save()`

**Supported fields:**

```kotlin
data class Tag(
    val title: String,
    val artist: String,
    val album: String,
    val comment: String,
    val genre: String,
    val year: Int,
    val track: Int,
    val duration: Long,
    val bitrate: Int,
    val sampleRate: Int,
    val channels: Int,
    val path: String,
    val size: Long,
    val modifiedTime: Long
)
```

**TODO:** We will support more fields in the future, such as `albumArtist`, `disc` and `replayGain`s.

### Album art

**get:** `Tag.getPicture(path: String)`

**save:** **TODO**

### Lyrics

**get:** `Tag.getLyrics(path: String)`

**save:** `Tag.saveLyrics(path: String, lyrics: String)` (only works for mp3, ogg and flac files for now)

**remove:** `Tag.saveLyrics(path: String, lyrics = "")`

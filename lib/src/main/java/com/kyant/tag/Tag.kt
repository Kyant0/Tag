package com.kyant.tag

import android.content.ContentResolver
import android.net.Uri

@Suppress("unused")
data class Tag(
    // tags
    val title: String = "",
    val artist: String = "",
    val album: String = "",
    val albumArtist: String = "",
    val comment: String = "",
    val genre: String = "",
    val year: Int = 0,
    val disc: Int = 0,
    val track: Int = 0,
    // properties
    val duration: Long = 0,
    val bitrate: Int = 0,
    val sampleRate: Int = 0,
    val channels: Int = 0,
    // file info
    val path: String = "",
    val size: Long = 0,
    val lastModified: Long = 0
) {
    fun isEmpty(): Boolean = this == Empty

    fun isTagEmpty(): Boolean = title.isEmpty() &&
        artist.isEmpty() &&
        album.isEmpty() &&
        albumArtist.isEmpty() &&
        comment.isEmpty() &&
        genre.isEmpty() &&
        year == 0 &&
        disc == 0 &&
        track == 0

    external fun save(): Boolean

    companion object {
        val Empty = Tag()

        external fun getTag(path: String): Tag?

        private external fun getFdTag(fd: Int): Tag?

        external fun getPicture(path: String): ByteArray?

        private external fun getFdPicture(fd: Int): ByteArray?

        external fun getLyrics(path: String): String?

        private external fun getFdLyrics(fd: Int): String?

        external fun saveLyrics(path: String, lyrics: String): Boolean

        private external fun saveFdLyrics(fd: Int, lyrics: String): Boolean

        fun getTag(contentResolver: ContentResolver, uri: Uri): Tag? =
            contentResolver.openFileDescriptor(uri, "r")?.use {
                getFdTag(it.fd)
            }

        fun getPicture(contentResolver: ContentResolver, uri: Uri): ByteArray? =
            contentResolver.openFileDescriptor(uri, "r")?.use {
                getFdPicture(it.fd)
            }

        fun getLyrics(contentResolver: ContentResolver, uri: Uri): String? =
            contentResolver.openFileDescriptor(uri, "r")?.use {
                getFdLyrics(it.fd)
            }

        fun saveLyrics(contentResolver: ContentResolver, uri: Uri, lyrics: String): Boolean =
            contentResolver.openFileDescriptor(uri, "rw")?.use {
                saveFdLyrics(it.fd, lyrics)
            } ?: false

        init {
            System.loadLibrary("tag2")
        }
    }
}

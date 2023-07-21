package com.kyant.tag

import android.content.ContentResolver
import android.net.Uri

data class Tag(
    val title: String,
    val artist: String,
    val album: String,
    val albumArtist: String,
    val comment: String,
    val genre: String,
    val year: Int,
    val disc: Int,
    val track: Int,
    val duration: Long,
    val bitrate: Int,
    val sampleRate: Int,
    val channels: Int,
    val path: String,
    val size: Long,
    val modifiedTime: Long
) {
    external fun save(): Boolean

    companion object {
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

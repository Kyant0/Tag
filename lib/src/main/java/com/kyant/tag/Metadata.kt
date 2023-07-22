package com.kyant.tag

import android.content.ContentResolver
import android.net.Uri

data class Metadata(
    val lengthInMilliseconds: Long = 0,
    val bitrate: Int = 0,
    val sampleRate: Int = 0,
    val channels: Int = 0,
    val properties: Map<String, Array<String>> = emptyMap()
) {
    companion object {
        external fun getMetadata(path: String): Metadata?

        private external fun getFdMetadata(fd: Int): Metadata?

        external fun getPicture(path: String): ByteArray?

        private external fun getFdPicture(fd: Int): ByteArray?

        external fun getLyrics(path: String): String?

        private external fun getFdLyrics(fd: Int): String?

        external fun saveLyrics(path: String, lyrics: String): Boolean

        private external fun saveFdLyrics(fd: Int, lyrics: String): Boolean

        fun getMetadata(contentResolver: ContentResolver, uri: Uri): Metadata? =
            contentResolver.openFileDescriptor(uri, "r")?.use {
                getFdMetadata(it.fd)
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

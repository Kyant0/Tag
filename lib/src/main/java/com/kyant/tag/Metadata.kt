package com.kyant.tag

data class Metadata(
    val lengthInMilliseconds: Long = 0,
    val bitrate: Int = 0,
    val sampleRate: Int = 0,
    val channels: Int = 0,
    val properties: Map<String, Array<String>> = emptyMap()
) {
    companion object {
        external fun getMetadata(path: String): Metadata?

        external fun getPicture(path: String): ByteArray?

        external fun getLyrics(path: String): String?

        external fun saveLyrics(path: String, lyrics: String): Boolean

        init {
            System.loadLibrary("tag2")
        }
    }
}

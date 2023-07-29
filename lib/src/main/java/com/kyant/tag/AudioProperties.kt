package com.kyant.tag

import kotlinx.serialization.Serializable

@Serializable
data class AudioProperties(
    val lengthInMilliseconds: Long = 0,
    val bitrate: Int = 0,
    val sampleRate: Int = 0,
    val channels: Int = 0
) : java.io.Serializable {
    companion object {
        fun Metadata.toAudioProperties(): AudioProperties = AudioProperties(
            lengthInMilliseconds,
            bitrate,
            sampleRate,
            channels
        )
    }
}

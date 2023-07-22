package com.kyant.tag

import kotlinx.serialization.Serializable

@Serializable
data class Tags(
    // Basic tags
    val title: List<String> = emptyList(),
    val album: List<String> = emptyList(),
    val artist: List<String> = emptyList(),
    val albumArtist: List<String> = emptyList(),
    val subtitle: List<String> = emptyList(),
    val trackNumber: List<String> = emptyList(),
    val discNumber: List<String> = emptyList(),
    val date: List<String> = emptyList(),
    val originalDate: List<String> = emptyList(),
    val genre: List<String> = emptyList(),
    val comment: List<String> = emptyList(),

    // Sort names
    val titleSort: List<String> = emptyList(),
    val albumSort: List<String> = emptyList(),
    val artistSort: List<String> = emptyList(),
    val albumArtistSort: List<String> = emptyList(),
    val composerSort: List<String> = emptyList(),

    // Credits
    val composer: List<String> = emptyList(),
    val lyricist: List<String> = emptyList(),
    val conductor: List<String> = emptyList(),
    val remixer: List<String> = emptyList(),
    val performer: List<String> = emptyList(),

    // Other tags
    val isrc: List<String> = emptyList(),
    val asin: List<String> = emptyList(),
    val bpm: List<String> = emptyList(),
    val encodedBy: List<String> = emptyList(),
    val mood: List<String> = emptyList(),
    val media: List<String> = emptyList(),
    val label: List<String> = emptyList(),
    val catalogNumber: List<String> = emptyList(),
    val barcode: List<String> = emptyList(),
    val releaseCountry: List<String> = emptyList(),
    val releaseStatus: List<String> = emptyList(),
    val releaseType: List<String> = emptyList(),

    // MusicBrainz identifiers
    val musicBrainzTrackId: List<String> = emptyList(),
    val musicBrainzAlbumId: List<String> = emptyList(),
    val musicBrainzReleaseGroupId: List<String> = emptyList(),
    val musicBrainzReleaseTrackId: List<String> = emptyList(),
    val musicBrainzWorkId: List<String> = emptyList(),
    val musicBrainzArtistId: List<String> = emptyList(),
    val musicBrainzAlbumArtistId: List<String> = emptyList(),
    val acoustidId: List<String> = emptyList(),
    val acoustidFingerprint: List<String> = emptyList(),
    val musicIpPuid: List<String> = emptyList()
) {
    companion object {
        fun Metadata.toTags(): Tags = Tags(
            properties["TITLE"]?.toList() ?: emptyList(),
            properties["ALBUM"]?.toList() ?: emptyList(),
            properties["ARTIST"]?.toList() ?: emptyList(),
            properties["ALBUMARTIST"]?.toList() ?: emptyList(),
            properties["SUBTITLE"]?.toList() ?: emptyList(),
            properties["TRACKNUMBER"]?.toList() ?: emptyList(),
            properties["DISCNUMBER"]?.toList() ?: emptyList(),
            properties["DATE"]?.toList() ?: emptyList(),
            properties["ORIGINALDATE"]?.toList() ?: emptyList(),
            properties["GENRE"]?.toList() ?: emptyList(),
            properties["COMMENT"]?.toList() ?: emptyList(),
            properties["TITLESORT"]?.toList() ?: emptyList(),
            properties["ALBUMSORT"]?.toList() ?: emptyList(),
            properties["ARTISTSORT"]?.toList() ?: emptyList(),
            properties["ALBUMARTISTSORT"]?.toList() ?: emptyList(),
            properties["COMPOSERSORT"]?.toList() ?: emptyList(),
            properties["COMPOSER"]?.toList() ?: emptyList(),
            properties["LYRICIST"]?.toList() ?: emptyList(),
            properties["CONDUCTOR"]?.toList() ?: emptyList(),
            properties["REMIXER"]?.toList() ?: emptyList(),
            properties["PERFORMER"]?.toList() ?: emptyList(),
            properties["ISRC"]?.toList() ?: emptyList(),
            properties["ASIN"]?.toList() ?: emptyList(),
            properties["BPM"]?.toList() ?: emptyList(),
            properties["ENCODEDBY"]?.toList() ?: emptyList(),
            properties["MOOD"]?.toList() ?: emptyList(),
            properties["MEDIA"]?.toList() ?: emptyList(),
            properties["LABEL"]?.toList() ?: emptyList(),
            properties["CATALOGNUMBER"]?.toList() ?: emptyList(),
            properties["BARCODE"]?.toList() ?: emptyList(),
            properties["RELEASECOUNTRY"]?.toList() ?: emptyList(),
            properties["RELEASESTATUS"]?.toList() ?: emptyList(),
            properties["RELEASETYPE"]?.toList() ?: emptyList(),
            properties["MUSICBRAINZ_TRACKID"]?.toList() ?: emptyList(),
            properties["MUSICBRAINZ_ALBUMID"]?.toList() ?: emptyList(),
            properties["MUSICBRAINZ_RELEASEGROUPID"]?.toList() ?: emptyList(),
            properties["MUSICBRAINZ_RELEASETRACKID"]?.toList() ?: emptyList(),
            properties["MUSICBRAINZ_WORKID"]?.toList() ?: emptyList(),
            properties["MUSICBRAINZ_ARTISTID"]?.toList() ?: emptyList(),
            properties["MUSICBRAINZ_ALBUMARTISTID"]?.toList() ?: emptyList(),
            properties["ACOUSTID_ID"]?.toList() ?: emptyList(),
            properties["ACOUSTID_FINGERPRINT"]?.toList() ?: emptyList(),
            properties["MUSICIP_PUID"]?.toList() ?: emptyList()
        )
    }
}

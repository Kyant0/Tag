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
    val releaseType: List<String> = emptyList()
) {
    fun merge(other: Tags): Tags {
        return Metadata(properties = this.toPropertiesMap() + other.toPropertiesMap()).toTags()
    }

    override fun toString(): String {
        val data = buildString {
            if (title.isNotEmpty()) append("title=$title, ")
            if (album.isNotEmpty()) append("album=$album, ")
            if (artist.isNotEmpty()) append("artist=$artist, ")
            if (albumArtist.isNotEmpty()) append("albumArtist=$albumArtist, ")
            if (subtitle.isNotEmpty()) append("subtitle=$subtitle, ")
            if (trackNumber.isNotEmpty()) append("trackNumber=$trackNumber, ")
            if (discNumber.isNotEmpty()) append("discNumber=$discNumber, ")
            if (date.isNotEmpty()) append("date=$date, ")
            if (originalDate.isNotEmpty()) append("originalDate=$originalDate, ")
            if (genre.isNotEmpty()) append("genre=$genre, ")
            if (comment.isNotEmpty()) append("comment=$comment, ")
            if (titleSort.isNotEmpty()) append("titleSort=$titleSort, ")
            if (albumSort.isNotEmpty()) append("albumSort=$albumSort, ")
            if (artistSort.isNotEmpty()) append("artistSort=$artistSort, ")
            if (albumArtistSort.isNotEmpty()) append("albumArtistSort=$albumArtistSort, ")
            if (composerSort.isNotEmpty()) append("composerSort=$composerSort, ")
            if (composer.isNotEmpty()) append("composer=$composer, ")
            if (lyricist.isNotEmpty()) append("lyricist=$lyricist, ")
            if (conductor.isNotEmpty()) append("conductor=$conductor, ")
            if (remixer.isNotEmpty()) append("remixer=$remixer, ")
            if (performer.isNotEmpty()) append("performer=$performer, ")
            if (isrc.isNotEmpty()) append("isrc=$isrc, ")
            if (asin.isNotEmpty()) append("asin=$asin, ")
            if (bpm.isNotEmpty()) append("bpm=$bpm, ")
            if (encodedBy.isNotEmpty()) append("encodedBy=$encodedBy, ")
            if (mood.isNotEmpty()) append("mood=$mood, ")
            if (media.isNotEmpty()) append("media=$media, ")
            if (label.isNotEmpty()) append("label=$label, ")
            if (catalogNumber.isNotEmpty()) append("catalogNumber=$catalogNumber, ")
            if (barcode.isNotEmpty()) append("barcode=$barcode, ")
            if (releaseCountry.isNotEmpty()) append("releaseCountry=$releaseCountry, ")
            if (releaseStatus.isNotEmpty()) append("releaseStatus=$releaseStatus, ")
            if (releaseType.isNotEmpty()) append("releaseType=$releaseType, ")
        }.removeSuffix(", ")
        return "Tags($data)"
    }

    fun toPropertiesMap(): Map<String, Array<String>> {
        val properties = mutableMapOf<String, Array<String>>()

        properties["TITLE"] = title.toTypedArray()
        properties["ALBUM"] = album.toTypedArray()
        properties["ARTIST"] = artist.toTypedArray()
        properties["ALBUMARTIST"] = albumArtist.toTypedArray()
        properties["SUBTITLE"] = subtitle.toTypedArray()
        properties["TRACKNUMBER"] = trackNumber.toTypedArray()
        properties["DISCNUMBER"] = discNumber.toTypedArray()
        properties["DATE"] = date.toTypedArray()
        properties["ORIGINALDATE"] = originalDate.toTypedArray()
        properties["GENRE"] = genre.toTypedArray()
        properties["COMMENT"] = comment.toTypedArray()
        properties["TITLESORT"] = titleSort.toTypedArray()
        properties["ALBUMSORT"] = albumSort.toTypedArray()
        properties["ARTISTSORT"] = artistSort.toTypedArray()
        properties["ALBUMARTISTSORT"] = albumArtistSort.toTypedArray()
        properties["COMPOSERSORT"] = composerSort.toTypedArray()
        properties["COMPOSER"] = composer.toTypedArray()
        properties["LYRICIST"] = lyricist.toTypedArray()
        properties["CONDUCTOR"] = conductor.toTypedArray()
        properties["REMIXER"] = remixer.toTypedArray()
        properties["PERFORMER"] = performer.toTypedArray()
        properties["ISRC"] = isrc.toTypedArray()
        properties["ASIN"] = asin.toTypedArray()
        properties["BPM"] = bpm.toTypedArray()
        properties["ENCODEDBY"] = encodedBy.toTypedArray()
        properties["MOOD"] = mood.toTypedArray()
        properties["MEDIA"] = media.toTypedArray()
        properties["LABEL"] = label.toTypedArray()
        properties["CATALOGNUMBER"] = catalogNumber.toTypedArray()
        properties["BARCODE"] = barcode.toTypedArray()
        properties["RELEASECOUNTRY"] = releaseCountry.toTypedArray()
        properties["RELEASESTATUS"] = releaseStatus.toTypedArray()
        properties["RELEASETYPE"] = releaseType.toTypedArray()

        return properties
    }

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
            properties["RELEASETYPE"]?.toList() ?: emptyList()
        )
    }
}

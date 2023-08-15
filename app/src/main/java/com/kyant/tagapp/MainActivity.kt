package com.kyant.tagapp

import android.content.Intent
import android.os.Build
import android.os.Bundle
import android.provider.Settings
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.WindowInsets
import androidx.compose.foundation.layout.asPaddingValues
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.systemBars
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.VerticalDivider
import androidx.compose.material3.darkColorScheme
import androidx.compose.material3.lightColorScheme
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.core.view.WindowCompat
import com.kyant.tag.AudioProperties.Companion.toAudioProperties
import com.kyant.tag.Metadata
import com.kyant.tag.Tags.Companion.toTags
import java.io.File
import kotlin.streams.toList as kotlinToList

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        WindowCompat.setDecorFitsSystemWindows(window, false)

        val tags = try {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
                File("/storage/emulated/0/Music/tests/data").listFiles()
                    ?.toList()
                    ?.parallelStream()
                    ?.map { it.path to Metadata.getMetadata(it.path) }
                    ?.kotlinToList()
            } else {
                File("/storage/emulated/0/Music").listFiles()
                    ?.toList()
                    ?.map { it.path to Metadata.getMetadata(it.path) }
            }
        } catch (_: Exception) {
            null
        } ?: emptyList()

        setContent {
            MaterialTheme(colorScheme = if (isSystemInDarkTheme()) darkColorScheme() else lightColorScheme()) {
                Surface {
                    LazyColumn(contentPadding = WindowInsets.systemBars.asPaddingValues()) {
                        item {
                            Text(
                                text = "/Music/tests/data",
                                modifier = Modifier.padding(24.dp, 96.dp, 24.dp, 32.dp),
                                style = MaterialTheme.typography.headlineLarge
                            )
                        }
                        item {
                            Surface(color = MaterialTheme.colorScheme.primaryContainer) {
                                Column(
                                    modifier = Modifier
                                        .fillMaxWidth()
                                        .padding(24.dp),
                                    verticalArrangement = Arrangement.spacedBy(16.dp)
                                ) {
                                    Text(
                                        text = "Please copy https://github.com/taglib/taglib/tree/master/tests to /Music/tests manually.",
                                        style = MaterialTheme.typography.bodyMedium
                                    )
                                    Button(onClick = {
                                        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
                                            startActivity(Intent(Settings.ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION))
                                        } else {
                                            Toast.makeText(
                                                this@MainActivity,
                                                "Make sure you are using Android R+",
                                                Toast.LENGTH_SHORT
                                            ).show()
                                        }
                                    }) {
                                        Text(text = "Give access")
                                    }
                                    Text(
                                        text = "Then restart the app.",
                                        style = MaterialTheme.typography.bodyMedium
                                    )
                                }
                            }
                            Spacer(modifier = Modifier.height(8.dp))
                        }
                        items(tags) { (path, metadata) ->
                            Text(
                                text = path.substringAfterLast("/Music/tests/data/"),
                                modifier = Modifier.padding(24.dp, 8.dp),
                                style = MaterialTheme.typography.titleMedium
                            )
                            if (metadata == null) {
                                Text(
                                    text = "No metadata",
                                    modifier = Modifier.padding(horizontal = 24.dp),
                                    style = MaterialTheme.typography.bodyMedium
                                )
                                VerticalDivider(modifier = Modifier.padding(24.dp, 16.dp, 24.dp, 8.dp))
                                return@items
                            }
                            Text(
                                text = metadata.toAudioProperties().toString(),
                                modifier = Modifier.padding(horizontal = 24.dp),
                                style = MaterialTheme.typography.bodyMedium
                            )
                            VerticalDivider(modifier = Modifier.padding(24.dp, 4.dp))
                            Text(
                                text = metadata.toTags().toString(),
                                modifier = Modifier.padding(horizontal = 24.dp),
                                style = MaterialTheme.typography.bodyMedium
                            )
                            VerticalDivider(modifier = Modifier.padding(24.dp, 16.dp, 24.dp, 8.dp))
                        }
                    }
                }
            }
        }
    }
}
